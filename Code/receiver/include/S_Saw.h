#ifndef SSAW
#define SSAW

#include <Arduino.h>
#include <stdint.h>

// Preset structure for different motor/ESC combinations
struct MotorPreset {
    const char* name;
    uint16_t pulse_off_us;   // szerokość impulsu STOP
    uint16_t pulse_min_us;   // minimalna prędkość (0%)
    uint16_t pulse_max_us;   // maksymalna prędkość (100%)
    uint32_t pulse_period_us; //czas trwania impulsu
};
namespace MotorPresets {
    //  2700KV (działały poprawnie)
    const MotorPreset KV2700 = {
        "2700KV (oryginalne)",
        1100, 1300, 1940, 20000
    };
    //  920KV 
    const MotorPreset KV920 = {
        "920KV",
        1000, 1050, 2000, 20000
    };
}

constexpr const MotorPreset* ACTIVE_MOTOR_PRESET = &MotorPresets::KV920;
// constexpr const MotorPreset* ACTIVE_MOTOR_PRESET = &MotorPresets::KV2700;

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
  int SetSpeed(uint8_t target_speed_percent);

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
  const uint32_t ledc_freq = 50;    // Częstotliwość PWM w Hz
  const uint16_t ledc_resolution = 8; // Rozdzielczość PWM 

  const uint32_t off_speed = (ACTIVE_MOTOR_PRESET->pulse_off_us * 255UL) / ACTIVE_MOTOR_PRESET->pulse_period_us;
  const uint32_t min_speed = (ACTIVE_MOTOR_PRESET->pulse_min_us * 255UL) / ACTIVE_MOTOR_PRESET->pulse_period_us;
  const uint32_t max_speed = (ACTIVE_MOTOR_PRESET->pulse_max_us * 255UL) / ACTIVE_MOTOR_PRESET->pulse_period_us;

  //------//
  // PAMIĘĆ//
  //------//
  uint8_t current_saw_speed_percent = 0;
  uint32_t current_duty = 0;
  uint8_t current_saw_state = 0; //0=off, 1=on, 2=hold
};

#endif