/*
	ADC :  12 bit (0 - 4095 , 0V - 3.3V) 
*/


/* Libraries */
#include "driver/adc_types_legacy.h"
#include "hal/adc_types.h"
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdbool.h>

//ADC
#include <driver/adc.h>
#include <esp_adc_cal.h>


static esp_adc_cal_characteristics_t adc1_chars;


void app_main(void){
	
	esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_12, ADC_WIDTH_BIT_DEFAULT , 0, &adc1_chars);
	
    /* ADC channel and ADC scale volts (by defult ADC volts are 1.1 volts) */
	adc1_config_channel_atten(ADC1_CHANNEL_5,ADC_ATTEN_DB_12);
	
	
	while(true){
		
		float adc_val = adc1_get_raw(ADC_CHANNEL_5);
		printf("ADC Value is : %f\n", adc_val);
		vTaskDelay(500/portTICK_PERIOD_MS);
		
	}
}