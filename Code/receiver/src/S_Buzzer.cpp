#include <S_Buzzer.h>

//-------------//
// INICJALIZACJE//
//-------------//

// Konstruktor
S_Buzzer::S_Buzzer()
{
  Init();
}

//---------------//
// DEFINICJE METOD//
//---------------//

void S_Buzzer::Init(){
  pinMode(buzzer_pin, OUTPUT);
}

int S_Buzzer::Beep(){

  tone(buzzer_pin, 1000);

  tone(buzzer_pin, 0);

  return 0;
}

int S_Buzzer::Waw(){

  // for (int freq = waw_min_frequency; freq <= waw_max_frequency; freq++) {
  //   tone(esp_pin_buzzer, freq);  
  // }
  for (int freq = waw_max_frequency; freq >= waw_min_frequency; freq--) {
    tone(buzzer_pin, freq);
  }

  return 0;
}