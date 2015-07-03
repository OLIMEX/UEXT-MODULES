#include <IRremote.h>

int RECV_PIN = 11;
int led=13;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  
  if (irrecv.decode(&results)) {
    if (results.value==0x41) digitalWrite(led, HIGH);
    if (results.value==0x42) digitalWrite(led, LOW);
    Serial.println(results.value, HEX);
    irrecv.resume();    
  }
}