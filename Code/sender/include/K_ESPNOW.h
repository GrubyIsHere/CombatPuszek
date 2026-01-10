#ifndef KESPNOW
#define KESPNOW

// https://randomnerdtutorials.com/esp-now-esp32-arduino-ide/
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

// dodać pola
typedef struct struct_message
{
  float speed_left;
  float speed_right;
  bool saw;
  bool brake;
  bool connected;
} struct_message;

class K_ESPNOW
{
public:
  //----------------//
  // DEKLARACJE METOD//
  //----------------//
  // Konstruktor
  K_ESPNOW();

  int Send();

  int Init();

  //------//
  // PAMIĘĆ//
  //------//

  static struct_message control;

private:
  //------//
  // PAMIĘĆ//
  //------//

  uint8_t receiver_mac_address[6] = {0x88, 0x13, 0xBF, 0x06, 0x21, 0xA4}; //biała brudna

  //----------------//
  // DEKLARACJE METOD//
  //----------------//

  //-------//
  // OBIEKTY//
  //-------//

  WiFiClass *wifi;
  esp_now_peer_info_t receiver;

  //-------//
  // NASTAWY//
  //-------//

  const long interval = 6; // dilej w us
};

#endif