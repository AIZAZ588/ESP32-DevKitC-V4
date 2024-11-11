/***
 *   When wakeup from deep sleep controller will restart
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* Topic related */
#include "esp_sleep.h"

void app_main(void)
{
    /*                            sec  ms    us                               */
    esp_sleep_enable_timer_wakeup(5 * 1000 * 1000); /* it expects value in us */

    printf("going into deep sleep\n");

    esp_deep_sleep_start();
}
