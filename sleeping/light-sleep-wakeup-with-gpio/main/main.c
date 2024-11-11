#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* Topic related */
#include "esp_sleep.h"
#include "esp32/rom/uart.h"
#include "driver/rtc_io.h"

#define delayms(x) vTaskDelay(x/portTICK_PERIOD_MS)

#define INPUT_PIN 16

void app_main(void)
{
    /* Configure GPIO */
    gpio_set_direction(INPUT_PIN,GPIO_MODE_INPUT);
    gpio_pullup_en(INPUT_PIN);
    gpio_wakeup_enable(INPUT_PIN,GPIO_INTR_LOW_LEVEL); /* wake up on logic low */

    /* Sleeping setting */
    esp_sleep_enable_gpio_wakeup();

    for(;;){
        printf("Going into sleep\n");
        uart_tx_wait_idle(CONFIG_ESP_CONSOLE_UART_NUM); /* wait for uart to complete its transfer  */
        esp_light_sleep_start();

        if(esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_GPIO){
            printf("wakeup using gpio\n");
            printf("going into sleep after 2 sec\n");
            delayms(2*1000);
            uart_tx_wait_idle(CONFIG_ESP_CONSOLE_UART_NUM);
        }
    }

}
