const int sensorPin = A0;
double Current = 0;
double OutputSensorVoltage = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(6,OUTPUT);
  digitalWrite(6,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  OutputSensorVoltage = analogRead(sensorPin)*5.0/1023.0;
  Current = (OutputSensorVoltage - 2.5)/0.185;

  Serial.print("Current = ");
  Serial.print(Current);
  Serial.print("\n");

  delay(200);
}
