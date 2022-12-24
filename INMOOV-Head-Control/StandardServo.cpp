#include <Arduino.h>
#include <Servo.h>
#include "StandardServo.h"

StandardServo::StandardServo(byte pin){
  m_pin = pin;
}
StandardServo::StandardServo(byte pin, float PWMPerDegree, int minRotation, int maxRotation ,bool reverseDirection, int defaultRotation){
    m_pin = pin;
    m_PWMPerDegree = PWMPerDegree;
    m_minRotation = minRotation * m_PWMPerDegree;
    m_maxRotation = maxRotation * m_PWMPerDegree;
    m_defaultRotation  = defaultRotation * m_PWMPerDegree;
}

void StandardServo::attach(){
    m_servo.attach(m_pin);
    m_servo.writeMicroseconds(m_defaultRotation);
}

void StandardServo::moveTowardsTarget(float degreesToMove){
    m_servo.writeMicroseconds(degreesToMove * m_PWMPerDegree);
}
