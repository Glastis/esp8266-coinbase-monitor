int                 https_get_request(char *value, t_coord *coord)
{
  WiFiClientSecure  client;

  if (!client.connect(HOST, SSL_PORT))
  {
    return (-1);
  }
  write_newline(coord, "Connected!");
  if (!client.verify(FINGERPRINT_SHA_1, HOST))
  {
    return (-2);
  }
  write_newline(coord, "Host OK");
  client.print(String("GET ") + FETCH_URL + " HTTP/1.1\r\n" +
               "Host: " + HOST + "\r\n" +
               "User-Agent: " + USER_AGENT + "\r\n" +
               "Connection: close\r\n\r\n");
  write_newline(coord, "Request sent");
  while (client.connected())
  {
    String line = client.readStringUntil('\n');

    write(coord, ".");
    if (!compare_str_beg(line.c_str(), RESPONSE_BEG_REF))
    {
      memcpy(value, &line.c_str()[ETH_VALUE_BEG], ETH_VALUE_LEN);
      value[ETH_VALUE_LEN] = '\0';
      return (1);
    }
  }
  return (-3);
}

int                 get_eth_value(char *value, t_coord *coord)
{
   HTTPClient       http;
   int              response;
   
   http.begin(FETCH_URL);
   response = http.GET();
   if (response <= 0)
   {
      return (response);
   }
   memcpy(value, &http.getString().c_str()[ETH_VALUE_BEG], ETH_VALUE_LEN);
   http.end();
   return (response);
}

void                print_eth_value(t_coord *coord)
{
  char              value[ETH_VALUE_LEN + 1];
  int               retv;
  
  clear_screen(coord);
  write_newline(coord, "Fetching...");
  if ((retv = https_get_request(value, coord)) <= 0)
  {
    String  rep = String(retv);
    
    write(coord, "ERROR: Got ");
    write_newline(coord, (char *)rep.c_str());
    write_newline(coord, "Looks bad news");
    write(coord, ":(");
  }
  else
  {
    clear_screen(coord);
    write_newline(coord, "ETH Value:");
    write_newline(coord, value);
    new_line(coord);
    write(coord, "\\o_");
  }
}

