#include "Motor.h"

Motor::Motor(int _pinPlus, int _pinMinus, int _minimumPWM, int _maximumPWM) {
    this->pinPlus = _pinPlus;  
    this->pinMinus = _pinMinus;
    this->minimumPWM = _minimumPWM;
    this->maximumPWM = _maximumPWM;

}

void Motor::init(){
    
    SoftPWMBegin();
    SoftPWMSet(this->pinPlus, 0);
    SoftPWMSet(this->pinMinus, 0);

    Serial.println("MOTORS INIT!");
}

int Motor::scaleSpeedToPWM(int _speedPercent) {
    // Begrenze den Eingabewert auf 0–100
    _speedPercent = constrain(_speedPercent, 0, 100);

    if (_speedPercent == 0) return 0; // Kein Signal bei 0%

    int range = maximumPWM - minimumPWM;
    return minimumPWM + (_speedPercent * range) / 100;
}

void Motor::setSpeed(int _speed){

    /*
     Wir skalieren den gebebenen Speed auf 0-100  innerhalb der range von 0-255 unter Berücksichtigung des Minumum wertes
    */
    int speed = this->scaleSpeedToPWM(_speed);
    //Serial.print("Set Motorspeed in %: "); Serial.println(_speed);
    //Serial.print("Set Motorspeed in PWM: "); Serial.println(speed);
    this->targetSpeed = speed;
}

void Motor::setDirection(int _direction){
    //Serial.print("Set Motordirection: "); Serial.println(_direction);
    this->direction = _direction;
}

void Motor::_loop(){

    if(this->targetSpeed != this->actualSpeed || this->direction != this->actualDirection){
        
        this->actualDirection = this->direction;
        if(this->direction == 1){
            SoftPWMSet(this->pinMinus, 0);
            SoftPWMSet(this->pinPlus, this->targetSpeed);
            this->actualSpeed = this->targetSpeed;
            //Serial.println("Motor CCW");
        }
        if(this->direction == 0){
            //CCW
            SoftPWMSet(this->pinPlus, 0);
            SoftPWMSet(this->pinMinus, this->targetSpeed);
            this->actualSpeed = this->targetSpeed;
            //Serial.println("Motor CW 0");
        }    
        
    }



}
