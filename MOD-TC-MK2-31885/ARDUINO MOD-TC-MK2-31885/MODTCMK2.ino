#include <Wire.h>

//remember to read the document which describes
//the latest firmware revision of MOD-TC-MK2-31885
//it is quite likely that the I2C address is different

void Read_MOD_TC_MK2() {
        long r;
        signed int TCtemp, INtemp;
        unsigned char c;

        Wire.beginTransmission(0x48);       // OLIMEX I2C address
	Wire.write(0x01);
	Wire.write(0xA0);                  // MOD-TC-MK2 address
	Wire.write(0x21);                  // read temperature command
	Wire.endTransmission();

	delay(500);

	r = 0; 
	Wire.requestFrom (0x48, 4); // request data from MOD-TC-MK2
	while (Wire.available ()) {
               r <<=8;
               c = Wire.read();
               r |=c;
        }       
          
       TCtemp=(r>>18) & 0b1111111111111;  //read the temperature
    
       if (r & (1L<<31))                  //add sign
          TCtemp += 0x8000;
       
       Serial.print(" TC = ");
       Serial.print(TCtemp * 0.25);    //print the TC temperature
       
       INtemp=(r>>4) & 0b11111111111;
        
       if (r & (1L<<15)) 
          INtemp += 0x8000;

       Serial.print(" INT = "); 
       Serial.println(INtemp*0.0625);
        
       if (r & (1L<<16)) {
          Serial.print("ERROR: ");
          if (r & 1<<2) Serial.println(" TC CONNECTED TO VCC");
          if (r & 1<<1) Serial.println(" TC SHORT");
          if (r & 1<<0) Serial.println(" TC OPEN");
       }
       Serial.println();
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  Read_MOD_TC_MK2();
}
