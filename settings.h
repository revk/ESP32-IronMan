// Settings
// Generated from:-
// settings.def
// components/ESP32-RevK/settings.def

#include <stdint.h>
#include <stddef.h>
typedef struct revk_settings_s revk_settings_t;
struct revk_settings_s {
 void *ptr;
 const char name[16];
 const char *def;
 const char *flags;
 const char *comment;
 uint16_t size;
 uint8_t group;
 uint8_t bit;
 uint8_t dot:4;
 uint8_t len:4;
 uint8_t type:3;
 uint8_t decimal:5;
 uint8_t array:7;
 uint8_t malloc:1;
 uint8_t revk:1;
 uint8_t live:1;
 uint8_t fix:1;
 uint8_t set:1;
 uint8_t hex:1;
 uint8_t base64:1;
 uint8_t secret:1;
 uint8_t dq:1;
 uint8_t gpio:1;
 uint8_t rtc:1;
};
typedef struct revk_settings_blob_s revk_settings_blob_t;
struct revk_settings_blob_s {
 uint16_t len;
 uint8_t data[];
};
typedef struct revk_gpio_s revk_gpio_t;
struct revk_gpio_s {
 uint16_t num:10;
 uint16_t strong:1;
 uint16_t weak:1;
 uint16_t pulldown:1;
 uint16_t nopull:1;
 uint16_t invert:1;
 uint16_t set:1;
};
enum {
#ifdef	CONFIG_REVK_SETTINGS_PASSWORD
#endif
 REVK_SETTINGS_BITFIELD_otaauto,
 REVK_SETTINGS_BITFIELD_otabeta,
 REVK_SETTINGS_BITFIELD_prefixapp,
#ifdef	CONFIG_REVK_BLINK_LIB
#endif
#ifdef  CONFIG_REVK_APMODE
#ifdef	CONFIG_REVK_APCONFIG
#endif
#endif
#ifdef  CONFIG_REVK_MQTT
#endif
#if     defined(CONFIG_REVK_WIFI) || defined(CONFIG_REVK_MESH)
 REVK_SETTINGS_BITFIELD_wifips,
 REVK_SETTINGS_BITFIELD_wifimaxps,
#endif
#ifndef	CONFIG_REVK_MESH
 REVK_SETTINGS_BITFIELD_aplr,
 REVK_SETTINGS_BITFIELD_aphide,
#endif
#ifdef	CONFIG_REVK_MESH
 REVK_SETTINGS_BITFIELD_meshlr,
 REVK_SETTINGS_BITFIELD_meshroot,
#endif
};
typedef struct revk_settings_bits_s revk_settings_bits_t;
struct revk_settings_bits_s {
#ifdef	CONFIG_REVK_SETTINGS_PASSWORD
#endif
 uint8_t otaauto:1;	// OTA auto upgrade
 uint8_t otabeta:1;	// OTA from beta release
 uint8_t prefixapp:1;	// MQTT includes appname
#ifdef	CONFIG_REVK_BLINK_LIB
#endif
#ifdef  CONFIG_REVK_APMODE
#ifdef	CONFIG_REVK_APCONFIG
#endif
#endif
#ifdef  CONFIG_REVK_MQTT
#endif
#if     defined(CONFIG_REVK_WIFI) || defined(CONFIG_REVK_MESH)
 uint8_t wifips:1;	// WiFi power save
 uint8_t wifimaxps:1;	// WiFi power save (max)
#endif
#ifndef	CONFIG_REVK_MESH
 uint8_t aplr:1;	// AP LR mode
 uint8_t aphide:1;	// AP hide SSID
#endif
#ifdef	CONFIG_REVK_MESH
 uint8_t meshlr:1;
 uint8_t meshroot:1;
#endif
};
extern revk_gpio_t eye1;	// Left eye
extern revk_gpio_t eye2;	// Right eye
extern revk_gpio_t pwr;	// Visor servo power
extern revk_gpio_t pwm;	// Visor service PWM
extern revk_gpio_t button1;	// Activation button1
extern revk_gpio_t button2;	// Activation button2
extern revk_gpio_t rgb;	// RGB LED chain
extern uint8_t leds;	// Number of LEDs
extern uint8_t ledeye1;	// LED number for eye 1
extern uint8_t ledeye2;	// LED number for eye 2
extern uint8_t ledpwr;	// LED number for servo PWR
extern uint8_t ledpwm;	// LED number for servo PWM
extern uint8_t ledbutton1;	// LED number for button1
extern uint8_t ledbutton2;	// LED number for button2
extern uint8_t visorclose;	// Angle (degrees) visor close
extern uint8_t visoropen;	// Angle (degrees) visor open
#ifdef	CONFIG_REVK_SETTINGS_PASSWORD
extern char* password;	// Settings password (this is not sent securely so use with care on local networks you control)
#endif
extern char* hostname;	// Host name
extern char* appname;
extern char* otahost;	// OTA hostname
extern uint8_t otadays;	// OTA auto load (days)
extern uint16_t otastart;	// OTA check after startup (min seconds)
#define	otaauto	revk_settings_bits.otaauto
#define	otabeta	revk_settings_bits.otabeta
extern revk_settings_blob_t* otacert;	// OTA cert of otahost
extern char* ntphost;	// NTP host
extern char* tz;	// Timezone (<a href='https://gist.github.com/alwynallan/24d96091655391107939' target=_blank>info</a>)
extern uint32_t watchdogtime;	// Watchdog (seconds)
extern char* prefixcommand;	// MQTT Prefix for commands (simple text, no / included)
extern char* prefixsetting;	// MQTT Prefix for settings (simple text, no / included)
extern char* prefixstate;	// MQTT Prefix for state
extern char* prefixevent;	// MQTT Prefix for event
extern char* prefixinfo;	// MQTT Prefix for info
extern char* prefixerror;	// MQTT Prefix for error
#define	prefixapp	revk_settings_bits.prefixapp
#ifdef	CONFIG_REVK_BLINK_LIB
extern revk_gpio_t blink[3];	// LED array
#endif
extern revk_settings_blob_t* clientkey;
extern revk_settings_blob_t* clientcert;
#ifdef  CONFIG_REVK_APMODE
#ifdef	CONFIG_REVK_APCONFIG
extern uint16_t apport;	// TCP port for config web pages on AP
#endif
extern uint32_t aptime;	// Limit AP to time (seconds)
extern uint32_t apwait;	// Wait off line before starting AP (seconds)
extern revk_gpio_t apgpio;	// Start AP on GPIO
#endif
#ifdef  CONFIG_REVK_MQTT
extern char* mqtthost[CONFIG_REVK_MQTT_CLIENTS];
extern uint16_t mqttport[CONFIG_REVK_MQTT_CLIENTS];
extern char* mqttuser[CONFIG_REVK_MQTT_CLIENTS];
extern char* mqttpass[CONFIG_REVK_MQTT_CLIENTS];
extern revk_settings_blob_t* mqttcert[CONFIG_REVK_MQTT_CLIENTS];
#endif
#if     defined(CONFIG_REVK_WIFI) || defined(CONFIG_REVK_MESH)
extern uint16_t wifireset;
extern char* wifissid;	// WiFI SSID (name)
extern char* wifipass;	// WiFi password
extern char* wifiip;	// WiFi Fixed IP
extern char* wifigw;	// WiFi Fixed gateway
extern char* wifidns[3];	// WiFi fixed DNS
extern uint8_t wifibssid[6];	// WiFI BSSID
extern uint8_t wifichan;	// WiFI channel
#define	wifips	revk_settings_bits.wifips
#define	wifimaxps	revk_settings_bits.wifimaxps
#endif
#ifndef	CONFIG_REVK_MESH
extern char* apssid;	// AP mode SSID (name)
extern char* appass;	// AP mode password
extern uint8_t apmax;
extern char* apip;	// AP mode block
#define	aplr	revk_settings_bits.aplr
#define	aphide	revk_settings_bits.aphide
#endif
#ifdef	CONFIG_REVK_MESH
extern char* nodename;
extern uint16_t meshreset;
extern uint8_t meshid[6];
extern uint8_t meshkey[16];
extern uint16_t meshwidth;
extern uint16_t meshdepth;
extern uint16_t meshmax;
extern char* meshpass;
#define	meshlr	revk_settings_bits.meshlr
#define	meshroot	revk_settings_bits.meshroot
#endif
extern revk_settings_bits_t revk_settings_bits;
enum {
 REVK_SETTINGS_UNSIGNED,
 REVK_SETTINGS_BIT,
 REVK_SETTINGS_BLOB,
 REVK_SETTINGS_STRING,
 REVK_SETTINGS_OCTET,
};
#define	REVK_SETTINGS_HAS_COMMENT
#define	REVK_SETTINGS_HAS_GPIO
#define	REVK_SETTINGS_HAS_NUMERIC
#define	REVK_SETTINGS_HAS_UNSIGNED
#define	REVK_SETTINGS_HAS_BIT
#define	REVK_SETTINGS_HAS_BLOB
#define	REVK_SETTINGS_HAS_STRING
#define	REVK_SETTINGS_HAS_OCTET
typedef uint8_t revk_setting_bits_t[10];
typedef uint8_t revk_setting_group_t[2];
extern const char revk_settings_secret[];
