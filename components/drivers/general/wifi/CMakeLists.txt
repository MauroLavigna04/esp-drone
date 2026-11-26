idf_component_register(
    SRCS
        "wifi_esp32.c"
        "web_server.c"
    INCLUDE_DIRS "." "include"
    REQUIRES
        crazyflie
        platform
        config
        esp_wifi
        esp_http_server
)