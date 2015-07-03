 #include <Servo.h> 
 Servo myservo; 

 #define Hpower 100

 void setup() {
   Serial.begin(9600);
   myservo.attach(9);
   myservo.write(10);
 }

void loop() { 
   if (analogRead(A0)>Hpower) {
     myservo.write(110);     
     delay(1000);
     myservo.write(10);     
     delay(100); 
   }
 }