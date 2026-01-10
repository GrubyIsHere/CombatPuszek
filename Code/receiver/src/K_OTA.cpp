#include <K_OTA.h>

//-------------//
// INICJALIZACJE//
//-------------//

// Konstruktor
K_OTA::K_OTA()
{
  wifi = new WiFiClass();
  server = new WebServer(80);
  ota = new ElegantOTAClass(); //adres OTA: esp_ip/update
  webserwer_task_handler = new TaskHandle_t();

  Init();
}

//---------------//
// DEFINICJE METOD//
//---------------//

int K_OTA::Run()
{
  server->handleClient();
  ota->loop();
  return 0;
}

void K_OTA::Init()
{
  IPAddress set_ip(ip[0], ip[1], ip[2], ip[3]);
  IPAddress set_gateway(gateway[0], gateway[1], gateway[2], gateway[3]);
  IPAddress set_subnet(subnet[0], subnet[1], subnet[2], subnet[3]);

  wifi->config(set_ip, set_gateway, set_subnet);
  wifi->mode(WIFI_STA);
  wifi->begin(ssid, password);

  server->begin();

  ota->begin(server); //adres OTA: esp_ip/update

  xTaskCreate(
    K_OTA::WebserwerHeartbeat, // Funkcja zadania
    "OTA_Serwer",              // Nazwa zadania
    4096,                      // Rozmiar stosu (4 KB)
    this,                      // Parametry zadania
    1,                         // Priorytet (1 – niski, 2 – wyższy)
    webserwer_task_handler     // Uchwyt zadania
  );
}

void K_OTA::WebserwerHeartbeat(void *parameter) 
{
  K_OTA* instance = static_cast<K_OTA*>(parameter); //jakiś kurwa drut castowy, żeby task w tle sie tworzył poprawnie
  while (true) {
    instance->Run();
    vTaskDelay(10 / portTICK_PERIOD_MS);  // Krótkie opóźnienie, aby nie dławić CPU
  }
}