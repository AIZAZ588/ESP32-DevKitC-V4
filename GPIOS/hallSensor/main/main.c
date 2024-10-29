#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* func is already defined in lib */
uint32_t hall_sens_read();
#define delayms(x)  vTaskDelay(x / portTICK_PERIOD_MS)

void app_main(void)
{
    while(true){
        printf("hall Sensor : %ld\n", hall_sens_read());
        delayms(100);
    }

}
