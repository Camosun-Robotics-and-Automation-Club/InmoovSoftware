#ifndef STANDARD_SERVO_H
#define STANDARD_SERVO_H

#include <Arduino.h>
#include <Servo.h>

/*
    Repersents one servo of the robot
*/
class StandardServo {
    public:
        /*
            Default constuctor
        */
        StandardServo();
        /*
            Constructor only specifying pin number
        */
        StandardServo(byte pin);

        /*
            Constructor specifying all attributes
        */
        StandardServo(byte pin, 
                      int minPWMTime,           //Min PWM time of the servo
                      int maxPWMTime,           //Max PWM time of the servo
                      int degreeRange,          //The range of the servo in degrees(starting at 0)
                      float outputGearRatio,    //Gear ration of the part that the servo is connected to(mathamatical representation eg. 0.5 = 2/1)
                      bool reverseDirection,    //Is the rotation of the part different to that of the servo?
                      int minRotation,          //Min rotation of the part(in degrees)
                      int maxRotation,          //Max rotation of the part(in degrees) 
                      int startingRotation);    //The rotation of the part to set when the servo is started(in degrees relative to the min/max Rotation)
        
        /*
            Modifed arduino standard map function that uses floats
            Remaps x in the range in_min to in_max, to the range out_min to out_max
        */
        float mapf(float x, float in_min, float in_max, float out_min, float out_max);

        /*
            Returns the change in PWM time to rotate the part the given number of degrees
        */
        float degreesToPWM(float degrees);
        
        /*
            Initializes the servo and sets it to its default rotation
        */
        void attach();

        /* 
            Move the robot a given amount from its current position(in degrees)
            This is relative to the min/max Rotation(0=minRotation)
            Will constrain the move to min and max rotation
            Returns true if the move was in bounds, returns false if the move was constrained
        */
        bool moveRelative(float degreesToMove);

        /*
            Move the robot to a specific location(in degrees)
            This is relative to the min/max Rotation(0=minRotation)
            Will constrain the move to min and max rotation
            Returns true if the move was in bounds, returns false if the move was constrained
        */
        bool moveAbsolute(float degree);

        /*
            Returns the gear ratio
        */
        float getGearRatio();

        /*
            Returns the current position of the robot in degrees
        */
        float getCurrentRotation();

    private:
        /*
            Writes the target PWM time to the servo
            Contrains move to the min/max rotation values
            Returns false if the move was constrained
        */
        bool moveToTargetMicroseconds(float target);

        byte m_pin = 1;
        int m_minPWMTime = 1000;  
        int m_maxPWMTime = 2000;  
        int m_degreeRange = 180;  
        
        float m_outputGearRatio = 1;    
        bool m_reverseDirection = 0;    
        int m_minRotation = 1000;       
        int m_maxRotation = 2000;
        int m_minRotationDegrees = 0;       
        int m_maxRotationDegrees = 180;
        int m_rotationRangeDegrees = 180;       
        int m_startingRotation = 1500;  

        int m_currentRotation = 1500;  
        Servo m_servo;
};

#endif
