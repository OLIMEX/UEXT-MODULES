#include <Wire.h>
#include <IO2.h>

// Control MOD-IO2 at address 0x21
IO2 io2(0x21);
void setup () {
  Serial.begin(9600);
}
void loop () {
  if(digitalRead(2) == LOW){
    Serial.print("ID: ");
    unsigned char id = io2.readID();
    Serial.println(id, HEX);
    Serial.print("Checking ID: ");
    if(id == 0x23)
      Serial.println("OK");
    else
      Serial.println("FAIL");
     while(digitalRead(2) == LOW);
  }
}
