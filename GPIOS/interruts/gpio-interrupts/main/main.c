/*
					External interrupt
					
	* Interrupt on a positive edge of an input signal
	* GPIO6, GPIO7, GPIO8, GPIO9, GPIO10, and GPIO11 can not be used for External interrupts
	
*/

/* libraries */
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>


/* Pins */
#define LED       27
#define BUTTON    25
#define DEBOUNCE_DELAY 250

bool interruptAvalible  = false;

static bool level = false;

static void IRAM_ATTR Button_isr_handler(void* arg){
	if(!interruptAvalible)
	{
		interruptAvalible = true;
	}	
}
 

void app_main(void){

	/* PINS Configuration */
	
     gpio_set_direction(LED,    GPIO_MODE_OUTPUT);
     gpio_set_direction(BUTTON, GPIO_MODE_INPUT );
     gpio_set_pull_mode(BUTTON, GPIO_PULLUP_ONLY);
     
     
     /* Install ISR */
     /*
     	If this function is used, the ISR service provides a global GPIO ISR
     	and individual pin handlers are registered via the gpio_isr_handler_add() function.
     */
     gpio_set_intr_type(BUTTON, GPIO_INTR_POSEDGE);
     gpio_install_isr_service(0);  /* '0' means isr default behavior, with no special configurations. */
	
	 gpio_isr_handler_add(BUTTON, Button_isr_handler, NULL);  
     
     
		
	while(true){
		
		if(interruptAvalible){
			level = !level;
			gpio_set_level(LED, level);
			vTaskDelay(DEBOUNCE_DELAY/portTICK_PERIOD_MS);
			interruptAvalible  =false;
		}
		vTaskDelay(100/portTICK_PERIOD_MS);
	}
}