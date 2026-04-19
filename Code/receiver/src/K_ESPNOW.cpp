#include <K_ESPNOW.h>

//-------------//
// INICJALIZACJE//
//-------------//

//musi być tu zainicjalizowane, żeby działało globalnie, bo niedorozówj cpp
struct_message K_ESPNOW::control;
volatile unsigned long K_ESPNOW::last_receive_time = 0;

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

  last_receive_time = millis();

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

  esp_now_register_recv_cb(esp_now_recv_cb_t(CallbackCopy));

  last_receive_time = millis();

  return 0;
}

bool K_ESPNOW::IsConnected() 
{
  return (millis() - last_receive_time) < CONNECTION_TIMEOUT_MS;
}

void K_ESPNOW::UpdateConnectionState() 
{
  if (!IsConnected()) 
  {
    Serial.println("Error: disconnected");
    control.connected = false;
  }
}