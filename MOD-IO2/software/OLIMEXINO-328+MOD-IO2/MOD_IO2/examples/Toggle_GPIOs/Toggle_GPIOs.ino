#include <Wire.h>
#include <IO2.h>

// Control MOD-IO2 at address 0x21
IO2 io2(0x21);
void setup () {
  io2.pinMode(io2.GPIO0 | io2.GPIO1, io2.OUT);
}
void loop () {
  io2.digitalWrite(io2.GPIO0 | io2.GPIO1, io2.HI);
  delay(10);
  io2.digitalWrite(io2.GPIO0 | io2.GPIO1, io2.LO);
  delay(10);
}
