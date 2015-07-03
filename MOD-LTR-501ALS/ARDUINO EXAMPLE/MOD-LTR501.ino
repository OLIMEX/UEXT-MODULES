#include <Wire.h>

unsigned int ADC_0, ADC_1, PS;
float distance;

void setup() {
    Serial.begin(9600);
    Wire.begin();
}

void Write(unsigned char reg, unsigned char data){
  Wire.beginTransmission(0x23);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

unsigned char Read(unsigned char reg){
  unsigned char data;
  
  Wire.beginTransmission(0x23);
  Wire.write(reg);
  Wire.endTransmission();
  
  Wire.requestFrom(0x23, 1);
  while(Wire.available()){
    data = Wire.read();  
  }
  
  return data;
}

void loop() {

  Serial.print("Checking ID: ");
  unsigned char id = Read(0x86);
  if(id == 0x80)
   Serial.println("OK");
  else
   Serial.println("Fail!"); 
   
  Serial.print("Setting configuration: ");
  Write(0x80, 0x03);  //Active mode, 64k lux range
  Write(0x81, 0x03);  //PS active mode, x1 GAIN
  Write(0x82, 0x6B);  //LED 60Hz, 50% duty, 50mA
  Write(0x83, 0x7F);  //127 pulses
  Write(0x84, 0x02);  //PS 100ms measure rate
  Write(0x85, 0x03);  //ALS Integration 100ms, repeat rate 500ms
  Serial.println("Ok");

    unsigned char stat = Read(0x8C);
    if(stat & 0x04){
      //ALS new data
      unsigned char data[4];
      for(int i = 0; i < 4; i++){
        data[i] = Read(0x88 + i);
      }
      ADC_1 = (data[1] << 8) | data[0];
      ADC_0 = (data[3] << 8) | data[1];
      Serial.print("ALS1: ");
      Serial.print(ADC_1, DEC);
      Serial.println(" LUX");
      Serial.print("ALS0: ");
      Serial.print(ADC_0, DEC);
      Serial.println(" LUX");
    }
    if(stat & 0x01){
      //PS new data
      unsigned char data[2];
      for(int i = 0; i < 2; i++){
        data[i] = Read(0x8D + i);
      }
      PS = (data[1] << 8) | data[0];
      distance = 10 -(10.0/2047)*PS;
      Serial.print("PS: ");
      Serial.print(distance, 2);
      Serial.println("cm");
      Serial.println("");
    }   
    tone(11,1000,50);
    delay(49+distance*200);
}
