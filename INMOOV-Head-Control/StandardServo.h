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
        byte m_pin;
        Servo m_servo;
        float m_PWMPerDegree;
        int m_minRotation;
        int m_maxRotation;
        bool m_reverseDirection;
        int m_defaultRotation;
        int m_currentLocation;
};

#endif
