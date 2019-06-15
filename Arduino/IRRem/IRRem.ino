#include <IRremote.h>

int RECV_PIN = 12;
String inp;
int res;
int on = 0;
IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  Serial.begin(19200);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    inp = String(results.value);
    res = inp.toInt();
    Serial.println(res);
    
  
  switch(res) {
      case 18615:
        digitalWrite(9,HIGH);
        digitalWrite(10,HIGH);
        break;
      case -8161:
        digitalWrite(9,LOW);
        digitalWrite(10,LOW);
        break;
      case 20655: 
        on = !on;
        digitalWrite(9, on ? HIGH : LOW);
        break;
      case -10201:
        on = !on;
        digitalWrite(10, on ? HIGH : LOW);
        break;
    }
    
    delay(100);
    irrecv.resume();
  }
}
