#include <Arduino.h>
#include <Servo.h>
#include "StandardServo.h"

StandardServo::StandardServo(byte pin) {
  m_pin = pin;
}
StandardServo::StandardServo(byte pin, float PWMPerDegree, int minRotation, int maxRotation , bool reverseDirection, int defaultRotation) {
  m_pin = pin;
  m_PWMPerDegree = PWMPerDegree;
  m_minRotation = ((minRotation * m_PWMPerDegree) + 1000);
  m_maxRotation = ((maxRotation * m_PWMPerDegree) + 1000);
  m_defaultRotation  = constrain(((defaultRotation * m_PWMPerDegree) + 1000), m_minRotation, m_maxRotation);
}

void StandardServo::attach() {
  m_servo.attach(m_pin);
  m_servo.writeMicroseconds(m_defaultRotation);
  m_currentRotation = m_defaultRotation;
}

bool StandardServo::moveTowardsTarget(float degreesToMove) {
  bool validMove;
  int newRotation = m_currentRotation + (degreesToMove * m_PWMPerDegree);//Get the new roation
  if((newRotation > m_maxRotation) || (newRotation < m_minRotation)){//Check if it is in bounds
    validMove = false;
  }else{
    validMove = true;
  }
  newRotation = constrain(newRotation, m_minRotation, m_maxRotation);//Constain new roation to bounds
  m_servo.writeMicroseconds(newRotation);//Write new rotation to servo
  m_currentRotation = newRotation;//Update current posistion
  return validMove;//Return if the move was in bounds
}
