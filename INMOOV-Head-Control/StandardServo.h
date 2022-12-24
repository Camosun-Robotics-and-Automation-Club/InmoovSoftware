#ifndef STANDARD_SERVO_H
#define STANDARD_SERVO_H

#include <Arduino.h>
#include <Servo.h>

class StandardServo {
    public:
        StandardServo(byte pin);
        StandardServo(byte pin, float PWMPerDegree, int minRotation, int maxRotation ,bool reverseDirection, int defaultRotation);
        void attach();
        void moveTowardsTarget(float degreesToMove);
    private:
        byte m_pin = 1;
        Servo m_servo;
        float m_PWMPerDegree = 1000/180;
        int m_minRotation = 1000;
        int m_maxRotation = 2000;
        bool m_reverseDirection = 0;
        int m_defaultRotation = 1500;
        int m_currentRotation = 1500;
};

#endif