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
#include <math.h>

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
   while (1)
   {
      sleep (1);
   }
}
