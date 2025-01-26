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
#include <driver/rtc_io.h>
#include <hal/spi_types.h>
#include <driver/gpio.h>
#include <driver/mcpwm_prelude.h>
#include "esp_bt.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"

#define	typeisrgbw(x)	(((x)%12)/6)
#define	typeissk6812(x)	((x)/12)
#define	typebase(x)	((x)%6)

led_strip_handle_t strip[STRIPS] = { 0 };

#define	CPS	40

#define SERVO_TIMEBASE_RESOLUTION_HZ 1000000    // 1MHz, 1us per tick
#define SERVO_TIMEBASE_PERIOD        20000      // 20000 ticks, 20ms
#define SERVO_MIN_PULSEWIDTH_US 1000    // Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH_US 2000    // Maximum pulse width in microsecond
#define SERVO_MAX_DEGREE        90      // Maximum angle
RTC_NOINIT_ATTR int16_t pwmangle;

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
   uint8_t die:1;               // Deep sleep
   uint8_t dying:1;             // Deep sleep (after sound)
   uint8_t speaker:1;           // Have speaker
   uint8_t lowpower:1;          // WiFI off
   uint8_t eyes:1;              // Eyes on
   uint8_t glove:1;             // Glove on
   uint8_t pwr:1;               // Servo power on
   uint8_t open:1;              // Visor open
   uint8_t connect:1;           // WiFi connect
   uint8_t cylon:1;             // Cylon effect
   uint8_t connected:1;         // WiFi connected
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
   //if (slot.width == 4) slot.flags |= SDMMC_SLOT_FLAG_UHS1;
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
   b.speaker = 1;
   while (!b.die)
   {
      usleep (100000);
      while (!revk_gpio_get (sdcd))
         continue;
      e = esp_vfs_fat_sdmmc_mount (sd_mount, &host, &slot, &mount_config, &card);
      if (e)
      {
         ESP_LOGE (TAG, "SD mount failed");
         if (b.dying)
            b.die = 1;
         else
            sleep (10);
         continue;
      }
      ESP_LOGE (TAG, "SD mounted");
      while (revk_gpio_get (sdcd) && !b.die)
      {
         if (!play)
         {
            if (b.dying)
               b.die = 1;
            usleep (10000);
            continue;
         }
         if (!*play)
         {
            play = NULL;
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
         {                      // Failed to play
            ESP_LOGE (TAG, "Play %s:%s", play, bad);
            if (f >= 0)
               close (f);
            play = NULL;
            if (b.dying)
               b.die = 1;
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
            while (size && !play && revk_gpio_get (sdcd) && !b.die)
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
         if (b.dying)
            b.die = 1;
      }
      esp_vfs_fat_sdcard_unmount (sd_mount, card);
      sleep (1);
   }
   vTaskDelete (NULL);
}

void
dobutton (uint8_t button, uint8_t press)
{
   ESP_LOGE (TAG, "Button%d press %d", button, press);
   switch (button)
   {
   case 0:                     // First button
      switch (ironman)
      {
      case REVK_SETTINGS_IRONMAN_HELMET:
         switch (press)
         {
         case 1:
            if (b.pwr)
               b.open ^= 1;
            break;
         case 2:
            if (b.pwr)
               b.eyes ^= 1;     // Eyes off
            b.cylon = ~b.eyes;
            break;
         }
         break;
      case REVK_SETTINGS_IRONMAN_ARCREACTOR:
         switch (press)
         {
         case 1:
            play = "SUIT1";
            break;
         case 2:
            play = "SUIT2";
            break;
         case 3:
            play = "SUIT3";
            break;
         }
         break;
      case REVK_SETTINGS_IRONMAN_GLOVE:
         switch (press)
         {
         case 1:
            b.glove = 1;
            break;
         case 2:
            break;
         }
         break;
      }
      break;
   case 1:                     // Second button
      break;
   }
}

//--------------------------------------------------------------------------------
// BLE Server

#define HRPS_HT_MEAS_MAX_LEN            (13)

#define HRPS_MANDATORY_MASK             (0x0F)
#define HRPS_BODY_SENSOR_LOC_MASK       (0x30)
#define HRPS_HR_CTNL_PT_MASK            (0xC0)

#define GATTS_TABLE_TAG "IronMan"

#define BLE_APP_ID                     0x55

#define ADV_CONFIG_FLAG                           (1 << 0)
#define SCAN_RSP_CONFIG_FLAG                      (1 << 1)

static char example_device_name[ESP_BLE_ADV_NAME_LEN_MAX] = "IronMan";
static uint8_t adv_config_done = 0;


static uint8_t manufacturer[4] = { 'R', 'e', 'v', 'K' };

static uint8_t sec_service_uuid[16] = {
   /* LSB <--------------------------------------------------------------------------------> MSB */
   //first uuid, 16bit, [12],[13] is the value
   0xfb, 0x34, 0x9b, 0x5f, 0x80, 0x00, 0x00, 0x80, 0x00, 0x10, 0x00, 0x00, 0x18, 0x0D, 0x00, 0x00,
};

// config adv data
static esp_ble_adv_data_t heart_rate_adv_config = {
   .set_scan_rsp = false,
   .include_txpower = true,
   .min_interval = 0x0006,      //slave connection min interval, Time = min_interval * 1.25 msec
   .max_interval = 0x0010,      //slave connection max interval, Time = max_interval * 1.25 msec
   .appearance = 0x00,
   .manufacturer_len = 0,       //TEST_MANUFACTURER_DATA_LEN,
   .p_manufacturer_data = NULL, //&manufacturer[0],
   .service_data_len = 0,
   .p_service_data = NULL,
   .service_uuid_len = sizeof (sec_service_uuid),
   .p_service_uuid = sec_service_uuid,
   .flag = (ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT),
};

// config scan response data
static esp_ble_adv_data_t heart_rate_scan_rsp_config = {
   .set_scan_rsp = true,
   .include_name = true,
   .manufacturer_len = sizeof (manufacturer),
   .p_manufacturer_data = manufacturer,
};

static esp_ble_adv_params_t heart_rate_adv_params = {
   .adv_int_min = 0x100,
   .adv_int_max = 0x100,
   .adv_type = ADV_TYPE_IND,
   .own_addr_type = BLE_ADDR_TYPE_RPA_PUBLIC,
   .channel_map = ADV_CHNL_ALL,
   .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

struct gatts_profile_inst
{
   esp_gatts_cb_t gatts_cb;
   uint16_t gatts_if;
   uint16_t app_id;
   uint16_t conn_id;
   uint16_t service_handle;
   esp_gatt_srvc_id_t service_id;
   uint16_t char_handle;
   esp_bt_uuid_t char_uuid;
   esp_gatt_perm_t perm;
   esp_gatt_char_prop_t property;
   uint16_t descr_handle;
   esp_bt_uuid_t descr_uuid;
};

static void gatts_profile_event_handler (esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t * param);

/* One gatt-based profile one app_id and one gatts_if, this array will store the gatts_if returned by ESP_GATTS_REG_EVT */
static struct gatts_profile_inst heart_rate_profile_tab[] = {
   {
                              .gatts_cb = gatts_profile_event_handler,
                              .gatts_if = ESP_GATT_IF_NONE,     /* Not get the gatt_if, so initial is ESP_GATT_IF_NONE */
                              },

};

#define HEART_PROFILE_NUM (sizeof(heart_rate_profile_tab)/sizeof(*heart_rate_profile_tab))

/*
 *  Heart Rate PROFILE ATTRIBUTES
 ****************************************************************************************
 */

/// Heart Rate Sensor Service
static const uint16_t heart_rate_svc = ESP_GATT_UUID_HEART_RATE_SVC;

#define CHAR_DECLARATION_SIZE   (sizeof(uint8_t))
static const uint16_t primary_service_uuid = ESP_GATT_UUID_PRI_SERVICE;
static const uint16_t character_declaration_uuid = ESP_GATT_UUID_CHAR_DECLARE;
static const uint16_t character_client_config_uuid = ESP_GATT_UUID_CHAR_CLIENT_CONFIG;
static const uint8_t char_prop_notify = ESP_GATT_CHAR_PROP_BIT_NOTIFY;
static const uint8_t char_prop_read = ESP_GATT_CHAR_PROP_BIT_READ;
static const uint8_t char_prop_read_write = ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_READ;

/// Heart Rate Sensor Service - Heart Rate Measurement Characteristic, notify
static const uint16_t heart_rate_meas_uuid = ESP_GATT_HEART_RATE_MEAS;
static const uint8_t heart_measurement_ccc[2] = { 0x00, 0x00 };


/// Heart Rate Sensor Service -Body Sensor Location characteristic, read
static const uint16_t body_sensor_location_uuid = ESP_GATT_BODY_SENSOR_LOCATION;
static const uint8_t body_sensor_loc_val[1] = { 0x00 };


/// Heart Rate Sensor Service - Heart Rate Control Point characteristic, write&read
static const uint16_t heart_rate_ctrl_point = ESP_GATT_HEART_RATE_CNTL_POINT;
static const uint8_t heart_ctrl_point[1] = { 0x00 };

/// Full HRS Database Description - Used to add attributes into the database
static const esp_gatts_attr_db_t heart_rate_gatt_db[] = {
   // Heart Rate Service Declaration
   {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *) & primary_service_uuid, ESP_GATT_PERM_READ,
                                          sizeof (uint16_t), sizeof (heart_rate_svc), (uint8_t *) & heart_rate_svc}
                    },

   // Heart Rate Measurement Characteristic Declaration
    {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *) & character_declaration_uuid, ESP_GATT_PERM_READ,
                                                   CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *) & char_prop_notify}
                             },

   // Heart Rate Measurement Characteristic Value
   {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *) & heart_rate_meas_uuid, ESP_GATT_PERM_READ,
                                                  HRPS_HT_MEAS_MAX_LEN, 0, NULL}
                            },

   // Heart Rate Measurement Characteristic - Client Characteristic Configuration Descriptor
      {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *) & character_client_config_uuid, ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
                             sizeof (uint16_t), sizeof (heart_measurement_ccc), (uint8_t *) heart_measurement_ccc}
       },

   // Body Sensor Location Characteristic Declaration
      {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *) & character_declaration_uuid, ESP_GATT_PERM_READ,
                             CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE, (uint8_t *) & char_prop_read}
       },

   // Body Sensor Location Characteristic Value
      {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *) & body_sensor_location_uuid, ESP_GATT_PERM_READ_ENCRYPTED,
                             sizeof (uint8_t), sizeof (body_sensor_loc_val), (uint8_t *) body_sensor_loc_val}
       },

   // Heart Rate Control Point Characteristic Declaration
   {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *) & character_declaration_uuid, ESP_GATT_PERM_READ,
                                                      CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
                                                      (uint8_t *) & char_prop_read_write}
                                },

   // Heart Rate Control Point Characteristic Value
   {{ESP_GATT_AUTO_RSP},
                               {ESP_UUID_LEN_16, (uint8_t *) & heart_rate_ctrl_point,
                                ESP_GATT_PERM_WRITE_ENCRYPTED | ESP_GATT_PERM_READ_ENCRYPTED,
                                sizeof (uint8_t), sizeof (heart_ctrl_point), (uint8_t *) heart_ctrl_point}
                               },
};

#define HRS_IDX_NB	(sizeof(heart_rate_gatt_db)/sizeof(*heart_rate_gatt_db))
static uint16_t heart_rate_handle_table[HRS_IDX_NB];

static char *
esp_key_type_to_str (esp_ble_key_type_t key_type)
{
   char *key_str = NULL;
   switch (key_type)
   {
   case ESP_LE_KEY_NONE:
      key_str = "ESP_LE_KEY_NONE";
      break;
   case ESP_LE_KEY_PENC:
      key_str = "ESP_LE_KEY_PENC";
      break;
   case ESP_LE_KEY_PID:
      key_str = "ESP_LE_KEY_PID";
      break;
   case ESP_LE_KEY_PCSRK:
      key_str = "ESP_LE_KEY_PCSRK";
      break;
   case ESP_LE_KEY_PLK:
      key_str = "ESP_LE_KEY_PLK";
      break;
   case ESP_LE_KEY_LLK:
      key_str = "ESP_LE_KEY_LLK";
      break;
   case ESP_LE_KEY_LENC:
      key_str = "ESP_LE_KEY_LENC";
      break;
   case ESP_LE_KEY_LID:
      key_str = "ESP_LE_KEY_LID";
      break;
   case ESP_LE_KEY_LCSRK:
      key_str = "ESP_LE_KEY_LCSRK";
      break;
   default:
      key_str = "INVALID BLE KEY TYPE";
      break;

   }

   return key_str;
}

static char *
esp_auth_req_to_str (esp_ble_auth_req_t auth_req)
{
   char *auth_str = NULL;
   switch (auth_req)
   {
   case ESP_LE_AUTH_NO_BOND:
      auth_str = "ESP_LE_AUTH_NO_BOND";
      break;
   case ESP_LE_AUTH_BOND:
      auth_str = "ESP_LE_AUTH_BOND";
      break;
   case ESP_LE_AUTH_REQ_MITM:
      auth_str = "ESP_LE_AUTH_REQ_MITM";
      break;
   case ESP_LE_AUTH_REQ_BOND_MITM:
      auth_str = "ESP_LE_AUTH_REQ_BOND_MITM";
      break;
   case ESP_LE_AUTH_REQ_SC_ONLY:
      auth_str = "ESP_LE_AUTH_REQ_SC_ONLY";
      break;
   case ESP_LE_AUTH_REQ_SC_BOND:
      auth_str = "ESP_LE_AUTH_REQ_SC_BOND";
      break;
   case ESP_LE_AUTH_REQ_SC_MITM:
      auth_str = "ESP_LE_AUTH_REQ_SC_MITM";
      break;
   case ESP_LE_AUTH_REQ_SC_MITM_BOND:
      auth_str = "ESP_LE_AUTH_REQ_SC_MITM_BOND";
      break;
   default:
      auth_str = "INVALID BLE AUTH REQ";
      break;
   }

   return auth_str;
}

static void
show_bonded_devices (void)
{
   int dev_num = esp_ble_get_bond_device_num ();
   if (dev_num == 0)
   {
      ESP_LOGI (GATTS_TABLE_TAG, "Bonded devices number zero\n");
      return;
   }

   esp_ble_bond_dev_t *dev_list = (esp_ble_bond_dev_t *) malloc (sizeof (esp_ble_bond_dev_t) * dev_num);
   if (!dev_list)
   {
      ESP_LOGI (GATTS_TABLE_TAG, "malloc failed, return\n");
      return;
   }
   esp_ble_get_bond_device_list (&dev_num, dev_list);
   ESP_LOGI (GATTS_TABLE_TAG, "Bonded devices number %d", dev_num);
   for (int i = 0; i < dev_num; i++)
   {
      ESP_LOGI (GATTS_TABLE_TAG, "[%u] addr_type %u, addr " ESP_BD_ADDR_STR "",
                i, dev_list[i].bd_addr_type, ESP_BD_ADDR_HEX (dev_list[i].bd_addr));
   }

   free (dev_list);
}

static void __attribute__((unused)) remove_all_bonded_devices (void)
{
   int dev_num = esp_ble_get_bond_device_num ();
   if (dev_num == 0)
   {
      ESP_LOGI (GATTS_TABLE_TAG, "Bonded devices number zero\n");
      return;
   }

   esp_ble_bond_dev_t *dev_list = (esp_ble_bond_dev_t *) malloc (sizeof (esp_ble_bond_dev_t) * dev_num);
   if (!dev_list)
   {
      ESP_LOGI (GATTS_TABLE_TAG, "malloc failed, return\n");
      return;
   }
   esp_ble_get_bond_device_list (&dev_num, dev_list);
   for (int i = 0; i < dev_num; i++)
   {
      esp_ble_remove_bond_device (dev_list[i].bd_addr);
   }

   free (dev_list);
}

static void
gap_event_handler (esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t * param)
{
   ESP_LOGV (GATTS_TABLE_TAG, "GAP_EVT, event %d", event);

   switch (event)
   {
   case ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT:
      adv_config_done &= (~SCAN_RSP_CONFIG_FLAG);
      if (adv_config_done == 0)
      {
         esp_ble_gap_start_advertising (&heart_rate_adv_params);
      }
      break;
   case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
      adv_config_done &= (~ADV_CONFIG_FLAG);
      if (adv_config_done == 0)
      {
         esp_ble_gap_start_advertising (&heart_rate_adv_params);
      }
      break;
   case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
      //advertising start complete event to indicate advertising start successfully or failed
      if (param->adv_start_cmpl.status != ESP_BT_STATUS_SUCCESS)
      {
         ESP_LOGE (GATTS_TABLE_TAG, "Advertising start failed, status %x", param->adv_start_cmpl.status);
         break;
      }
      ESP_LOGI (GATTS_TABLE_TAG, "Advertising start successfully");
      break;
   case ESP_GAP_BLE_PASSKEY_REQ_EVT:   /* passkey request event */
      ESP_LOGI (GATTS_TABLE_TAG, "Passkey request");
      break;
   case ESP_GAP_BLE_OOB_REQ_EVT:
      {
         ESP_LOGI (GATTS_TABLE_TAG, "OOB request");
         uint8_t tk[16] = { 1 };        //If you paired with OOB, both devices need to use the same tk
         esp_ble_oob_req_reply (param->ble_security.ble_req.bd_addr, tk, sizeof (tk));
         break;
      }
   case ESP_GAP_BLE_LOCAL_IR_EVT:      /* BLE local IR event */
      ESP_LOGI (GATTS_TABLE_TAG, "Local identity root");
      break;
   case ESP_GAP_BLE_LOCAL_ER_EVT:      /* BLE local ER event */
      ESP_LOGI (GATTS_TABLE_TAG, "Local encryption root");
      break;
   case ESP_GAP_BLE_NC_REQ_EVT:
      /* The app will receive this evt when the IO has DisplayYesNO capability and the peer device IO also has DisplayYesNo capability.
         show the passkey number to the user to confirm it with the number displayed by peer device. */
      esp_ble_confirm_reply (param->ble_security.ble_req.bd_addr, true);
      ESP_LOGI (GATTS_TABLE_TAG, "Numeric Comparison request, passkey %" PRIu32, param->ble_security.key_notif.passkey);
      break;
   case ESP_GAP_BLE_SEC_REQ_EVT:
      /* send the positive(true) security response to the peer device to accept the security request.
         If not accept the security request, should send the security response with negative(false) accept value */
      esp_ble_gap_security_rsp (param->ble_security.ble_req.bd_addr, true);
      break;
   case ESP_GAP_BLE_PASSKEY_NOTIF_EVT: ///the app will receive this evt when the IO  has Output capability and the peer device IO has Input capability.
      ///show the passkey number to the user to input it in the peer device.
      ESP_LOGI (GATTS_TABLE_TAG, "Passkey notify, passkey %06" PRIu32, param->ble_security.key_notif.passkey);
      break;
   case ESP_GAP_BLE_KEY_EVT:
      //shows the ble key info share with peer device to the user.
      ESP_LOGI (GATTS_TABLE_TAG, "Key exchanged, key_type %s", esp_key_type_to_str (param->ble_security.ble_key.key_type));
      break;
   case ESP_GAP_BLE_AUTH_CMPL_EVT:
      {
         esp_bd_addr_t bd_addr;
         memcpy (bd_addr, param->ble_security.auth_cmpl.bd_addr, sizeof (esp_bd_addr_t));
         ESP_LOGI (GATTS_TABLE_TAG, "Authentication complete, addr_type %u, addr " ESP_BD_ADDR_STR "",
                   param->ble_security.auth_cmpl.addr_type, ESP_BD_ADDR_HEX (bd_addr));
         if (!param->ble_security.auth_cmpl.success)
         {
            ESP_LOGI (GATTS_TABLE_TAG, "Pairing failed, reason 0x%x", param->ble_security.auth_cmpl.fail_reason);
         } else
         {
            ESP_LOGI (GATTS_TABLE_TAG, "Pairing successfully, auth_mode %s",
                      esp_auth_req_to_str (param->ble_security.auth_cmpl.auth_mode));
         }
         show_bonded_devices ();
         break;
      }
   case ESP_GAP_BLE_REMOVE_BOND_DEV_COMPLETE_EVT:
      {
         ESP_LOGD (GATTS_TABLE_TAG, "Bond device remove, status %d, device " ESP_BD_ADDR_STR "",
                   param->remove_bond_dev_cmpl.status, ESP_BD_ADDR_HEX (param->remove_bond_dev_cmpl.bd_addr));
         break;
      }
   case ESP_GAP_BLE_SET_LOCAL_PRIVACY_COMPLETE_EVT:
      if (param->local_privacy_cmpl.status != ESP_BT_STATUS_SUCCESS)
      {
         ESP_LOGE (GATTS_TABLE_TAG, "Local privacy config failed, status %x", param->local_privacy_cmpl.status);
         break;
      }
      ESP_LOGI (GATTS_TABLE_TAG, "Local privacy config successfully");

      esp_err_t ret = esp_ble_gap_config_adv_data (&heart_rate_adv_config);
      if (ret)
      {
         ESP_LOGE (GATTS_TABLE_TAG, "config adv data failed, error code = %x", ret);
      } else
      {
         adv_config_done |= ADV_CONFIG_FLAG;
      }

      ret = esp_ble_gap_config_adv_data (&heart_rate_scan_rsp_config);
      if (ret)
      {
         ESP_LOGE (GATTS_TABLE_TAG, "config adv data failed, error code = %x", ret);
      } else
      {
         adv_config_done |= SCAN_RSP_CONFIG_FLAG;
      }

      break;
   default:
      break;
   }
}

static void
gatts_profile_event_handler (esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t * param)
{
   ESP_LOGV (GATTS_TABLE_TAG, "event = %x", event);
   switch (event)
   {
   case ESP_GATTS_REG_EVT:
      ESP_LOGI (GATTS_TABLE_TAG, "GATT server register, status %d, app_id %d, gatts_if %d",
                param->reg.status, param->reg.app_id, gatts_if);
      esp_ble_gap_set_device_name (example_device_name);
      //generate a resolvable random address
      esp_ble_gap_config_local_privacy (true);
      esp_ble_gatts_create_attr_tab (heart_rate_gatt_db, gatts_if, HRS_IDX_NB, 0);
      break;
   case ESP_GATTS_READ_EVT:
      break;
   case ESP_GATTS_WRITE_EVT:
      ESP_LOGI (GATTS_TABLE_TAG, "Characteristic write, value ");
      ESP_LOG_BUFFER_HEX(GATTS_TABLE_TAG, param->write.value, param->write.len);
      break;
   case ESP_GATTS_EXEC_WRITE_EVT:
      break;
   case ESP_GATTS_MTU_EVT:
      break;
   case ESP_GATTS_CONF_EVT:
      break;
   case ESP_GATTS_UNREG_EVT:
      break;
   case ESP_GATTS_DELETE_EVT:
      break;
   case ESP_GATTS_START_EVT:
      break;
   case ESP_GATTS_STOP_EVT:
      break;
   case ESP_GATTS_CONNECT_EVT:
      ESP_LOGI (GATTS_TABLE_TAG, "Connected, conn_id %u, remote " ESP_BD_ADDR_STR "",
                param->connect.conn_id, ESP_BD_ADDR_HEX (param->connect.remote_bda));
      /* start security connect with peer device when receive the connect event sent by the master */
      esp_ble_set_encryption (param->connect.remote_bda, ESP_BLE_SEC_ENCRYPT_MITM);
      break;
   case ESP_GATTS_DISCONNECT_EVT:
      ESP_LOGI (GATTS_TABLE_TAG, "Disconnected, remote " ESP_BD_ADDR_STR ", reason 0x%x",
                ESP_BD_ADDR_HEX (param->disconnect.remote_bda), param->disconnect.reason);
      /* start advertising again when missing the connect */
      esp_ble_gap_start_advertising (&heart_rate_adv_params);
      break;
   case ESP_GATTS_OPEN_EVT:
      break;
   case ESP_GATTS_CANCEL_OPEN_EVT:
      break;
   case ESP_GATTS_CLOSE_EVT:
      break;
   case ESP_GATTS_LISTEN_EVT:
      break;
   case ESP_GATTS_CONGEST_EVT:
      break;
   case ESP_GATTS_CREAT_ATTR_TAB_EVT:
      {
         if (param->create.status == ESP_GATT_OK)
         {
            if (param->add_attr_tab.num_handle == HRS_IDX_NB)
            {
               ESP_LOGI (GATTS_TABLE_TAG, "Attribute table create successfully, num_handle %x", param->add_attr_tab.num_handle);
               memcpy (heart_rate_handle_table, param->add_attr_tab.handles, sizeof (heart_rate_handle_table));
               esp_ble_gatts_start_service (heart_rate_handle_table[0]);
            } else
            {
               ESP_LOGE (GATTS_TABLE_TAG, "Attribute table create abnormally, num_handle (%d) doesn't equal to HRS_IDX_NB(%d)",
                         param->add_attr_tab.num_handle, HRS_IDX_NB);
            }
         } else
         {
            ESP_LOGE (GATTS_TABLE_TAG, "Attribute table create failed, error code = %x", param->create.status);
         }
         break;
      }

   default:
      break;
   }
}


static void
gatts_event_handler (esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t * param)
{
   /* If event is register event, store the gatts_if for each profile */
   if (event == ESP_GATTS_REG_EVT)
   {
      if (param->reg.status == ESP_GATT_OK)
      {
         heart_rate_profile_tab[0].gatts_if = gatts_if;
      } else
      {
         ESP_LOGI (GATTS_TABLE_TAG, "Reg app failed, app_id %04x, status %d", param->reg.app_id, param->reg.status);
         return;
      }
   }

   do
   {
      int idx;
      for (idx = 0; idx < HEART_PROFILE_NUM; idx++)
      {
         if (gatts_if == ESP_GATT_IF_NONE ||    /* ESP_GATT_IF_NONE, not specify a certain gatt_if, need to call every profile cb function */
             gatts_if == heart_rate_profile_tab[idx].gatts_if)
         {
            if (heart_rate_profile_tab[idx].gatts_cb)
            {
               heart_rate_profile_tab[idx].gatts_cb (event, gatts_if, param);
            }
         }
      }
   }
   while (0);
}

void
do_ble_server (void)
{
   esp_err_t ret;

#if CONFIG_EXAMPLE_CI_PIPELINE_ID
   memcpy (example_device_name, esp_bluedroid_get_example_name (), ESP_BLE_ADV_NAME_LEN_MAX);
#endif

   ESP_ERROR_CHECK (esp_bt_controller_mem_release (ESP_BT_MODE_CLASSIC_BT));

   esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT ();
   ret = esp_bt_controller_init (&bt_cfg);
   if (ret)
   {
      ESP_LOGE (GATTS_TABLE_TAG, "%s init controller failed: %s", __func__, esp_err_to_name (ret));
      return;
   }
   ret = esp_bt_controller_enable (ESP_BT_MODE_BLE);
   if (ret)
   {
      ESP_LOGE (GATTS_TABLE_TAG, "%s enable controller failed: %s", __func__, esp_err_to_name (ret));
      return;
   }

   ESP_LOGI (GATTS_TABLE_TAG, "%s init bluetooth", __func__);

   ret = esp_bluedroid_init ();
   if (ret)
   {
      ESP_LOGE (GATTS_TABLE_TAG, "%s init bluetooth failed: %s", __func__, esp_err_to_name (ret));
      return;
   }
   ret = esp_bluedroid_enable ();
   if (ret)
   {
      ESP_LOGE (GATTS_TABLE_TAG, "%s enable bluetooth failed: %s", __func__, esp_err_to_name (ret));
      return;
   }

   ret = esp_ble_gatts_register_callback (gatts_event_handler);
   if (ret)
   {
      ESP_LOGE (GATTS_TABLE_TAG, "gatts register error, error code = %x", ret);
      return;
   }
   ret = esp_ble_gap_register_callback (gap_event_handler);
   if (ret)
   {
      ESP_LOGE (GATTS_TABLE_TAG, "gap register error, error code = %x", ret);
      return;
   }
   ret = esp_ble_gatts_app_register (BLE_APP_ID);
   if (ret)
   {
      ESP_LOGE (GATTS_TABLE_TAG, "gatts app register error, error code = %x", ret);
      return;
   }

   /* set the security iocap & auth_req & key size & init key response key parameters to the stack */
   esp_ble_auth_req_t auth_req = ESP_LE_AUTH_REQ_SC_MITM_BOND;  //bonding with peer device after authentication
   esp_ble_io_cap_t iocap = ESP_IO_CAP_NONE;    //set the IO capability to No output No input
   uint8_t key_size = 16;       //the key size should be 7~16 bytes
   uint8_t init_key = ESP_BLE_ENC_KEY_MASK | ESP_BLE_ID_KEY_MASK;
   uint8_t rsp_key = ESP_BLE_ENC_KEY_MASK | ESP_BLE_ID_KEY_MASK;
   //set static passkey
   uint32_t passkey = 123456;
   uint8_t auth_option = ESP_BLE_ONLY_ACCEPT_SPECIFIED_AUTH_DISABLE;
   uint8_t oob_support = ESP_BLE_OOB_DISABLE;
   esp_ble_gap_set_security_param (ESP_BLE_SM_SET_STATIC_PASSKEY, &passkey, sizeof (uint32_t));
   esp_ble_gap_set_security_param (ESP_BLE_SM_AUTHEN_REQ_MODE, &auth_req, sizeof (uint8_t));
   esp_ble_gap_set_security_param (ESP_BLE_SM_IOCAP_MODE, &iocap, sizeof (uint8_t));
   esp_ble_gap_set_security_param (ESP_BLE_SM_MAX_KEY_SIZE, &key_size, sizeof (uint8_t));
   esp_ble_gap_set_security_param (ESP_BLE_SM_ONLY_ACCEPT_SPECIFIED_SEC_AUTH, &auth_option, sizeof (uint8_t));
   esp_ble_gap_set_security_param (ESP_BLE_SM_OOB_SUPPORT, &oob_support, sizeof (uint8_t));
   /* If your BLE device acts as a Slave, the init_key means you hope which types of key of the master should distribute to you,
      and the response key means which key you can distribute to the master;
      If your BLE device acts as a master, the response key means you hope which types of key of the slave should distribute to you,
      and the init key means which key you can distribute to the slave. */
   esp_ble_gap_set_security_param (ESP_BLE_SM_SET_INIT_KEY, &init_key, sizeof (uint8_t));
   esp_ble_gap_set_security_param (ESP_BLE_SM_SET_RSP_KEY, &rsp_key, sizeof (uint8_t));
}

void
do_ble_client (void)
{

}

void
app_main ()
{
   //ESP_LOGE (TAG, "Started");
   revk_boot (&app_callback);
   revk_start ();
   if (blink[0].set)
      revk_blink_init ();       // Library blink
   for (int n = 0; n < BUTTONS; n++)
      revk_gpio_input (button[n]);
   if (spklrc.set && spkbclk.set && spkdata.set && sdcmd.set)
      revk_task ("spk", spk_task, NULL, 8);
   int leds = 0;
   for (int s = 0; s < STRIPS; s++)
      if (stripgpio[s].set && stripcount[s])
      {
         leds += stripcount[s];
         ESP_LOGE (TAG, "PWM started using GPIO %d%s, %d LEDs", stripgpio[s].num, stripgpio[s].invert ? " (inverted)" : "",
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
   mcpwm_timer_handle_t visortimer = NULL;
   if (visorpwm.set)
   {
      mcpwm_timer_config_t timer_config = {
         .group_id = 0,
         .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
         .resolution_hz = SERVO_TIMEBASE_RESOLUTION_HZ,
         .period_ticks = SERVO_TIMEBASE_PERIOD,
         .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
      };
      ESP_ERROR_CHECK (mcpwm_new_timer (&timer_config, &visortimer));
      mcpwm_oper_handle_t oper = NULL;
      mcpwm_operator_config_t operator_config = {
         .group_id = 0,         // operator must be in the same group to the timer
      };
      ESP_ERROR_CHECK (mcpwm_new_operator (&operator_config, &oper));
      ESP_ERROR_CHECK (mcpwm_operator_connect_timer (oper, visortimer));
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
      ESP_ERROR_CHECK (mcpwm_timer_enable (visortimer));
      ESP_ERROR_CHECK (mcpwm_timer_start_stop (visortimer, MCPWM_TIMER_START_NO_STOP));
   }

   b.pwr = 1;
   b.eyes = 1;
   b.init = 1;

   if (ironman == REVK_SETTINGS_IRONMAN_ARCREACTOR)
      do_ble_server ();
   else
      do_ble_client ();

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

   while (!b.die && !revk_shutting_down (NULL))
   {
      usleep (1000000 / CPS);
      static uint8_t pushlast = 0;      // Last button state
      static uint8_t press[BUTTONS] = { 0 };    // Press count
      static uint8_t pushtime[BUTTONS] = { 0 }; // Push time
      if (!b.dying)
         for (int n = 0; n < BUTTONS; n++)
         {
            uint8_t push = revk_gpio_get (button[n]);
            if (b.init || ((pushlast >> n) & 1) != push)
            {                   // Change
               pushlast = ((pushlast & ~(1 << n)) | (push << n));
               if (push && !b.init)
               {                // Count presses
                  press[n]++;
                  ESP_LOGD (TAG, "Push%d %d", n, press[n]);     // TODO
               }
               if (ledbutton[n])
                  set_led (ledbutton[n], 255, push ? REVK_SETTINGS_LEDEYEC_RED : REVK_SETTINGS_LEDEYEC_GREEN);
               pushtime[n] = 0; // Start timer
            } else if (!push)
            {                   // Released
               if (press[n] && pushtime[n]++ >= CPS / 2)
               {                // Action
                  dobutton (n, press[n]);
                  press[n] = 0;
               }
            } else if (pushtime[n]++ >= CPS * 3)
            {                   // Held
               if (b.speaker)
               {                // try and play power off - not foolproof
                  play = "POWEROFF";
                  b.dying = 1;
               } else
                  b.die = 1;    // off now
            }
         }
      if (b.connect)
      {
         b.connected = 1;
         b.connect = 0;
         revk_command ("upgrade", NULL);        // Immediate upgrade attempt
      }
      {
         if (b.init && pwmangle == visoropen)
            b.open = 1;
         int newangle = b.open ? visoropen : visorclose;
         static int8_t step = 0;
         if (b.init || newangle != pwmangle)
         {
            if (newangle > pwmangle && step < 100)
               step++;
            else if (newangle < pwmangle && step > -100)
               step--;
            pwmangle += step / 3;
            if (pwmangle > visoropen)
               pwmangle = visoropen;
            if (pwmangle < visorclose)
               pwmangle = visorclose;
            if (newangle == pwmangle)
               step = 0;
            if (visorpwm.set)
            {                   // PWM
               REVK_ERR_CHECK (mcpwm_comparator_set_compare_value (comparator, angle_to_compare (pwmangle)));
               ESP_LOGD (TAG, "Angle %d (%d) value %ld ", pwmangle, step, angle_to_compare (pwmangle));
            }
         }
      }
      if (leds)
      {
         for (int i = 0; i < leds; i++)
            set_led (i, 255, REVK_SETTINGS_LEDEYEC_BLACK);      // Clear
         // PWM (open/closed)
         if (ledpwm)
            set_led (ledpwm - 1, 255, b.open ? REVK_SETTINGS_LEDEYEC_RED : REVK_SETTINGS_LEDEYEC_GREEN);
         // Static LEDs
         if (ledfixed && ledfixeds)
            for (int i = ledfixed; i < ledfixed + ledfixeds; i++)
               set_led (i - 1, 255, ledfixedc);
         // Arc
         if (ledarc && ledarcs)
            for (int i = ledarc; i < ledarc + ledarcs; i++)
               set_led (i - 1, 255, (i & 1) ? ledarcc1 : ledarcc2);
         // Eye 1
         if (ledeye1 && b.eyes)
            for (int i = 0; i < ledeyes; i++)
               set_led (i + ledeye1 - 1, 255, ledeyec);
         // Eye 2
         if (ledeye2 && b.eyes)
            for (int i = 0; i < ledeyes; i++)
               set_led (i + ledeye2 - 1, 255, ledeyec);
         // Pulse
         if (ledpulse && ledpulses)
         {
            static uint8_t cycle = 0;
            cycle += 8;
            for (int i = ledpulse; i < ledpulse + ledpulses; i++)
               set_led (i - 1, 64 + cos8[cycle] / 2, ledpulsec);
         }
         // Glove
         if (ledglove && ledgloves && b.glove)
         {
            static uint8_t cycle = 0;
            for (int i = 0; i < ledgloves; i++)
               set_led (i + ledglove - 1, (cycle + ledgloves - i) > 255 ? 255 : cycle + ledgloves - i, ledglovec);
            cycle += 8;
            if (!cycle)
               b.glove = 0;
         }
         if (b.cylon && ledcylon && ledcylons)
         {                      // Cylon
            static int8_t cycle = 0,
               dir = 1;
            set_led (ledcylon + cycle - 1, 255, ledcylonc);
            if (cycle == ledcylons - 1)
               dir = -1;
            else if (!cycle)
               dir = 1;
            cycle += dir;
         }
         for (int s = 0; s < STRIPS; s++)
            if (strip[s])
               led_strip_refresh (strip[s]);
      }
      if (blink[0].set)
         revk_blink_do ();      // Library blink
      b.init = 0;
   }
   if (leds)
   {                            // Dark
      for (int i = 0; i < leds; i++)
         set_led (i, 255, REVK_SETTINGS_LEDEYEC_BLACK); // Clear
      for (int s = 0; s < STRIPS; s++)
         if (strip[s])
            led_strip_refresh (strip[s]);
   }
   if (b.die)
   {                            // Deep sleep
      revk_pre_shutdown ();
      if (blink[0].set)
         revk_blink_do ();      // Library blink
      if (visorpwm.set)
         ESP_ERROR_CHECK (mcpwm_timer_enable (visortimer));
      while (revk_gpio_get (button[0]))
         usleep (100000);       // Button release
      // Alarm
      if (rtc_gpio_is_valid_gpio (button[0].num))
      {                         // Deep sleep
         ESP_LOGE (TAG, "Deep sleep on button %d %s", button[0].num, button[0].invert ? "low" : "high");
         rtc_gpio_set_direction_in_sleep (button[0].num, RTC_GPIO_MODE_INPUT_ONLY);
         REVK_ERR_CHECK (esp_sleep_enable_ext0_wakeup (button[0].num, 1 - button[0].invert));
      } else
      {                         // Light sleep
         ESP_LOGE (TAG, "Light sleep on button %d %s", button[0].num, button[0].invert ? "low" : "high");
         gpio_wakeup_enable (button[0].num, button[0].invert ? GPIO_INTR_LOW_LEVEL : GPIO_INTR_HIGH_LEVEL);
         esp_sleep_enable_gpio_wakeup ();
      }
      // Shutdown
      sleep (1);                // Allow tasks to end
      // Night night
      if (rtc_gpio_is_valid_gpio (button[0].num))
         esp_deep_sleep_start ();
      else
         esp_light_sleep_start ();
      esp_restart ();
   }
   // Restart
   play = "";
   if (revk_shutting_down (NULL) > 5)
   {                            // Upgrade
      // Don't play while erasing flash
      int n = 20;
      while (n--)
      {
         if (blink[0].set)
            revk_blink_do ();   // Library blink
         usleep (100000);
      }
      play = "UPGRADE";
      while (1)
      {
         if (blink[0].set)
            revk_blink_do ();   // Library blink
         usleep (100000);
         if (revk_shutting_down (NULL) == 3)
            break;
      }
   }
   play = "RESTART";
}
