#include <Arduino.h>

//A simple program that will transmit everyones name over serial, used to practicing version control.

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello from Eric Pazder !");
  Serial.println("Hello from your name !");
}