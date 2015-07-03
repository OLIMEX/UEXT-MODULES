// connect MOD-WII-NUNCHUCK to UEXT
// connect Servo motors to A1 and A3


#include <math.h>
#include<Servo.h>
#include "Wire.h"
#include "WiiChuck.h"
#define MAXANGLE 90
#define MINANGLE -90

Servo myservo;
Servo myservo2;
WiiChuck chuck = WiiChuck();
int angleStart, currentAngle;
int tillerStart = 0;
double angle;
float power=0.0;

void setup() {
  Serial.begin(115200);
  myservo.attach(A1);
  myservo.write(50);
  myservo2.attach(A3);
  myservo2.write(50);
  chuck.begin();
  chuck.update();
}

void loop() {
  chuck.update();
  myservo.write((chuck.readRoll()+200)/3);
  myservo2.write(chuck.readPitch()/1.4);
}
