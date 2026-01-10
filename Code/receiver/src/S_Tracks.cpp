#include <S_Tracks.h>

//-------------//
// INICJALIZACJE//
//-------------//

// Konstruktor
S_Tracks::S_Tracks()
{
  Init();
}

//---------------//
// DEFINICJE METOD//
//---------------//

void S_Tracks::Init()
{
  //output setup
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      pinMode(eng_pins[i][j], OUTPUT);
    }
  }

  // bezruch na starcie
  Brake(LEFT);
  Brake(RIGHT);
}

void S_Tracks::SetMotor(track_id id, uint8_t in1_state, uint8_t in2_state, uint8_t pwm_value)
{
  digitalWrite(eng_pins[id][0], in1_state);
  digitalWrite(eng_pins[id][1], in2_state);
  analogWrite(eng_pins[id][2], pwm_value);
}

int S_Tracks::Move(track_id id, direction dir, int speed)
{
  if (dir == BRAKE) {
    return Brake(id);
  }

  if (dir == STOP) {
    return Stop(id);
  }

  // //korekta krzywej osi lewej
  // if (id == LEFT) {
  //   speed = map(speed, 0, 100, 0, 85);
  // }

  // Ograniczenie do zakresu 0-100 i przeskalowanie na 0-255
  speed = constrain(speed, 0, 100);
  speed = map(speed, 0, 100, 0, 255);

  //do pamięci
  current_speed[id] = speed;
  current_direction[id] = dir;

  if (dir == FORWARD) {
    SetMotor(id, HIGH, LOW, speed);
  } else if (dir == BACKWARD) {
    SetMotor(id, LOW, HIGH, speed);
  }

  return 0;
}

int S_Tracks::Brake(track_id id)
{
  current_direction[id] = BRAKE;
  current_speed[id] = 0;
  SetMotor(id, HIGH, HIGH, 0);
  return 0;
}

int S_Tracks::Stop(track_id id){
  current_direction[id] = STOP;
  current_speed[id] = 0;
  SetMotor(id, LOW, LOW, 255);
  return 0;
}
