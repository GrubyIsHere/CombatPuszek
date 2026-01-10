#include <S_Lights.h>

//-------------//
// INICJALIZACJE//
//-------------//

// Konstruktor
S_Lights::S_Lights()
{
  Init();
}

//---------------//
// DEFINICJE METOD//
//---------------//

void S_Lights::Init()
{
  pinMode(light_front_left_pin, OUTPUT);
  pinMode(light_front_right_pin, OUTPUT);
  pinMode(light_back_left_pin, OUTPUT);
  pinMode(light_back_right_pin, OUTPUT);
}

int S_Lights::Toggle(light_id id)
{
  // Sprawdź poprawność ID
  if (id < 0 || id > 3)
  {
    return -1;
  }

  // Przełącz odpowiedni bit na przeciwny
  lights_states ^= (1 << id);

  // Ustaw odpowiedni pin na podstawie stanu
  bool state = (lights_states >> id) & 1;

  // jeśli stan jest aktywny, to włącz światło (z zadaną wcześniej jasnością)
  if (state)
  {
    analogWrite(lights_pins[id], lights_brightness[id]);
  }
  else
  {
    analogWrite(lights_pins[id], 0); // jeśli stan nieaktywny to wyłącz
  }

  return state;
}

int S_Lights::Dim(light_id id, int brightness)
{
  // Ograniczenie do zakresu 0-100 i przeskalowanie na 0-255
  brightness = constrain(brightness, 0, 100);
  lights_brightness[id] = map(brightness, 0, 100, 0, 255);

  // zastosuj dla nową jasność jeśli światło jest włączone
  if ((lights_states >> id) & 1)
  {
    analogWrite(lights_pins[id], lights_brightness[id]);
  }

  return brightness;
}

bool S_Lights::On(light_id id)
{
  // Sprawdź poprawność ID
  if (id < 0 || id > 3)
  {
    return false;
  }

  // Ustaw bit światła na 1 (włączony)
  lights_states |= (1 << id);

  // Włącz światło z zapisaną jasnością
  analogWrite(lights_pins[id], lights_brightness[id]);

  return true;
}

bool S_Lights::Off(light_id id)
{
  // Sprawdź poprawność ID
  if (id < 0 || id > 3)
  {
    return false;
  }

  // Ustaw bit światła na 0 (wyłączony)
  lights_states &= ~(1 << id);

  // Wyłącz światło
  analogWrite(lights_pins[id], 0);

  return true;
}

int S_Lights::Blink(light_id id, int blink_count, int speed)
{
  if (next_task_index >= max_blink_tasks)
  {
    return pdFALSE; // Brak wolnych slotów na task
  }

  TaskParams *params = new TaskParams;
  params->instance = this;
  params->id = id;
  params->speed = speed;
  params->blink_count = blink_count;
  params->task_index = next_task_index;

  BaseType_t result = xTaskCreate(
      BlinkHeartbeat,
      "BlinkTask",
      2048,
      params,
      1,
      &blink_task_handlers[next_task_index]);

  if (result == pdPASS)
  {
    next_task_index++;
  }
  else
  {
    delete params;
  }

  return result;
}

void S_Lights::BlinkHeartbeat(void *parameters)
{
  TaskParams* params = static_cast<TaskParams *>(parameters);

  while (params->blink_count > 0)
  {
    for (int i = 100; i >= 0; i--)
    {
      params->instance->Dim(params->id, i);
      vTaskDelay(params->speed / portTICK_PERIOD_MS);
    }
    params->blink_count--;
  }

  params->instance->blink_task_handlers[params->task_index] = NULL;
  
  delete params;
  vTaskDelete(NULL);
}
