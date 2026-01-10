#ifndef BUTTONS
#define BUTTONS

#include <stdint.h>
#include <Arduino.h>

class S_Buttons {
public:
//----------------//
//DEKLARACJE METOD//
//----------------//

  enum button_id {
    THUMB = 0,
    POINTER = 1,
    MIDDLE = 2,
    RING = 3,
    PINKY = 4,
    ALL = 5
  };

// Konstruktor
  S_Buttons();

  uint8_t GetState(button_id id);
 
private:
//----------------//
//DEKLARACJE METOD//
//----------------//

//-------//
//OBIEKTY//
//-------//

  //np obiekty z klas z bibliotek z gita

//-------//
//NASTAWY//
//-------//

  const uint8_t thumb_finger_button_pin = 27; 
  const uint8_t pointer_finger_button_pin = 23;
  const uint8_t middle_finger_button_pin = 22;
  const uint8_t ring_finger_button_pin = 21;
  const uint8_t pinky_finger_button_pin = 19;

//------//
//PAMIĘĆ//
//------//

};

#endif