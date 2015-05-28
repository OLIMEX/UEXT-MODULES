#include "lcd3310_GPIO.h"

void setup()
{
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  LCDInit();
  LCDContrast (0x60);
  LCDClear();
  LCDUpdate();
}

void loop()
{
    LCDStr(0, (unsigned char *) "Hello World!", 0);
    LCDTriangle(10,10,80,45,0,47);
    LCDCircle(50,30,10);
    LCDRectangle(20,20,40,40);
    LCDUpdate();
}
