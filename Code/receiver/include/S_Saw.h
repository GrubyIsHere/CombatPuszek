#ifndef SSAW
#define SSAW

#include <Arduino.h>
#include <stdint.h>

class S_Saw
{
public:
  //----------------//
  // DEKLARACJE METOD//
  //----------------//
  //(de)konstruktory
  S_Saw();
  ~S_Saw();

  int Stop();
  int Start();
  int Hold();
  int SetSpeed(uint8_t speetarget_speed_percentd);

private:
  //----------------//
  // DEKLARACJE METOD//
  //----------------//
  void Init();

  //-------//
  // NASTAWY//
  //-------//
  const uint8_t saw_pin = 4;

  const uint8_t ledc_channel = 0;  // Kanał LEDC (0-15)
  const uint32_t ledc_freq = 50;    // Częstotliwość PWM w Hz (typowe dla ESC)
  const uint16_t ledc_resolution = 8; // Rozdzielczość PWM 

  const uint16_t pulse_off_us = 1100;
  const uint16_t pulse_min_us = 1300;
  const uint16_t pulse_max_us = 1940;
  const uint32_t pulse_period_us = 20000;

  const uint32_t off_speed = (pulse_off_us * 255) / pulse_period_us;
  const uint32_t min_speed = (pulse_min_us * 255) / pulse_period_us;
  const uint32_t max_speed = (pulse_max_us * 255) / pulse_period_us;

  //------//
  // PAMIĘĆ//
  //------//
  uint8_t current_saw_speed_percent = 0;
  uint8_t current_duty = 0;
  uint8_t current_saw_state = 0; //0=off, 1=on, 2=hold
};

#endif