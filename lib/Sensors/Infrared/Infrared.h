#ifndef INFRARED_H
#define INFRARED_H

#include <Arduino.h>

/*
Infrarot Sensor funktioniert sehr trivial. Wir lesen das digitale Signal.
Reflektiert er sein eigenes Signal = HIGH, frei = LOW.
*/

/*
    Timer A&O

    if(millis() - lastRead > 50){
        lastRead = millis();

    }
    !!!!!!

    Prinzip
    getter & setter
*/

class Infrared {

    public:
        Infrared(int _pin);
        
        void _loop();

        //getter
        bool getState();


    private:
        
        int pin;
        int readInterval = 50;
        unsigned long lastRead = 0;
        int lastState = 0;
};

#endif
