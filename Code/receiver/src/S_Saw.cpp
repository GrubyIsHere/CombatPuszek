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
  Stop();
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

  // //procedura kalibracji ESC
  // ledcWrite(ledc_channel, off_speed);
  // delay(100);
  // ledcWrite(ledc_channel, max_speed);
  // delay(100);

  // Silnik wyłączony na start
  Stop();
}

int S_Saw::Stop()
{
  current_duty = off_speed;
  ledcWrite(ledc_channel, current_duty);
  current_saw_state = 0;
  return 0;
}

int S_Saw::Start()
{
  current_duty = max_speed;
  ledcWrite(ledc_channel, current_duty);
  current_saw_state = 1;
  return 0;
}

int S_Saw::Hold()
{
  current_duty = min_speed;
  ledcWrite(ledc_channel, current_duty);
  current_saw_state = 2;
  return 0;
}

int S_Saw::SetSpeed(uint8_t target_speed_percent)
{
   uint32_t pulse_width = map(target_speed_percent, 0, 100,
                             ACTIVE_MOTOR_PRESET->pulse_min_us,
                             ACTIVE_MOTOR_PRESET->pulse_max_us);

  uint8_t duty = (pulse_width * 255) / ACTIVE_MOTOR_PRESET->pulse_period_us;

  current_duty = duty;
  current_saw_speed_percent = target_speed_percent;

  return current_duty;
}