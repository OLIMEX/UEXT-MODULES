#include <Servo.h> 
 
Servo myservo1, myservo2, myservo3;
boolean alpha, gamma;
int beta=0;
int delta=1;
 
void setup() 
{ 
  myservo1.attach(0); 
  myservo2.attach(2);
  myservo3.attach(6);
  delay(500);
  
  myservo1.write(10);
  myservo2.write(10);
  alpha=0;
  gamma=0;
  delay(500);
} 
 
void loop() 
{ 
  if(!alpha) myservo1.write(90);
    else myservo1.write(10); 
    alpha=!alpha;
  if (beta%2==1) myservo2.write(50);
    else if ((beta%8==0)||(beta%8==2)) myservo2.write(10);
    else myservo2.write(90);
  beta++;
  if (beta%10==0) gamma=!gamma;
  myservo3.write(360*gamma);    
  delay(500); 
} 