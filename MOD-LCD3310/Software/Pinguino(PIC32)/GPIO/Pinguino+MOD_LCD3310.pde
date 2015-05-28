#include <LCD3310_GPIO\lcd3310_GPIO.c>

char Inverse = 0;
int Button_Released = 1;

void setup()
{
    pinMode (2, INPUT);
 
    LCDInit();
    LCDContrast(0x7F);
    LCDStr(0, (unsigned char *)"*** OLIMEX ***", Inverse);
    LCDStr(1, (unsigned char *)"     PIC32    ", !Inverse);
    LCDStr(2, (unsigned char *)"  Pinguino +  ", Inverse);
    LCDStr(3, (unsigned char *)"  MOD-LCD3310 ", !Inverse);
    LCDStr(4, (unsigned char *)"  using GPIO  ", Inverse);
    LCDStr(5, (unsigned char *)"  interface   ", !Inverse);
}

void loop ()
{
    if (digitalRead (2) && Button_Released)
    {
        Inverse = !Inverse;
        LCDStr(0, (unsigned char *)"*** OLIMEX ***", Inverse);
        LCDStr(1, (unsigned char *)"     PIC32    ", !Inverse);
        LCDStr(2, (unsigned char *)"  Pinguino +  ", Inverse);
        LCDStr(3, (unsigned char *)"  MOD-LCD3310 ", !Inverse);
        LCDStr(4, (unsigned char *)"  using GPIO  ", Inverse);
        LCDStr(5, (unsigned char *)"  interface   ", !Inverse);
        Button_Released = 0;
    }
    if (!digitalRead (2))
        Button_Released = 1;
}
