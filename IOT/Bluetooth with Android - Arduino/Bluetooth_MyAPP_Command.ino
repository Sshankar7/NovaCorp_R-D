String voice;
int
led2 = 2, //Connect LED 1 To Pin #2
led3 = 3, //Connect LED 2 To Pin #3
led4 = 4; //Connect LED 3 To Pin #4
//--------------------------Call A Function-------------------------------// 
void allon(){
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
}
void alloff(){
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
}
//-----------------------------------------------------------------------// 
void setup() {
  Serial.begin(9600);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}
//-----------------------------------------------------------------------// 
void loop() {
  while (Serial.available()){  //Check if there is an available byte to read
    delay(10); //Delay added to make thing stable
    char c = Serial.read(); //Conduct a serial read
    if (c == '#') {
      break;
    } //Exit the loop when the # is detected after the word
    voice += c; //Shorthand for voice = voice + c
  } 
  if (voice.length() > 0) {
    Serial.println(voice);
    //-----------------------------------------------------------------------//   
    //----------Control Multiple Pins/ LEDs----------// 
    if(voice == "all on") {
      delay(10);
      allon();
    }  //Turn Off All Pins (Call Function)
    else if(voice == "all of"){
      delay(10);
      alloff();
    } //Turn On  All Pins (Call Function)

    //----------Turn On One-By-One----------//
    else if(voice == "light on") {
      digitalWrite(led2, HIGH);
    }
    else if(voice == "*computer on") {
      digitalWrite(led3, HIGH);
    }
    else if(voice == "fan on") {
      digitalWrite(led4, HIGH);
    }
    //----------Turn Off One-By-One----------//
    else if(voice == "light off") {
      digitalWrite(led2, LOW);
    }
    else if(voice == "computer off") {
      delay(10);
      digitalWrite(led3, LOW);
    }
    else if(voice == "fan of") {
      digitalWrite(led4, LOW);
    }
    //-----------------------------------------------------------------------// 
    voice="";
  }
} //Reset the variable after initiating

