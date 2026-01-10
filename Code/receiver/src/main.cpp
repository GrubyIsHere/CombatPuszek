#include <A_Robot.h>
#include <K_ESPNOW.h>
#include <Arduino.h>

K_ESPNOW E;
A_Robot R;

// do timingu połączenia (zmienione na licznik brakujących potwierdzeń)
unsigned long missed_confirmations = 0;
const unsigned long max_missed_confirmations = 1000; // po ilu brakujących potwierdzeniach uznać za rozłączone

// Flaga do śledzenia czy otrzymaliśmy nowe dane w tym cyklu
bool received = false;

void setup() {
  // Serial Monitor DEBUG
  Serial.begin(115200);
  Serial.println("predone");

  E.Init();

  Serial.println("done");
}

void loop() {

  E.control.connected = false;

  E.Receive();

  bool temp = E.control.connected;

  if (!temp)
  {
    ++missed_confirmations;
  } else {
    missed_confirmations = 0;
  }
  
  if (missed_confirmations >= max_missed_confirmations) {
    E.control.connected = false;
  } else {
    E.control.connected = true;
  }

  R.ManualControl();
  Serial.println("------------------------");
  Serial.println(missed_confirmations);

  Serial.println("------------------------");
  Serial.println(E.control.brake);
  Serial.println(E.control.connected);
  Serial.println(E.control.saw);
  Serial.println(E.control.speed_left);
  Serial.println(E.control.speed_right);
  // delay(1000);
}
