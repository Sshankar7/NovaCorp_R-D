void setup() {

Serial.begin(9600);
pinMode(6,OUTPUT);
digitalWrite(6,HIGH);
}

void loop() {

float average = 0;
for(int i = 0; i < 1000; i++) {
average = average + (0.02641938 * analogRead(A0) - 13.5135135);
delay(1);
}
Serial.print(average);
Serial.println(" mA");
}
