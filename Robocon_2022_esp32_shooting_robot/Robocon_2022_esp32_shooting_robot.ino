// // Additional Functionalities
// #include "OTA.h"
// #include "User_interface.h"
// #include "MPU6050.h"

// Functional Macros
#include "PS3.h"
#include "Movement.h"
#include "Servo.h"
#include "Shooting.h"

void setup() {
  // Setup Read Spead and Serial monitor's Baud Rate
  analogReadResolution(12);
  Serial.begin(115200);

  // // Additional Macro Setups
  // OTA_setup();
  // User_interface_setup();
  // MPU6050_setup();

  // Macro Setups
  PS3_setup();
  Movement_setup();
  Servo_setup();
  launch_setup();

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
int SpeedMode = 1;
void loop() {
  launch(255);
  // // Additonal Macro Service Routines (Polling)
  // OLED_display();
  // server.handleClient();

  // Macro Service Routines (Polling)
  PS3_move(stick_LX, stick_LY, stick_RX , stick_RY);
  Servo_run(Triangle, Square, L1, R1);

  //  delay(1);
}
