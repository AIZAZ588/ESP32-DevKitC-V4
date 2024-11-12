/***
 *     When waking up from deep sleep controller will restart.
 *     Exit 1 mean we can use multiple gpio to to wakeup from deep sleep
 *     Exit 1 settings can be :
 *          *) if any gpio pin goes high
 *          *) if all gpio pins goes low (which are masked)
 *     This code is for case 1) if any gpio goes high
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* Topic related */
#include "esp_sleep.h"
#include "driver/rtc_io.h"

#define WAKE_UP_BUTTON 4
RTC_DATA_ATTR uint8_t count  = 0; /* To keep track of the wakeup counts */

void app_main(void)
{
    /* enable pull-up */
    rtc_gpio_pullup_dis(WAKE_UP_BUTTON);
    rtc_gpio_pulldown_en(WAKE_UP_BUTTON);

    /* wakeup settings */
    uint64_t mask = 1 << WAKE_UP_BUTTON;
    esp_sleep_enable_ext1_wakeup(mask,ESP_EXT1_WAKEUP_ANY_HIGH);

    printf("woken up counts %d.\t",count++);
    printf("Going into deep sleep..\n");

    /* Start deep sleep */
    esp_deep_sleep_start();

}
