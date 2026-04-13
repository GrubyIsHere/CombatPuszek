#ifndef KESPNOW
#define KESPNOW

// https://randomnerdtutorials.com/esp-now-esp32-arduino-ide/
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

//dodać pola jak będzie pilot z analogami
typedef struct struct_message
{
  int16_t speed_left;
  int16_t speed_right;
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

  bool IsConnected();           // sprawdza timeout
  void UpdateConnectionState(); // aktualizuje control.connected na podstawie czasu

  //------//
  // PAMIĘĆ//
  //------//

  static struct_message control; 

private:
  //------//
  // PAMIĘĆ//
  //------//

  static volatile unsigned long last_receive_time; // czas ostatniego pakietu


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

  static const unsigned long CONNECTION_TIMEOUT_MS = 500; // np. 500 ms

};

#endif