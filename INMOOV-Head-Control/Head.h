#include "StandardServo.h"

class Head {
    public:
        Head(StandardServo eyesPanServo,
            StandardServo eyesTiltServo,
            StandardServo jawServo,
            StandardServo headYawServo,
            StandardServo headPitchServo,
            StandardServo headRollServo,
            int servoUpdataRate);  //How many times per second the servos' position is updated

        /*
            Attaches all the servos
        */
        void attach();

        /*
            Sets the target positions for the eye servos
        */
        void setEyeRotationTarget(float pan, float tilt);

        /*
            Sets the target positions for the jaw servo
        */
        void setJawRotationTarget(float angle);

        /*
            Sets the target positions for the head rotation servos
        */
        void setHeadRotationTarget(float yaw, float pitch, float roll);

        /*
            Moves all servos to their target rotations over the given duration

            If given the adress of interrupt flag, the rotation will be stopped if the flag is set to true

            If interruptOnSerial is set to true, the rotation will be stopped if there is anything in the serial buffer
            
            Returns true if the loop was interrupted, returns false if not
        */
        bool rotateToTarget(float duration, bool* interruptFlag = 0, bool interruptOnSerial = false);
    private:
        /*
            Order for all arrays : [0]eye pan, [1]eye tilt, [2]jaw, [3]head yaw, [4]head pitch, [5]head roll
        */
        float m_targetRotations[6];     //Target rotations for all the servos
        float m_currentRotations[6];    //Current rotatinos for all the servos
        StandardServo m_allServos[6];   //All the servo objects

        int m_servoUpdateRate = 40;     
        
};
