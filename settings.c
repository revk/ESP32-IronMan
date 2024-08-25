// Settings
// Generated from:-
// settings.def
// components/ESP32-RevK/settings.def

#include <stdint.h>
#include "sdkconfig.h"
#include "settings.h"
revk_settings_bits_t revk_settings_bits={0};
#define	str(s)	#s
#define	quote(s)	str(s)
revk_settings_t const revk_settings[]={
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="eye1",.comment="Left eye",.len=4,.ptr=&eye1,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="eye2",.comment="Right eye",.len=4,.ptr=&eye2,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="pwr",.comment="Visor servo power",.len=3,.ptr=&pwr,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="pwm",.comment="Visor service PWM",.len=3,.ptr=&pwm,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="button1",.comment="Activation button1",.len=7,.ptr=&button1,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="button2",.comment="Activation button2",.len=7,.ptr=&button2,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="rgb",.comment="RGB LED chain",.len=3,.ptr=&rgb,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.name="leds",.comment="Number of LEDs in chain",.len=4,.ptr=&leds,.size=sizeof(uint8_t)},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledeye1",.comment="LED number for eye 1",.group=1,.len=7,.dot=3,.ptr=&ledeye1,.size=sizeof(uint8_t)},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledeye2",.comment="LED number for eye 2",.group=1,.len=7,.dot=3,.ptr=&ledeye2,.size=sizeof(uint8_t)},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledpwr",.comment="LED number for servo PWR",.group=1,.len=6,.dot=3,.ptr=&ledpwr,.size=sizeof(uint8_t)},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledpwm",.comment="LED number for servo PWM",.group=1,.len=6,.dot=3,.ptr=&ledpwm,.size=sizeof(uint8_t)},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledbutton1",.comment="LED number for button1",.group=1,.len=10,.dot=3,.ptr=&ledbutton1,.size=sizeof(uint8_t)},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledbutton2",.comment="LED number for button2",.group=1,.len=10,.dot=3,.ptr=&ledbutton2,.size=sizeof(uint8_t)},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledarc",.comment="LED number start of arc ring",.group=1,.len=6,.dot=3,.ptr=&ledarc,.size=sizeof(uint8_t)},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledarcs",.comment="How many LED in arc ring",.group=1,.len=7,.dot=3,.ptr=&ledarcs,.size=sizeof(uint8_t)},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledpulse",.comment="LED number start of pulsing",.group=1,.len=8,.dot=3,.ptr=&ledpulse,.size=sizeof(uint8_t)},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledpulses",.comment="How many LED in pusling",.group=1,.len=9,.dot=3,.ptr=&ledpulses,.size=sizeof(uint8_t)},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledblue",.comment="LED number start of blue LEDs",.group=1,.len=7,.dot=3,.ptr=&ledblue,.size=sizeof(uint8_t)},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledblues",.comment="How many LED in blue LED",.group=1,.len=8,.dot=3,.ptr=&ledblues,.size=sizeof(uint8_t)},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledgreen",.comment="LED number start of green LEDs",.group=1,.len=8,.dot=3,.ptr=&ledgreen,.size=sizeof(uint8_t)},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledgreens",.comment="How many LED in green LED",.group=1,.len=9,.dot=3,.ptr=&ledgreens,.size=sizeof(uint8_t)},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledred",.comment="LED number start of red LEDs",.group=1,.len=6,.dot=3,.ptr=&ledred,.size=sizeof(uint8_t)},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledreds",.comment="How many LED in red LED",.group=1,.len=7,.dot=3,.ptr=&ledreds,.size=sizeof(uint8_t)},
 {.type=REVK_SETTINGS_UNSIGNED,.name="visorclose",.comment="Angle (degrees) visor close",.group=2,.len=10,.dot=5,.ptr=&visorclose,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="visoropen",.comment="Angle (degrees) visor open",.group=2,.len=9,.dot=5,.ptr=&visoropen,.size=sizeof(uint8_t),.live=1},
#ifdef	CONFIG_REVK_SETTINGS_PASSWORD
 {.type=REVK_SETTINGS_STRING,.name="password",.comment="Settings password (this is not sent securely so use with care on local networks you control)",.len=8,.ptr=&password,.malloc=1,.revk=1,.hide=1,.secret=1},
#endif
 {.type=REVK_SETTINGS_STRING,.name="hostname",.comment="Host name",.len=8,.ptr=&hostname,.malloc=1,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="appname",.comment="Application name",.len=7,.dq=1,.def=quote(CONFIG_REVK_APPNAME),.ptr=&appname,.malloc=1,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="otahost",.comment="OTA hostname",.group=3,.len=7,.dot=3,.dq=1,.def=quote(CONFIG_REVK_OTAHOST),.ptr=&otahost,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="otadays",.comment="OTA auto load (days)",.group=3,.len=7,.dot=3,.dq=1,.def=quote(CONFIG_REVK_OTADAYS),.ptr=&otadays,.size=sizeof(uint8_t),.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="otastart",.comment="OTA check after startup (min seconds)",.group=3,.len=8,.dot=3,.def="600",.ptr=&otastart,.size=sizeof(uint16_t),.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="otaauto",.comment="OTA auto upgrade",.group=3,.len=7,.dot=3,.def="1",.bit=REVK_SETTINGS_BITFIELD_otaauto,.revk=1,.hide=1,.live=1},
 {.type=REVK_SETTINGS_BIT,.name="otabeta",.comment="OTA from beta release",.group=3,.len=7,.dot=3,.bit=REVK_SETTINGS_BITFIELD_otabeta,.revk=1,.hide=1,.live=1},
 {.type=REVK_SETTINGS_BLOB,.name="otacert",.comment="OTA cert of otahost",.group=3,.len=7,.dot=3,.dq=1,.def=quote(CONFIG_REVK_OTACERT),.ptr=&otacert,.malloc=1,.revk=1,.base64=1},
 {.type=REVK_SETTINGS_STRING,.name="ntphost",.comment="NTP host",.len=7,.dq=1,.def=quote(CONFIG_REVK_NTPHOST),.ptr=&ntphost,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_STRING,.name="tz",.comment="Timezone (<a href='https://gist.github.com/alwynallan/24d96091655391107939' target=_blank>info</a>)",.len=2,.dq=1,.def=quote(CONFIG_REVK_TZ),.ptr=&tz,.malloc=1,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="watchdogtime",.comment="Watchdog (seconds)",.len=12,.dq=1,.def=quote(CONFIG_REVK_WATCHDOG),.ptr=&watchdogtime,.size=sizeof(uint32_t),.revk=1},
 {.type=REVK_SETTINGS_STRING,.name="topicgroup",.comment="MQTT Alternative hostname accepted for commands",.group=4,.len=10,.dot=5,.ptr=&topicgroup,.malloc=1,.revk=1,.array=2},
 {.type=REVK_SETTINGS_STRING,.name="topiccommand",.comment="MQTT Topic for commands",.group=4,.len=12,.dot=5,.def="command",.ptr=&topiccommand,.malloc=1,.revk=1,.old="prefixcommand"			},
 {.type=REVK_SETTINGS_STRING,.name="topicsetting",.comment="MQTT Topic for settings",.group=4,.len=12,.dot=5,.def="setting",.ptr=&topicsetting,.malloc=1,.revk=1,.old="prefixsetting"			},
 {.type=REVK_SETTINGS_STRING,.name="topicstate",.comment="MQTT Topic for state",.group=4,.len=10,.dot=5,.def="state",.ptr=&topicstate,.malloc=1,.revk=1,.old="prefixstate"			},
 {.type=REVK_SETTINGS_STRING,.name="topicevent",.comment="MQTT Topic for event",.group=4,.len=10,.dot=5,.def="event",.ptr=&topicevent,.malloc=1,.revk=1,.old="prefixevent"			},
 {.type=REVK_SETTINGS_STRING,.name="topicinfo",.comment="MQTT Topic for info",.group=4,.len=9,.dot=5,.def="info",.ptr=&topicinfo,.malloc=1,.revk=1,.old="prefixinfo"			},
 {.type=REVK_SETTINGS_STRING,.name="topicerror",.comment="MQTT Topic for error",.group=4,.len=10,.dot=5,.def="error",.ptr=&topicerror,.malloc=1,.revk=1,.old="prefixerror"			},
 {.type=REVK_SETTINGS_BIT,.name="prefixapp",.comment="MQTT use appname/ in front of hostname in topic",.group=5,.len=9,.dot=6,.dq=1,.def=quote(CONFIG_REVK_PREFIXAPP),.bit=REVK_SETTINGS_BITFIELD_prefixapp,.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="prefixhost",.comment="MQTT use (appname/)hostname/topic instead of topic/(appname/)hostname",.group=5,.len=10,.dot=6,.dq=1,.def=quote(CONFIG_REVK_PREFIXHOST),.bit=REVK_SETTINGS_BITFIELD_prefixhost,.revk=1},
#ifdef	CONFIG_REVK_BLINK_DEF
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="blink",.comment="LED array",.len=5,.dq=1,.def=quote(CONFIG_REVK_BLINK),.ptr=&blink,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1,.array=3},
#endif
 {.type=REVK_SETTINGS_BLOB,.name="clientkey",.comment="Client Key (OTA and MQTT TLS)",.group=6,.len=9,.dot=6,.ptr=&clientkey,.malloc=1,.revk=1,.base64=1,.hide=1},
 {.type=REVK_SETTINGS_BLOB,.name="clientcert",.comment="Client certificate (OTA and MQTT TLS)",.group=6,.len=10,.dot=6,.ptr=&clientcert,.malloc=1,.revk=1,.base64=1,.hide=1},
#ifdef  CONFIG_REVK_APMODE
#ifdef	CONFIG_REVK_APCONFIG
 {.type=REVK_SETTINGS_UNSIGNED,.name="apport",.comment="TCP port for config web pages on AP",.group=7,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APPORT),.ptr=&apport,.size=sizeof(uint16_t),.revk=1},
#endif
 {.type=REVK_SETTINGS_UNSIGNED,.name="aptime",.comment="Limit AP to time (seconds)",.group=7,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APTIME),.ptr=&aptime,.size=sizeof(uint32_t),.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="apwait",.comment="Wait off line before starting AP (seconds)",.group=7,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APWAIT),.ptr=&apwait,.size=sizeof(uint32_t),.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="apgpio",.comment="Start AP on GPIO",.group=7,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APGPIO),.ptr=&apgpio,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1},
#endif
#ifdef  CONFIG_REVK_MQTT
 {.type=REVK_SETTINGS_STRING,.name="mqtthost",.comment="MQTT hostname",.group=8,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MQTTHOST),.ptr=&mqtthost,.malloc=1,.revk=1,.array=CONFIG_REVK_MQTT_CLIENTS,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="mqttport",.comment="MQTT port",.group=8,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MQTTPORT),.ptr=&mqttport,.size=sizeof(uint16_t),.revk=1,.array=CONFIG_REVK_MQTT_CLIENTS,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="mqttuser",.comment="MQTT username",.group=8,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MQTTUSER),.ptr=&mqttuser,.malloc=1,.revk=1,.array=CONFIG_REVK_MQTT_CLIENTS,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="mqttpass",.comment="MQTT password",.group=8,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MQTTPASS),.ptr=&mqttpass,.malloc=1,.revk=1,.array=CONFIG_REVK_MQTT_CLIENTS,.secret=1,.hide=1},
 {.type=REVK_SETTINGS_BLOB,.name="mqttcert",.comment="MQTT certificate",.group=8,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MQTTCERT),.ptr=&mqttcert,.malloc=1,.revk=1,.array=CONFIG_REVK_MQTT_CLIENTS,.base64=1,.hide=1},
#endif
#if     defined(CONFIG_REVK_WIFI) || defined(CONFIG_REVK_MESH)
 {.type=REVK_SETTINGS_UNSIGNED,.name="wifireset",.comment="Restart if WiFi off for this long (seconds)",.group=9,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIRESET),.ptr=&wifireset,.size=sizeof(uint16_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="wifissid",.comment="WiFI SSID (name)",.group=9,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFISSID),.ptr=&wifissid,.malloc=1,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="wifipass",.comment="WiFi password",.group=9,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIPASS),.ptr=&wifipass,.malloc=1,.revk=1,.hide=1,.secret=1},
 {.type=REVK_SETTINGS_STRING,.name="wifiip",.comment="WiFi Fixed IP",.group=9,.len=6,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIIP),.ptr=&wifiip,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_STRING,.name="wifigw",.comment="WiFi Fixed gateway",.group=9,.len=6,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIGW),.ptr=&wifigw,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_STRING,.name="wifidns",.comment="WiFi fixed DNS",.group=9,.len=7,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIDNS),.ptr=&wifidns,.malloc=1,.revk=1,.array=3},
 {.type=REVK_SETTINGS_OCTET,.name="wifibssid",.comment="WiFI BSSID",.group=9,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIBSSID),.ptr=&wifibssid,.size=sizeof(uint8_t[6]),.revk=1,.hex=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="wifichan",.comment="WiFI channel",.group=9,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFICHAN),.ptr=&wifichan,.size=sizeof(uint8_t),.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="wifiuptime",.comment="WiFI turns off after this many seconds",.group=9,.len=10,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIUPTIME),.ptr=&wifiuptime,.size=sizeof(uint16_t),.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="wifips",.comment="WiFi power save",.group=9,.len=6,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIPS),.bit=REVK_SETTINGS_BITFIELD_wifips,.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="wifimaxps",.comment="WiFi power save (max)",.group=9,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIMAXPS),.bit=REVK_SETTINGS_BITFIELD_wifimaxps,.revk=1},
#endif
#ifndef	CONFIG_REVK_MESH
 {.type=REVK_SETTINGS_STRING,.name="apssid",.comment="AP mode SSID (name)",.group=7,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APSSID),.ptr=&apssid,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_STRING,.name="appass",.comment="AP mode password",.group=7,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APPASS),.ptr=&appass,.malloc=1,.revk=1,.secret=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="apmax",.comment="AP max clients",.group=7,.len=5,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APMAX),.ptr=&apmax,.size=sizeof(uint8_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="apip",.comment="AP mode block",.group=7,.len=4,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APIP),.ptr=&apip,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="aplr",.comment="AP LR mode",.group=7,.len=4,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APLR),.bit=REVK_SETTINGS_BITFIELD_aplr,.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="aphide",.comment="AP hide SSID",.group=7,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APHIDE),.bit=REVK_SETTINGS_BITFIELD_aphide,.revk=1},
#endif
#ifdef	CONFIG_REVK_MESH
 {.type=REVK_SETTINGS_STRING,.name="nodename",.comment="Mesh node name",.len=8,.ptr=&nodename,.malloc=1,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="meshreset",.comment="Reset if mesh off for this long (seconds)",.group=10,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHRESET),.ptr=&meshreset,.size=sizeof(uint16_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_OCTET,.name="meshid",.comment="Mesh ID (hex)",.group=10,.len=6,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHID),.ptr=&meshid,.size=sizeof(uint8_t[6]),.revk=1,.hex=1,.hide=1},
 {.type=REVK_SETTINGS_OCTET,.name="meshkey",.comment="Mesh key",.group=10,.len=7,.dot=4,.ptr=&meshkey,.size=sizeof(uint8_t[16]),.revk=1,.secret=1,.hex=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="meshwidth",.comment="Mesh width",.group=10,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHWIDTH),.ptr=&meshwidth,.size=sizeof(uint16_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="meshdepth",.comment="Mesh depth",.group=10,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHDEPTH),.ptr=&meshdepth,.size=sizeof(uint16_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="meshmax",.comment="Mesh max devices",.group=10,.len=7,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHMAX),.ptr=&meshmax,.size=sizeof(uint16_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="meshpass",.comment="Mesh AP password",.group=10,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHPASS),.ptr=&meshpass,.malloc=1,.revk=1,.secret=1,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="meshlr",.comment="Mesh use LR mode",.group=10,.len=6,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHLR),.bit=REVK_SETTINGS_BITFIELD_meshlr,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="meshroot",.comment="This is preferred mesh root",.group=10,.len=8,.dot=4,.bit=REVK_SETTINGS_BITFIELD_meshroot,.revk=1,.hide=1},
#endif
{0}};
#undef quote
#undef str
revk_gpio_t eye1={0};
revk_gpio_t eye2={0};
revk_gpio_t pwr={0};
revk_gpio_t pwm={0};
revk_gpio_t button1={0};
revk_gpio_t button2={0};
revk_gpio_t rgb={0};
uint8_t leds=0;
uint8_t ledeye1=0;
uint8_t ledeye2=0;
uint8_t ledpwr=0;
uint8_t ledpwm=0;
uint8_t ledbutton1=0;
uint8_t ledbutton2=0;
uint8_t ledarc=0;
uint8_t ledarcs=0;
uint8_t ledpulse=0;
uint8_t ledpulses=0;
uint8_t ledblue=0;
uint8_t ledblues=0;
uint8_t ledgreen=0;
uint8_t ledgreens=0;
uint8_t ledred=0;
uint8_t ledreds=0;
uint8_t visorclose=0;
uint8_t visoropen=0;
#ifdef	CONFIG_REVK_SETTINGS_PASSWORD
char* password=NULL;
#endif
char* hostname=NULL;
char* appname=NULL;
char* otahost=NULL;
uint8_t otadays=0;
uint16_t otastart=0;
revk_settings_blob_t* otacert=NULL;
char* ntphost=NULL;
char* tz=NULL;
uint32_t watchdogtime=0;
char* topicgroup[2]={0};
char* topiccommand=NULL;
char* topicsetting=NULL;
char* topicstate=NULL;
char* topicevent=NULL;
char* topicinfo=NULL;
char* topicerror=NULL;
#ifdef	CONFIG_REVK_BLINK_DEF
revk_gpio_t blink[3]={0};
#endif
revk_settings_blob_t* clientkey=NULL;
revk_settings_blob_t* clientcert=NULL;
#ifdef  CONFIG_REVK_APMODE
#ifdef	CONFIG_REVK_APCONFIG
uint16_t apport=0;
#endif
uint32_t aptime=0;
uint32_t apwait=0;
revk_gpio_t apgpio={0};
#endif
#ifdef  CONFIG_REVK_MQTT
char* mqtthost[CONFIG_REVK_MQTT_CLIENTS]={0};
uint16_t mqttport[CONFIG_REVK_MQTT_CLIENTS]={0};
char* mqttuser[CONFIG_REVK_MQTT_CLIENTS]={0};
char* mqttpass[CONFIG_REVK_MQTT_CLIENTS]={0};
revk_settings_blob_t* mqttcert[CONFIG_REVK_MQTT_CLIENTS]={0};
#endif
#if     defined(CONFIG_REVK_WIFI) || defined(CONFIG_REVK_MESH)
uint16_t wifireset=0;
char* wifissid=NULL;
char* wifipass=NULL;
char* wifiip=NULL;
char* wifigw=NULL;
char* wifidns[3]={0};
uint8_t wifibssid[6]={0};
uint8_t wifichan=0;
uint16_t wifiuptime=0;
#endif
#ifndef	CONFIG_REVK_MESH
char* apssid=NULL;
char* appass=NULL;
uint8_t apmax=0;
char* apip=NULL;
#endif
#ifdef	CONFIG_REVK_MESH
char* nodename=NULL;
uint16_t meshreset=0;
uint8_t meshid[6]={0};
uint8_t meshkey[16]={0};
uint16_t meshwidth=0;
uint16_t meshdepth=0;
uint16_t meshmax=0;
char* meshpass=NULL;
#endif
const char revk_settings_secret[]="✶✶✶✶✶✶✶✶";
