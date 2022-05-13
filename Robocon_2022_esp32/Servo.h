#include <Servo.h>
//https://randomnerdtutorials.com/esp32-servo-motor-web-server-arduino-ide/

static const int servoPin = 4;

Servo servo1;

void Servo_setup() {
  servo1.attach(servoPin);
}

void Servo_run(int posDegrees) {
  servo1.write(posDegrees);

}
