#include <A_Robot.h>
#include <K_ESPNOW.h>
#include <Arduino.h>

K_ESPNOW E;
A_Robot R;

void setup() {
  // Serial Monitor DEBUG
  // Serial.begin(115200);
  // Serial.println("predone");

  E.Init();

  // Serial.println("done");
}

void loop() {

  E.UpdateConnectionState();

  R.ManualControl();

// debug
  // Serial.println("------------------------");
  // Serial.println(missed_confirmations);

  // Serial.println("------------------------");
  // Serial.println(E.control.brake);
  // Serial.println(E.control.connected);
  // Serial.println(E.control.saw);
  // Serial.println(E.control.speed_left);
  // Serial.println(E.control.speed_right);
  // delay(1000);
}
