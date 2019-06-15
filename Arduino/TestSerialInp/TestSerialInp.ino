void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);
  Serial.begin(19200);
}
String str;
int inp;
void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
  {
    str = Serial.readString();
    inp = str.toInt();
    Serial.println(str);
    Serial.println(inp);
    
    if(inp == 1) {
      Serial.println("HIGH");
      digitalWrite(2,HIGH);
      }
     else if(inp == 0) {
      Serial.println("LOW");
      digitalWrite(2,LOW);
      }
   }
      
  }
  
