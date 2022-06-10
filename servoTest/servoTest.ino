#include "PWMServo.h"

const int servoPin = 32;
// Scooper1 = 25, Scooper2 = 26, GripperLeft = 32, GripperRight = 33;

// Constant Variables
static const int WaitTime = 3000;     // Scooper Wait Time in millis
static const float Speed = 0.3;    // Gripper Speed in Degrees per Iteration
static const float MaxGripDeg = 160;      // Maximum Gripper Servo Angle in Degrees
static const float MinGripDeg = 20;       // Minimum Gripper Servo Angle in Degrees

void Servo_setup() {
  PWMsetup(1, servoPin);

  GripperPos = MinGripDeg;
}




void setup() {
  // put your setup code here, to run once:
  Servo_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  setPos(1, 90);
  

}
