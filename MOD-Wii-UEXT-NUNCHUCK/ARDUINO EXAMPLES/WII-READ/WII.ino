#include "Wire.h"
#include WiiChuck.h

WiiChuck chuck = WiiChuck();

void setup() {
  Serial.begin(115200);
  chuck.begin();
  chuck.update();
}

void loop() {
  delay(500);
  chuck.update(); 

  Serial.print(chuck.readJoyX());
  Serial.print(", ");  
  Serial.print(chuck.readJoyY());
  Serial.print(", ");  

  if (chuck.buttonZ) 
     Serial.print("Z");
  else  
     Serial.print("-");

  Serial.print(", ");  

  if (chuck.buttonC) 
     Serial.print("C");
  else  
     Serial.print("-");

  Serial.println();

}
