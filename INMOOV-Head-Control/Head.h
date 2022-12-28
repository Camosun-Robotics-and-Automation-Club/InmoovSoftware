include "StandardServo.h"

class Head {
    public:
        Head(StandardServo eyesPanServo,
            StandardServo eyesTiltServo,
            StandardServo jawServo,
            StandardServo headYawServo,
            StandardServo headPitchServo,
            StandardServo headRollServo,
            int servoUpdataRate);
        void attach();
        void setEyeRotationTarget(float pan, float tilt);
        void setJawRotationTarget(float angle);
        void setHeadRotationTarget(float yaw, float pitch, float roll);
        bool rotateToTarget(float duration, bool* interruptFlag = 0, bool interruptOnSerial = false);
    private:
        //Order: [0]eye pan, [1]eye tilt, [2]jaw, [3]head yaw, [4]head pitch, [5]head roll
        float m_targetRotations[6];
        float m_currentRotations[6];
        StandardServo m_allServos[6];
        int m_servoUpdateRate = 40;
};
