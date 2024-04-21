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
#define SERVO_MIN_PULSEWIDTH_US 500     // Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH_US 2500    // Maximum pulse width in microsecond
#define SERVO_MIN_DEGREE        -90     // Minimum angle
#define SERVO_MAX_DEGREE        90      // Maximum angle

static inline uint32_t
angle_to_compare (int angle)
{
   return (angle - SERVO_MIN_DEGREE) * (SERVO_MAX_PULSEWIDTH_US - SERVO_MIN_PULSEWIDTH_US) / (SERVO_MAX_DEGREE - SERVO_MIN_DEGREE) +
      SERVO_MIN_PULSEWIDTH_US;
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
   if (client || !prefix || target || strcmp (prefix, prefixcommand) || !suffix)
      return NULL;              //Not for us or not a command from main MQTT
   return NULL;
}

void
app_main ()
{
   revk_boot (&app_callback);
   revk_start ();
   revk_gpio_input (button1);
   revk_gpio_input (button2);
   revk_gpio_output (left, 0);
   revk_gpio_output (right, 0);
   revk_gpio_output (pwr, 0);
   if (rgb.set && leds)
   {
      led_strip_config_t strip_config = {
         .strip_gpio_num = rgb.num,
         .max_leds = leds,      // LIGHTS, blinker, beeper, clicker, and status
         .led_pixel_format = LED_PIXEL_FORMAT_GRB,      // Pixel format of your LED strip
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
      ESP_ERROR_CHECK (mcpwm_comparator_set_compare_value (comparator, angle_to_compare (0)));
      ESP_ERROR_CHECK (mcpwm_generator_set_action_on_timer_event (generator,
                                                                  MCPWM_GEN_TIMER_EVENT_ACTION (MCPWM_TIMER_DIRECTION_UP,
                                                                                                MCPWM_TIMER_EVENT_EMPTY,
                                                                                                MCPWM_GEN_ACTION_HIGH)));
      ESP_ERROR_CHECK (mcpwm_generator_set_action_on_compare_event
                       (generator, MCPWM_GEN_COMPARE_EVENT_ACTION (MCPWM_TIMER_DIRECTION_UP, comparator, MCPWM_GEN_ACTION_LOW)));
      ESP_ERROR_CHECK (mcpwm_timer_enable (timer));
      ESP_ERROR_CHECK (mcpwm_timer_start_stop (timer, MCPWM_TIMER_START_NO_STOP));
   }

   revk_gpio_output (pwr, 1);


   while (1)
   {
      sleep (1);
      ESP_ERROR_CHECK (mcpwm_comparator_set_compare_value
                       (comparator, angle_to_compare (revk_gpio_get (button1) ? visoropen : visorclose)));
   }
}
