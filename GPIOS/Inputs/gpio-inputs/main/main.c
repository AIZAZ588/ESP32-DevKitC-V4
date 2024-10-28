#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_PIN 17
#define Pushbutton_PIN 18

void app_main(void)
{
    /* gpio output */
    gpio_set_direction(LED_PIN,GPIO_MODE_OUTPUT);

    /* gpio input */
    gpio_set_direction(Pushbutton_PIN,GPIO_MODE_INPUT);
    gpio_pulldown_en(Pushbutton_PIN); /* Enable internal pull down resistor */
    gpio_pullup_dis(Pushbutton_PIN);  /* Disable internal pull up resistor */

    while(true)
    {
        /* Read voltage level of push button */
        int level = gpio_get_level(Pushbutton_PIN);

        /* Write that level to led pin */
        gpio_set_level(LED_PIN,level);

        /* Small delay to Avoid WDT Reset */
        vTaskDelay(1);
    }

}
