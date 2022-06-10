
const byte motorPin1Launch[] =  {27, 12};
const byte motorPWMLaunch[] = {14,  13};

const byte motorChannelLaunch[] = {10, 11};


int motor_Speed_launch = 0;
const byte PWM_resolution_launch = 8;//16;
const int PWM_resolution_max_value_launch = 255;//65536;


void launch_setup()
{

  for (int x = 0; x < sizeof(motorPin1Launch); x++)
  {
    pinMode(motorPin1[x], OUTPUT);
//    pinMode(motorPin2[x], OUTPUT);
    ledcSetup(motorChannelLaunch[x], 5000, PWM_resolution_launch);
    ledcAttachPin(motorPWMLaunch[x] , motorChannelLaunch[x] );
  }
}


void launch(int Speed, int startMotor) 
{
   if (startMotor) {
     // for loop to run each motors individually
    for (int x = 0; x < sizeof(motorPin1Launch); x++)
    {
  
      if (Speed > 0)
      { // Forward
        digitalWrite(motorPin1Launch[x], HIGH);
        ledcWrite(motorChannelLaunch[x] , abs(Speed));
      }
      else if (Speed < 0)
      { // Reverse
        digitalWrite(motorPin1[x], LOW);
        ledcWrite(motorChannelLaunch[x] , abs(Speed));
      }
      else
      { //Stop
        digitalWrite(motorPin1[x], LOW);
        ledcWrite(motorChannelLaunch[x] , 0);
      }
    }
   }
   else if (!startMotor) {
          for (int x = 0; x < sizeof(motorPin1Launch); x++) {
            digitalWrite(motorPin1[x], LOW);
            ledcWrite(motorChannelLaunch[x] , 0);
          }
   }
}
