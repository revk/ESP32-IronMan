// Settings
// Generated from:-
// main/settings.def
// components/ESP32-RevK/settings.def

#include <stdint.h>
#include "sdkconfig.h"
#include "settings.h"
revk_settings_bits_t revk_settings_bits={0};
#define	str(s)	#s
#define	quote(s)	str(s)
revk_settings_t const revk_settings[]={
#define	STRIPS	3	// ESP32S3 only has 4 channels and one is for on board LED
#define	BUTTONS	2
 {.type=REVK_SETTINGS_UNSIGNED,.isenum=1,.name="ironman",.comment="What part",.len=7,.def="1",.ptr=&ironman,.size=sizeof(uint8_t),.enums="Suit,Helmet,Left Glove,Right Glove"	},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="button",.comment="Activation buttons",.len=6,.def="-12,-13",.ptr=&button,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.array=BUTTONS},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="stripgpio",.comment="GPIOs for LED string",.group=1,.len=9,.dot=5,.def="6,7,41",.ptr=&stripgpio,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.array=STRIPS,.old="rgb"		},
 {.type=REVK_SETTINGS_UNSIGNED,.name="stripcount",.comment="How many LEDs in string",.group=1,.len=10,.dot=5,.def="12",.ptr=&stripcount,.size=sizeof(uint16_t),.array=STRIPS,.old="leds"	},
 {.type=REVK_SETTINGS_UNSIGNED,.isenum=1,.name="striptype",.comment="Type of LED string",.group=1,.len=9,.dot=5,.ptr=&striptype,.size=sizeof(uint8_t),.array=STRIPS,.enums="WS2812 GRB,WS2812 GBR,WS2812 RGB,WS2812 RBG,WS2812 BGR,WS2812 BRG,WS2812 GRBW,WS2812 GBRW,WS2812 RGBW,WS2812 RBGW,WS2812 BGRW,WS2812 BRGW,SK7812 GRB,SK7812 GBR,SK7812 RGB,SK7812 RBG,SK7812 BGR,SK7812 BRG,SK7812 GRBW,SK7812 GBRW,SK7812 RGBW,SK7812 RBGW,SK7812 BGRW,SK7812 BRGW" },
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="sddat2",.comment="MicroSD DAT2",.group=2,.len=6,.dot=2,.def="38",.ptr=&sddat2,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="sddat3",.comment="MicroSD DAT3",.group=2,.len=6,.dot=2,.def="37",.ptr=&sddat3,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.old="sdss"	},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="sdcmd",.comment="MicroSD CMD",.group=2,.len=5,.dot=2,.def="36",.ptr=&sdcmd,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.old="sdmosi"	},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="sdclk",.comment="MicroSD CLK",.group=2,.len=5,.dot=2,.def="35",.ptr=&sdclk,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.old="sdsck"	},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="sddat0",.comment="MicroSD DAT0",.group=2,.len=6,.dot=2,.def="34",.ptr=&sddat0,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.old="sdmiso"	},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="sddat1",.comment="MicroSD DAT1",.group=2,.len=6,.dot=2,.def="33",.ptr=&sddat1,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="sdcd",.comment="MicroSD CD",.group=2,.len=4,.dot=2,.def="-47",.ptr=&sdcd,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="micdata",.comment="Microphone Data / SD",.group=3,.len=7,.dot=3,.def="44",.ptr=&micdata,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="micclock",.comment="Microphone Clock / SCK",.group=3,.len=8,.dot=3,.def="43",.ptr=&micclock,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="micws",.comment="Microphone WS (not set for PDM)",.group=3,.len=5,.dot=3,.def="46",.ptr=&micws,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="spkpwr",.comment="Speaker power on",.group=4,.len=6,.dot=3,.def="4",.ptr=&spkpwr,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="spklrc",.comment="Speaker LR clock",.group=4,.len=6,.dot=3,.def="1",.ptr=&spklrc,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="spkbclk",.comment="Speaker Bit clock",.group=4,.len=7,.dot=3,.def="2",.ptr=&spkbclk,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="spkdata",.comment="Speaker Data",.group=4,.len=7,.dot=3,.def="3",.ptr=&spkdata,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="usb",.comment="USB connected",.len=3,.ptr=&usb,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="chg",.comment="Charge indicator",.len=3,.ptr=&chg,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledeye1",.comment="LED number for eye 1",.group=5,.len=7,.dot=3,.ptr=&ledeye1,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledeye2",.comment="LED number for eye 2",.group=5,.len=7,.dot=3,.ptr=&ledeye2,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledeyes",.comment="How many LEDs in eye",.group=5,.len=7,.dot=3,.def="1",.ptr=&ledeyes,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.isenum=1,.name="ledeyec",.comment="Eye LED colour",.group=5,.len=7,.dot=3,.def="6",.ptr=&ledeyec,.size=sizeof(uint8_t),.live=1,.enums="Black,Red,Green,Yellow,Blue,Magenta,Cyan,White,W,W+Red,W+Green,W+Yellow,W+Blue,W+Magenta,W+Cyan,W+White"		},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledarc",.comment="LED number start of arc ring",.group=5,.len=6,.dot=3,.ptr=&ledarc,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledarcs",.comment="How many LED in arc ring",.group=5,.len=7,.dot=3,.ptr=&ledarcs,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.isenum=1,.name="ledarcc1",.comment="Arc LED colour (bright)",.group=5,.len=8,.dot=3,.def="9",.ptr=&ledarcc1,.size=sizeof(uint8_t),.live=1,.enums="Black,Red,Green,Yellow,Blue,Magenta,Cyan,White,W,W+Red,W+Green,W+Yellow,W+Blue,W+Magenta,W+Cyan,W+White"		},
 {.type=REVK_SETTINGS_UNSIGNED,.isenum=1,.name="ledarcc2",.comment="Arc LED colour (dim)",.group=5,.len=8,.dot=3,.def="8",.ptr=&ledarcc2,.size=sizeof(uint8_t),.live=1,.enums="Black,Red,Green,Yellow,Blue,Magenta,Cyan,White,W,W+Red,W+Green,W+Yellow,W+Blue,W+Magenta,W+Cyan,W+White"		},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledpulse",.comment="LED number start of pulsing",.group=5,.len=8,.dot=3,.ptr=&ledpulse,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledpulses",.comment="How many LED in pulsing",.group=5,.len=9,.dot=3,.ptr=&ledpulses,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.isenum=1,.name="ledpulsec",.comment="Pulse LED colour",.group=5,.len=9,.dot=3,.def="1",.ptr=&ledpulsec,.size=sizeof(uint8_t),.live=1,.enums="Black,Red,Green,Yellow,Blue,Magenta,Cyan,White,W,W+Red,W+Green,W+Yellow,W+Blue,W+Magenta,W+Cyan,W+White"		},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledglove",.comment="LED number start of glove",.group=5,.len=8,.dot=3,.ptr=&ledglove,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledgloves",.comment="How many LED in glove",.group=5,.len=9,.dot=3,.ptr=&ledgloves,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.isenum=1,.name="ledglovec",.comment="Glove LED colour",.group=5,.len=9,.dot=3,.def="7",.ptr=&ledglovec,.size=sizeof(uint8_t),.live=1,.enums="Black,Red,Green,Yellow,Blue,Magenta,Cyan,White,W,W+Red,W+Green,W+Yellow,W+Blue,W+Magenta,W+Cyan,W+White"		},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledfixed",.comment="LED number start of fixed LEDs",.group=5,.len=8,.dot=3,.ptr=&ledfixed,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledfixeds",.comment="How many LED in fixed LED",.group=5,.len=9,.dot=3,.ptr=&ledfixeds,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.isenum=1,.name="ledfixedc",.comment="Fixed LED colour",.group=5,.len=9,.dot=3,.def="6",.ptr=&ledfixedc,.size=sizeof(uint8_t),.live=1,.enums="Black,Red,Green,Yellow,Blue,Magenta,Cyan,White,W,W+Red,W+Green,W+Yellow,W+Blue,W+Magenta,W+Cyan,W+White"		},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledcylon",.comment="LED number start of cylon LEDs",.group=5,.len=8,.dot=3,.ptr=&ledcylon,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledcylons",.comment="How many LED in cylon LED",.group=5,.len=9,.dot=3,.ptr=&ledcylons,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.isenum=1,.name="ledcylonc",.comment="cylon LED colour",.group=5,.len=9,.dot=3,.def="1",.ptr=&ledcylonc,.size=sizeof(uint8_t),.live=1,.enums="Black,Red,Green,Yellow,Blue,Magenta,Cyan,White,W,W+Red,W+Green,W+Yellow,W+Blue,W+Magenta,W+Cyan,W+White"		},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledspin",.comment="LED number start of spin LEDs",.group=5,.len=7,.dot=3,.ptr=&ledspin,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledspins",.comment="How many LED in spin LED",.group=5,.len=8,.dot=3,.ptr=&ledspins,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.isenum=1,.name="ledspinc",.comment="spin LED colour",.group=5,.len=8,.dot=3,.def="1",.ptr=&ledspinc,.size=sizeof(uint8_t),.live=1,.enums="Black,Red,Green,Yellow,Blue,Magenta,Cyan,White,W,W+Red,W+Green,W+Yellow,W+Blue,W+Magenta,W+Cyan,W+White"		},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledpwm",.comment="LED number for servo PWM status",.group=5,.len=6,.dot=3,.ptr=&ledpwm,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="ledbutton",.comment="LED number for button status",.group=5,.len=9,.dot=3,.ptr=&ledbutton,.size=sizeof(uint8_t),.live=1,.array=BUTTONS},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="visorpwm",.comment="Visor servo PWM",.group=6,.len=8,.dot=5,.def="42",.ptr=&visorpwm,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.old="pwm"		},
 {.type=REVK_SETTINGS_SIGNED,.name="visorclose",.comment="Angle visor close",.group=6,.len=10,.dot=5,.def="0",.ptr=&visorclose,.size=sizeof(int16_t),.live=1,.unit="°"	},
 {.type=REVK_SETTINGS_SIGNED,.name="visoropen",.comment="Angle visor open",.group=6,.len=9,.dot=5,.def="130",.ptr=&visoropen,.size=sizeof(int16_t),.live=1,.unit="°"	},
#ifdef	CONFIG_REVK_SETTINGS_PASSWORD
 {.type=REVK_SETTINGS_STRING,.name="password",.comment="Settings password (this is not sent securely so use with care on local networks you control)",.len=8,.ptr=&password,.malloc=1,.revk=1,.hide=1,.secret=1},
#endif
 {.type=REVK_SETTINGS_STRING,.name="hostname",.comment="Host name",.len=8,.ptr=&hostname,.malloc=1,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="appname",.comment="Application name",.len=7,.dq=1,.def=quote(CONFIG_REVK_APPNAME),.ptr=&appname,.malloc=1,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="otahost",.comment="OTA hostname",.group=7,.len=7,.dot=3,.dq=1,.def=quote(CONFIG_REVK_OTAHOST),.ptr=&otahost,.malloc=1,.revk=1,.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="otadays",.comment="OTA auto load (days)",.group=7,.len=7,.dot=3,.dq=1,.def=quote(CONFIG_REVK_OTADAYS),.ptr=&otadays,.size=sizeof(uint8_t),.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="otastart",.comment="OTA check after startup (min seconds)",.group=7,.len=8,.dot=3,.def="600",.ptr=&otastart,.size=sizeof(uint16_t),.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="otaauto",.comment="OTA auto upgrade",.group=7,.len=7,.dot=3,.def="1",.bit=REVK_SETTINGS_BITFIELD_otaauto,.revk=1,.hide=1,.live=1},
#ifdef	CONFIG_REVK_WEB_BETA
 {.type=REVK_SETTINGS_BIT,.name="otabeta",.comment="OTA from beta release",.group=7,.len=7,.dot=3,.bit=REVK_SETTINGS_BITFIELD_otabeta,.revk=1,.hide=1,.live=1},
#endif
 {.type=REVK_SETTINGS_BLOB,.name="otacert",.comment="OTA cert of otahost",.group=7,.len=7,.dot=3,.dq=1,.def=quote(CONFIG_REVK_OTACERT),.ptr=&otacert,.malloc=1,.revk=1,.base64=1},
 {.type=REVK_SETTINGS_BIT,.name="dark",.comment="Default LED off",.len=4,.bit=REVK_SETTINGS_BITFIELD_dark,.revk=1,.live=1},
 {.type=REVK_SETTINGS_STRING,.name="ntphost",.comment="NTP host",.len=7,.dq=1,.def=quote(CONFIG_REVK_NTPHOST),.ptr=&ntphost,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_STRING,.name="tz",.comment="Timezone (<a href='https://gist.github.com/alwynallan/24d96091655391107939' target=_blank>info</a>)",.len=2,.dq=1,.def=quote(CONFIG_REVK_TZ),.ptr=&tz,.malloc=1,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="watchdogtime",.comment="Watchdog (seconds)",.len=12,.dq=1,.def=quote(CONFIG_REVK_WATCHDOG),.ptr=&watchdogtime,.size=sizeof(uint32_t),.revk=1},
#ifdef  CONFIG_IDF_TARGET_ESP32S3
 {.type=REVK_SETTINGS_UNSIGNED,.name="usbuptime",.comment="USB  turns off after this many seconds",.len=9,.dq=1,.def=quote(CONFIG_REVK_USBUPTIME),.ptr=&usbuptime,.size=sizeof(uint16_t),.revk=1},
#endif
#ifdef  CONFIG_IDF_TARGET_ESP32S3
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="factorygpio",.comment="Factory reset GPIO (press 3 times)",.len=11,.def="-21",.ptr=&factorygpio,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1},
#else
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="factorygpio",.comment="Factory reset GPIO (press 3 times)",.len=11,.ptr=&factorygpio,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1},
#endif
 {.type=REVK_SETTINGS_STRING,.name="topicgroup",.comment="MQTT Alternative hostname accepted for commands",.group=8,.len=10,.dot=5,.ptr=&topicgroup,.malloc=1,.revk=1,.array=2},
 {.type=REVK_SETTINGS_STRING,.name="topiccommand",.comment="MQTT Topic for commands",.group=8,.len=12,.dot=5,.def="command",.ptr=&topiccommand,.malloc=1,.revk=1,.old="prefixcommand"			},
 {.type=REVK_SETTINGS_STRING,.name="topicsetting",.comment="MQTT Topic for settings",.group=8,.len=12,.dot=5,.def="setting",.ptr=&topicsetting,.malloc=1,.revk=1,.old="prefixsetting"			},
 {.type=REVK_SETTINGS_STRING,.name="topicstate",.comment="MQTT Topic for state",.group=8,.len=10,.dot=5,.def="state",.ptr=&topicstate,.malloc=1,.revk=1,.old="prefixstate"			},
 {.type=REVK_SETTINGS_STRING,.name="topicevent",.comment="MQTT Topic for event",.group=8,.len=10,.dot=5,.def="event",.ptr=&topicevent,.malloc=1,.revk=1,.old="prefixevent"			},
 {.type=REVK_SETTINGS_STRING,.name="topicinfo",.comment="MQTT Topic for info",.group=8,.len=9,.dot=5,.def="info",.ptr=&topicinfo,.malloc=1,.revk=1,.old="prefixinfo"			},
 {.type=REVK_SETTINGS_STRING,.name="topicerror",.comment="MQTT Topic for error",.group=8,.len=10,.dot=5,.def="error",.ptr=&topicerror,.malloc=1,.revk=1,.old="prefixerror"			},
 {.type=REVK_SETTINGS_STRING,.name="topicha",.comment="MQTT Topic for homeassistant",.group=8,.len=7,.dot=5,.def="homeassistant",.ptr=&topicha,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="prefixapp",.comment="MQTT use appname/ in front of hostname in topic",.group=9,.len=9,.dot=6,.dq=1,.def=quote(CONFIG_REVK_PREFIXAPP),.bit=REVK_SETTINGS_BITFIELD_prefixapp,.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="prefixhost",.comment="MQTT use (appname/)hostname/topic instead of topic/(appname/)hostname",.group=9,.len=10,.dot=6,.dq=1,.def=quote(CONFIG_REVK_PREFIXHOST),.bit=REVK_SETTINGS_BITFIELD_prefixhost,.revk=1},
#ifdef	CONFIG_REVK_BLINK_DEF
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="blink",.comment="R, G, B LED array (set all the same for WS2812 LED)",.len=5,.dq=1,.def=quote(CONFIG_REVK_BLINK),.ptr=&blink,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1,.array=3},
#endif
#ifdef  CONFIG_REVK_APMODE
#ifdef	CONFIG_REVK_APCONFIG
 {.type=REVK_SETTINGS_UNSIGNED,.name="apport",.comment="TCP port for config web pages on AP",.group=10,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APPORT),.ptr=&apport,.size=sizeof(uint16_t),.revk=1},
#endif
 {.type=REVK_SETTINGS_UNSIGNED,.name="aptime",.comment="Limit AP to time (seconds)",.group=10,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APTIME),.ptr=&aptime,.size=sizeof(uint32_t),.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="apwait",.comment="Wait off line before starting AP (seconds)",.group=10,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APWAIT),.ptr=&apwait,.size=sizeof(uint32_t),.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="apgpio",.comment="Start AP on GPIO",.group=10,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APGPIO),.ptr=&apgpio,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1},
#endif
#ifdef  CONFIG_REVK_MQTT
 {.type=REVK_SETTINGS_STRING,.name="mqtthost",.comment="MQTT hostname",.group=11,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MQTTHOST),.ptr=&mqtthost,.malloc=1,.revk=1,.array=CONFIG_REVK_MQTT_CLIENTS,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="mqttport",.comment="MQTT port",.group=11,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MQTTPORT),.ptr=&mqttport,.size=sizeof(uint16_t),.revk=1,.array=CONFIG_REVK_MQTT_CLIENTS,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="mqttuser",.comment="MQTT username",.group=11,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MQTTUSER),.ptr=&mqttuser,.malloc=1,.revk=1,.array=CONFIG_REVK_MQTT_CLIENTS,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="mqttpass",.comment="MQTT password",.group=11,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MQTTPASS),.ptr=&mqttpass,.malloc=1,.revk=1,.array=CONFIG_REVK_MQTT_CLIENTS,.secret=1,.hide=1},
 {.type=REVK_SETTINGS_BLOB,.name="mqttcert",.comment="MQTT CA certificate",.group=11,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MQTTCERT),.ptr=&mqttcert,.malloc=1,.revk=1,.array=CONFIG_REVK_MQTT_CLIENTS,.base64=1},
#endif
 {.type=REVK_SETTINGS_BLOB,.name="clientkey",.comment="Client Key (OTA and MQTT TLS)",.group=12,.len=9,.dot=6,.ptr=&clientkey,.malloc=1,.revk=1,.base64=1},
 {.type=REVK_SETTINGS_BLOB,.name="clientcert",.comment="Client certificate (OTA and MQTT TLS)",.group=12,.len=10,.dot=6,.ptr=&clientcert,.malloc=1,.revk=1,.base64=1},
#if     defined(CONFIG_REVK_WIFI) || defined(CONFIG_REVK_MESH)
 {.type=REVK_SETTINGS_UNSIGNED,.name="wifireset",.comment="Restart if WiFi off for this long (seconds)",.group=13,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIRESET),.ptr=&wifireset,.size=sizeof(uint16_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="wifissid",.comment="WiFI SSID (name)",.group=13,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFISSID),.ptr=&wifissid,.malloc=1,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="wifipass",.comment="WiFi password",.group=13,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIPASS),.ptr=&wifipass,.malloc=1,.revk=1,.hide=1,.secret=1},
 {.type=REVK_SETTINGS_STRING,.name="wifiip",.comment="WiFi Fixed IP",.group=13,.len=6,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIIP),.ptr=&wifiip,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_STRING,.name="wifigw",.comment="WiFi Fixed gateway",.group=13,.len=6,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIGW),.ptr=&wifigw,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_STRING,.name="wifidns",.comment="WiFi fixed DNS",.group=13,.len=7,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIDNS),.ptr=&wifidns,.malloc=1,.revk=1,.array=3},
 {.type=REVK_SETTINGS_OCTET,.name="wifibssid",.comment="WiFI BSSID",.group=13,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIBSSID),.ptr=&wifibssid,.size=sizeof(uint8_t[6]),.revk=1,.hex=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="wifichan",.comment="WiFI channel",.group=13,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFICHAN),.ptr=&wifichan,.size=sizeof(uint8_t),.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="wifiuptime",.comment="WiFI turns off after this many seconds",.group=13,.len=10,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIUPTIME),.ptr=&wifiuptime,.size=sizeof(uint16_t),.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="wifips",.comment="WiFi power save",.group=13,.len=6,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIPS),.bit=REVK_SETTINGS_BITFIELD_wifips,.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="wifimaxps",.comment="WiFi power save (max)",.group=13,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIMAXPS),.bit=REVK_SETTINGS_BITFIELD_wifimaxps,.revk=1},
#endif
#ifndef	CONFIG_REVK_MESH
 {.type=REVK_SETTINGS_STRING,.name="apssid",.comment="AP mode SSID (name)",.group=10,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APSSID),.ptr=&apssid,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_STRING,.name="appass",.comment="AP mode password",.group=10,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APPASS),.ptr=&appass,.malloc=1,.revk=1,.secret=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="apmax",.comment="AP max clients",.group=10,.len=5,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APMAX),.ptr=&apmax,.size=sizeof(uint8_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="apip",.comment="AP mode block",.group=10,.len=4,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APIP),.ptr=&apip,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="aplr",.comment="AP LR mode",.group=10,.len=4,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APLR),.bit=REVK_SETTINGS_BITFIELD_aplr,.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="aphide",.comment="AP hide SSID",.group=10,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APHIDE),.bit=REVK_SETTINGS_BITFIELD_aphide,.revk=1},
#endif
#ifdef	CONFIG_REVK_MESH
 {.type=REVK_SETTINGS_STRING,.name="nodename",.comment="Mesh node name",.len=8,.ptr=&nodename,.malloc=1,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="meshreset",.comment="Reset if mesh off for this long (seconds)",.group=14,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHRESET),.ptr=&meshreset,.size=sizeof(uint16_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_OCTET,.name="meshid",.comment="Mesh ID (hex)",.group=14,.len=6,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHID),.ptr=&meshid,.size=sizeof(uint8_t[6]),.revk=1,.hex=1,.hide=1},
 {.type=REVK_SETTINGS_OCTET,.name="meshkey",.comment="Mesh key",.group=14,.len=7,.dot=4,.ptr=&meshkey,.size=sizeof(uint8_t[16]),.revk=1,.secret=1,.hex=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="meshwidth",.comment="Mesh width",.group=14,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHWIDTH),.ptr=&meshwidth,.size=sizeof(uint16_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="meshdepth",.comment="Mesh depth",.group=14,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHDEPTH),.ptr=&meshdepth,.size=sizeof(uint16_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="meshmax",.comment="Mesh max devices",.group=14,.len=7,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHMAX),.ptr=&meshmax,.size=sizeof(uint16_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="meshpass",.comment="Mesh AP password",.group=14,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHPASS),.ptr=&meshpass,.malloc=1,.revk=1,.secret=1,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="meshlr",.comment="Mesh use LR mode",.group=14,.len=6,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHLR),.bit=REVK_SETTINGS_BITFIELD_meshlr,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="meshroot",.comment="This is preferred mesh root",.group=14,.len=8,.dot=4,.bit=REVK_SETTINGS_BITFIELD_meshroot,.revk=1,.hide=1},
#endif
{0}};
#undef quote
#undef str
#define	STRIPS	3	// ESP32S3 only has 4 channels and one is for on board LED
#define	BUTTONS	2
uint8_t ironman=0;
revk_gpio_t button[BUTTONS]={0};
revk_gpio_t stripgpio[STRIPS]={0};
uint16_t stripcount[STRIPS]={0};
uint8_t striptype[STRIPS]={0};
revk_gpio_t sddat2={0};
revk_gpio_t sddat3={0};
revk_gpio_t sdcmd={0};
revk_gpio_t sdclk={0};
revk_gpio_t sddat0={0};
revk_gpio_t sddat1={0};
revk_gpio_t sdcd={0};
revk_gpio_t micdata={0};
revk_gpio_t micclock={0};
revk_gpio_t micws={0};
revk_gpio_t spkpwr={0};
revk_gpio_t spklrc={0};
revk_gpio_t spkbclk={0};
revk_gpio_t spkdata={0};
revk_gpio_t usb={0};
revk_gpio_t chg={0};
uint8_t ledeye1=0;
uint8_t ledeye2=0;
uint8_t ledeyes=0;
uint8_t ledeyec=0;
uint8_t ledarc=0;
uint8_t ledarcs=0;
uint8_t ledarcc1=0;
uint8_t ledarcc2=0;
uint8_t ledpulse=0;
uint8_t ledpulses=0;
uint8_t ledpulsec=0;
uint8_t ledglove=0;
uint8_t ledgloves=0;
uint8_t ledglovec=0;
uint8_t ledfixed=0;
uint8_t ledfixeds=0;
uint8_t ledfixedc=0;
uint8_t ledcylon=0;
uint8_t ledcylons=0;
uint8_t ledcylonc=0;
uint8_t ledspin=0;
uint8_t ledspins=0;
uint8_t ledspinc=0;
uint8_t ledpwm=0;
uint8_t ledbutton[BUTTONS]={0};
revk_gpio_t visorpwm={0};
int16_t visorclose=0;
int16_t visoropen=0;
#ifdef	CONFIG_REVK_SETTINGS_PASSWORD
char* password=NULL;
#endif
char* hostname=NULL;
char* appname=NULL;
char* otahost=NULL;
uint8_t otadays=0;
uint16_t otastart=0;
#ifdef	CONFIG_REVK_WEB_BETA
#endif
revk_settings_blob_t* otacert=NULL;
char* ntphost=NULL;
char* tz=NULL;
uint32_t watchdogtime=0;
#ifdef  CONFIG_IDF_TARGET_ESP32S3
uint16_t usbuptime=0;
#endif
#ifdef  CONFIG_IDF_TARGET_ESP32S3
revk_gpio_t factorygpio={0};
#else
revk_gpio_t factorygpio={0};
#endif
char* topicgroup[2]={0};
char* topiccommand=NULL;
char* topicsetting=NULL;
char* topicstate=NULL;
char* topicevent=NULL;
char* topicinfo=NULL;
char* topicerror=NULL;
char* topicha=NULL;
#ifdef	CONFIG_REVK_BLINK_DEF
revk_gpio_t blink[3]={0};
#endif
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
revk_settings_blob_t* clientkey=NULL;
revk_settings_blob_t* clientcert=NULL;
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
