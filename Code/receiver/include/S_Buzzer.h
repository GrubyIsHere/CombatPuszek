#ifndef BUZZER
#define BUZZER

#include <stdint.h>
#include <Arduino.h>

#include <map>

class S_Buzzer {
public:
//----------------//
//DEKLARACJE METOD//
//----------------//
  // Konstruktor
  S_Buzzer();

  int Beep();
  int Waw();

private:
//----------------//
//DEKLARACJE METOD//
//----------------//

  void Init();

//-------//
//OBIEKTY//
//-------//

  //np obiekty z klas z bibliotek z gita

//-------//
//NASTAWY//
//-------//

  const uint8_t buzzer_pin = 13; 

  const uint32_t waw_min_frequency = 900;  
  const uint32_t waw_max_frequency = 24000;

//------//
//PAMIĘĆ//
//------//

  bool beep_mode_toggle = 0;
  bool waw_mode_toggle = 0;

};

#endif