
#include "MotionController.h"



MotionController::MotionController(Motor& _motorLeft, Motor& _motorRight)
 : 
    motorLeft(_motorLeft), 
    motorRight(_motorRight)
 {

  
}

void MotionController::init(){
    this->motorLeft.init();
    this->motorRight.init();
}

void MotionController::setMotion(float power, float turn){
    this->power = constrain(power, -1.0f, 1.0f);
    this->turn = constrain(turn, -1.0f, 1.0f);
    this->hasChanged = true;
}

void MotionController::_loop(){

    if(this->hasChanged){
        this->hasChanged = false;

        power = constrain(power, -1.0f, 1.0f);
        turn = constrain(turn, -1.0f, 1.0f);

        float absPower = abs(power);

        // ➤ NEU: Panzerdrehung bei power = 0
        if (absPower <= 0.01f && abs(turn) > 0.01f) {
            int pwm = abs(turn) * 100;

            if (turn < 0) {
                motorLeft.setDirection(0);  // CW
                motorRight.setDirection(0); // CW
            } else {
                motorLeft.setDirection(1);  // CCW
                motorRight.setDirection(1); // CCW
            }

            motorLeft.setSpeed(pwm);
            motorRight.setSpeed(pwm);
            //Serial.println("Panzerdrehung bei power = 0");
            return;
        }

        // ➤ Gewichtete Verteilung für Kurve
        float rightFactor = (1.0f - turn) / 2.0f;
        float leftFactor  = (1.0f + turn) / 2.0f;

        int pwmLeft = absPower * 2.0f * leftFactor * 100;
        int pwmRight = absPower * 2.0f * rightFactor * 100;

        pwmLeft = constrain(pwmLeft, 0, 100);
        pwmRight = constrain(pwmRight, 0, 100);

        // ➤ AUTOMATISCH Panzerdrehung, wenn eine Seite ≈ 0
        if (pwmLeft <= 2 || pwmRight <= 2) {
            int pwm = absPower * 100;

            if (turn < 0) {
                motorLeft.setDirection(0);  // CW
                motorRight.setDirection(0); // CW
            } else {
                motorLeft.setDirection(1);  // CCW
                motorRight.setDirection(1); // CCW
            }

            motorLeft.setSpeed(pwm);
            motorRight.setSpeed(pwm);
            //Serial.println("Panzerdrehung automatisch wegen PWM = 0");
            return;
        }

        // ➤ Normale Fahrlogik
        motorLeft.setDirection(power >= 0.0f ? 1 : 0);  
        motorRight.setDirection(power >= 0.0f ? 0 : 1);  

        motorLeft.setSpeed(pwmLeft);
        motorRight.setSpeed(pwmRight);
    }
}