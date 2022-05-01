//#include "OTA.h"
#include "PS3.h"
//#include "User_interface.h"
#include "Movement.h"
#include "MPU6050.h"

void setup() {
  analogReadResolution(12);
  Serial.begin(115200);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  OTA_setup();
  PS3_setup();
  Movement_setup();
//  User_interface_setup();
  //MPU6050_setup();
  
  while (!Ps3.isConnected())
  {
    motor(motor_Speed);
//    OLED_display();
//    OLED_display();
    PS3_move(stick_LX, stick_LY, stick_RX , stick_RY);
//    server.handleClient();
    delay(1);
  }
}

void loop() {

  //  pot_Value = map(analogRead(pot_Pin), 0, 4095, -65535, 65535) ;
  //   int Speed[] = {pot_Value, -pot_Value, -pot_Value, pot_Value};
  //  Serial.println(pot_Value);
  // Speed[] = {0, 0, 0, 0};

//  OLED_display();
  PS3_move(stick_LX, stick_LY, stick_RX , stick_RY);

//  server.handleClient();
  delay(1);

}
