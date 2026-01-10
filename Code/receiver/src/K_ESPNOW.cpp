#include <K_ESPNOW.h>

//-------------//
// INICJALIZACJE//
//-------------//

//musi być tu zainicjalizowane, żeby działało globalnie, bo niedorozówj cpp
struct_message K_ESPNOW::control;

// Konstruktor
K_ESPNOW::K_ESPNOW()
{
  wifi = new WiFiClass();
}

//---------------//
// DEFINICJE METOD//
//---------------//

// Callback function that will be executed when data is received ; DEBUG
void K_ESPNOW::CallbackCopy(const uint8_t *mac,const uint8_t *incomingData, int len)
{
  memcpy(&control, incomingData, sizeof(control));

  //DEBUG
  // Serial.println(control.brake);
  // Serial.println(control.connected);
  // Serial.println(control.saw);
  // Serial.println(control.speed_left);
  // Serial.println(control.speed_right);
}

int K_ESPNOW::Init()
{
  wifi->mode(WIFI_STA);

  while (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
  }

  return 0;
}

esp_err_t K_ESPNOW::Receive()
{
return esp_now_register_recv_cb(esp_now_recv_cb_t(CallbackCopy));
}