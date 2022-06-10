
static const int minBit = 1638; // corresponding to 0 deg
static const int maxBit = 7864; // corresponding to 180 deg

//static const int minBit = 1639; // corresponding to 0 deg
//static const int maxBit = 8191; // corresponding to 180 deg

static const int minDeg = 0;
static const int maxDeg = 180;
static const int freq = 50;
const int bitWidth = 16;
int servoPulse;


void PWMsetup(int channel, int pin) {
  ledcSetup(channel, freq,  bitWidth); // 50 Hz, 16-bit width
  ledcAttachPin(pin, channel);   // GPIO pin assigned to channel
}

// Creates a PWM signal by mapping the position of the servo in degrees to 
void setPos(int channel, int deg) {
  servoPulse = map(deg, minDeg, maxDeg, minBit, maxBit);
  ledcWrite(channel, servoPulse);   
}


//
//int ledState = LOW;             // ledState used to set the LED
//unsigned long previousMillis = 0;        // will store last time LED was updated
//const long interval = 5000;           // interval at which to blink (milliseconds)
//void setup() {
//  ledcSetup(1, freq,  bitWidth); // channel 1, 50 Hz, 16-bit width
//  ledcAttachPin(pin1, 1);   // GPIO 23 assigned to channel 1
//
//  ledcSetup(2, freq,  bitWidth); // channel 1, 50 Hz, 16-bit width
//  ledcAttachPin(pin2, 2);   // GPIO 23 assigned to channel 1
//}
//
//  float value = 90;
//  int servoPulse =0;
//void loop() {
//  //      ledcWrite(1, 1638);       // 0 degrees
//  //      ledcWrite(2, 7864);       // 0 degrees
//  //      delay(3000);
//  //      ledcWrite(1, 7864);       // 180 degrees
//  //      ledcWrite(2, 1638);       // 0 degrees
//  //      delay(3000);
// 
//
//  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis >= interval) {
//    // save the last time you blinked the LED
//    previousMillis = currentMillis;
//    if (ledState == LOW) {
//      ledState = HIGH;
//      value = 150;
//      servoPulse = map(value, 0, 180, 1638, 7864);
//      ledcWrite(1, servoPulse);       // 90 degrees
//      
//      value = 30;
//      servoPulse = map(value, 0, 180, 1638, 7864);
//      ledcWrite(2,servoPulse);
////      servoPulse = 20;
//    }
//    else {
//      ledState = LOW;
//      value = 30;
//      servoPulse = map(value, 0, 180, 1638, 7864);
//      ledcWrite(1, servoPulse);       // 180 degrees
//      
//      value = 150;
//      servoPulse = map(value, 0, 180, 1638, 7864);
//      ledcWrite(2,servoPulse);       // 0 degrees
//    }
//  }
//}
