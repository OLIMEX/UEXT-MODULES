#include "SPI.h"
#include "font.h"
#include "lcd8x8rgb.h"

boolean point=1;
int cntr=0;

void setup() {
   Serial.begin(9600);

   SPI.setDataMode(SPI_MODE1);
   SPI.setClockDivider(SPI_CLOCK_DIV64);
   SPI.begin();

   pinMode(chipSelectPin, OUTPUT);

   vClear();
}

void loop() {
   cntr++;     //code for making a winking face
   vClear();
   if (cntr>50) {
      point=!point;
      cntr=0;
   }
   color=4;                        //left eye
   drawRectangle(16,4,17,5);
   color=2;
   if (point) {
      drawRectangle(8,4,9,5);     //right eye 1
      color=1;
      for (int k=0;k<4;k++) drawPixel(11+k,12);    //closed mouth
   } else {
      drawPixel(11,5);                 //right eye 2
      drawLine(7,6,10,6);
      drawPixel(6,5);
      color=1;                     //draw filled heart
      drawPixel(3,6);
      drawLine(2,5,4,5);
      drawLine(1,4,5,4);
      drawPixel(2,3);
      drawPixel(4,3);
      drawLine(7,10,18,10);       //open mouth
      int g=0;
      for (int k=0; k<10; k++) {
         if (k<5) g++;
         else if (k>5) g--;
         if (g>5) g=5;
         drawPixel(k+8, g+10);
      }
   }
   Transfer();
}

