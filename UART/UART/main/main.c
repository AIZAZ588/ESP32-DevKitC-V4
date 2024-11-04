/**
 * @brief : UART (Universal Asynchronous Receiver - Transmitter)
 *          In this Example i shorted rx with tx
 * 
 *      To configure uart following steps needs to be followed
 * 
 * @Step1 : Configure driver (struck)
 * @Step2 : Select UART
 * @Step3 : Select/Configure uart Pins
 * @Step4 : Install driver
 * 
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "string.h"
#include "esp_log.h"

#define CUSTOM_UART UART_NUM_1
#define CUSTOM_UART_TX 25
#define CUSTOM_UART_RX 26
#define RX_BUFF_SIZE 1024
#define TX_BUFF_SIZE 1024

void app_main(void)
{
    /* Step 1 */
    uart_config_t custom_uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    /* Step 2 */
    uart_param_config(CUSTOM_UART,&custom_uart_config);


    /* Step 3 */
    uart_set_pin(CUSTOM_UART,CUSTOM_UART_TX,CUSTOM_UART_RX,UART_PIN_NO_CHANGE,UART_PIN_NO_CHANGE);


    /* Step 3: Install UART driver with both RX and TX buffers */

    uart_driver_install(CUSTOM_UART, RX_BUFF_SIZE, 0, 0, NULL, 0);

    char msg[] = "Hello world\r\n";
    printf("msg : %s\n",msg);

    /* Sending data on uart */
    uart_write_bytes(CUSTOM_UART,msg,sizeof(msg));
    // ESP_ERROR_CHECK(uart_write_bytes(CUSTOM_UART,msg,sizeof(msg)));
    // ESP_ERROR_CHECK_WITHOUT_ABORT(uart_write_bytes(CUSTOM_UART,msg,sizeof(msg)));


    /* Receiving data on uart */
    /* creating buffer */
    char incomming_msg[RX_BUFF_SIZE];
    memset(incomming_msg,0,sizeof(incomming_msg));

    /* reading into buffer */
    uart_read_bytes(CUSTOM_UART,incomming_msg,sizeof(incomming_msg),pdMS_TO_TICKS(500));

    printf("received : %s/n",incomming_msg);

    
}
