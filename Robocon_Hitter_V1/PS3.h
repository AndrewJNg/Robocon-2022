// Allows control using a PS3 controller by using the github library by jvpernis
//https://github.com/jvpernis/esp32-ps3

#include <Ps3Controller.h>

// PS3 Status Variables
int player = 0;
int battery = 0;

// PS3 Control Variables (Movement) 
int stick_LX;   
int stick_LY;
int stick_RX;
int stick_RY;    

// Micro-movement Variables
int smallUp = 0;
int smallDown = 0;
int smallLeft = 0;
int smallRight = 0;
int smallRotLeft = 0;
int smallRotRight = 0;

// PS3 Control Variables (Servos) 
int Triangle = 0; // 0 = not pressed (hold position), 1 = pressed (Request Scoop)
int shootingSpeed = 150;

int Square = 0;   // 0 = not pressed (hold position), 1 = pressed (Request Ball Release)
int Circle = 0;
int L1 = 0;       // 0 = not pressed (hold position), 1 = pressed (Tighten Gripper) 
int R1 = 0;       // 0 = not pressed (hold position), 1 = pressed (Loosen Gripper)

// PS3 Control Variables (Stepper) 
int L2 = 0;       // 0 = not pressed (hold position), 1 = pressed (Move Gripper Up) 
int R2 = 0;       // 0 = not pressed (hold position), 1 = pressed (Move Gripper Down)

// Internal Variable Changes when PS3 Control changes
void notify()
{
  // Movement
  if ( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ) {
    stick_LX = Ps3.data.analog.stick.lx;
    stick_LY = -Ps3.data.analog.stick.ly;
  }
//  else
//  {
//    stick_LX = 0;
//    stick_LY = 0;
//  }
  if ( abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2 ) {
    stick_RX = Ps3.data.analog.stick.rx;
    stick_RY = -Ps3.data.analog.stick.ry;
  }
//  else
//  {
//    stick_RX = 0;
//    stick_RY = 0;
//  }

// MICRO-MOVEMENTS (TRANSLATION)
  if( Ps3.event.button_down.up ) {
    smallUp = 1;
    Serial.println("Started pressing the up button");
  }
  if( Ps3.event.button_up.up ) {
    smallUp = 0;
    Serial.println("Released the up button");
  }
  if( Ps3.event.button_down.right ) {
    smallRight = 1;
    Serial.println("Started pressing the right button");
  }
  if( Ps3.event.button_up.right ) {
    smallRight = 0;
    Serial.println("Released the right button");
  }
  if( Ps3.event.button_down.down ) {
    smallDown = 1;
    Serial.println("Started pressing the down button");
  }
  if( Ps3.event.button_up.down ) {
    smallDown = 0;
    Serial.println("Released the down button");
  }
  if( Ps3.event.button_down.left ) {
    smallLeft = 1;
    Serial.println("Started pressing the left button");
  }
  if( Ps3.event.button_up.left ) {
    smallLeft = 0;
    Serial.println("Released the left button");
  }
  
  // MICRO-MOVEMENTS (ROTATION)
  if( Ps3.event.button_down.r1 )        smallRotRight = 1;
  if( Ps3.event.button_up.r1 )          smallRotRight = 0;
  if( Ps3.event.button_down.l1 )        smallRotLeft = 1;
  if( Ps3.event.button_up.l1 )          smallRotLeft = 0;

  // SHOOTING SPEED
  // 
  if( Ps3.event.button_down.circle && Circle = 0 ) {
    shootingSpeed += 10;
    Circle = 1;
  }
  if( Ps3.event.button_up.circle )      Circle = 0;
  if( Ps3.event.button_down.square && Square = 0 ) {
    shootingSpeed -= 10;
    Square = 1;
  }
  if( Ps3.event.button_up.square )      Square = 0;

  
  if( Ps3.event.button_down.triangle )  Triangle = 1;
  if( Ps3.event.button_up.triangle )    Triangle = 0;
//  if( Ps3.event.button_down.r1 )        R1 = 1;
//  if( Ps3.event.button_up.r1 )          R1 = 0;
//  if( Ps3.event.button_down.l1 )        L1 = 1;
//  if( Ps3.event.button_up.l1 )          L1 = 0;

  // Stepper
  if( Ps3.event.button_down.r2 )  R2 = 1;
  if( Ps3.event.button_up.r2 )    R2 = 0;
  if( Ps3.event.button_down.l2 )  L2 = 1;
  if( Ps3.event.button_up.l2 )    L2 = 0;
}

void onConnect() {
  Serial.println("Connected.");
}

void PS3_setup()
{
  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("01:02:03:04:05:06");
}

// Helper Function to Calculate Analog Stick Angle
float PS3_LeftAnalogStickAngle (int LX, int LY)
{
  float LX_vector = map(LX, -128, 127, -10000, 10000) / 100;
  float LY_vector = map(LY, -127, 128, -10000, 10000) / 100;
  float angle ;
  if (LY_vector == 0 && LX_vector > 0) angle = PI / 2;
  else if (LY_vector == 0 && LX_vector < 0) angle = 3 * PI / 2;
  else if (LY_vector == 0 && LX_vector == 0) angle = 0;
  else angle = atan(abs(LX_vector) / abs(LY_vector));

  if ( LX_vector > 0 && LY_vector > 0) angle = angle;
  else if ( LX_vector > 0 && LY_vector < 0) angle = PI - angle ;
  else if ( LX_vector < 0 && LY_vector < 0) angle = PI + angle;
  else if ( LX_vector < 0 && LY_vector > 0) angle = 2 * PI - angle;

  return angle;
}

// Helper Function to Calculate Analog Stick Speed
float PS3_LeftAnalogStickSpeed(int LX, int LY)
{
  float LX_vector = 0;
  float LY_vector = 0;
  if (abs(LX) > 15) LX_vector = map(LX, -128, 127, -10000, 10000) / 100;
//  else LX_vector = 0;
  if (abs(LY) > 15) LY_vector = map(LY, -127, 128, -10000, 10000) / 100;
//  else LY_vector = 0;
  float Speed = sqrt(LX_vector * LX_vector + LY_vector * LY_vector);
  if (Speed > 100) Speed = 100;

  return Speed;
}
