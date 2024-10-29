#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/touch_pad.h"

#define delayms(x) vTaskDelay(x / portTICK_PERIOD_MS)

void app_main(void)
{
    touch_pad_init();
    touch_pad_set_voltage(TOUCH_LVOLT_0V5,TOUCH_HVOLT_2V7,TOUCH_HVOLT_ATTEN_1V5);
    touch_pad_config(TOUCH_PAD_NUM9,100); /* The lower the threshold, the more sensitive the touch sensor will be. */

    uint16_t val = 0;
    while(1){
        touch_pad_read(TOUCH_PAD_NUM9,&val);
        printf("touch val : %d\n",val);
        delayms(200);
    }
    /**
     * There are functions like 
     * touch_pad_filter_start(10);
     * touch_pad_read_raw_data(TOUCH_PAD_NUM9, &touch_rawValue);
     * touch_pad_read_filtered(TOUCH_PAD_NUM9, &touch_filter_value);
     */

}
