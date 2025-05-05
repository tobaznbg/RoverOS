#include "Autopilot.h"


Autopilot::Autopilot(MotionController& motionController, UltraSonic& sonic, Infrared& infraredLeft, Infrared& infraredRight)
    : motionController(motionController), sonic(sonic), infraredLeft(infraredLeft), infraredRight(infraredRight) {
    // Constructor implementation
}
void Autopilot::init() {
    // Initialization code
   
}

void Autopilot::setArmed(bool _armed) {
    // Set the armed state
    this->armed = _armed;
}

void Autopilot::setMaxSpeed(int _speed) {
    // Set the maximum speed
    this->maxSpeed = _speed;
}


float Autopilot::computeSpeedFromDistance(float distanceCm) {
    
    if (distanceCm <= safetyDistance) return 0.0;
    if (distanceCm >= maxSpeedDistance) return 1.0;

    // Linear skalieren zwischen minDist und maxDist
    return (distanceCm - safetyDistance) / (maxSpeedDistance - safetyDistance);
}


void Autopilot::_loop(){

    if(!armed){
        motionController.setMotion(0,0);
    }

    //erste idee ist, wir fahren einfach mal los und passen dann die geschwindigkeit zum nächsten objekt linear an.
    float acSpeed = computeSpeedFromDistance(sonic.getDistance());
    //Serial.println(acSpeed);
    motionController.setMotion(acSpeed, 0);


}