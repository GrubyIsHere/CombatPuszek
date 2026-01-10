#include <S_Buttons.h>

//-------------//
// INICJALIZACJE//
//-------------//

// Konstruktor
S_Buttons::S_Buttons()
{
  pinMode(thumb_finger_button_pin, INPUT_PULLUP);
  pinMode(pointer_finger_button_pin, INPUT_PULLUP);
  pinMode(middle_finger_button_pin, INPUT_PULLUP);
  pinMode(ring_finger_button_pin, INPUT_PULLUP);
  pinMode(pinky_finger_button_pin, INPUT_PULLUP);
}

//---------------//
// DEFINICJE METOD//
//---------------//

uint8_t S_Buttons::GetState(button_id id)
{
  switch (id)
  {
  case THUMB:
    return !digitalRead(thumb_finger_button_pin); //negacje bo pullup zwierany do down => odwrotna logika
  case POINTER:
    return !digitalRead(pointer_finger_button_pin);
  case MIDDLE:
    return !digitalRead(middle_finger_button_pin);
  case RING:
    return !digitalRead(ring_finger_button_pin);
  case PINKY:
    return !digitalRead(pinky_finger_button_pin);
  case ALL:
    return
    ((!digitalRead(pointer_finger_button_pin)) &&
    (!digitalRead(middle_finger_button_pin)) && 
    (!digitalRead(ring_finger_button_pin)) &&   
    (!digitalRead(pinky_finger_button_pin)));   
  return 2;
  }
}