/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 8 servos, one after the other on the
  first 8 pins of the PCA9685

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815
  
  These drivers use I2C to communicate, 2 pins are required to  
  interface.

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// our servo # counter
long int gap = 2000;
long int st;
void setup() {
  bootM4();
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");
  bootM4();
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates 
  pwm.setPWM(0, 0, SERVOMIN);
  pwm.setPWM(2, 0, SERVOMIN);
  pwm.setPWM(4, 0, SERVOMIN);
  pwm.setPWM(8, 0, SERVOMIN);
  pwm.setPWM(12, 0, SERVOMIN);
  st=millis();
}

// You can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. It's not precise!
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;

  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= SERVO_FREQ;   // Analog servos run at ~60 Hz updates
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000000;  // convert input seconds to us
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

void loop() {
  pwm.rotate(0,0);
  delay(10);
  pwm.rotate(2,1);
  delay(10);
  pwm.rotate(4,2);
  delay(10);
  pwm.rotate(8,3);
  delay(10);
  pwm.rotate(12,4);
  delay(10);
//  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen+=1){
//    pwm.setPWM(0, 0, pulselen);
//    Serial.println(pwm.getPulse());
//    delay(10);
//    }
//  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen-=1){
//    pwm.setPWM(0, 0, pulselen);
//    Serial.println(pwm.getPulse());
//    delay(10);
//    }
//  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen+=5) {
//    pwm.setPWM(0, 0, pulselen);
//    delay(10);
//    if(on_check(st, gap)){
//    pwm.setPWM(2, 0, pulselen-10);
//    Serial.println(pwm.getPWM(2));
//    delay(10);
//    }
//    if(on_check(st, gap*2)){
//    pwm.setPWM(4, 0, pulselen-20);
//    delay(10);
//    }
//    if(on_check(st, gap*3)){
//    pwm.setPWM(8, 0, pulselen-30);
//    delay(10);
//    }
//    if(on_check(st, gap*4)){
//    pwm.setPWM(12, 0, pulselen-40);
//    delay(10);
//    }
//
//  delay(10);
//  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen-=5) {
//    pwm.setPWM(0, 0, pulselen);
//    delay(10);
//    if(on_check(st, gap)){
//    pwm.setPWM(2, 0, pulselen+10);
//    delay(10);
//    }
//    if(on_check(st, gap*2)){
//    pwm.setPWM(4, 0, pulselen+20);
//    delay(10);
//    }
//    if(on_check(st, gap*3)){
//    pwm.setPWM(8, 0, pulselen+30);
//    delay(10);
//    }
//    if(on_check(st, gap*4)){
//    pwm.setPWM(12, 0, pulselen+40);
//    delay(10);
//    }
//  }
//  }
}
  // Drive each servo one at a time using writeMicroseconds(), it's not precise due to calculation rounding!
  // The writeMicroseconds() function is used to mimic the Arduino Servo library writeMicroseconds() behavior. 
//  for (uint16_t microsec = USMIN; microsec < USMAX; microsec++) {
//    pwm.writeMicroseconds(servonum, microsec);
//  }
//
//  delay(500);
//  for (uint16_t microsec = USMAX; microsec > USMIN; microsec--) {
//    pwm.writeMicroseconds(servonum, microsec);
//  }
