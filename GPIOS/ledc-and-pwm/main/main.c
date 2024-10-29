/***
 *                  Steps for using PWM for LEDs
 * 1) Configure timer
 * 2) Configure channel
 * 3) Set duty cycle
 *  3.1) Update duty cycle
 *
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "driver/gpio.h"
#include "esp_err.h"

#define delayms(x) vTaskDelay(x / portTICK_PERIOD_MS)

void app_main(void)
{
    /*
        Step 1) : Configure timer
                  _t means template
    */
    ledc_timer_config_t timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 5000,
        .clk_cfg = LEDC_AUTO_CLK};
    ledc_timer_config(&timer);

    /**
     *  Step 2) : Configure channel
     *            _t means template
     */
    ledc_channel_config_t channel = {
        .gpio_num = 25,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0, /* 16 channels are avalible */
        .timer_sel = LEDC_TIMER_0,
        .intr_type = LEDC_INTR_DISABLE,
        .duty = 0, /* Start with 0 duty cycle */
        .hpoint = 0};
    ledc_channel_config(&channel);

    /***
     * Step 3) : Step duty cycle, update duty cycle
     *
     */
    while (1)
    {
        /* Increasing duty cycle from 0 to 1023 */
        for (uint16_t i = 0; i <= 1023; i++)
        {
            ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, i));
            ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0));
            delayms(10);
        }

        /* Decreasing duty cycle from 1023 to 0 */
        for (uint16_t i = 1023; i > 0; i--)
        {
            ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, i));
            ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0));
            delayms(10);
        }
        delayms(1000);
    }

                                            /* or use this  */
    /* Install fade function service */
    // ledc_fade_func_install(0);
    // while(1){
    //     ESP_ERROR_CHECK(ledc_set_fade_time_and_start(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0,0,1000,LEDC_FADE_WAIT_DONE));
    //     ESP_ERROR_CHECK(ledc_set_fade_time_and_start(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0,1024,1000,LEDC_FADE_WAIT_DONE));
    // }
}