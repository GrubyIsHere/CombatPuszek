#ifndef AROBOT
#define AROBOT

#include <stdint.h>

#include <S_Battery.h>
#include <S_Buzzer.h>
#include <S_Lights.h>
#include <S_Saw.h>
#include <S_Tracks.h>

#include <K_ESPNOW.h>

class A_Robot : public K_ESPNOW
{
public:
  //----------------//
  // DEKLARACJE METOD//
  //----------------//
  // Konstruktor
  A_Robot();

  int ManualControl();
  int BatteryCheck();

private:
  //----------------//
  // DEKLARACJE METOD//
  //----------------//

  void Init();

  //-------//
  // OBIEKTY//
  //-------//

  S_Battery * battery;
  S_Buzzer * buzzer; 
  S_Lights * lights; 
  S_Saw * saw;
  S_Tracks * tracks; 

  //-------//
  // NASTAWY//
  //-------//

  //------//
  // PAMIĘĆ//
  //------//

  bool saw_first_started = 0;
};

#endif