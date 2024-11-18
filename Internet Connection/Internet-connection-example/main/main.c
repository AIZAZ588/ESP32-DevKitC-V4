#include <stdio.h>
#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_http_client.h"
#include "esp_netif.h"
#include "include/protocol_examples_common.h"

/* to grep something from internet  */
esp_err_t clientEvent(esp_http_client_event_t *evt){
    switch (evt->event_id)
    {
    case HTTP_EVENT_ON_DATA:
        printf("%.*s\n", evt->data_len,(char*)evt->data);
        break;
    default:
    break;
    }
    return ESP_OK;
}

void app_main(void)
{
    /* to make sure nvs is properly initalized */
    nvs_flash_init();

    /* initialize tcp ip Adaptor  */
    // tcpip_adapter_init();
    esp_netif_init();

    /* event loop requires for internet connection */
    esp_event_loop_create_default();

    /* from protocol example .h*/
    example_connect();

    /* to grep something from internet  */
    /* creating confutation */
    esp_http_client_config_t clientConfig = {
        .url = "http://google.com",
        .event_handler = clientEvent
    };

    /* pass config to handler */
    esp_http_client_handle_t clinet  =esp_http_client_init(&clientConfig);
    esp_http_client_perform(clinet);
    esp_http_client_cleanup(clinet);


}
