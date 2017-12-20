#include <Wire.h>
#include <stdio.h>
#include <WiFiClientSecure.h>
#include "OLED.h"
#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"

#define INT_MAX_LEN         12

#define SSID  							"WIFI_NAME_HERE"
#define PASS  							"WIFI_PASS_HERE"
#define IP_LEN							15

#define MAXX							  128
#define MAXY							  64
#define CHAR_X 						  8
#define CHAR_Y						  8
#define MAX_CHAR_PER_LINE 	((MAXX) / (CHAR_X))
#define MAX_LINES         	((MAXY) / (CHAR_Y))
#define MAX_CHAR         		((MAX_CHAR_PER_LINE) * (MAX_LINES))

#define FINGERPRINT_SHA_256 "EB 20 25 29 F8 56 00 57 E3 CF A0 38 18 AE AA 25 07 8C 61 A0 54 2B 21 AC AA 59 9E 83 43 F9 E1 00" //you might have to refresh coinbase.com certificate fingerprint (5 minutes max)
#define FINGERPRINT_SHA_1   "2E BE 69 17 28 57 16 83 15 7C 18 49 6A DA 1E 66 FD 1B 26 2F" //you might have to refresh coinbase.com certificate fingerprint (5 minutes max)
#define HOST                "www.coinbase.com"
#define FETCH_URL           "/api/v2/prices/ETH-EUR/historic?period=hour"
#define USER_AGENT          "curl/7.47.0"
#define SSL_PORT            443
#define RESPONSE_BEG_REF    "{\"data\":{\"currency\":\"EUR\""
#define ETH_VALUE_BEG       46
#define ETH_VALUE_END       52
#define ETH_VALUE_LEN       ((ETH_VALUE_END) - (ETH_VALUE_BEG))
#define REFRESH_DELAY_SEC   30
#define REFRESH_DELAY       ((REFRESH_DELAY_SEC) * 1000)


typedef struct {
  int		x;
  int		y;
} t_coord;
