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
#include <driver/sdmmc_host.h>
#include "esp_vfs_fat.h"
#include <driver/i2s_std.h>
#include <hal/spi_types.h>
#include <driver/gpio.h>
#include <driver/mcpwm_prelude.h>

#define	typeisrgbw(x)	(((x)%12)/6)
#define	typeissk6812(x)	((x)/12)
#define	typebase(x)	((x)%6)

led_strip_handle_t strip[STRIPS] = { 0 };

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

const char sd_mount[] = "/sd";
const char *play = "POWERON";

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
spk_task (void *arg)
{
   esp_err_t e = 0;
   revk_gpio_input (sdcd);
   sdmmc_slot_config_t slot = SDMMC_SLOT_CONFIG_DEFAULT ();
   slot.clk = sdclk.num;
   slot.cmd = sdcmd.num;
   slot.d0 = sddat0.num;
   slot.d1 = sddat1.set ? sddat1.num : -1;
   slot.d2 = sddat2.set ? sddat2.num : -1;
   slot.d3 = sddat3.set ? sddat3.num : -1;
   //slot.cd = sdcd.set ? sdcd.num : -1; // We do CD, and not sure how we would tell it polarity
   slot.width = (sddat2.set && sddat3.set ? 4 : sddat1.set ? 2 : 1);
   if (slot.width == 1)
      slot.flags |= SDMMC_SLOT_FLAG_INTERNAL_PULLUP;    // Old boards?
   sdmmc_host_t host = SDMMC_HOST_DEFAULT ();
   host.max_freq_khz = SDMMC_FREQ_HIGHSPEED;
   host.slot = SDMMC_HOST_SLOT_1;
   esp_vfs_fat_sdmmc_mount_config_t mount_config = {
      .format_if_mount_failed = 1,
      .max_files = 2,
      .allocation_unit_size = 16 * 1024,
      .disk_status_check_enable = 1,
   };
   sdmmc_card_t *card = NULL;
   while (1)
   {
      while (!revk_gpio_get (sdcd))
         usleep (100000);
      e = esp_vfs_fat_sdmmc_mount (sd_mount, &host, &slot, &mount_config, &card);
      if (e)
      {
         ESP_LOGE (TAG, "SD mount failed");
         sleep (10);
         continue;
      }
      ESP_LOGE (TAG, "SD mounted");
      while (revk_gpio_get (sdcd))
      {
         if (!play)
         {
            usleep (10000);
            continue;
         }
         // Find WAV file
         const char *bad = NULL;
         char *fn = NULL;
         asprintf (&fn, "%s/%s.WAV", sd_mount, play);
         int f = open (fn, O_RDONLY);
         free (fn);
         if (f < 0)
            bad = "File not found";
         uint16_t channels = 0;
         uint16_t bits = 0;
         uint32_t rate = 0;
         uint32_t size = 0;
         if (!bad)
         {
            uint8_t buf[44];
            if (read (f, buf, sizeof (buf)) != sizeof (buf))
               bad = "Header read failed";
            if (!bad && memcmp (buf + 0, "RIFF", 4))
               bad = "Not RIFF";
            if (!bad && memcmp (buf + 8, "WAVE", 4))
               bad = "Not WAVE";
            if (!bad && memcmp (buf + 12, "fmt ", 4))
               bad = "Not fmt";
            if (!bad && *(uint32_t *) (buf + 16) != 16)
               bad = "Not 16 byte header";
            if (!bad && *(uint16_t *) (buf + 20) != 1)
               bad = "Not PCM";
            channels = *(uint16_t *) (buf + 22);
            if (!bad && channels != 1 && channels != 2)
               bad = "Not mono/stereo";
            rate = *(uint32_t *) (buf + 24);
            if (!bad && rate != 8000 && rate != 16000 && rate != 32000 && rate != 44100 && rate != 48000 && rate != 88200 && rate != 96000)     // MAX98357A rates
               bad = "Unacceptable sample rate";
            bits = *(uint16_t *) (buf + 34);
            if (!bad && bits != 8 && bits != 16 && bits != 24 && bits != 32)
               bad = "Silly sample size";
            if (!bad && *(uint32_t *) (buf + 28) != rate * bits * channels / 8)
               bad = "Wrong sample bytes";
            if (!bad && memcmp (buf + 36, "data", 4))
               bad = "Not data";
            size = *(uint32_t *) (buf + 40);
         }
         if (bad)
         {
            ESP_LOGE (TAG, "Play %s:%s", play, bad);
            if (f >= 0)
               close (f);
            play = NULL;
            continue;
         }
         ESP_LOGE (TAG, "Spk init PWR %d BCLK %d DAT %d LR %d rate %lu channels %u bits %u size %lu file %s", spkpwr.num,
                   spkbclk.num, spkdata.num, spklrc.num, rate, channels, bits, size, play);
         play = NULL;           // ready for new play
         // Start speaker
         i2s_chan_handle_t spk_handle = { 0 };
         revk_gpio_output (spkpwr, 1);  // Power on
         i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG (I2S_NUM_AUTO, I2S_ROLE_MASTER);
         e = i2s_new_channel (&chan_cfg, &spk_handle, NULL);
         i2s_std_config_t cfg = {
            .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG (rate),
            .slot_cfg =
               I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG (bits == 8 ? I2S_DATA_BIT_WIDTH_8BIT : bits ==
                                                    16 ? I2S_DATA_BIT_WIDTH_16BIT : I2S_DATA_BIT_WIDTH_32BIT,
                                                    channels == 2 ? I2S_SLOT_MODE_STEREO : I2S_SLOT_MODE_MONO),
            .gpio_cfg = {
                         .mclk = I2S_GPIO_UNUSED,
                         .bclk = spkbclk.num,
                         .ws = spklrc.num,
                         .dout = spkdata.num,
                         .din = I2S_GPIO_UNUSED,
                         .invert_flags = {
                                          .mclk_inv = false,
                                          .bclk_inv = spkbclk.invert,
                                          .ws_inv = spklrc.invert,
                                          },
                         },
         };
         if (!e)
            e = i2s_channel_init_std_mode (spk_handle, &cfg);
         if (!e)
            e = i2s_channel_enable (spk_handle);
         if (!e)
         {
            // Play file until end of file, unmounted, or play set again
            uint16_t n = channels * bits * 1000 / 8;
            uint8_t *buf = malloc (n);
            while (size && !play && revk_gpio_get (sdcd))
            {
               size_t l = read (f, buf, n);
               if (l != n)
                  break;
               e = i2s_channel_write (spk_handle, buf, n, &l, 100);
               if (e)
                  break;
               size -= l;
            }
            free (buf);
         }
         close (f);
         // Power off
         revk_gpio_output (spkpwr, 0);  // Power off
         i2s_channel_disable (spk_handle);
         i2s_del_channel (spk_handle);
         sleep (1);
      }
      esp_vfs_fat_sdcard_unmount (sd_mount, card);
      sleep (1);
   }
}

void
app_main ()
{
   //ESP_LOGE (TAG, "Started");
   revk_boot (&app_callback);
   revk_start ();
   if (blink[0].set)
      revk_blink_init ();       // Library blink
   revk_gpio_input (button[0]);
   revk_gpio_input (button[1]);
   if (spklrc.set && spkbclk.set && spkdata.set && sdcmd.set)
      revk_task ("spk", spk_task, NULL, 8);
   int leds = 0;
   for (int s = 0; s < STRIPS; s++)
      if (stripgpio[s].set && stripcount[s])
      {
         leds += stripcount[s];
         ESP_LOGE (TAG, "Started using GPIO %d %s, %d LEDs", stripgpio[s].num, stripgpio[s].invert ? " (inverted)" : "",
                   stripcount[s]);
         led_strip_config_t strip_config = {
            .strip_gpio_num = stripgpio[s].num,
            .max_leds = stripcount[s],  // The number of LEDs in the strip,
            .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
            .led_model = typeissk6812 (striptype[s]) ? LED_MODEL_SK6812 : LED_MODEL_WS2812,     // LED strip model
            .flags.invert_out = stripgpio[s].invert,    // whether to invert the output signal(useful when your hardware has a level inverter)
         };
         if (typeisrgbw (striptype[s]))
            strip_config.color_component_format.format.num_components = 4;
         uint8_t t = typebase (striptype[s]);
         if (t == REVK_SETTINGS_STRIPTYPE_WS2812_RGB || t == REVK_SETTINGS_STRIPTYPE_WS2812_RBG)
            strip_config.color_component_format.format.r_pos = 0;
         if (t == REVK_SETTINGS_STRIPTYPE_WS2812_GRB || t == REVK_SETTINGS_STRIPTYPE_WS2812_BRG)
            strip_config.color_component_format.format.r_pos = 1;
         if (t == REVK_SETTINGS_STRIPTYPE_WS2812_GBR || t == REVK_SETTINGS_STRIPTYPE_WS2812_BGR)
            strip_config.color_component_format.format.r_pos = 2;
         if (t == REVK_SETTINGS_STRIPTYPE_WS2812_GBR || t == REVK_SETTINGS_STRIPTYPE_WS2812_GRB)
            strip_config.color_component_format.format.g_pos = 0;
         if (t == REVK_SETTINGS_STRIPTYPE_WS2812_RGB || t == REVK_SETTINGS_STRIPTYPE_WS2812_BGR)
            strip_config.color_component_format.format.g_pos = 1;
         if (t == REVK_SETTINGS_STRIPTYPE_WS2812_RBG || t == REVK_SETTINGS_STRIPTYPE_WS2812_BRG)
            strip_config.color_component_format.format.g_pos = 2;
         if (t == REVK_SETTINGS_STRIPTYPE_WS2812_BRG || t == REVK_SETTINGS_STRIPTYPE_WS2812_BGR)
            strip_config.color_component_format.format.b_pos = 0;
         if (t == REVK_SETTINGS_STRIPTYPE_WS2812_RBG || t == REVK_SETTINGS_STRIPTYPE_WS2812_GBR)
            strip_config.color_component_format.format.b_pos = 1;
         if (t == REVK_SETTINGS_STRIPTYPE_WS2812_RGB || t == REVK_SETTINGS_STRIPTYPE_WS2812_GRB)
            strip_config.color_component_format.format.b_pos = 2;
         led_strip_rmt_config_t rmt_config = {
            .clk_src = RMT_CLK_SRC_DEFAULT,     // different clock source can lead to different power consumption
            .resolution_hz = 10 * 1000 * 1000,  // 10 MHz
         };
#ifdef	CONFIG_IDF_TARGET_ESP32S3
         if (!s)
            rmt_config.flags.with_dma = true;   // Seems can only be one, investigate more on this
#endif
         REVK_ERR_CHECK (led_strip_new_rmt_device (&strip_config, &rmt_config, &strip[s]));
         if (strip[s])
            REVK_ERR_CHECK (led_strip_clear (strip[s]));
      }
   mcpwm_cmpr_handle_t comparator = NULL;
   if (visorpwm.set)
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
         .gen_gpio_num = visorpwm.num,
         .flags.invert_pwm = visorpwm.invert,
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

   void set_led (uint16_t led, uint8_t level, uint8_t c)
   {                            // led index from 0
      int s = 0;
      while (s < STRIPS && led >= stripcount[s])
         led -= stripcount[s++];
      if (s == STRIPS || !strip[s])
         return;
      uint8_t r = ((c & 1) ? level : 0);
      uint8_t g = ((c & 2) ? level : 0);
      uint8_t b = ((c & 4) ? level : 0);
      uint8_t w = ((c & 8) ? level : 0);
      if (typeisrgbw (striptype[s]))
         led_strip_set_pixel_rgbw (strip[s], led, gamma8[r], gamma8[g], gamma8[b], gamma8[w]);
      else
         led_strip_set_pixel (strip[s], led, gamma8[r], gamma8[g], gamma8[b]);
   }

   while (1)
   {
      usleep (25000);
      // Main button
      uint8_t push = revk_gpio_get (button[0]);
      static uint8_t push1 = 0;
      static uint8_t press1 = 0;
      if (b.init || push != b.pushed1)
      {
         if (push)
         {
            press1++;
            ESP_LOGE (TAG, "Push1 %d", press1);
         }
         push1 = 1;
         b.pushed1 = push;
         if (ledbutton1)
            set_led (ledbutton1, 255, push ? REVK_SETTINGS_LEDEYEC_RED : REVK_SETTINGS_LEDEYEC_GREEN);
      } else if (push1 && push1++ >= 10)
      {                         // Action
         push1 = 0;
         ESP_LOGE (TAG, "Pushed1 %d", press1);
         if (press1 == 1)
         {
            if (b.pwr)
               b.open ^= 1;
            else
               b.pwr = 1;
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
      push = revk_gpio_get (button[1]);
      static uint8_t push2 = 0;
      static uint8_t press2 = 0;
      if (b.init || push != b.pushed2)
      {
         if (push)
         {
            press2++;
            ESP_LOGE (TAG, "Push2 %d", press2);
         }
         push2 = 1;
         b.pushed2 = push;
         if (ledbutton2)
            set_led (ledbutton2, 255, push ? REVK_SETTINGS_LEDEYEC_RED : REVK_SETTINGS_LEDEYEC_GREEN);
      } else if (push2 && push2++ >= 10)
      {                         // Action
         push2 = 0;
         ESP_LOGE (TAG, "Pushed2 %d", press2);
         // No action for now
         press2 = 0;
      }
      if (b.connect)
      {
         b.connected = 1;
         b.connect = 0;
         revk_command ("upgrade", NULL);        // Immediate upgrade attempt
      }
      {
         int newangle = b.open ? visoropen : visorclose;
         static uint16_t angle;
         static int8_t step = 0;
         if (b.init || newangle != angle)
         {
            if (newangle > angle && step < 10)
               step++;
            else if (newangle < angle && step > -10)
               step--;
            angle += step;
            if (angle > visoropen)
               angle = visoropen;
            if (angle < visorclose)
               angle = visorclose;
            if (newangle == angle)
               step = 0;
            if (visorpwm.set)
            {                   // PWM
               REVK_ERR_CHECK (mcpwm_comparator_set_compare_value (comparator, angle_to_compare (angle)));
               ESP_LOGE (TAG, "Angle %d (%d) value %ld ", angle, step, angle_to_compare (angle));
            }
         }
      }
      if (leds)
      {
         for (int i = 0; i < leds; i++)
            set_led (i, 255, REVK_SETTINGS_LEDEYEC_BLACK);      // Clear
         if (!revk_shutting_down (NULL))
         {
            // Static LEDs
            if (ledarc && ledarcs)
               for (int i = ledarc; i < ledarc + ledarcs; i++)
                  set_led (i - 1, 255, (i & 1) ? ledarcc1 : ledarcc2);

            if (ledfixed && ledfixeds)
               for (int i = ledfixed; i < ledfixed + ledfixeds; i++)
                  set_led (i - 1, 255, ledfixedc);

            // PWM (open/closed)
            if (ledpwm)
               set_led (ledpwm - 1, 255, b.open ? REVK_SETTINGS_LEDEYEC_RED : REVK_SETTINGS_LEDEYEC_GREEN);
            // Eye 1
            if (ledeye1 && b.eyes)
               for (int i = 0; i < ledeyes; i++)
                  set_led (i + ledeye1 - 1, 255, ledeyec);
            // Eye 2
            if (ledeye2 && b.eyes)
               for (int i = 0; i < ledeyes; i++)
                  set_led (i + ledeye2 - 1, 255, ledeyec);
            if (ledpulse && ledpulses)
            {
               static uint8_t cycle = 0;
               cycle += 8;
               for (int i = ledpulse; i < ledpulse + ledpulses; i++)
                  set_led (i - 1, 64 + cos8[cycle] / 2, ledpulsec);
            }
            if (b.cylon && ledcylon && ledcylons)
            {                   // Cylon
               static int8_t cycle = 0,
                  dir = 1;
               set_led (ledcylon + cycle - 1, 255, ledcylonc);
               if (cycle == ledcylons - 1)
                  dir = -1;
               else if (!cycle)
                  dir = 1;
               cycle += dir;
            }
         }
         for (int s = 0; s < STRIPS; s++)
            if (strip[s])
               led_strip_refresh (strip[s]);
      }
      if (blink[0].set)
         revk_blink_do ();      // Library blink
      b.init = 0;
   }
}
