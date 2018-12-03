#include <Wire.h>
#include <IO2.h>

// Control MOD-IO2 at address 0x21
IO2 io2(0x21);
void setup () {
  Serial.begin(9600);
}
void loop () {
  unsigned int adc = 0;
  float voltage = 0;
  adc = io2.analogRead(io2.AN0);
  voltage = (adc/1023.0)*3.3;
  Serial.print(voltage, 2);
  Serial.println("V");
  delay(1000);
}
