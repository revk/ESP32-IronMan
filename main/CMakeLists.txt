set (COMPONENT_SRCS "IronMan.c" "settings.c" "ble_server.c" "ble_client.c")
set (COMPONENT_REQUIRES "ESP32-RevK" "driver" "esp_driver_sdmmc" "fatfs" "led_strip" "bt")
register_component ()
