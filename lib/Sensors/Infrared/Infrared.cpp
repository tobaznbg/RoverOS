
#include "Infrared.h"


Infrared::Infrared(int _pin) {
    pin = _pin;
    pinMode(pin, INPUT);
}

bool Infrared::getState(){
        if(lastState == 0){
            return true;
        }else{
            return false;
        }
}

void Infrared::_loop() {
    

    if(millis() - lastRead >= readInterval){
        lastRead = millis();
        lastState = digitalRead(pin);
    }


}