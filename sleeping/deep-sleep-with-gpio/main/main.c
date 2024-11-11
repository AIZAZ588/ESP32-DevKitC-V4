/***
 * Key points:
 *  Only RTC GPIOs can wake up the ESP32 from deep sleep because deep sleep mode powers down most of the chip, 
 *  including the main CPU and peripheral modules, 
 *  leaving only the RTC (Real-Time Clock) domain active. 
 *  The RTC domain is capable of maintaining a small number of GPIOs that can be used to trigger wakeup events.
 *  
 * @functions
 *  esp_sleep_enable_ext0_wakeup() -> This function configures a single RTC GPIO as the wakeup source.
 *  esp_sleep_enable_ext1_wakeup() -> This function allows multiple RTC GPIOs to be configured as wakeup sources.
 * 
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* Topic related */
#include "driver/gpio.h"
#include "esp_sleep.h"
#include "driver/rtc_io.h"

#define wakeupButton GPIO_NUM_4

#define GPIO_USE_FOR_DEEP_SLEEP_WAKEUP

// #define GPIO_USE_FOR_GOING_INTO_DEEP_SLEEP

void app_main(void)
{

#if defined(GPIO_USE_FOR_DEEP_SLEEP_WAKEUP)
    /* Configure RTC gpio */
    rtc_gpio_pullup_en(wakeupButton);
    rtc_gpio_pulldown_dis(wakeupButton);

    esp_sleep_enable_ext0_wakeup(wakeupButton, 0); /* wakeup at logic 0 (ground) */
    printf("Going into deep sleep\n");
    esp_deep_sleep_start();

#elif defined(GPIO_USE_FOR_GOING_INTO_DEEP_SLEEP)
    gpio_set_direction(wakeupButton, GPIO_MODE_INPUT);
    gpio_pullup_en(wakeupButton);
    gpio_pulldown_dis(wakeupButton);

    while (1)
    {
        if (gpio_get_level(wakeupButton) == 0)
        {
            printf("Going into deep sleep\n");
            vTaskDelay(100 / portTICK_PERIOD_MS);
            esp_deep_sleep_start();
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);  // Polling interval
    }

#endif
}
