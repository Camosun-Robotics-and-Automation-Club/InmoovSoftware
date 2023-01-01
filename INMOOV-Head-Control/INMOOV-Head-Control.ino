#include "StandardServo.h"
#include "Head.h"

StandardServo servo_1(3, 500, 2500, 180, 1, 0, 0, 180, 90);
StandardServo servo_2(5, 500, 2500, 180, 1, 0, 0, 180, 90);
StandardServo servo_3(6, 500, 2500, 180, 1, 0, 0, 180, 90);
StandardServo servo_4(7, 500, 2500, 180, 1, 0, 0, 180, 90);
StandardServo servo_5(8, 500, 2500, 180, 1, 0, 0, 180, 90);
StandardServo servo_6(9, 500, 2500, 180, 1, 0, 0, 180, 90);

Head head(servo_1,
          servo_2,
          servo_3,
          servo_4,
          servo_5,
          servo_6,
          40);

int duration = 3000;
volatile bool interrupt1 = 0;
#define interruptPin 2 // Pin number for the digital interrupt, !NOTE! only certain pins can be used as interrupts

bool interrupt()
{
  if (digitalRead(interruptPin))
  {
    interrupt1 = 0;
  }
  else
  {
    interrupt1 = 1;
  }
  return interrupt1;
}

void setup()
{
  head.attach();
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), interrupt, CHANGE);
}

void loop()
{
  while (exampleMovement() == false)
  {
    Serial.println("interrupt1");
    Serial.println(interrupt1);
  };
  Serial.println("interrupt detected");
  Serial.println(interrupt1);
  delay(5000);
}
