// connect MOD-WII-NUNCHUCK to UEXT

#include <math.h>
#include "Wire.h"
#include "WiiChuck.h"
#define MAXANGLE 90
#define MINANGLE -90

WiiChuck chuck = WiiChuck();
int range = 5;

void setup() {
  Serial.begin(115200);
  chuck.begin();
  chuck.update();
  Mouse.begin();
}

void loop() {

  delay(2);
  chuck.update(); 

  int  xDistance=chuck.readJoyX()-13;
  int  yDistance=-(chuck.readJoyY()-6);

  if (chuck.readJoyX()==-1) yDistance=0;
  if (xDistance<0) xDistance=(xDistance*range)/118;
    else xDistance=(xDistance*range)/137;
  if (yDistance<0) yDistance=(yDistance*range)/138;
    else yDistance=(yDistance*range)/117;
    
  if ((xDistance != 0) || (yDistance != 0)) {
    Mouse.move(xDistance, yDistance, 0);
  }

  if (chuck.buttonC) {
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT); 
    }
  } 
  else {
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT); 
    }
  }

  if (chuck.buttonZ) {
    if (!Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.press(MOUSE_RIGHT); 
    }
  } 
  else {
    if (Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.release(MOUSE_RIGHT); 
    }
  }

}
