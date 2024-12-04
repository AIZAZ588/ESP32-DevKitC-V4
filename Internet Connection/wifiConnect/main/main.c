#include <stdio.h>
#include "connect.h"
#include "nvs_flash.h" /* To store all the data for wifi */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char* TAG = "wifi_connect";

void wifi_connect(void *params){
    
    esp_err_t err = wifi_connect_sta("Ai","123456789",1000);
    vTaskDelay(pdMS_TO_TICKS(10000));
    if(err){
        ESP_LOGI(TAG,"Failed to connect");
        vTaskDelete(NULL);
    }
    for(int n = 5; n < 0; n--){
        printf("disconnecting in %d sec\n",n);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    wifi_disconnect();
    vTaskDelete(NULL);
    
}

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    wifi_init();

    /* Create Task for wifi */
    xTaskCreate(wifi_connect,"wifi connect",1024*5,NULL,5,NULL);

}
