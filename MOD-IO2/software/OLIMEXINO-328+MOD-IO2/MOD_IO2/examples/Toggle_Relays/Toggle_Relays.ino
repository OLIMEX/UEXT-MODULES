#include <Wire.h>
#include <IO2.h>

// Control MOD-IO2 at address 0x21
IO2 io2(0x21);
void setup () {
  Serial.begin(9600);
  io2.pinMode(io2.GPIO0 | io2.GPIO1, io2.IN);
  io2.setPullpin(io2.GPIO0 | io2.GPIO1, io2.ON);
}
void loop () {
  if(io2.digitalRead(io2.GPIO0) == io2.LO)
    io2.setRelay(io2.RELAY1, io2.ON);
  else
    io2.setRelay(io2.RELAY1, io2.OFF);
    
  if(io2.digitalRead(io2.GPIO1) == io2.LO)
    io2.setRelay(io2.RELAY2, io2.ON);
  else
    io2.setRelay(io2.RELAY2, io2.OFF);
    
  delay(500);
  
  
}
