#include <Arduino.h>
#include <K_ESPNOW.h>
#include <S_Buttons.h>

// Complete project details at https://RandomNerdTutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
K_ESPNOW E;
S_Buttons B;

// do timingu połączenia (musi być globalne)
unsigned long lastTime = 0;  
unsigned long interval = 1;

void setup()
{
  E.Init();

  // Serial.begin(115200);
  // Serial.println("done");
}

void loop()
{
  // Serial.println("loopstart");

  if (B.GetState(B.POINTER))
  {
    E.control.speed_left = 100;
  }
  else if (B.GetState(B.RING))
  {
    E.control.speed_left = -100;
  }
  else
  {
    E.control.speed_left = 0;
  }

  if (B.GetState(B.MIDDLE))
  {
    E.control.speed_right = 100;
  }
  else if (B.GetState(B.PINKY))
  {
    E.control.speed_right = -100;
  }
  else
  {
    E.control.speed_right = 0;
  }
  E.control.saw = B.GetState(B.THUMB);
  // jak wciskamy wszystkie sterowania (z piłą lub bez) to brake
  E.control.brake = B.GetState(B.ALL);
  E.control.connected = true; //sprawdzenie stanu (powinno nadpisywać receiver na true)

  E.Send();

  //debug
  // Serial.println("beforesend");
  // Serial.println(E.Send());
  // Serial.println("loopend");
  // Serial.println("Bool send: ");
  // Serial.println(E.control.brake);
  // Serial.println(E.control.connected);
  // Serial.println(E.control.saw);
  // Serial.println(E.control.speed_left);
  // Serial.println(E.control.speed_right);
  // delay(1000);
}