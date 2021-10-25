
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  180 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  1000 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

long int gap = 2000;
long int st;
void setup() {
//  bootM4();
  Serial.begin(9600);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates 
  //initiate servos to 0 degree
  pwm.setPWM(0, 0, SERVOMIN);
  pwm.setPWM(1, 0, SERVOMIN);
  pwm.setPWM(2, 0, SERVOMIN);
  pwm.setPWM(3, 0, SERVOMIN);
  pwm.setPWM(4, 0, SERVOMIN);
  pwm.setPWM(5, 0, SERVOMIN);
  st=millis();
}

void loop() {
//  Serial.println(millis()-st);
  pwm.rotate(0);
  delay(20);
  pwm.rotate(1);
  delay(20);
  pwm.rotate(2);
  delay(20);
  pwm.rotate(3);
  delay(20);
  pwm.rotate(4);
  delay(20);
  pwm.rotate(5);
  delay(20);
}
