#include <Servo.h>

Servo servo;

String readString;

void setup() {
  Serial.begin(9600);

  servo.attach(3);
}

void loop() {
  if (Serial.available())  {
  char c = Serial.read();  //gets one byte from serial buffer
  if (c == ',') {
    if (readString.length() >1) {

      int n = readString.toInt();  //convert readString into a number FIX ME make float for precision

      if(n >= 0 && n <= 180)
      {
        servo.write(n);
      }
        readString=""; //clears variable for new input
    }
  }  
  else {     
    readString += c; //makes the string readString
    }
  }
}
