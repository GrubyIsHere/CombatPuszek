#include <Arduino.h>
#include <Servo.h>

Servo ESC;     // create servo object to control the ESC

void setup() {
  ESC.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  pinMode(3,INPUT_PULLUP);
}

void loop() {
  if(digitalRead(3)==LOW){
    ESC.write(170);
  } else {
    ESC.write(0);
  }
}
