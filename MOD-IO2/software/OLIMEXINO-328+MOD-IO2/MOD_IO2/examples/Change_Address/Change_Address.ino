#include <Wire.h>
#include <IO2.h>

// Control MOD-IO2 at address 0x21
const unsigned char newAddress = 0x30;
const unsigned int button = 2;
IO2 io2(0x21);
void setup () {
  // GPIO4 (PROG JUMPER) must be set as input
  // with pullpin turned ON
  io2.pinMode(io2.GPIO4, io2.IN);
  io2.setPullpin(io2.GPIO4, io2.ON);
}
void loop () {
  if(digitalRead(button) == LOW){
    io2.setAddress(newAddress);
    while(digitalRead(button) == LOW);
  }    
}
