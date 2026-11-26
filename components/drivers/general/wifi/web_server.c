#include "esp_log.h"
#include "esp_http_server.h"
#include "web_server.h"

// Tag used for debug logging
static const char *TAG = "web_server";

static const char *html_page = R"raw(
<!DOCTYPE html>
<html>
<head>
    <title>ESP-IDF: ESP32 Web Server</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
    <h1>ESP-IDF: ESP32 Web Server</h1>
    <p>Hello from ESP32!</p>
</body>
</html>
)raw";



// HTTP GET handler for root "/"
static esp_err_t root_get_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, html_page, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}
// Register URI handler
static const httpd_uri_t uri_get = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = root_get_handler,
    .user_ctx  = NULL
};
// Start the HTTP server
httpd_handle_t start_web_server(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK) {
        ESP_LOGI(TAG, "HTTP server started on port %d", config.server_port);
        
        httpd_register_uri_handler(server, &uri_get);
        
        return server;
    }
    
    ESP_LOGE(TAG, "Failed to start HTTP server");
    return NULL;
}




// static const httpd_uri_t ws = {
//     .uri        = "/ws",
//     .method     = HTTP_GET,
//     .handler    = handler,           // Your WebSocket data handler
//     .user_ctx   = NULL,
//     .is_websocket = true,
//     .ws_pre_handshake_cb = ws_auth_handler // Set the pre-handshake callback
// };

// //Function for starting the webserver
// httpd_handle_t start_webserver(void)
// {
// // Generate default configuration
// httpd_config_t config = HTTPD_DEFAULT_CONFIG();

// // Empty handle to http_server
//      httpd_handle_t server = NULL;

// // Start the httpd server
// if (httpd_start(&server, &config) == ESP_OK) {
// // Register URI handlers
//          httpd_register_uri_handler(server, &uri_get);
//          httpd_register_uri_handler(server, &uri_post);
//      }
// // If server failed to start, handle will be NULL
// return server;
// }