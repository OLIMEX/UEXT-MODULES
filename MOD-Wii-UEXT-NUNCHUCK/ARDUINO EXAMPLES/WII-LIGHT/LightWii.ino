/* Fade through all colors */

// connect MOD-WII-NUNCHUCK to UEXT
// connect MOD-RGB to UEXT
// use UEXTx5 extension

#include <math.h>
#include <Wire.h>
#include "WiiChuck.h"

#define ADDRESS 0xA0
#define MAXANGLE 90
#define MINANGLE -90

WiiChuck chuck = WiiChuck();
int angleStart, currentAngle;
int tillerStart = 0;
double angle;
float power=0.0;

unsigned char R, G, B; 
int Bmov, Gmov;

void setup()
{
  Serial.begin(115200);
  chuck.begin();
  chuck.update();
  pinMode(0,INPUT);
  /* Open I2C */
  Wire.begin();
  
  Wire.beginTransmission(0x48);  //Olimex ADDRESS
  Wire.write(0x05) ;             //MOD-RGB device type address
  Wire.write(ADDRESS);              //MOD-RGB address (0xA0 is the DEFAULT address)
  Wire.write(0x00);              //Stop PWM
  Wire.endTransmission();
  
  Wire.beginTransmission(0x48);  //Olimex ADDRESS
  Wire.write(0x05) ;             //MOD-RGB device type address
  Wire.write(ADDRESS);              //MOD-RGB address (0xA0 is the DEFAULT address)
  Wire.write(0x01);              //Start PWM
  Wire.endTransmission();
  
  R = 105;
  G = 105;
  B = 105; 
}

void loop()
{    
  delay(10);
  chuck.update();
  
  Bmov = chuck.readJoyX();
    if (Bmov<5) 
       if (B<25)
          B=5;
       else B-=20;
    if (Bmov>15) 
       if (B>225)
          B=245;
       else B+=20;
  Gmov = chuck.readJoyY();
    if (Gmov<0)
       if (G<25)
          G=5;
       else G-=20;
    if (Gmov>10)
       if (G>225)
          G=245;
       else G+=20;

  if (chuck.buttonZ)
     if (R<25)
        R=5;
     else R-=20; 
 
  if (chuck.buttonC)
     if (R>225)
        R=245;
     else R+=20;

     Wire.beginTransmission(0x48);
     Wire.write(0x05);
     Wire.write(ADDRESS);
     Wire.write(0x03);
     Wire.write(R);
     Wire.write(G);
     Wire.write(B);
     Wire.endTransmission(); 
}
