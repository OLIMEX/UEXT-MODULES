// speaker connected to D11
// MOD-WII-NUNCHUCK connected to UEXT

#include <math.h>

#include "Wire.h"
#include "WiiChuck.h"

#define MAXANGLE 90
#define MINANGLE -90

WiiChuck chuck = WiiChuck();
int angleStart, currentAngle;
int tillerStart = 0;
double angle;
float power=0.0;

void setup() {
  Serial.begin(115200);
  chuck.begin();
  chuck.update();
}

void loop() {
  tone(11,chuck.readRoll()+900,(chuck.readPitch()/3)+10);
  chuck.update();
}
