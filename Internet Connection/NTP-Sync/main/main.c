#include <stdio.h>

/* Topic Specific */
#include <stdlib.h>
#include <time.h>
#include <esp_sntp.h>
#include "esp_log.h"

/* Internet */
#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"

#define TAG "NTP_TIME"

/* Functions */
void on_got_time(struct timeval *tv);
void get_local_time(struct timeval *val);


void app_main(void)
{
     /* to make sure nvs is properly initalized */
    nvs_flash_init();

    /* initialize tcp ip Adaptor  */
    esp_netif_init();

    /* event loop requires for internet connection */
    esp_event_loop_create_default();

    /* from protocol example .h*/
    example_connect();

    /* SNTP Sync mode immediate  */
    sntp_set_sync_mode(SNTP_SYNC_MODE_IMMED);

    /* Specify time server */
    sntp_setservername(0,"pool.ntp.org");

    sntp_init();

    /**
     * 
     * @brief  set a callback function for time synchronization notification
     *    Call back function for
     * *  To Sync fetched time and sync with chip time 
     * *  To find whether time has'bn synced or not
     */

    sntp_set_time_sync_notification_cb(on_got_time);

}

void on_got_time(struct timeval *tv){

    /* print unix time */
    printf("sec %lld\n",tv->tv_sec);
    get_local_time(tv);
    example_disconnect();

}

void get_local_time(struct timeval *val){
    char buff[50];

    /**
     *   Set Time Zone
     */
    setenv("TZ", "PKT-5", 1);


    struct tm *timeinfo = localtime(&val->tv_sec);
    tzset();

    /**
     *  https://www.tutorialspoint.com/c_standard_library/c_function_strftime.htm
     *  
     *  * %c :   Date and time representation	Sun Aug 19 02:56:02 2012
     *
     * */
    strftime(buff,sizeof(buff),"%c",timeinfo);
    ESP_LOGI(TAG,"Time now :: %s",buff);
}
