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
  m_reverseDirection = reverseDirection;
  m_defaultRotation  = constrain(((defaultRotation * m_PWMPerDegree) + 1000), m_minRotation, m_maxRotation);
}

void StandardServo::attach() {
  m_servo.attach(m_pin);
  moveToTargetMicroseconds(m_defaultRotation);
  m_currentRotation = m_defaultRotation;
}

bool StandardServo::moveTowardsTarget(float degreesToMove) {
  int newRotation = m_currentRotation + (degreesToMove * m_PWMPerDegree);//Get the new roation
  return moveToTargetMicroseconds(newRotation);
}

bool StandardServo::moveToTarget(int target){
  target = ((target * m_PWMPerDegree) + 1000);
  return moveToTargetMicroseconds(target);
}

bool StandardServo::moveToTargetMicroseconds(int target){
  bool validMove;
  if((target > m_maxRotation) || (target < m_minRotation)){//Check if it is in bounds
    validMove = false;
  }else{
    validMove = true;
  }
  target = constrain(target, m_minRotation, m_maxRotation);//Constain target roation to bounds
  if(m_reverseDirection){
    m_servo.writeMicroseconds(map(target,1000,2000,2000,1000));//Write target rotation flipped to servo
  }else{
    m_servo.writeMicroseconds(target);//Write target rotation to servo
  }
  m_currentRotation = target;//Update current posistion
  return validMove;//Return if the move was in bounds
  
}

float StandardServo::getPWMPerDegree(){return m_PWMPerDegree;}

float StandardServo::getCurrentRotation(){return ((m_currentRotation - 1000)/m_PWMPerDegree);}
