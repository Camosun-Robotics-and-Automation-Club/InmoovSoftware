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
  m_defaultRotation  = ((defaultRotation * m_PWMPerDegree) + 1000);
}

void StandardServo::attach() {
  m_servo.attach(m_pin);
  m_servo.writeMicroseconds(m_defaultRotation);
  m_currentRotation = m_defaultRotation;
}

void StandardServo::moveTowardsTarget(float degreesToMove) {
  m_currentRotation += (degreesToMove * m_PWMPerDegree);
  Serial.println(m_currentRotation);
  m_servo.writeMicroseconds(m_currentRotation);
}
