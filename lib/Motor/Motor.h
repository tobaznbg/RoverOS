#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "SoftPWM.h"

class Motor {

    public:
        Motor(int _pinPlus, int _pinMinus, int _minimumPWM, int _maximumPWM);
        void init();
        void _loop();

        void setSpeed(int _speed);              //0-100%
        void setDirection(int _direction);      //CW = 0, CCW = 1

        

    private:
        int pinPlus;  //weil wir davon ausgehen, nach unseren Prinzip, dass wenn wir hier volles Signal anlegen, dass der Motor dann auch entsprechend CW läuft.
        int pinMinus;
        
        int minimumPWM = 60;
        int maximumPWM = 255;

        int targetSpeed = 0;
        int actualSpeed = 0;
        int direction;
        int actualDirection = 0;

        int scaleSpeedToPWM(int _speedPercent);
};

#endif