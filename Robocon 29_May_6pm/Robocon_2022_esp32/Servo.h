#include <Servo.h>

// Servo Pins
static const int servoPin1 = 25;
static const int servoPin2 = 26;
static const int servoPin3 = 32;
static const int servoPin4 = 33;

// Constant Variables
static const int ScooperWaitTime = 3;     // Scooper Wait Time in Seconds
static const int GateWaitTime = 10;        // Gate Wait Time in Seconds
static const float GripperSpeed = 0.3;    // Gripper Speed in Degrees per Iteration
static const float MaxGripDeg = 160;      // Maximum Gripper Servo Angle in Degrees
static const float MinGripDeg = 20;       // Minimum Gripper Servo Angle in Degrees

// Servo Definitions
Servo Scooper;
Servo Gate;
Servo GripperLeft;
Servo GripperRight;

// Internal Variables
static boolean ScooperReady = true;
static boolean GateReady = true;
static float GripperPos;
static unsigned long ScooperStartTime = 0;
static unsigned long GateStartTime = 0;
static unsigned long TimeElapsedScooper = 0;
static unsigned long TimeElapsedGate = 0;


// Function Prototypes
void run_Scooper(int);
void run_Gate(int);
void run_Gripper(int, int);

// Servos Initialization
void Servo_setup() {
  Scooper.write(0);
  Gate.write(90);
  GripperPos = MinGripDeg;
  Scooper.attach(servoPin1);
  Gate.attach(servoPin2);
  GripperLeft.attach(servoPin3);
  GripperRight.attach(servoPin4);
}

// Servos Service Routine
void Servo_run(int Triangle, int Square, int L1, int R1) {
  run_Scooper(Triangle);
  run_Gate(Square);
  run_Gripper(L1, R1);
}

void run_Scooper(int Triangle) {
  if (Triangle) {
    ScooperStartTime = millis();
    ScooperReady = false;
    Scooper.write(90);
    Serial.println("Scooper Initiated.");
  }
  TimeElapsedScooper = millis() - ScooperStartTime;
  if (!ScooperReady && TimeElapsedScooper >= ScooperWaitTime * 1000)  {
    Scooper.write(0);
    Serial.println("Scooper Reset.");
    ScooperReady = true;
  } 
}

void run_Gate(int Square) {
  if (Square) {
    GateStartTime = millis();
    GateReady = false;;
    Gate.write(0);
    Serial.println("Gate Initiated.");
  }
  TimeElapsedGate = millis() - GateStartTime;
  if (!GateReady &&  TimeElapsedGate >= GateWaitTime * 1000)  {
    Gate.write(90);
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
  GripperLeft.write(GripperPos);
  GripperRight.write(180 - GripperPos);
  
}
