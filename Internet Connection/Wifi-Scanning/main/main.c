#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

/* Topic specific */
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"

/* functions def */
/* wifi */
void wifiInit()
{
    ESP_ERROR_CHECK(nvs_flash_init());
    esp_netif_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* Initialize our wifi configuration */
    wifi_init_config_t wifi_config = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&wifi_config);

    /* wifi as Station or AP Mode */
    esp_wifi_set_mode(WIFI_MODE_STA);

    /* Start wifi */
    ESP_ERROR_CHECK(esp_wifi_start());
}

/* Scanning Config */
void Scan_config_start()
{
    wifi_scan_config_t scan_config = {
        /** zero because we don't want scan for any specific wifi channel  */
        .ssid = 0,    /**< SSID of AP */
        .bssid = 0,   /**< MAC address of AP */
        .channel = 0, /**< channel, scan the specific channel *show_hidden;  */

        /** Show Hidden Networks */
        .show_hidden = true};

    /** Start Scanning */
    /** start with block execution of other program */
    ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, true));
}

#define MAX_APs 10

void app_main(void)
{

    wifiInit();
    Scan_config_start();

    wifi_ap_record_t wifi_rec[MAX_APs];
    uint16_t maxRec = MAX_APs;

    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&maxRec, wifi_rec));

    printf("Found %d access points:\n", maxRec);
    printf("\n");
    printf("               SSID              | Channel | RSSI  \n");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < maxRec; i++)
        printf("%32s | %7d | %4d \n", (char *)wifi_rec[i].ssid, wifi_rec[i].primary, wifi_rec[i].rssi);
    printf("----------------------------------------------------------------\n");
}
