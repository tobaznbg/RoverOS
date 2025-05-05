#include <Arduino.h>

//PIN ASSIGNMENT
#define MOTORS_LEFT_PLUS 2
#define MOTORS_LEFT_MINUS 3

#define MOTORS_RIGHT_PLUS 4
#define MOTORS_RIGHT_MINUS 5


#include "Motor.h"
/*
  Jeweils für CW

  Logic 0
  Plus 0, Minus = speed

  Logic 1
  Plus speed, Minus = 0
*/

Motor motorsLeft(MOTORS_LEFT_PLUS, MOTORS_LEFT_MINUS, 60, 255);
Motor motorsRight(MOTORS_RIGHT_PLUS, MOTORS_RIGHT_MINUS, 60, 255);

#include "UltraSonic/UltraSonic.h"
UltraSonic sonic(10);

#include "Infrared/Infrared.h"
Infrared infraredLeft(8);
Infrared infraredRight(7);

#include "MotionController.h"
MotionController motionController(motorsLeft, motorsRight);

#include "Autopilot.h"
Autopilot roverPilot(motionController, sonic, infraredLeft, infraredRight);






void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, RoverOS!");

  sonic.init();
  motionController.init();

  roverPilot.init();
  roverPilot.setMaxSpeed(100);
  roverPilot.setArmed(true);

  //motionController.setMotion(0, -0.1);
  //motionController.setSpeed(30);
  //motionController.setMotion("AI");
 
 
}

unsigned long lastChange = 0;
int lastMotion = 0;

void loop() {
  
  /*if(millis() - lastChange > 2000){
    lastChange = millis();
    
    if(lastMotion == 0){
      motionController.setSpeed(50);
      motionController.setMotion("FW");
      lastMotion = 1;
      return;
    }

    if(lastMotion == 1){
      motionController.setSpeed(10);
      motionController.setMotion("L");
      lastMotion = 2;
      return;
    }

    if(lastMotion == 2){
      motionController.setSpeed(10);
      motionController.setMotion("R");
      lastMotion = 3;
      return;
    }

    if(lastMotion == 3){
      motionController.setSpeed(50);
      motionController.setMotion("BW");
      lastMotion = 4;
      return;
    }

    if(lastMotion == 4){
      motionController.setMotion("BRAKE");
      lastMotion = 0;
      return;
    }
    
    
  }*/
  //Serial.print("L:"); Serial.print(infraredLeft.getState()); Serial.print(" | R: "); Serial.println(infraredRight.getState());  

  sonic._loop();
  infraredLeft._loop();
  infraredRight._loop();

  motionController._loop();
  motorsLeft._loop();
  motorsRight._loop();

  roverPilot._loop();
}
