int analogPin = 2;
/* the analog pin we are using on the Arduino */
int myLDR = 0;
/* temporary variable to store the the LDR value */
int myDarkNumber = 500;
/* the threshold for dark */
int ledPin = 13;
void setup(){
	 Serial.begin(9600);
	 /* setting up communication and speed */
	
	
pinMode(ledPin,OUTPUT);
/* declare ledPin as OUTPUT */
}
void loop(){
	 myLDR = analogRead(analogPin);
	 /* read the value from the LDR and store it */
	 if (myLDR >= myDarkNumber){
		 digitalWrite(ledPin,HIGH);
	 }else{
		 digitalWrite(ledPin,LOW);
	 }
}

