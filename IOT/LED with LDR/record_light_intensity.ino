int analogPin = 2;
/* the analog pin we are using on the Arduino */
int myLDR = 0;
/* temporary variable to store the LDR value */
void setup(){
	 Serial.begin(9600);
/* setting up communication and communication speed */
}
void loop(){
	 myLDR = analogRead(analogPin);
	 /* read the value from ther LDR and store it */
	 Serial.println(myLDR);
	 /* print the value stored in myLDR */
	 delay(200);
} 

