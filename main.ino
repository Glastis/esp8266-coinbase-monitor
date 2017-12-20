#include "main.h"

OLED      display(0, 2);
t_coord   coord;

void setup()
{
  
  char      tmpip[IP_LEN];

  init_coord(&coord);
  display.begin();
  WiFi.begin(SSID, PASS);
  check_connection(&coord);
  memcpy(tmpip, (const void *)WiFi.localIP().toString().c_str(), IP_LEN);
  new_line(&coord);
  write(&coord, "IP:");
  write(&coord, tmpip);
  delay(1000);
}

void loop()
{
  print_eth_value(&coord);
  delay(REFRESH_DELAY);
}

