
 #include <Servo.h> 
 Servo myservo; 

 #define HITS 3
 #define Hpower 100
 #define LHit 10000
 #define SHit 3000
 
 int counter, Save[HITS-1], iSave[HITS-1], z, Nhits, i, gg;
 boolean hflag;

 void setup() {
   Serial.begin(9600);
   myservo.attach(9);
   myservo.write(10);     
   delay(500);
   counter=0;
   z=0;
   Nhits=0;
   for (i=0;i<(HITS-1);i++) Save[i]=0;
   while (hflag==0) {
     if (analogRead(A0)>Hpower) {
       Serial.println("Begin");
       delay(50);
       while (Nhits<(HITS-1)) {
         while (counter<LHit) {
           if (Nhits==(HITS-1)) {
             hflag=1;
             break;
           }
           if (analogRead(A0)>Hpower) {
             if (counter<SHit) {
             Serial.print("SHORT ");
             Save[z]=1;
             delay(50);
             } else {
             Serial.print("LONG ");
             Save[z]=2;
             delay(50);
             }
             z++;
             Nhits++;
             counter=0;
             continue;
           }
           counter++;
         }
         if (counter>=LHit) {
         hflag=0;
         Serial.println();
         Serial.println("Too slow");
         counter=0;
         z=0;
         Nhits=0;
         break;
         }
         if (hflag==1) {
           Serial.println();
           Serial.print("Password ' ");
           for (i=0;i<(HITS-1);i++) {
             Serial.print(Save[i]);
             Serial.print(" ");
           }
           Serial.println("' has been saved!");
         }
       }
     }
   } 
 }
   

 void loop(){
   counter=0;
   z=0;
   Nhits=0;
   for (i=0;i<(HITS-1);i++) iSave[i]=0;
     if (analogRead(A0)>Hpower) {
       Serial.println("Begin");
       delay(50);
       while (Nhits<(HITS-1)) {
         while (counter<LHit) {
           if (Nhits==(HITS-1)) {
             hflag=1;
             break;
           }
           if (analogRead(A0)>Hpower) {
             if (counter<SHit) {
             Serial.print("SHORT ");
             iSave[z]=1;
             delay(50);
             } else {
             Serial.print("LONG ");
             iSave[z]=2;
             delay(50);
             }
             z++;
             Nhits++;
             counter=0;
             continue;
           }
           counter++;
         }
         if (counter>=LHit) {
           hflag=0;
           Serial.println();
           Serial.println("Too slow!");
           counter=0;
           z=0;
           Nhits=0;
           break;
         }
         if (hflag==1) {
           gg=0;
           for (i=0;i<(HITS-1);i++)
             if (Save[i]==iSave[i]) gg++;
             if (gg==(HITS-1)) {
               Serial.println();
               Serial.println("Success! You can look at the treasure!");     
               delay(100);
               myservo.write(110);     
               delay(2000);
               myservo.write(10);     
               delay(500); 
             } else {
               Serial.println();
               Serial.println("Wrong Password!");     
               delay(100);
             }
         }
       }
     }
}