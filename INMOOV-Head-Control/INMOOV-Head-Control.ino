#include "StandardServo.h" //  Class
#include "Head.h"          //  Class

// class, variable object name, pin #, minPWMTime, maxPWMTime, degreeRange, outputGearRatio, reverseDirection, minRotation, maxRotation, absolute starting position
StandardServo servo_1(3, 500, 2500, 180, 1, 0, 0, 180, 90);
StandardServo servo_2(5, 500, 2500, 180, 1, 0, 0, 180, 90);
StandardServo servo_3(6, 500, 2500, 180, 1, 0, 0, 180, 90);
StandardServo servo_4(7, 500, 2500, 180, 1, 0, 0, 180, 90);
StandardServo servo_5(8, 500, 2500, 180, 1, 0, 0, 180, 90);
StandardServo servo_6(9, 500, 2500, 180, 1, 0, 0, 180, 90);

// class, variable object name,
Head head(servo_1, // objects included in class
          servo_2, //        "
          servo_3, //        "
          servo_4, //        "
          servo_5, //        "
          servo_6, //        "
          40);     //        update frequency

int duration = 500;           //  Time for how long the movement will take place
volatile bool interrupt1 = 0; //  Variable for the state of the interrupt
#define interruptPin 2        //  Pin number for the digital interrupt, !NOTE! only certain pins can be used as interrupts

/*
Function to monitor the interrupt pin that returns the interrupt state
*/
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
  head.attach();                       //  Attach the head class
  Serial.begin(9600);                  //  Initialize serial comunications
  randomSeed(analogRead(A0));          //  Use the analog signal from pin A0 to start a random point from
  pinMode(interruptPin, INPUT_PULLUP); //  Initialize a pin for the interrupt and pull it high
  /*  Initialize an interrupt pin that throughs an interrupt when it's state changes */
  attachInterrupt(digitalPinToInterrupt(interruptPin), interrupt, CHANGE);
}

void loop()
{
  /*
  This is the main loop, it runs the example movement function while it returns a false interrupt state
  it prints the interrupt state and if the example movement returns a true interrupt it exits the loop and
  prints interrupt detected and waits 5 seconds before looping back to the top and checking the interrupt
  state returned by the example movement function
  */
  while (exampleMovement() == false)
  {
    Serial.println("interrupt1");
    Serial.println(interrupt1);
  }
  Serial.println("interrupt detected");
  Serial.println(interrupt1);
  delay(5000);
}
