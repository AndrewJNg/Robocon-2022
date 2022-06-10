// motor control system for TB6612FNG motor driver
// Also includes PS3 to motor control


//  motor control pin layout   [ Left Front, Right Front , Back Left , Back Right]
const byte motorPin1[] =  {17, 4, 18, 15};
const byte motorPWM[] = {5,  16, 19, 2};

//const byte motorPin1[] =  {15,4, 17, 18};
//const byte motorPWM[] = {2,  16, 5, 19}

//const byte motorPin2[] = {22, 2, 12, 17};
const byte motorChannel[] = {6, 7, 8, 9};
//const byte motorSTBY[] = {27};

int motor_Speed[] = {0, 0, 0, 0};
const byte PWM_resolution = 8;//16;
const int PWM_resolution_max_value = 255;//65536;


void motor(int Speed[])
{
  // invert back motors of the system
  Speed[0] = Speed[0];
  Speed[1] = Speed[1];
  Speed[2] = -Speed[2];
  Speed[3] = -Speed[3];

 // for loop to run each motors individually
  for (int x = 0; x < sizeof(motorPin1); x++)
  {

    if (Speed[x] > 0)
    { // Forward
      digitalWrite(motorPin1[x], HIGH);
      ledcWrite(motorChannel[x] , abs(Speed[x]));
    }
    else if (Speed[x] < 0)
    { // Reverse
      digitalWrite(motorPin1[x], LOW);
      ledcWrite(motorChannel[x] , abs(Speed[x]));
    }
    else
    { //Stop
      digitalWrite(motorPin1[x], LOW);
      ledcWrite(motorChannel[x] , 0);
    }
  }
  
}

void PS3_move(int LX, int LY, int RX , int RY)
{
  // angle from 0 to 2*pi
  float angle = PS3_LeftAnalogStickAngle (LX, LY)  ;

  //Speed  (range of 0 to 100)
  float Speed_total_percent = PS3_LeftAnalogStickSpeed(LX, LY);

  // turn speed for rotational movement
  float turn_Speed = 0;

  // filter to ignore inputs below 15 from controller for rotation only
  if (abs(RX) > 15) turn_Speed = map(RX, -128, 127 , -50, 50);


  /*Mecanum wheels programming instructions found on this website
    https://seamonsters-2605.github.io/archive/mecanum
    similar principle is applied, however the direction of motion was changed (clockwise being positive angle)
  */

  motor_Speed[0] = map(sin(angle + (1 * PI) / 4) * Speed_total_percent * 100, -10000, 10000, -PWM_resolution_max_value, PWM_resolution_max_value);
  motor_Speed[1] = map(sin(angle + (3 * PI) / 4) * Speed_total_percent * 100, -10000, 10000, -PWM_resolution_max_value, PWM_resolution_max_value);
  motor_Speed[2] = map(sin(angle + (3 * PI) / 4) * Speed_total_percent * 100, -10000, 10000, -PWM_resolution_max_value, PWM_resolution_max_value);
  motor_Speed[3] = map(sin(angle + (1 * PI) / 4) * Speed_total_percent * 100, -10000, 10000, -PWM_resolution_max_value, PWM_resolution_max_value);

  //apply turn Speed to allow control using right analog stick
  motor_Speed[0] = motor_Speed[0] + turn_Speed;
  motor_Speed[1] = motor_Speed[1] - turn_Speed;
  motor_Speed[2] = motor_Speed[2] + turn_Speed;
  motor_Speed[3] = motor_Speed[3] - turn_Speed;

  // run all motors with according speeds
  motor(motor_Speed);

}

//void smallRot(int speed, float angle , int rotateSpeed)
//{
//  Speed_total_percent = 50;
//  
//  motor_Speed[0] = map(sin(angle + (1 * PI) / 4) * Speed_total_percent * 100, -10000, 10000, -PWM_resolution_max_value, PWM_resolution_max_value);
//  motor_Speed[1] = map(sin(angle + (3 * PI) / 4) * Speed_total_percent * 100, -10000, 10000, -PWM_resolution_max_value, PWM_resolution_max_value);
//  motor_Speed[2] = map(sin(angle + (3 * PI) / 4) * Speed_total_percent * 100, -10000, 10000, -PWM_resolution_max_value, PWM_resolution_max_value);
//  motor_Speed[3] = map(sin(angle + (1 * PI) / 4) * Speed_total_percent * 100, -10000, 10000, -PWM_resolution_max_value, PWM_resolution_max_value);
//
//  //apply turn Speed to allow control using right analog stick
//  motor_Speed[0] = motor_Speed[0] + turn_Speed;
//  motor_Speed[1] = motor_Speed[1] - turn_Speed;
//  motor_Speed[2] = motor_Speed[2] + turn_Speed;
//  motor_Speed[3] = motor_Speed[3] - turn_Speed;
//
//  // run all motors with according speeds
//  motor(motor_Speed);
//}


//void PS3_move_DPAD()
//{
//  // int Speed = pot_Value = map(analogRead(pot_Pin), 0, 4095, 0, PWM_resolution_max_value) ;
//  int Speed =150 ;
//
//  if ((Ps3.data.button.up == 0)  && (Ps3.data.button.right == 0) && (Ps3.data.button.down == 0) && (Ps3.data.button.left == 0) && (Ps3.data.button.l1 == 0) && (Ps3.data.button.r1 == 0))
//  {
//    motor_Speed[0] = 0;
//    motor_Speed[1] = 0;
//    motor_Speed[2] = 0;
//    motor_Speed[3] = 0;
//  }
//  else if ((Ps3.data.button.up == 1)  && (Ps3.data.button.right == 0) && (Ps3.data.button.down == 0) && (Ps3.data.button.left == 0))
//  {
//    motor_Speed[0] = +Speed;
//    motor_Speed[1] = +Speed;
//    motor_Speed[2] = +Speed;
//    motor_Speed[3] = +Speed;
//  }
//  else if ((Ps3.data.button.up == 1)  && (Ps3.data.button.right == 1) && (Ps3.data.button.down == 0) && (Ps3.data.button.left == 0))
//  {
//    motor_Speed[0] = +Speed;
//    motor_Speed[1] = 0;
//    motor_Speed[2] = 0;
//    motor_Speed[3] = +Speed;
//  }
//  else if ((Ps3.data.button.up == 0)  && (Ps3.data.button.right == 1) && (Ps3.data.button.down == 0) && (Ps3.data.button.left == 0))
//  {
//    motor_Speed[0] = +Speed;
//    motor_Speed[1] = -Speed;
//    motor_Speed[2] = -Speed;
//    motor_Speed[3] = +Speed;
//  }
//  else if ((Ps3.data.button.up == 0)  && (Ps3.data.button.right == 1) && (Ps3.data.button.down == 1) && (Ps3.data.button.left == 0))
//  {
//    motor_Speed[0] = 0;
//    motor_Speed[1] = -Speed;
//    motor_Speed[2] = -Speed;
//    motor_Speed[3] = 0;
//  }
//  else if ((Ps3.data.button.up == 0)  && (Ps3.data.button.right == 0) && (Ps3.data.button.down == 1) && (Ps3.data.button.left == 0))
//  {
//    motor_Speed[0] = -Speed;
//    motor_Speed[1] = -Speed;
//    motor_Speed[2] = -Speed;
//    motor_Speed[3] = -Speed;
//  }
//  else if ((Ps3.data.button.up == 0)  && (Ps3.data.button.right == 0) && (Ps3.data.button.down == 1) && (Ps3.data.button.left == 1))
//  {
//    motor_Speed[0] = -Speed;
//    motor_Speed[1] = 0;
//    motor_Speed[2] = 0;
//    motor_Speed[3] = -Speed;
//  }
//  else if ((Ps3.data.button.up == 0)  && (Ps3.data.button.right == 0) && (Ps3.data.button.down == 0) && (Ps3.data.button.left == 1))
//  {
//    motor_Speed[0] = -Speed;
//    motor_Speed[1] = +Speed;
//    motor_Speed[2] = +Speed;
//    motor_Speed[3] = -Speed;
//  }
//  else if ((Ps3.data.button.up == 1)  && (Ps3.data.button.right == 0) && (Ps3.data.button.down == 0) && (Ps3.data.button.left == 1))
//  {
//    motor_Speed[0] = 0;
//    motor_Speed[1] = Speed;
//    motor_Speed[2] = Speed;
//    motor_Speed[3] = 0;
//  }
//  else if ((Ps3.data.button.l1 == 1) && (Ps3.data.button.r1 == 0))
//  {
//    motor_Speed[0] = -Speed;
//    motor_Speed[1] = Speed;
//    motor_Speed[2] = -Speed;
//    motor_Speed[3] = Speed;
//  }
//  else if ((Ps3.data.button.l1 == 0) && (Ps3.data.button.r1 == 1))
//  {
//    motor_Speed[0] = Speed;
//    motor_Speed[1] = -Speed;
//    motor_Speed[2] = Speed;
//    motor_Speed[3] = -Speed;
//  }
//  else
//  {
//    motor_Speed[0] = 0;
//    motor_Speed[1] = 0;
//    motor_Speed[2] = 0;
//    motor_Speed[3] = 0;
//  }
//
//  motor(motor_Speed);
//}

void Movement_setup()
{
  // movement setup

  // activate Standby pin 
//  for (int x = 0; x < sizeof(motorSTBY); x++)
//  {
//    pinMode(motorSTBY[x], OUTPUT);
//  }

// set motor pins as output
  for (int x = 0; x < sizeof(motorPin1); x++)
  {
    pinMode(motorPin1[x], OUTPUT);
//    pinMode(motorPin2[x], OUTPUT);
    ledcSetup(motorChannel[x], 5000, PWM_resolution);
    ledcAttachPin(motorPWM[x] , motorChannel[x] );
  }
}
