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
 const char *old;
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
 uint8_t hide:1;
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
 REVK_SETTINGS_BITFIELD_prefixhost,
#ifdef	CONFIG_REVK_BLINK_DEF
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
 uint8_t prefixapp:1;	// MQTT use appname/ in front of hostname in topic
 uint8_t prefixhost:1;	// MQTT use (appname/)hostname/topic instead of topic/(appname/)hostname
#ifdef	CONFIG_REVK_BLINK_DEF
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
 uint8_t meshlr:1;	// Mesh use LR mode
 uint8_t meshroot:1;	// This is preferred mesh root
#endif
};
extern revk_gpio_t eye1;	// Left eye
extern revk_gpio_t eye2;	// Right eye
extern revk_gpio_t pwr;	// Visor servo power
extern revk_gpio_t pwm;	// Visor service PWM
extern revk_gpio_t button1;	// Activation button1
extern revk_gpio_t button2;	// Activation button2
extern revk_gpio_t rgb;	// RGB LED chain
extern uint8_t leds;	// Number of LEDs in chain
extern uint8_t ledeye1;	// LED number for eye 1
extern uint8_t ledeye2;	// LED number for eye 2
extern uint8_t ledeyes;	// How many LEDs in eye
extern uint8_t ledpwr;	// LED number for servo PWR
extern uint8_t ledpwm;	// LED number for servo PWM
extern uint8_t ledbutton1;	// LED number for button1
extern uint8_t ledbutton2;	// LED number for button2
extern uint8_t ledarc;	// LED number start of arc ring
extern uint8_t ledarcs;	// How many LED in arc ring
extern uint8_t ledpulse;	// LED number start of pulsing
extern uint8_t ledpulses;	// How many LED in pusling
extern uint8_t ledblue;	// LED number start of blue LEDs
extern uint8_t ledblues;	// How many LED in blue LED
extern uint8_t ledgreen;	// LED number start of green LEDs
extern uint8_t ledgreens;	// How many LED in green LED
extern uint8_t ledred;	// LED number start of red LEDs
extern uint8_t ledreds;	// How many LED in red LED
extern uint8_t ledcylon;	// LED number start of cylon LEDs
extern uint8_t ledcylons;	// How many LED in cylon LED
extern uint8_t visorclose;	// Angle (degrees) visor close
extern uint8_t visoropen;	// Angle (degrees) visor open
#ifdef	CONFIG_REVK_SETTINGS_PASSWORD
extern char* password;	// Settings password (this is not sent securely so use with care on local networks you control)
#endif
extern char* hostname;	// Host name
extern char* appname;	// Application name
extern char* otahost;	// OTA hostname
extern uint8_t otadays;	// OTA auto load (days)
extern uint16_t otastart;	// OTA check after startup (min seconds)
#define	otaauto	revk_settings_bits.otaauto
#define	otabeta	revk_settings_bits.otabeta
extern revk_settings_blob_t* otacert;	// OTA cert of otahost
extern char* ntphost;	// NTP host
extern char* tz;	// Timezone (<a href='https://gist.github.com/alwynallan/24d96091655391107939' target=_blank>info</a>)
extern uint32_t watchdogtime;	// Watchdog (seconds)
extern char* topicgroup[2];	// MQTT Alternative hostname accepted for commands
extern char* topiccommand;	// MQTT Topic for commands
extern char* topicsetting;	// MQTT Topic for settings
extern char* topicstate;	// MQTT Topic for state
extern char* topicevent;	// MQTT Topic for event
extern char* topicinfo;	// MQTT Topic for info
extern char* topicerror;	// MQTT Topic for error
#define	prefixapp	revk_settings_bits.prefixapp
#define	prefixhost	revk_settings_bits.prefixhost
#ifdef	CONFIG_REVK_BLINK_DEF
extern revk_gpio_t blink[3];	// LED array
#endif
extern revk_settings_blob_t* clientkey;	// Client Key (OTA and MQTT TLS)
extern revk_settings_blob_t* clientcert;	// Client certificate (OTA and MQTT TLS)
#ifdef  CONFIG_REVK_APMODE
#ifdef	CONFIG_REVK_APCONFIG
extern uint16_t apport;	// TCP port for config web pages on AP
#endif
extern uint32_t aptime;	// Limit AP to time (seconds)
extern uint32_t apwait;	// Wait off line before starting AP (seconds)
extern revk_gpio_t apgpio;	// Start AP on GPIO
#endif
#ifdef  CONFIG_REVK_MQTT
extern char* mqtthost[CONFIG_REVK_MQTT_CLIENTS];	// MQTT hostname
extern uint16_t mqttport[CONFIG_REVK_MQTT_CLIENTS];	// MQTT port
extern char* mqttuser[CONFIG_REVK_MQTT_CLIENTS];	// MQTT username
extern char* mqttpass[CONFIG_REVK_MQTT_CLIENTS];	// MQTT password
extern revk_settings_blob_t* mqttcert[CONFIG_REVK_MQTT_CLIENTS];	// MQTT certificate
#endif
#if     defined(CONFIG_REVK_WIFI) || defined(CONFIG_REVK_MESH)
extern uint16_t wifireset;	// Restart if WiFi off for this long (seconds)
extern char* wifissid;	// WiFI SSID (name)
extern char* wifipass;	// WiFi password
extern char* wifiip;	// WiFi Fixed IP
extern char* wifigw;	// WiFi Fixed gateway
extern char* wifidns[3];	// WiFi fixed DNS
extern uint8_t wifibssid[6];	// WiFI BSSID
extern uint8_t wifichan;	// WiFI channel
extern uint16_t wifiuptime;	// WiFI turns off after this many seconds
#define	wifips	revk_settings_bits.wifips
#define	wifimaxps	revk_settings_bits.wifimaxps
#endif
#ifndef	CONFIG_REVK_MESH
extern char* apssid;	// AP mode SSID (name)
extern char* appass;	// AP mode password
extern uint8_t apmax;	// AP max clients
extern char* apip;	// AP mode block
#define	aplr	revk_settings_bits.aplr
#define	aphide	revk_settings_bits.aphide
#endif
#ifdef	CONFIG_REVK_MESH
extern char* nodename;	// Mesh node name
extern uint16_t meshreset;	// Reset if mesh off for this long (seconds)
extern uint8_t meshid[6];	// Mesh ID (hex)
extern uint8_t meshkey[16];	// Mesh key
extern uint16_t meshwidth;	// Mesh width
extern uint16_t meshdepth;	// Mesh depth
extern uint16_t meshmax;	// Mesh max devices
extern char* meshpass;	// Mesh AP password
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
#define	REVK_SETTINGS_HAS_OLD
#define	REVK_SETTINGS_HAS_COMMENT
#define	REVK_SETTINGS_HAS_GPIO
#define	REVK_SETTINGS_HAS_NUMERIC
#define	REVK_SETTINGS_HAS_UNSIGNED
#define	REVK_SETTINGS_HAS_BIT
#define	REVK_SETTINGS_HAS_BLOB
#define	REVK_SETTINGS_HAS_STRING
#define	REVK_SETTINGS_HAS_OCTET
typedef uint8_t revk_setting_bits_t[12];
typedef uint8_t revk_setting_group_t[2];
extern const char revk_settings_secret[];
