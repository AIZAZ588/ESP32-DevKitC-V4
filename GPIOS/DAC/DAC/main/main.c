#include <stdio.h>
#include "driver/gpio.h"
#include "driver/dac.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define TAG "DAC"

void app_main(void) {
    ESP_LOGD(TAG,"DAC Output Test");

    // Enable DAC channel
    ESP_LOGD(TAG,"DAC Enable : %d", dac_output_enable(DAC_CHANNEL_1));

    // Set output voltage to maximum
    ESP_LOGD(TAG,"DAC Set volage level : %d", dac_output_voltage(DAC_CHANNEL_1, 200));


    // Wait to observe the output
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));  // Delay for 1 second
    }
}
