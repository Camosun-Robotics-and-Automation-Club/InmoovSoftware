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
          40);     //        servo update frequency(hz)

int duration = 500;           //  Time for how long the movement will take place(in milliseconds)
volatile bool interrupt1 = 0; //  Variable for the state of the interrupt
#define interruptPin 2        //  Pin number for the digital interrupt, !NOTE! only certain pins can be used as interrupts

/*
Function to monitor the interrupt pin that returns the interrupt state
*/
void interrupt()
{
  interrupt1 = !digitalRead(interruptPin);
}

void setup()
{
  head.attach();                       //  Attach the head class
  Serial.begin(9600);                  //  Initialize serial comunications
  randomSeed(analogRead(A0));          //  Use the analog signal from pin A0 to start a random point from
  pinMode(interruptPin, INPUT_PULLUP); //  Initialize a pin for the interrupt and pull it high
  /*  Initialize an interrupt pin that triggers an interrupt when it's state changes */
  attachInterrupt(digitalPinToInterrupt(interruptPin), interrupt, CHANGE);
}

/*
  Main Loop
  */
void loop()
{
  /* Run the example movement routine until it returns true(meaning an interrupt was triggerd during the movement)*/
  while (exampleMovement() == false);
  /* Place code that need to run after an interrupt here*/
  Serial.println("Interrupt1 Triggered");
  delay(2000);
}
