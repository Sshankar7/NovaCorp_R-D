#include <IRremote.h>

int RECV_PIN = 11;
String inp;
int on = 0;
IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  Serial.begin(19200);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    inp = String(results.value, HEX);
    inp.toUpperCase();
    Serial.println(inp);
    Serial.println(results.value);
  
  if(inp == "1FE48B7") {
    for(int i=2; i<10; i++)
      digitalWrite(i,LOW);
    }
    else if(inp == "1FEE01F") {
    for(int i=2; i<10; i++)
      digitalWrite(i,HIGH);
    }
    else if(inp == "1FE50AF") {
      on = !on;
        digitalWrite(2, on ? HIGH : LOW);
      }
      else if(inp == "1FED827") {
      on = !on;
        digitalWrite(3, on ? HIGH : LOW);
      }
      else if(inp == "1FEF807") {
      on = !on;
        digitalWrite(4, on ? HIGH : LOW);
      }
      else if(inp == "1FE30CF") {
      on = !on;
        digitalWrite(5, on ? HIGH : LOW);
      }
      else if(inp == "1FEB04F") {
      on = !on;
        digitalWrite(6, on ? HIGH : LOW);
      }
      else if(inp == "1FE708F") {
      on = !on;
        digitalWrite(7, on ? HIGH : LOW);
      }
      else if(inp == "1FE00FF") {
      on = !on;
        digitalWrite(8, on ? HIGH : LOW);
      }
      else if(inp == "1FEF00F") {
      on = !on;
        digitalWrite(9, on ? HIGH : LOW);
      }
    
    delay(100);
    irrecv.resume();
  }
}
