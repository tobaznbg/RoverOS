#ifndef AUTOPILOT_H
#define AUTOPILOT_H


#include <Arduino.h>
#include "MotionController.h"
#include "UltraSonic/UltraSonic.h"
#include "Infrared/Infrared.h"

class Autopilot {

    public:
        Autopilot(MotionController& motionController, UltraSonic& sonic, Infrared& infraredLeft, Infrared& infraredRight);
        void init();
        void _loop();

        void setArmed(bool _armed);
        void setMaxSpeed(int _speed);

    private:
        MotionController& motionController;
        UltraSonic& sonic;
        Infrared& infraredLeft;
        Infrared& infraredRight;

        bool armed = false;
        int maxSpeed = 0;

        float computeSpeedFromDistance(float distanceCm);
        float safetyDistance = 15.0;
        float maxSpeedDistance = 35.0;

};


#endif