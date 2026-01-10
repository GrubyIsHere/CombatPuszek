#ifndef KESPNOW
#define KESPNOW

// https://randomnerdtutorials.com/esp-now-esp32-arduino-ide/
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

//dodać pola 
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

  int Init();

  esp_err_t Receive();

  //------//
  // PAMIĘĆ//
  //------//

  static struct_message control; 

private:
  //------//
  // PAMIĘĆ//
  //------//

  //----------------//
  // DEKLARACJE METOD//
  //----------------//

  //musi być static, bo niedojebanie callbacków w cpp
  static void CallbackCopy(const uint8_t * mac, const uint8_t *incomingData, int len);

  //-------//
  // OBIEKTY//
  //-------//

  WiFiClass *wifi;

  //-------//
  // NASTAWY//
  //-------//

  const long interval = 6; // dilej w us
};

#endif