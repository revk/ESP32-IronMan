// Settings
// Generated from:-
// main/settings.def
// components/ESP32-RevK/settings.def

#include <stdint.h>
#include <stddef.h>
typedef struct revk_settings_s revk_settings_t;
struct revk_settings_s {
 void *ptr;
 const char name[16];
 const char *def;
 union {
  const char *flags;
  const char *enums;
 };
 const char *old;
 const char *unit;
 const char *comment;
 uint16_t size;
 uint8_t group;
 uint8_t bit;
 uint8_t dot:4;
 uint8_t len:4;
 uint8_t type:3;
 uint8_t decimal:5;
 uint8_t digits:5;
 uint8_t array:7;
 uint8_t malloc:1;
 uint8_t revk:1;
 uint8_t live:1;
 uint8_t hide:1;
 uint8_t fix:1;
 uint8_t set:1;
 uint8_t hex:1;
 uint8_t base32:1;
 uint8_t base64:1;
 uint8_t secret:1;
 uint8_t dq:1;
 uint8_t rtc:1;
 uint8_t gpio:1;
 uint8_t isenum:1;
};
enum {
 REVK_SETTINGS_IRONMAN_ARCREACTOR,
 REVK_SETTINGS_IRONMAN_HELMET,
 REVK_SETTINGS_IRONMAN_GLOVE,
};
enum {
 REVK_SETTINGS_STRIPTYPE_WS2812_GRB,
 REVK_SETTINGS_STRIPTYPE_WS2812_GBR,
 REVK_SETTINGS_STRIPTYPE_WS2812_RGB,
 REVK_SETTINGS_STRIPTYPE_WS2812_RBG,
 REVK_SETTINGS_STRIPTYPE_WS2812_BGR,
 REVK_SETTINGS_STRIPTYPE_WS2812_BRG,
 REVK_SETTINGS_STRIPTYPE_WS2812_GRBW,
 REVK_SETTINGS_STRIPTYPE_WS2812_GBRW,
 REVK_SETTINGS_STRIPTYPE_WS2812_RGBW,
 REVK_SETTINGS_STRIPTYPE_WS2812_RBGW,
 REVK_SETTINGS_STRIPTYPE_WS2812_BGRW,
 REVK_SETTINGS_STRIPTYPE_WS2812_BRGW,
 REVK_SETTINGS_STRIPTYPE_SK7812_GRB,
 REVK_SETTINGS_STRIPTYPE_SK7812_GBR,
 REVK_SETTINGS_STRIPTYPE_SK7812_RGB,
 REVK_SETTINGS_STRIPTYPE_SK7812_RBG,
 REVK_SETTINGS_STRIPTYPE_SK7812_BGR,
 REVK_SETTINGS_STRIPTYPE_SK7812_BRG,
 REVK_SETTINGS_STRIPTYPE_SK7812_GRBW,
 REVK_SETTINGS_STRIPTYPE_SK7812_GBRW,
 REVK_SETTINGS_STRIPTYPE_SK7812_RGBW,
 REVK_SETTINGS_STRIPTYPE_SK7812_RBGW,
 REVK_SETTINGS_STRIPTYPE_SK7812_BGRW,
 REVK_SETTINGS_STRIPTYPE_SK7812_BRGW,
};
enum {
 REVK_SETTINGS_LEDEYEC_BLACK,
 REVK_SETTINGS_LEDEYEC_RED,
 REVK_SETTINGS_LEDEYEC_GREEN,
 REVK_SETTINGS_LEDEYEC_YELLOW,
 REVK_SETTINGS_LEDEYEC_BLUE,
 REVK_SETTINGS_LEDEYEC_MAGENTA,
 REVK_SETTINGS_LEDEYEC_CYAN,
 REVK_SETTINGS_LEDEYEC_WHITE,
 REVK_SETTINGS_LEDEYEC_W,
 REVK_SETTINGS_LEDEYEC_W_RED,
 REVK_SETTINGS_LEDEYEC_W_GREEN,
 REVK_SETTINGS_LEDEYEC_W_YELLOW,
 REVK_SETTINGS_LEDEYEC_W_BLUE,
 REVK_SETTINGS_LEDEYEC_W_MAGENTA,
 REVK_SETTINGS_LEDEYEC_W_CYAN,
 REVK_SETTINGS_LEDEYEC_W_WHITE,
};
enum {
 REVK_SETTINGS_LEDARCC1_BLACK,
 REVK_SETTINGS_LEDARCC1_RED,
 REVK_SETTINGS_LEDARCC1_GREEN,
 REVK_SETTINGS_LEDARCC1_YELLOW,
 REVK_SETTINGS_LEDARCC1_BLUE,
 REVK_SETTINGS_LEDARCC1_MAGENTA,
 REVK_SETTINGS_LEDARCC1_CYAN,
 REVK_SETTINGS_LEDARCC1_WHITE,
 REVK_SETTINGS_LEDARCC1_W,
 REVK_SETTINGS_LEDARCC1_W_RED,
 REVK_SETTINGS_LEDARCC1_W_GREEN,
 REVK_SETTINGS_LEDARCC1_W_YELLOW,
 REVK_SETTINGS_LEDARCC1_W_BLUE,
 REVK_SETTINGS_LEDARCC1_W_MAGENTA,
 REVK_SETTINGS_LEDARCC1_W_CYAN,
 REVK_SETTINGS_LEDARCC1_W_WHITE,
};
enum {
 REVK_SETTINGS_LEDARCC2_BLACK,
 REVK_SETTINGS_LEDARCC2_RED,
 REVK_SETTINGS_LEDARCC2_GREEN,
 REVK_SETTINGS_LEDARCC2_YELLOW,
 REVK_SETTINGS_LEDARCC2_BLUE,
 REVK_SETTINGS_LEDARCC2_MAGENTA,
 REVK_SETTINGS_LEDARCC2_CYAN,
 REVK_SETTINGS_LEDARCC2_WHITE,
 REVK_SETTINGS_LEDARCC2_W,
 REVK_SETTINGS_LEDARCC2_W_RED,
 REVK_SETTINGS_LEDARCC2_W_GREEN,
 REVK_SETTINGS_LEDARCC2_W_YELLOW,
 REVK_SETTINGS_LEDARCC2_W_BLUE,
 REVK_SETTINGS_LEDARCC2_W_MAGENTA,
 REVK_SETTINGS_LEDARCC2_W_CYAN,
 REVK_SETTINGS_LEDARCC2_W_WHITE,
};
enum {
 REVK_SETTINGS_LEDPULSEC_BLACK,
 REVK_SETTINGS_LEDPULSEC_RED,
 REVK_SETTINGS_LEDPULSEC_GREEN,
 REVK_SETTINGS_LEDPULSEC_YELLOW,
 REVK_SETTINGS_LEDPULSEC_BLUE,
 REVK_SETTINGS_LEDPULSEC_MAGENTA,
 REVK_SETTINGS_LEDPULSEC_CYAN,
 REVK_SETTINGS_LEDPULSEC_WHITE,
 REVK_SETTINGS_LEDPULSEC_W,
 REVK_SETTINGS_LEDPULSEC_W_RED,
 REVK_SETTINGS_LEDPULSEC_W_GREEN,
 REVK_SETTINGS_LEDPULSEC_W_YELLOW,
 REVK_SETTINGS_LEDPULSEC_W_BLUE,
 REVK_SETTINGS_LEDPULSEC_W_MAGENTA,
 REVK_SETTINGS_LEDPULSEC_W_CYAN,
 REVK_SETTINGS_LEDPULSEC_W_WHITE,
};
enum {
 REVK_SETTINGS_LEDFIXEDC_BLACK,
 REVK_SETTINGS_LEDFIXEDC_RED,
 REVK_SETTINGS_LEDFIXEDC_GREEN,
 REVK_SETTINGS_LEDFIXEDC_YELLOW,
 REVK_SETTINGS_LEDFIXEDC_BLUE,
 REVK_SETTINGS_LEDFIXEDC_MAGENTA,
 REVK_SETTINGS_LEDFIXEDC_CYAN,
 REVK_SETTINGS_LEDFIXEDC_WHITE,
 REVK_SETTINGS_LEDFIXEDC_W,
 REVK_SETTINGS_LEDFIXEDC_W_RED,
 REVK_SETTINGS_LEDFIXEDC_W_GREEN,
 REVK_SETTINGS_LEDFIXEDC_W_YELLOW,
 REVK_SETTINGS_LEDFIXEDC_W_BLUE,
 REVK_SETTINGS_LEDFIXEDC_W_MAGENTA,
 REVK_SETTINGS_LEDFIXEDC_W_CYAN,
 REVK_SETTINGS_LEDFIXEDC_W_WHITE,
};
enum {
 REVK_SETTINGS_LEDCYLONC_BLACK,
 REVK_SETTINGS_LEDCYLONC_RED,
 REVK_SETTINGS_LEDCYLONC_GREEN,
 REVK_SETTINGS_LEDCYLONC_YELLOW,
 REVK_SETTINGS_LEDCYLONC_BLUE,
 REVK_SETTINGS_LEDCYLONC_MAGENTA,
 REVK_SETTINGS_LEDCYLONC_CYAN,
 REVK_SETTINGS_LEDCYLONC_WHITE,
 REVK_SETTINGS_LEDCYLONC_W,
 REVK_SETTINGS_LEDCYLONC_W_RED,
 REVK_SETTINGS_LEDCYLONC_W_GREEN,
 REVK_SETTINGS_LEDCYLONC_W_YELLOW,
 REVK_SETTINGS_LEDCYLONC_W_BLUE,
 REVK_SETTINGS_LEDCYLONC_W_MAGENTA,
 REVK_SETTINGS_LEDCYLONC_W_CYAN,
 REVK_SETTINGS_LEDCYLONC_W_WHITE,
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
#define	STRIPS	3	// ESP32S3 only has 4 channels and one is for on board LED
#define	BUTTONS	2
#ifdef	CONFIG_REVK_SETTINGS_PASSWORD
#endif
 REVK_SETTINGS_BITFIELD_otaauto,
 REVK_SETTINGS_BITFIELD_otabeta,
 REVK_SETTINGS_BITFIELD_prefixapp,
 REVK_SETTINGS_BITFIELD_prefixhost,
#ifdef	CONFIG_REVK_BLINK_DEF
#endif
 REVK_SETTINGS_BITFIELD_dark,
#ifdef  CONFIG_IDF_TARGET_ESP32S3
#else
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
#define	STRIPS	3	// ESP32S3 only has 4 channels and one is for on board LED
#define	BUTTONS	2
#ifdef	CONFIG_REVK_SETTINGS_PASSWORD
#endif
 uint8_t otaauto:1;	// OTA auto upgrade
 uint8_t otabeta:1;	// OTA from beta release
 uint8_t prefixapp:1;	// MQTT use appname/ in front of hostname in topic
 uint8_t prefixhost:1;	// MQTT use (appname/)hostname/topic instead of topic/(appname/)hostname
#ifdef	CONFIG_REVK_BLINK_DEF
#endif
 uint8_t dark:1;	// Default LED off
#ifdef  CONFIG_IDF_TARGET_ESP32S3
#else
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
#define	STRIPS	3	// ESP32S3 only has 4 channels and one is for on board LED
#define	BUTTONS	2
extern uint8_t ironman;	// What part of suit
extern revk_gpio_t button[BUTTONS];	// Activation buttons
extern revk_gpio_t stripgpio[STRIPS];	// GPIOs for LED string
extern uint16_t stripcount[STRIPS];	// How many LEDs in string
extern uint8_t striptype[STRIPS];	// Type of LED string
extern revk_gpio_t sddat2;	// MicroSD DAT2
extern revk_gpio_t sddat3;	// MicroSD DAT3
extern revk_gpio_t sdcmd;	// MicroSD CMD
extern revk_gpio_t sdclk;	// MicroSD CLK
extern revk_gpio_t sddat0;	// MicroSD DAT0
extern revk_gpio_t sddat1;	// MicroSD DAT1
extern revk_gpio_t sdcd;	// MicroSD CD
extern revk_gpio_t micdata;	// Microphone Data / SD
extern revk_gpio_t micclock;	// Microphone Clock / SCK
extern revk_gpio_t micws;	// Microphone WS (not set for PDM)
extern revk_gpio_t spkpwr;	// Speaker power on
extern revk_gpio_t spklrc;	// Speaker LR clock
extern revk_gpio_t spkbclk;	// Speaker Bit clock
extern revk_gpio_t spkdata;	// Speaker Data
extern uint8_t ledeye1;	// LED number for eye 1
extern uint8_t ledeye2;	// LED number for eye 2
extern uint8_t ledeyes;	// How many LEDs in eye
extern uint8_t ledeyec;	// Eye LED colour
extern uint8_t ledarc;	// LED number start of arc ring
extern uint8_t ledarcs;	// How many LED in arc ring
extern uint8_t ledarcc1;	// Arc LED colour (bright)
extern uint8_t ledarcc2;	// Arc LED colour (dim)
extern uint8_t ledpulse;	// LED number start of pulsing
extern uint8_t ledpulses;	// How many LED in pulsing
extern uint8_t ledpulsec;	// Pulse LED colour
extern uint8_t ledfixed;	// LED number start of fixed LEDs
extern uint8_t ledfixeds;	// How many LED in fixed LED
extern uint8_t ledfixedc;	// Fixed LED colour
extern uint8_t ledcylon;	// LED number start of cylon LEDs
extern uint8_t ledcylons;	// How many LED in cylon LED
extern uint8_t ledcylonc;	// cylon LED colour
extern uint8_t ledpwm;	// LED number for servo PWM status
extern uint8_t ledbutton[BUTTONS];	// LED number for button status
extern revk_gpio_t visorpwm;	// Visor servo PWM
extern int16_t visorclose;	// Angle visor close
extern int16_t visoropen;	// Angle visor open
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
extern char* topicha;	// MQTT Topic for homeassistant
#define	prefixapp	revk_settings_bits.prefixapp
#define	prefixhost	revk_settings_bits.prefixhost
#ifdef	CONFIG_REVK_BLINK_DEF
extern revk_gpio_t blink[3];	// R, G, B LED array (set all the same for WS2812 LED)
#endif
#define	dark	revk_settings_bits.dark
#ifdef  CONFIG_IDF_TARGET_ESP32S3
extern revk_gpio_t factorygpio;	// Factory reset GPIO (press 3 times)
#else
extern revk_gpio_t factorygpio;	// Factory reset GPIO (press 3 times)
#endif
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
extern revk_settings_blob_t* mqttcert[CONFIG_REVK_MQTT_CLIENTS];	// MQTT CA certificate
#endif
extern revk_settings_blob_t* clientkey;	// Client Key (OTA and MQTT TLS)
extern revk_settings_blob_t* clientcert;	// Client certificate (OTA and MQTT TLS)
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
 REVK_SETTINGS_SIGNED,
 REVK_SETTINGS_UNSIGNED,
 REVK_SETTINGS_BIT,
 REVK_SETTINGS_BLOB,
 REVK_SETTINGS_STRING,
 REVK_SETTINGS_OCTET,
};
#define	REVK_SETTINGS_HAS_ENUM
#define	REVK_SETTINGS_HAS_OLD
#define	REVK_SETTINGS_HAS_UNIT
#define	REVK_SETTINGS_HAS_COMMENT
#define	REVK_SETTINGS_HAS_GPIO
#define	REVK_SETTINGS_HAS_NUMERIC
#define	REVK_SETTINGS_HAS_SIGNED
#define	REVK_SETTINGS_HAS_UNSIGNED
#define	REVK_SETTINGS_HAS_BIT
#define	REVK_SETTINGS_HAS_BLOB
#define	REVK_SETTINGS_HAS_STRING
#define	REVK_SETTINGS_HAS_OCTET
typedef uint8_t revk_setting_bits_t[14];
typedef uint8_t revk_setting_group_t[2];
extern const char revk_settings_secret[];
