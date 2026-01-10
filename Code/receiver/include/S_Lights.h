#ifndef SLIGHTS
#define SLIGHTS

#include <Arduino.h>
#include <stdint.h>

class S_Lights
{
public:

  //-------//
  // OBIEKTY//
  //-------//

  enum light_id {
    FRONT_LEFT = 0,
    FRONT_RIGHT = 1,
    BACK_LEFT = 2,
    BACK_RIGHT = 3
  };
 
  //----------------//
  // DEKLARACJE METOD//
  //----------------//
  // Konstruktor
  S_Lights();

  int Toggle(light_id id);
  int Dim(light_id id, int brightness);
  int Blink(light_id id, int blink_count, int speed); //polecam szybkość około 7
  bool On(light_id id);
  bool Off(light_id id);

private:
  //----------------//
  // DEKLARACJE METOD//
  //----------------//

  void Init();

  static void BlinkHeartbeat(void *parameters);

  //-------//
  // NASTAWY//
  //-------//

  const uint8_t light_front_left_pin = 32;
  const uint8_t light_front_right_pin = 23;
  const uint8_t light_back_left_pin = 14;
  const uint8_t light_back_right_pin = 16;

   //inny zapis powyższego dla lepszego kodu w cpp
  const uint8_t lights_pins[4] = {light_front_left_pin, light_front_right_pin, light_back_left_pin, light_back_right_pin};  

  static const uint8_t max_blink_tasks = 4; //do wątków; musi być static

  //-------//
  // OBIEKTY//
  //-------//

  TaskHandle_t blink_task_handlers[max_blink_tasks] = {NULL};

  // struktura do przekazania parametrów dla Blink
  struct TaskParams {
    S_Lights* instance;
    light_id id;
    int speed;
    int blink_count;
    uint8_t task_index;
  };

 
  //------//
  // PAMIĘĆ//
  //------//

  uint8_t lights_states = 0; // Przechowuje stany wszystkich świateł (1 bit na światło)
  uint8_t lights_brightness[4] = {0};  // Przechowuje aktualną jasność (0-255)
  uint8_t next_task_index = 0;
};

#endif