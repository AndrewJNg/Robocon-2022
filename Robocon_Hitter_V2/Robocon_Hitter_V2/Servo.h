//#include <Servo.h>

#include "PWMServo.h"


// Servo Pins
static const int servoPin1 = 26; // Scooper servo 1 13
static const int servoPin2 = 25; // Scooper servo 2

static const int servoPin3 = 32; // Gripper left
static const int servoPin4 = 33; // Gripper right

static const int servoPin5 = 1; // Release servo mechanism


// Constant Variables
static const int ScooperWaitTime = 2000;     // Scooper Wait Time in millis
static const int GateWaitTime = 10000;        // Gate Wait Time in millis
static const float GripperSpeed = 0.3;    // Gripper Speed in Degrees per Iteration
static const float MaxGripDeg = 160;      // Maximum Gripper Servo Angle in Degrees
static const float MinGripDeg = 20;       // Minimum Gripper Servo Angle in Degrees

// Servo Definitions
//Servo Scooper;
//Servo Gate;
//Servo GripperLeft;
//Servo GripperRight;

// Internal Variables
static boolean ScooperReady = true;
static boolean GateReady = true;
static float GripperPos;
static unsigned long ScooperStartTime = 0;
static unsigned long GateStartTime = 0;
static unsigned long TimeElapsedScooper = 0;
static unsigned long TimeElapsedGate = 0;
unsigned long prevMillisScoop = 0;  
unsigned long curMillisScoop = 0;  
unsigned long prevMillisGate = 0;  
unsigned long curMillisGate = 0;  



// Function Prototypes
void run_Scooper(int);
void run_Gate(int);
void run_Gripper(int, int);

// Servos Initialization
void Servo_setup() {
  PWMsetup(1, servoPin1);  // Scooper servo 1 
  PWMsetup(2, servoPin2);  // Scooper servo 2
  PWMsetup(3, servoPin3);  // Gripper left
  PWMsetup(4, servoPin4);  // Gripper right
  PWMsetup(5, servoPin5);  // Release servo mechanism

  setPos(1, 90);
  setPos(2, 180);
  setPos(5, 90);

  GripperPos = MinGripDeg;

 // OLD CODES COMMENTED OUT
 //  Scooper.write(0);
//  Gate.write(90);
//  GripperPos = MinGripDeg;
//  Scooper.attach(servoPin1);
//  Gate.attach(servoPin2);
//  GripperLeft.attach(servoPin3);
//  GripperRight.attach(servoPin4);
}

// Servos Service Routine
void Servo_run(int Triangle, int Square, int L1, int R1) {
    run_Scooper(Triangle); // Linear Actuator
//  run_Gate(Square);
//  run_Gripper(L1, R1);
}


void run_Scooper(int Triangle) {
  if (Triangle && ScooperReady) {
    //ScooperStartTime = millis();
    ScooperReady = false;
    // Scooper servos set to 90 deg
    setPos(1, 30);
    // setPos(2, 90);
    // Scooper.write(90);
    Serial.println("Scooper Initiated.");
  }
  
  curMillisScoop = millis();
  if (!ScooperReady && (curMillisScoop - prevMillisScoop >= ScooperWaitTime))  {
    prevMillisScoop = curMillisScoop;
    // Scooper servos set to 0 deg
    setPos(1, 130);
//    setPos(2, 180);
    //Scooper.write(0);
    Serial.println("Scooper Reset.");
    ScooperReady = true;
  } 
}

void run_Gate(int Square) {
  if (Square) {
    //GateStartTime = millis();
    GateReady = false;
    // Gate set to 0 deg
    setPos(5, 0);
    //Gate.write(0);
    Serial.println("Gate Initiated.");
  }
  curMillisGate = millis();
  if (!GateReady &&  (curMillisGate - prevMillisGate >= GateWaitTime))  {
    prevMillisGate = curMillisGate;
    // Gate set to 90 deg
    setPos(5, 90);
    //Gate.write(90);
    Serial.println("Gate Reset.");
    GateReady = true;
  } 
}

// Function to update Gripper
void run_Gripper(int L1, int R1) {
  if(L1 && !R1) {
    GripperPos = GripperPos - GripperSpeed;
    if(GripperPos < MinGripDeg) GripperPos = MinGripDeg;
    Serial.print("Gripper Loosening. Gripper Position: ");
    Serial.println(GripperPos);
  }
  if(R1 && !L1) {
    GripperPos = GripperPos + GripperSpeed;
    if(GripperPos > MaxGripDeg) GripperPos = MaxGripDeg;
    Serial.print("Gripper Tightening. Gripper Position: ");
    Serial.println(GripperPos);
  }
  setPos(3, GripperPos);
  setPos(4, 180 - GripperPos);
  //GripperLeft.write(GripperPos);
  //GripperRight.write(180 - GripperPos);
  
}
