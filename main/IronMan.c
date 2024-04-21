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

led_strip_handle_t strip = NULL;

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
   revk_gpio_output (left, 0);
   revk_gpio_output (right, 0);
   revk_gpio_output (pwr, 0);
   revk_gpio_output (pwm, 0);
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

   while (1)
      sleep (1);
}
