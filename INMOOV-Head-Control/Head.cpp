#include "Head.h"
#include "StandardServo.h"

Head::Head(StandardServo eyesPanServo,
            StandardServo eyesTiltServo,
            StandardServo jawServo,
            StandardServo headYawServo,
            StandardServo headPitchServo,
            StandardServo headRollServo,
            int servoUpdataRate)                //Number of times per second the servos update
{   
    m_allServos[0] = eyesPanServo;
    m_allServos[1] = eyesTiltServo;
    m_allServos[2] = jawServo;
    m_allServos[3] = headYawServo;
    m_allServos[4] = headPitchServo;
    m_allServos[5] = headRollServo;

    m_servoUpdateRate = servoUpdataRate;

    for(byte i = 0; i < 6; i++){    // Set all current/target rotations to the servos' starting rotation
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
    //if the interrupt flag is at its default state, set its reference to a false bool
    if(interruptFlag == 0){
        const bool interrupt = false;
        interruptFlag = &interrupt;
    }
    //Do movement stuff....
    float updateRate = float(m_servoUpdateRate)/1000.0;//Update rate of the servos in ms^-1
    float rotationsPerStep[6];
    for(byte i; i < 6; i++){  //For each servo
        float rotationAmount = m_targetRotations[i] - m_currentRotations[i];  //Get the range between the current rotation and the target rotation
        rotationsPerStep[i] = rotationAmount / (updateRate * duration);  //Get the degrees per step
        m_currentRotations[i] = m_targetRotations[i];
        //TODO: Check if the rotation per step is to small for the servo to register
    }

    for(byte i = 0; i < updateRate * duration;i++){
        for(byte s = 0; s < 6; s++){  //For each servo
            m_allServos[s].moveRelative(rotationsPerStep[s]);
        }
        delay(1/(updateRate * duration));
    }


    return false;

}
