
#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

class UltraSonic {

    public:
        UltraSonic(int _pin);
        void init();
        void _loop();

        float getDistance();


    private:
        int pin;

        int beamState = 0;
        unsigned long beamStateTimer = 0;
        unsigned long beamStateTimerMicros = 0;

        void sendBeam();
        void receiveBeam();
        unsigned long beamTime;
        float lastDistance = 0;

        int beamInterval = 50;
        unsigned long lastBeamTime = 0;
        
        bool beamed = false;
        

};

#endif