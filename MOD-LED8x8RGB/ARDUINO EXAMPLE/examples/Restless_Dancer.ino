#include "SPI.h"
#include "font.h"
#include "lcd8x8rgb.h"

unsigned int cntr=0;    // counter for the Sun
unsigned int cntr2=31;  // counter for the Moon (starts from the max value divided by 2, so that the Sun & Moon can switch)
unsigned int shake=0;
unsigned int walk=0;
char step=1;            // direction of walking

void setup() {
   Serial.begin(9600);

   SPI.setDataMode(SPI_MODE1);
   SPI.setClockDivider(SPI_CLOCK_DIV64);
   SPI.begin();

   pinMode(chipSelectPin, OUTPUT);

   vClear();
}

void loop() {
   randomSeed(analogRead(0));   //code for man, dancing all day and all night

   cntr++;                                 //draw Sun
   color=3;
   if (cntr>63) cntr=0;
   drawCircle(-4+cntr,6,2);
   drawLine(cntr,10,-8+cntr,2);
   drawLine(cntr,2,-8+cntr,10);
   drawLine(-9+cntr,6,1+cntr,6);
   drawLine(-4+cntr,1,-4+cntr,11);

   cntr2++;                               //draw Moon
   color=7;
   if (cntr2>63) cntr2=0;
   drawPixel(-2+cntr2,1);
   drawLine(-5+cntr2,2,-3+cntr2,2);
   drawLine(-6+cntr2,3,-4+cntr2,3);
   drawLine(-8+cntr2,4,-5+cntr2,4);
   drawLine(-9+cntr2,5,-6+cntr2,5);
   drawLine(-9+cntr2,6,-6+cntr2,6);
   drawLine(-8+cntr2,7,-5+cntr2,7);
   drawLine(-6+cntr2,8,-4+cntr2,8);
   drawLine(-5+cntr2,9,-3+cntr2,9);
   drawPixel(-2+cntr2,10);

   color=4;                              //draw Sea
   drawLine(1,16,24,16);
   color=6;
   for(int k=0;k<24;k++)
      drawPixel(k+1,random(14,16));
   color=5;                              //draw Dancer
   walk+=step;
   if (walk>21||walk<1) step=-step;
   drawRectangle(6+walk/2,4,8+walk/2,5);   //head
   drawPixel(7+walk/2,6);
   color=1;
   drawSolidRectangle(6+walk/2,7,8+walk/2,10);  //body
   color=5;
   shake++;
   if (shake>8) shake=0;
   drawLine(5+walk/2,8,2+walk/2,5+shake/2+random(3));   //hands
   drawLine(12+walk/2,11-shake/2-random(3),9+walk/2,8);
   color=2;
   drawLine(6+shake/3+walk/2,11,4+shake/2+walk/2,15);    //feet
   drawLine(8-shake/3+walk/2,11,10-shake/2+walk/2,15);

   Transfer();
   delay(sdelay);
   vClear();
}

