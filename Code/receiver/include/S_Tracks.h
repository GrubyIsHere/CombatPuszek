#ifndef STRACKS
#define STRACKS

#include <Arduino.h>
#include <stdint.h>

class S_Tracks
{
public:

  //-------//
  // OBIEKTY//
  //-------//

  enum track_id {
    LEFT = 0,
    RIGHT = 1
  };

  enum direction {
    FORWARD = 0,
    BACKWARD = 1,
    BRAKE = 2,
    STOP = 3,
  };

  //----------------//
  // DEKLARACJE METOD//
  //----------------//
  // Konstruktor
  S_Tracks();

  int Move(track_id id, direction dir, int speed = 0);
  int Brake(track_id id);
  int Stop(track_id id); //zatrzymuje, ale nie blokuje kół

private:
  //----------------//
  // DEKLARACJE METOD//
  //----------------//

  void Init();
  
  void SetMotor(track_id id, uint8_t in1_state, uint8_t in2_state, uint8_t pwm_value);

  //-------//
  // OBIEKTY//
  //-------//

  //-------//
  // NASTAWY//
  //-------//

  const uint8_t eng_L_in1_pin = 27;
  const uint8_t eng_L_in2_pin = 26;
  const uint8_t eng_L_pwm_pin = 25;

  const uint8_t eng_R_in1_pin = 18;
  const uint8_t eng_R_in2_pin = 19;
  const uint8_t eng_R_pwm_pin = 21;

  //inny zapis powyższego dla lepszego kodu w cpp
  const uint8_t eng_pins[2][3] = {
    {eng_L_in1_pin, eng_L_in2_pin, eng_L_pwm_pin},
    {eng_R_in1_pin, eng_R_in2_pin, eng_R_pwm_pin}
  };

  //------//
  // PAMIĘĆ//
  //------//

  uint8_t current_direction[2] = {BRAKE, BRAKE}; 
  uint8_t current_speed[2] = {0, 0};
};

#endif