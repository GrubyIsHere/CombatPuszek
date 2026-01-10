#ifndef KOTA
#define KOTA

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ElegantOTA.h>

class K_OTA
{
public:
  //----------------//
  // DEKLARACJE METOD//
  //----------------//
  // Konstruktor
  K_OTA();

  int Run();
  void Init();

private:
  //----------------//
  // DEKLARACJE METOD//
  //----------------//

  static void WebserwerHeartbeat(void *parameter);

  //-------//
  // OBIEKTY//
  //-------//

  WiFiClass *wifi;
  WebServer *server;
  ElegantOTAClass *ota;
  TaskHandle_t *webserwer_task_handler;

  // żeby połączyć się z OTA trzeba:
  //*1 utworzyć w mainie obiekt K_OTA
  //*2 dodać Init() do setupa
  //*3 tyle :)
  // ESP musi być w tym samym wifi co komputer z którego uploadujemy
  // OTA jest dostępna pod adresem esp_ip/update

  //-------//
  // NASTAWY//
  //-------//

  const char *ssid = "WasNet";
  const char *password = "HasloDoDomowegoWiFi01";

  // nastawy statycznego IP
  const uint8_t ip[4] = {192, 168, 1, 111};
  const uint8_t gateway[4] = {192, 168, 1, 1};
  const uint8_t subnet[4] = {255, 255, 0, 0};

  //------//
  // PAMIĘĆ//
  //------//
};

#endif