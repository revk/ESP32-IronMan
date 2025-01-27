// Common

extern struct bit_s
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
   uint8_t playing:1;           // File is playing
   uint8_t usb:1;               // USB connected
} b;

extern const char ble_device_name[ESP_BLE_ADV_NAME_LEN_MAX];
#define	ble_service_id	ESP_GATT_UUID_HEART_RATE_SVC

void do_ble_server (void);
void do_ble_client (void);
void do_play (const char *);
