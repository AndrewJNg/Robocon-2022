/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-stepper-motor-28byj-48-uln2003/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  
  Based on Stepper Motor Control - one revolution by Tom Igoe
*/

// For L298N Driver
#include <Stepper.h>

// Constant Variables
const int stepperSpeed = 300;       // Stepper Speed in RPM
const int stepsPerRevolution = 200; // Steps per Revolution for Stepper (Rated - Don't Change)

// Internal Variables
static int stepCount = 0;
static const int stepMax = 14900;
static const int stepMin = 100;

// ULN2003 Motor Driver Pins
#define IN1 13
#define IN2 12
#define IN3 14
#define IN4 27

// Stepper Definition
Stepper myStepper(stepsPerRevolution, IN1, IN2, IN3, IN4);

// Stpper Initialization
void Stepper_setup() {
  // Speed in RPM
  myStepper.setSpeed(stepperSpeed);
}

// Stepper Service Routine
void Stepper_run(int L2, int R2) {
  // Gripper Going Downwards
  if(!L2 && R2) {
    if(stepCount > stepMin) {
      myStepper.step(stepsPerRevolution);
      stepCount = stepCount - stepsPerRevolution;
    }
    Serial.print("Gripper Going Downwards. Step: ");
    Serial.println(stepCount);
  }

  // Gripper Going Upwards
  if(L2 && !R2) {
    if(stepCount < stepMax) {
      myStepper.step(-stepsPerRevolution);
      stepCount = stepCount + stepsPerRevolution;
    }
    Serial.print("Gripper Going Upwards. Step: ");
    Serial.println(stepCount);
  }
}
