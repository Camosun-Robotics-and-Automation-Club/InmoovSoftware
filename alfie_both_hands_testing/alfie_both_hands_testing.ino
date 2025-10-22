//Alfie test code by jessie
//used for testing as very simple to control each servo from serial monitor
//inputs take form of "[degree wanted to move to][letter from a-g, a is thumb f is pinkie g is wrist][L or R for left and right hand]"
//eg "45aR" would write the right thumb to angle 45% of it's max range "100fL," would write the left wrist 100% of it's range
//max range was taken from previous code, update and calibrate for better precision
//could also be used with a gui with serial communication eg C#

//next update is to make it accelerate and deaccelerate smoothly making it more lifelike
//bell curve over time of velocity sorta thing

//previous code was static and ran a loop
//make loop code to show off

#include <Servo.h>

Servo Lfingers[6]; //servo object array thumb is 0 pinkie is 4 wrist is 5
Servo Rfingers[6]; //could be a 2d array instead

String readString;

void setup() {

  Serial.begin(9600);

  for (int i; i < 6; i++) {
    pinMode((i + 2), OUTPUT); //pins 2-7 are for left hand
    pinMode((i + 8), OUTPUT); //pins 8-13 are for right hand
    Lfingers[i].attach(i + 2);
    Rfingers[i].attach(i + 8);
  }
}

void loop() {
  //multiple serial inputs code was like 80% stolen
  if (Serial.available()) {
    char c = Serial.read();  //gets one byte from serial buffer
    if (c == 'L' || c == 'R') {
      if (readString.length() > 1) {

        readString += c;
        int n = readString.toInt();  //convert readString into a number FIX ME make float for precision

        if (n >= 0 && n <= 100)  //each finger has it's own degree range so 0 is open 100 is closed FIX ME some servos are mounted backwards
        {
          if (c == 'L') {
            Serial.print("Writing ");
            Serial.print(n);
            Serial.print("% to ");
            write_left(n);
          }
          if (c == 'R') {
            Serial.print("Writing ");
            Serial.print(n);
            Serial.print("% to ");
            write_right(n);
          }
        }
        readString = "";  //clears variable for new input
      }
    } else {
      readString += c;  //makes the string readString
    }
  }
}

//this is left hand specific as the values are mapped to each servos finger range
void write_left(int n) {
  long val;
  if (readString.indexOf('a') > 0) {
    val = map(n, 0, 100, 110, 180);
    Lfingers[0].write(val);
    Serial.print('a');
  }

  if (readString.indexOf('b') > 0) {
    val = map(n, 0, 100, 20, 110);
    Lfingers[1].write(val);
    Serial.print('b');
  }

  if (readString.indexOf('c') > 0) {
    val = map(n, 0, 100, 20, 110);
    Lfingers[2].write(n);
    Serial.print('c');
  }

  if (readString.indexOf('d') > 0) {
    val = map(n, 0, 100, 20, 110);
    Lfingers[3].write(n);
    Serial.print('d');
  }

  if (readString.indexOf('e') > 0) {
    val = map(n, 0, 100, 30, 120);
    Lfingers[4].write(n);
    Serial.print('e');
  }

  if (readString.indexOf('f') > 0) {
    map(n, 0, 100, 0, 180);
    Lfingers[5].write(n);
    Serial.print('f');
  }

  Serial.println(" left hand");
}


//again each finger has it's own servo range based on the internal wiring
void write_right(int n) {
  long val;
  if (readString.indexOf('a') > 0) {
    val = map(n, 0, 100, 140, 100);
    Rfingers[0].write(val);
    Serial.print('a');
  }

  if (readString.indexOf('b') > 0) {
    val = map(n, 0, 100, 20, 90);
    Rfingers[1].write(val);
    Serial.print('b');
  }

  if (readString.indexOf('c') > 0) {
    val = map(n, 0, 100, 30, 100);
    Rfingers[2].write(n);
    Serial.print('c');
  }

  if (readString.indexOf('d') > 0) {
    val = map(n, 0, 100, 30, 100);
    Rfingers[3].write(n);
    Serial.print('d');
  }

  if (readString.indexOf('e') > 0) {
    val = map(n, 0, 100, 0, 180);
    Rfingers[4].write(n);
    Serial.print('e');
  }

  if (readString.indexOf('f') > 0) {
    map(n, 0, 100, 150, 80);
    Rfingers[5].write(n);
    Serial.print('f');
  }

  Serial.println(" right hand");
}
