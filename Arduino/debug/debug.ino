void setup(void) {
   pinMode(5,INPUT);
  pinMode(5,OUTPUT);
 
  Serial.begin(19200);
  Serial.println("Starts: ");
  }

  void loop(void) {
    analogWrite(5,234);
    //digitalWrite(5,HIGH);
    Serial.println(analogRead(5));
    delay(1000);
    Serial.print("BitRead: ");
    //Serial.println();
    // Serial.println(bitRead(PIN,5));   
    } 
