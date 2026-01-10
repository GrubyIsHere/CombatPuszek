#include <S_Saw.h>

//-------------//
// INICJALIZACJE//
//-------------//
// Konstruktor
S_Saw::S_Saw()
{
  Init();
}

// Destruktor
S_Saw::~S_Saw()
{
  ledcDetachPin(saw_pin);
}

//---------------//
// DEFINICJE METOD//
//---------------//
void S_Saw::Init()
{
  // Konfiguracja kanału LEDC dla silnika BLDC
  ledcSetup(ledc_channel, ledc_freq, ledc_resolution);
  ledcAttachPin(saw_pin, ledc_channel);

  //hardkoding prędkości max, bo nie mamy sterowania analogiem
  SetSpeed(100);

  // Silnik wyłączony na start
  ledcWrite(ledc_channel, off_speed);
}

int S_Saw::Stop()
{
  ledcWrite(ledc_channel, off_speed);
  current_saw_state = 0;
  return 0;
}

int S_Saw::Start()
{
  ledcWrite(ledc_channel, current_duty);
  current_saw_state = 1;
  return 0;
}

int S_Saw::Hold()
{
  ledcWrite(ledc_channel, min_speed);
  current_saw_state = 2;
  return 0;
}

int S_Saw::SetSpeed(uint8_t target_speed_percent)
{
  uint32_t pulse_width = map(target_speed_percent, 0, 100, pulse_min_us, pulse_max_us);

  uint8_t duty = (pulse_width * 255) / pulse_period_us;

  current_duty = duty;
  current_saw_speed_percent = target_speed_percent;

  return current_duty;
}