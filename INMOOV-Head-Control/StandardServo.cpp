#include <Arduino.h>
#include <Servo.h>
#include "StandardServo.h"

StandardServo::

StandardServo::StandardServo(byte pin){
  m_pin = pin; 
}

StandardServo::StandardServo(byte pin, 
                            int minPWMTime,
                            int maxPWMTime,
                            int degreeRange,                
                            float outputGearRatio,          
                            bool reverseDirection,
                            int minRotation, 
                            int maxRotation, 
                            int startingRotation) {
  m_pin = pin;                                              //Data pin number for the servo
  m_minPWMTime = minPWMTime;                                //Absolute minimum timing for the servo
  m_maxPWMTime = maxPWMTime;                                //Aboslute maximum timing for the servo
  m_degreeRange = degreeRange;                              //The range of rotation for the servo in degrees

  m_outputGearRatio = outputGearRatio;                      //Gear ration of the part that the servo is connected to(mathamatical representation eg. 0.5 = 2/1))
  m_reverseDirection = reverseDirection;                    //Is the rotaion of the servo diffrent to the roation of the part?

  m_rotationRangeDegrees = maxRotation - minRotation;       //The range of the part rotation in degrees

  m_minRotation = mapf((minRotation / m_outputGearRatio),    //PWM time minimum for part to rotate full range
                      0, 
                      m_degreeRange, 
                      m_minPWMTime, 
                      m_maxPWMTime);
                      
  m_maxRotation = mapf((maxRotation / m_outputGearRatio),    //PWM time maximum for part to rotate full range
                      0, 
                      m_degreeRange, 
                      m_minPWMTime, 
                      m_maxPWMTime);

  m_startingRotation = mapf((startingRotation / m_outputGearRatio),  //PWM time to set when the .attach() function is called for home position
                            0, 
                            m_rotationRangeDegrees, 
                            m_minRotation, 
                            m_maxRotation);

  m_currentRotation = startingRotation;                     //Current PWM time of the servo
}

float StandardServo::mapf(float x, float in_min, float in_max, float out_min, float out_max) {
            return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

bool StandardServo::moveToTargetMicroseconds(float target){   
  bool validMove;
  if((target > m_maxRotation) || (target < m_minRotation)){ //Check if target rotation is in bounds
    validMove = false;
  }else{
    validMove = true;
  }

  target = constrain(target, m_minRotation, m_maxRotation); //Constain target roation to bounds

  if(m_reverseDirection){
    m_servo.writeMicroseconds(int(mapf(target,
                                  m_minRotation,
                                  m_maxRotation,
                                  m_maxRotation,
                                  m_minRotation)));         //Write target rotation flipped to servo
  }else{
    m_servo.writeMicroseconds(int(target));                 //Write target rotation to servo
  }

  m_currentRotation = target;                               //Update current posistion
  return validMove;                                         //Return if the move was in bounds
  
}

void StandardServo::attach() {
  m_servo.attach(m_pin);                                    //Attach the servo
  moveToTargetMicroseconds(m_startingRotation);             //Rotate to the starting rotation
  m_currentRotation = m_startingRotation;                   //Update the current rotation
}

bool StandardServo::moveRelative(float degreesToMove) {
  int newRotation = m_currentRotation + (mapf((degreesToMove / m_outputGearRatio),
                                            0, 
                                            m_rotationRangeDegrees, 
                                            m_minRotation,                     
                                            m_maxRotation)) - m_minRotation;  //Remap the input degrees to servo PWM time using the gear ratio
                                                                              //and add it to the current rotation to create a new rotation
  Serial.println(newRotation);
  return moveToTargetMicroseconds(newRotation);             // Move to that new rotation
} 

bool StandardServo::moveAbsolute(float degree){
  return moveToTargetMicroseconds(mapf((degree / m_outputGearRatio),
                                        0, 
                                        m_rotationRangeDegrees, 
                                        m_minRotation, 
                                        m_maxRotation));     //Remap the input degrees to servo PWM time using the gear ratio
}

float StandardServo::getGearRatio(){
  return m_outputGearRatio;
}

float StandardServo::getCurrentRotation(){
  return mapf(m_currentRotation,
            m_minPWMTime, 
            m_maxPWMTime, 
            0, 
            m_degreeRange * m_outputGearRatio);             //Remap the PWM timing of the servo to degrees on rotation on the robot
}
            
