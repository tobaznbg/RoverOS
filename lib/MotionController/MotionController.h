#ifndef MOTIONCONTROLLER_H
#define MOTIONCONTROLLER_H

#include "Motor.h"
#include "UltraSonic/UltraSonic.h"
#include "Infrared/Infrared.h"

class MotionController {

    public:
        MotionController(Motor& _motorLeft, Motor& _motorRight);
        void init();
        void _loop();

        void setMotion(float _power, float _turn);

    private:
        Motor& motorLeft;
        Motor& motorRight;
        
        float power = 0;
        float turn = 0;

        bool hasChanged = false;

        bool motionAllowed = true;


};
#endif