#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <time.h>
#include <esp_sleep.h>
#include <esp_timer.h>
#include <esp32/rom/uart.h>

void app_main(void)
{ 
    /* Set wakeup timer */
    esp_sleep_enable_timer_wakeup(5000000); /* This accepts val in us */
    printf("going into light sleep\n");

    /* Capture time */
    uint64_t t1 = esp_timer_get_time();

    /* sleep */
    esp_light_sleep_start();

    /* when timer completes it will wakeup */
    uint64_t t2 = esp_timer_get_time();
    printf("duration of sleep was %lld\n", t2-t1/1000);

}
