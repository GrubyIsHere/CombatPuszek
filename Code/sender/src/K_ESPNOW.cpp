#include <K_ESPNOW.h>

//-------------//
// INICJALIZACJE//
//-------------//

// musi być tu zainicjalizowane, żeby działało globalnie, bo niedorozówj cpp
struct_message K_ESPNOW::control;

// Konstruktor
K_ESPNOW::K_ESPNOW()
{
  Serial.println("dupa1");
  wifi = new WiFiClass();
  Serial.println("dupa2");
  
  //Init();
  Serial.println("dupa3");

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

  esp_now_add_peer(&receiver);
  //Serial.println("CONECTED");

  return 0;
}

int K_ESPNOW::Send()
{
  esp_err_t result = esp_now_send(receiver_mac_address, (uint8_t *)&control, sizeof(control));

  if (result == ESP_OK)
  {
    return 0;
  }
  else
  {
    return 1;
  }
  delay(interval);
}