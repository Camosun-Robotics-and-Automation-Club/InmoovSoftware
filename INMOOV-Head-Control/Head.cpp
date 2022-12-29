#include "Head.h"
#include "StandardServo.h"

Head::Head(StandardServo eyesPanServo,
            StandardServo eyesTiltServo,
            StandardServo jawServo,
            StandardServo headYawServo,
            StandardServo headPitchServo,
            StandardServo headRollServo,
            int servoUpdataRate)                                                //Number of times per second the servos update
{   
    m_allServos[0] = eyesPanServo;                                              //Add each servo object to the all servos array
    m_allServos[1] = eyesTiltServo;
    m_allServos[2] = jawServo;
    m_allServos[3] = headYawServo;
    m_allServos[4] = headPitchServo;
    m_allServos[5] = headRollServo;

    m_servoUpdateRate = servoUpdataRate;                                        //How many times per second the servos' position is updated

    for(byte i = 0; i < 6; i++){                                                // Set all current/target rotations to the servos' starting rotation
        m_currentRotations[i] = m_allServos[i].getCurrentRotation();
        m_targetRotations[i] = m_allServos[i].getCurrentRotation();
    }
}

void Head::attach(){
    for(byte i = 0; i < 6; i++){
        m_allServos[i].attach();
    }
}

void Head::setEyeRotationTarget(float pan, 
                                float tilt)
{
    m_targetRotations[0] = pan;
    m_targetRotations[1] = tilt;
}

void Head::setJawRotationTarget(float angle){
    m_targetRotations[2] = angle;
}

void Head::setHeadRotationTarget(float yaw, 
                                float pitch, 
                                float roll)
{
    m_targetRotations[3] = yaw;
    m_targetRotations[4] = pitch;
    m_targetRotations[5] = roll;
}

bool Head::rotateToTarget(float duration, 
                          bool* interruptFlag = 0,
                          bool interruptOnSerial = false)
{   
    bool interrupted = false;
    long startTime = millis();                                                  //Get start time of rotation timer 

    if(interruptFlag == 0){                                                     //if the interrupt flag is at its default state, set its reference to a false bool
        const bool interrupt = false;
        interruptFlag = &interrupt;
    }

    float updateRate = float(m_servoUpdateRate)/1000.0;                         //Update rate of the servos in ms^-1

    float degreesPerStep[6];

    for(byte i; i < 6; i++){                                                    //For each servo
        float rotationAmount = m_targetRotations[i] - m_currentRotations[i];    //Get the range between the current rotation and the target rotation
        degreesPerStep[i] = rotationAmount / (updateRate * duration);           //Get the degrees per step
    }

    float delayPerStep = 1 / updateRate;
    int count = 1;

    while(count <= (updateRate * duration)){                                    //Loop until count has reached number of steps needed
        if(interruptOnSerial == 1 && Serial.available() > 0){                   //Exit loop if there is anything in the serial buffer
            interrupted = true;
            break;
        }

        if(*interruptFlag == true){                                             //Exit the loop if the interruptFlag is high
           interrupted = true;
           break; 
        }

        if((millis() - startTime) >  (delayPerStep * count)){                   //Timer goes off every delayPerStep
            count++;
            for(byte s = 0; s < 6; s++){                                        //For each servo update its position by one step
                m_currentRotations[s] += degreesPerStep[s];
                m_allServos[s].moveAbsolute(m_currentRotations[s]);
            }
        }
    }

    return interrupted;                                                         //Return true if the loop was interrupted, otherwise return false

}
