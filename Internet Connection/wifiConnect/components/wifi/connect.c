/**
 *  @brief : https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/wifi.html
 *
 */
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_log.h"

const static char *TAG = "WIFI";

void event_hander(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    switch (event_id)
    {
    case WIFI_EVENT_STA_START:
        ESP_LOGI(TAG, "connecting...");
        /* When this event happens, then its is known to us this wifi sta mode has'bn started and
            now we can connect to access point using our connect function
         */
        esp_wifi_connect();
        break;
    case WIFI_EVENT_STA_CONNECTED:
        ESP_LOGI(TAG, "connected!");
        break;
    case WIFI_EVENT_STA_DISCONNECTED:
        ESP_LOGI(TAG, "disconnected!");
        break;
    case IP_EVENT_STA_GOT_IP:
        ESP_LOGI(TAG, "GOT IP ");
        break;
    default:
        break;
    }
}

void wifi_init(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&wifi_init_config);

    /* Register events using event loop */
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, event_hander, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, event_hander, NULL));

    /* Set Storage for wifi */
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
}
esp_err_t wifi_connect_sta(const char *ssid, const char *pass, int timeout)
{
    /* create esp network interface */
    esp_netif_create_default_wifi_sta();

    /* Config wifi */
    wifi_config_t wifi_config;
    memset(&wifi_config,0,sizeof(wifi_config_t)); /* clear memory */
    strncpy((char*)wifi_config.sta.ssid,ssid, sizeof(wifi_config.sta.ssid)-1);         /* To make sure we didnot cross buffer limit of wifi_config */
    strncpy((char*)wifi_config.sta.password,pass, sizeof(wifi_config.sta.password)-1); /* To make sure we didnot cross buffer limit of wifi_config */
    
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(ESP_IF_WIFI_STA,&wifi_config);

    /* Start wifi */
    esp_wifi_start();

    return ESP_OK;
}
void wifi_connect_ap(const char *ssid, const char *pass)
{
}

void wifi_disconnect(void)
{
    esp_wifi_disconnect();
    esp_wifi_stop();
}