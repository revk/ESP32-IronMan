/* IronMan helmit app */
/* Copyright ©2024 Adrian Kennard. See LICENCE file for details .GPL 3.0 */

static const char __attribute__((unused)) TAG[] = "IronMan";

#include "revk.h"
#include "esp_system.h"
#include "esp_timer.h"
#include "esp_sleep.h"
#include "esp_task_wdt.h"
#include "esp_http_client.h"
#include "esp_http_server.h"
#include "esp_crt_bundle.h"
#include <hal/spi_types.h>
#include <driver/gpio.h>
#include <driver/mcpwm_prelude.h>

led_strip_handle_t strip = NULL;
#define SERVO_TIMEBASE_RESOLUTION_HZ 1000000    // 1MHz, 1us per tick
#define SERVO_TIMEBASE_PERIOD        20000      // 20000 ticks, 20ms
#define SERVO_MIN_PULSEWIDTH_US 1000    // Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH_US 2000    // Maximum pulse width in microsecond
#define SERVO_MAX_DEGREE        90      // Maximum angle

const uint8_t cos8[256] =
   { 255, 255, 255, 255, 255, 255, 254, 254, 253, 252, 252, 251, 250, 249, 248, 247, 246, 245, 243, 242, 240, 239, 237, 236, 234,
   232, 230, 228, 226, 224, 222, 220, 218, 216, 213, 211, 209, 206, 204, 201, 199, 196, 193, 191, 188, 185, 182, 179, 176, 174, 171,
   168, 165, 162, 159,
   156, 152, 149, 146, 143, 140, 137, 134, 131, 127, 124, 121, 118, 115, 112, 109, 106, 103, 99, 96, 93, 90, 87, 84, 81, 79, 76, 73,
   70, 67, 64, 62, 59,
   56, 54, 51, 49, 46, 44, 42, 39, 37, 35, 33, 31, 29, 27, 25, 23, 21, 19, 18, 16, 15, 13, 12, 10, 9, 8, 7, 6, 5, 4, 3, 3, 2, 1, 1,
   0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 1, 1, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 15, 16, 18, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 42, 44, 46, 49,
   51, 54, 56, 59, 62,
   64, 67, 70, 73, 76, 79, 81, 84, 87, 90, 93, 96, 99, 103, 106, 109, 112, 115, 118, 121, 124, 127, 131, 134, 137, 140, 143, 146,
   149, 152, 156, 159, 162,
   165, 168, 171, 174, 176, 179, 182, 185, 188, 191, 193, 196, 199, 201, 204, 206, 209, 211, 213, 216, 218, 220, 222, 224, 226, 228,
   230, 232, 234, 236,
   237, 239, 240, 242, 243, 245, 246, 247, 248, 249, 250, 251, 252, 252, 253, 254, 254, 255, 255, 255, 255, 255
};

struct
{
   uint8_t init:1;              // Startup
   uint8_t lowpower:1;          // WiFI off
   uint8_t eyes:1;              // Eyes on
   uint8_t pwr:1;               // Servo power on
   uint8_t open:1;              // Visor open
   uint8_t connect:1;           // WiFi connect
   uint8_t cylon:1;             // Cylon effect
   uint8_t connected:1;         // WiFi connected
   uint8_t pushed1:1;           // Pushed button1
   uint8_t pushed2:1;           // Pushed button2
} b = { 0 };

static inline uint32_t
angle_to_compare (int angle)
{
   return angle * (SERVO_MAX_PULSEWIDTH_US - SERVO_MIN_PULSEWIDTH_US) / SERVO_MAX_DEGREE + SERVO_MIN_PULSEWIDTH_US;
}

const char *
app_callback (int client, const char *prefix, const char *target, const char *suffix, jo_t j)
{
   char value[1000];
   int len = 0;
   *value = 0;
   if (j)
   {
      len = jo_strncpy (j, value, sizeof (value));
      if (len < 0)
         return "Expecting JSON string";
      if (len > sizeof (value))
         return "Too long";
   }
   if (client || !prefix || target || strcmp (prefix, topiccommand) || !suffix)
      return NULL;              //Not for us or not a command from main MQTT
   if (!strcmp (suffix, "connect"))
      b.connect = 1;
   if (!strcmp (suffix, "up"))
   {
      b.open = 1;               // Open
      b.pwr = 1;                // Power on
      return NULL;
   }
   if (!strcmp (suffix, "down"))
   {
      b.open = 0;               // Closed
      b.pwr = 1;                // Power on
      return NULL;
   }
   if (!strcmp (suffix, "cylon"))
   {
      b.eyes = 0;               // Eyes off
      b.cylon = 1;
      return NULL;
   }
   if (!strcmp (suffix, "eyes"))
   {
      b.eyes = 1;               // Eyes on
      b.cylon = 0;
      return NULL;
   }
   if (!strcmp (suffix, "dark"))
   {
      b.eyes = 0;               // Eyes off
      b.cylon = 0;
      return NULL;
   }
   return NULL;
}

void
app_main ()
{
   revk_boot (&app_callback);
   revk_start ();
   if (blink[0].num != rgb.num)
      revk_blink_init ();       // Library blink
   revk_gpio_input (button1);
   revk_gpio_input (button2);
   revk_gpio_output (eye1, 0);
   revk_gpio_output (eye2, 0);
   revk_gpio_output (pwr, 0);
   if (rgb.set && leds)
   {
      led_strip_config_t strip_config = {
         .strip_gpio_num = rgb.num,
         .max_leds = leds,      // LIGHTS, blinker, beeper, clicker, and status
#ifdef	LED_STRIP_COLOR_COMPONENT_FMT_GRB
            .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
#else
            .led_pixel_format = LED_PIXEL_FORMAT_GRB,
#endif
         .led_model = LED_MODEL_WS2812, // LED strip model
         .flags.invert_out = rgb.invert,
      };
      led_strip_rmt_config_t rmt_config = {
         .clk_src = RMT_CLK_SRC_DEFAULT,        // different clock source can lead to different power consumption
         .resolution_hz = 10 * 1000 * 1000,     // 10MHz
#ifdef  CONFIG_IDF_TARGET_ESP32S3
         .flags.with_dma = true,
#endif
      };
      REVK_ERR_CHECK (led_strip_new_rmt_device (&strip_config, &rmt_config, &strip));
   }
   mcpwm_cmpr_handle_t comparator = NULL;
   if (pwm.set)
   {
      mcpwm_timer_handle_t timer = NULL;
      mcpwm_timer_config_t timer_config = {
         .group_id = 0,
         .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
         .resolution_hz = SERVO_TIMEBASE_RESOLUTION_HZ,
         .period_ticks = SERVO_TIMEBASE_PERIOD,
         .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
      };
      ESP_ERROR_CHECK (mcpwm_new_timer (&timer_config, &timer));
      mcpwm_oper_handle_t oper = NULL;
      mcpwm_operator_config_t operator_config = {
         .group_id = 0,         // operator must be in the same group to the timer
      };
      ESP_ERROR_CHECK (mcpwm_new_operator (&operator_config, &oper));
      ESP_ERROR_CHECK (mcpwm_operator_connect_timer (oper, timer));
      mcpwm_comparator_config_t comparator_config = {
         .flags.update_cmp_on_tez = true,
      };
      ESP_ERROR_CHECK (mcpwm_new_comparator (oper, &comparator_config, &comparator));
      mcpwm_gen_handle_t generator = NULL;
      mcpwm_generator_config_t generator_config = {
         .gen_gpio_num = pwm.num,
         .flags.invert_pwm = pwm.invert,
      };
      ESP_ERROR_CHECK (mcpwm_new_generator (oper, &generator_config, &generator));
      ESP_ERROR_CHECK (mcpwm_comparator_set_compare_value (comparator, angle_to_compare (visorclose)));
      ESP_ERROR_CHECK (mcpwm_generator_set_action_on_timer_event (generator,
                                                                  MCPWM_GEN_TIMER_EVENT_ACTION (MCPWM_TIMER_DIRECTION_UP,
                                                                                                MCPWM_TIMER_EVENT_EMPTY,
                                                                                                MCPWM_GEN_ACTION_HIGH)));
      ESP_ERROR_CHECK (mcpwm_generator_set_action_on_compare_event
                       (generator, MCPWM_GEN_COMPARE_EVENT_ACTION (MCPWM_TIMER_DIRECTION_UP, comparator, MCPWM_GEN_ACTION_LOW)));
      ESP_ERROR_CHECK (mcpwm_timer_enable (timer));
      ESP_ERROR_CHECK (mcpwm_timer_start_stop (timer, MCPWM_TIMER_START_NO_STOP));
   }

   b.pwr = 1;
   b.eyes = 1;
   b.init = 1;

   while (1)
   {
      usleep (50000);
      // Main button
      uint8_t push = revk_gpio_get (button1);
      static uint8_t push1 = 0;
      static uint8_t press1 = 0;
      if (b.init || push != b.pushed1)
      {
         if (push)
            press1++;
         push1 = 1;
         b.pushed1 = push;
         if (ledbutton1 && ledbutton1 <= leds)
            revk_led (strip, ledbutton1, 255, revk_rgb (push ? 'R' : 'G'));
      } else if (push1 && push1++ >= 10)
      {                         // Action
         push1 = 0;
         if (press1 == 1)
         {
            if (b.pwr)
               b.open ^= 1;
         } else if (press1 == 2)
         {                      // off
            if (b.pwr)
               b.eyes ^= 1;     // Eyes off
            b.cylon = ~b.eyes;
         } else if (press1 == 3)
         {
            b.eyes = 0;         // Eyes off
            b.pwr = 0;          // power off
            b.cylon = 0;        // Cylon off
            revk_restart (1, "Reboot");
         }
         press1 = 0;
      }
      // Second button
      push = revk_gpio_get (button2);
      static uint8_t push2 = 0;
      static uint8_t press2 = 0;
      if (b.init || push != b.pushed2)
      {
         if (push)
            press2++;
         push2 = 1;
         b.pushed2 = push;
         if (ledbutton2 && ledbutton2 <= leds)
            revk_led (strip, ledbutton2, 255, revk_rgb (push ? 'R' : 'G'));
      } else if (push2 && push2++ >= 10)
      {                         // Action
         push2 = 0;
         // No action for now
         press2 = 0;
      }
      if (b.connect)
      {
         b.connected = 1;
         b.connect = 0;
         revk_command ("upgrade", NULL);
      }
      if (strip)
      {
         int angle = b.open ? visoropen : visorclose;
         static int wasangle = -1;
         if (b.init || angle != wasangle)
         {
            if (pwm.set)
            {                   // PWM
               REVK_ERR_CHECK (mcpwm_comparator_set_compare_value (comparator, angle_to_compare (angle)));
               ESP_LOGE (TAG, "Angle %d-%d value %ld", wasangle, angle, angle_to_compare (angle));
            }
            wasangle = angle;
         }
         for (int i = 0; i < leds; i++)
            revk_led (strip, i, 255, 0);        // Clear
         if (blink[0].num == rgb.num)
            revk_led (strip, 0, 255, revk_blinker ());
         if (!revk_shutting_down (NULL))
         {
            // Static LEDs
            if (ledarc && ledarcs && strip)
               for (int i = ledarc; i < ledarc + ledarcs; i++)
                  revk_led (strip, i - 1, (i & 1) ? 255 : 50, revk_rgb ((i & 1) ? *ledarcc1 : *ledarcc2));
            if (ledfixed && ledfixeds && strip)
               for (int i = ledfixed; i < ledfixed + ledfixeds; i++)
                  revk_led (strip, i - 1, 255, revk_rgb (*ledfixedc));

            if (ledpwm && ledpwm <= leds)
               revk_led (strip, ledpwm - 1, 255, revk_rgb (b.open ? 'G' : 'R'));
            // PWR
            revk_gpio_set (pwr, b.pwr);
            if (ledpwr && ledpwr <= leds)
               revk_led (strip, ledpwr - 1, 255, revk_rgb (b.pwr ? 'G' : 'R'));
            // Eye 1
            revk_gpio_set (eye1, b.eyes);
            if (ledeye1 && ledeye2 <= leds)
               for (int i = 0; i < ledeyes; i++)
                  revk_led (strip, i + ledeye1 - 1, 255, revk_rgb (b.eyes ? *ledeyec : 'K'));
            // Eye 2
            revk_gpio_set (eye2, b.eyes);
            if (ledeye2 && ledeye2 <= leds)
               for (int i = 0; i < ledeyes; i++)
                  revk_led (strip, i + ledeye2 - 1, 255, revk_rgb (b.eyes ? *ledeyec : 'K'));
            if (ledpulse && ledpulses && strip)
            {
               static uint8_t cycle = 0;
               cycle += 8;
               for (int i = ledpulse; i < ledpulse + ledpulses && i <= leds; i++)
                  revk_led (strip, i - 1, 64 + cos8[cycle] / 2, revk_rgb (*ledpulsec));
            }
            if (b.cylon && ledcylon && ledcylons && strip)
            {                   // Cylon
               static int8_t cycle = 0,
                  dir = 1;
               for (int i = ledcylon; i < ledcylon + ledcylons && i <= leds; i++)
                  revk_led (strip, i - 1, 255, revk_rgb (i == ledcylon + cycle ? *ledcylonc : 'K'));
               if (cycle == ledcylons - 1)
                  dir = -1;
               else if (!cycle)
                  dir = 1;
               cycle += dir;
            }
         }
         led_strip_refresh (strip);
      }
      if (blink[0].num != rgb.num)
         revk_blink_do ();      // Library blink
      b.init = 0;
   }
}
