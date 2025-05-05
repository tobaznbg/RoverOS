#include "UltraSonic.h"


UltraSonic::UltraSonic(int _pin) {
    pin = _pin;
}

void UltraSonic::init() {
    
}

void UltraSonic::sendBeam(){

    //4ms warten
    if(beamState == 1 && (millis() - beamStateTimer) > 4){
        
        beamStateTimer = millis();
        beamStateTimerMicros = micros();
        beamState = 2;
    }

    if(beamState == 2){
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
        beamState = 3;
        beamStateTimer = millis();
        beamStateTimerMicros = micros();
    }

    if(beamState == 3 && micros() - beamStateTimerMicros > 2){
        beamStateTimer = millis();
        beamStateTimerMicros = micros();
        beamState = 4;
    }

    if(beamState == 4){
        digitalWrite(pin, HIGH);
        beamState = 5;
        beamStateTimer = millis();
        beamStateTimerMicros = micros();
    }

    if(beamState == 5 && micros() - beamStateTimerMicros > 10){
        beamStateTimer = millis();
        beamStateTimerMicros = micros();
        digitalWrite(pin, LOW);
        beamState = 0;
        beamed = true;
    }
}

void UltraSonic::receiveBeam(){
    pinMode(pin, INPUT);
    float duration = pulseIn(pin, HIGH);

    lastDistance = duration * 0.034 / 2;
    //Serial.print("received: "); Serial.println(lastDistance);
    beamed = false;
}

float UltraSonic::getDistance(){
    return lastDistance;
}

void UltraSonic::_loop(){

    if((millis() - lastBeamTime) > beamInterval){
        lastBeamTime = millis();

        //init beam
        //Serial.println("sending beam");
        beamStateTimer = millis();
        beamStateTimerMicros = micros();
        beamed = false;
        beamState = 1;
        
        
    }

    sendBeam();

    if(beamed){
        receiveBeam();
    }

}