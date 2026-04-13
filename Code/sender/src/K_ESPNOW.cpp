#include <K_ESPNOW.h>

//-------------//
// INICJALIZACJE//
//-------------//

// musi być tu zainicjalizowane, żeby działało globalnie, bo niedorozówj cpp
struct_message K_ESPNOW::control;

// Konstruktor
K_ESPNOW::K_ESPNOW()
{
  wifi = new WiFiClass();
  last_send_time_ms = 0;

}

//---------------//
// DEFINICJE METOD//
//---------------//

int K_ESPNOW::Init()
{
  wifi->mode(WIFI_STA);

  while (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
  }
//Serial.println("initializing ESP-NOW DONE");
  memcpy(receiver.peer_addr, receiver_mac_address, 6);
  receiver.channel = 0;
  receiver.encrypt = false;

  while (esp_now_add_peer(&receiver) != ESP_OK) {
    Serial.println("Failed to add peer");
  }
  //Serial.println("CONECTED");

  return 0;
}

int K_ESPNOW::Send()
{
  unsigned long now = millis();

  if (now - last_send_time_ms < send_delay_ms) {
    return 2;   // wysyłanie pominięte – zbyt krótki odstęp czasu
  }

  last_send_time_ms = now;

  esp_err_t result = esp_now_send(receiver_mac_address, (uint8_t *)&control, sizeof(control));

  return (result == ESP_OK) ? 0 : 1;
}