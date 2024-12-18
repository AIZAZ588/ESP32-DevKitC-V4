#ifndef _CONNECT_H_
#define _CONNECT_H_

#include "esp_err.h"


void wifi_init(void);
esp_err_t wifi_connect_sta(const char* ssid, const char* pass, int timeout);
void wifi_connect_ap(const char* ssid, const char* pass);
void wifi_disconnect(void);

#endif
