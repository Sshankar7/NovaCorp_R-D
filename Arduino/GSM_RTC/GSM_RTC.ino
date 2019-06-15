//SDA of the RTC to pin 4 of the Arduino.
//SCL of the RTC to pin 5 of the Arduino

#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

const int DS1307 = 0x68; // Address of DS1307 see data sheets
const char* days[] =
{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char* months[] =
{"January", "February", "March", "April", "May", "June", "July", "August","September", "October", "November", "December"};
String str, input; 
// Initializes all values: 
byte second = 0;
byte minute = 0;
byte hour = 0;
byte weekday = 0;
byte monthday = 0;
byte month = 0;
byte year = 0;

  int indexPos;
  int lastIndexPos;
  int endIndexPos;
  byte hrs = 0;
  byte mins = 0;
  byte endMins = 0;
void setup() {
  Wire.begin();
  Serial.begin(9600);
  delay(2000); // This delay allows the MCU to read the current date and time.
  mySerial.begin(9600);
  delay(100);
  
  pinMode(4, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, INPUT);
  pinMode(6, OUTPUT);
  ReceiveMessage();
  
 // callSetTime();
}

// Continuous function for converting bytes to decimals and vice versa
void loop() {
  if(mySerial.available()>0)
 {
   str = mySerial.readString();
   Serial.println(str);
   StringTrim();
 }
 
  readTime();

  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.print(second);
  Serial.println("");
  delay(1000);
  
  indexPos = input.indexOf(':');
  lastIndexPos = input.lastIndexOf(';');
  endIndexPos = input.lastIndexOf('.');
  hrs = input.substring(0,indexPos).toInt();
  mins = input.substring(indexPos+1,lastIndexPos).toInt();
  endMins = input.substring(indexPos+1,endIndexPos).toInt();
 // Serial.println(hrs);
 // Serial.println(mins);
 // Serial.println(endMins);
  if(hour == hrs && minute == mins)
  {
    
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    //SendMessage();
  }
 else if(input == "ON")
 {
   digitalWrite(4, HIGH);
   digitalWrite(5, HIGH);
   digitalWrite(6, HIGH);
   //SendMessage();
 }
  else if(input == "OFF")
  {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    //SendMessage();
  }
  else if(hour == hrs && minute == endMins)
  {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    //SendMessage();
  }
}
byte decToBcd(byte val) {
  return ((val/10*16) + (val%10));
}
byte bcdToDec(byte val) {
  return ((val/16*10) + (val%16));
}

//Code to Receive message 
void ReceiveMessage()
{
  mySerial.println("AT+CMGF=1\r"); // AT Command to recieve a live SMS
  delay(1000);
}

//Code to Trim Received Message
void StringTrim() 
{
  int indexNo = str.indexOf('*');
  int lastIndexNo = str.lastIndexOf('#');
  input = str.substring(indexNo+1,lastIndexNo);
  input.toUpperCase();
  //Serial.print("STR " + str);
 // Serial.println("INPUT: " + input);
}

//Code to Send message
void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919801392602\"\r"); // Replace x with mobile number 8409915471
  delay(1000);
  check();// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void check() {
  
  int a = digitalRead(7);
  int b = digitalRead(8);
  int c = digitalRead(9);
  
  if(a == 0 && b == 0 && c == 0)
  mySerial.println("LED's are OFF!");
  else if (a == 1 && b == 1 && c == 1)
  mySerial.println("LED's are ON!");
  else 
  mySerial.println("Some LED's are malfunctioning!");
}

void callSetTime() {
  Serial.print("The current date and time is: ");
  printTime();
  Serial.println("Please change to newline ending the settings on the lower right of the Serial Monitor");
  Serial.println("Would you like to set the date and time now? Y/N");
 
  while (!Serial.available()) 
  
  delay(10);
  if (Serial.read() == 'y' || Serial.read() == 'Y')

  // This set of functions allows the user to change the date and time
  {
    Serial.read();
    setTime();
    Serial.print("The current date and time is now: ");
    printTime();
  }
  
 Serial.println("Thank you.");
}

// This set of codes is allows input of data
void setTime() {
  Serial.print("Please enter the current year, 00-99. - ");
  year = readByte();
  Serial.println(year);
  Serial.print("Please enter the current month, 1-12. - ");
  month = readByte();
  Serial.println(months[month-1]);
  Serial.print("Please enter the current day of the month, 1-31. - ");
  monthday = readByte();
  Serial.println(monthday);
  Serial.println("Please enter the current day of the week, 1-7.");
  Serial.print("1 Sun | 2 Mon | 3 Tues | 4 Weds | 5 Thu | 6 Fri | 7 Sat - ");
  weekday = readByte();
  Serial.println(days[weekday-1]);
  Serial.print("Please enter the current hour in 24hr format, 0-23. - ");
  hour = readByte();
  Serial.println(hour);
  Serial.print("Please enter the current minute, 0-59. - ");
  minute = readByte();
  Serial.println(minute);
  second = 0;
  Serial.println("The data has been entered.");
 
  // The following codes transmits the data to the RTC
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0));
  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(weekday));
  Wire.write(decToBcd(monthday));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.write(byte(0));
  Wire.endTransmission();
  // Ends transmission of data
}


byte readByte() {
  while (!Serial.available()) delay(10);
  byte reading = 0;
  byte incomingByte = Serial.read();
  while (incomingByte != '\n') {
    if (incomingByte >= '0' && incomingByte <= '9')
      reading = reading * 10 + (incomingByte - '0');
    else;
    incomingByte = Serial.read();
  }
  Serial.flush();
  return reading;
}


void printTime() {
  char buffer[3];
  const char* AMPM = 0;
  readTime();
  Serial.print(days[weekday-1]);
  Serial.print(" ");
  Serial.print(months[month-1]);
  Serial.print(" ");
  Serial.print(monthday);
  Serial.print(", 20");
  Serial.print(year);
  Serial.print(" ");
  if (hour > 12) {
    hour -= 12;
    AMPM = " PM";
  }
  else AMPM = " AM";
  Serial.print(hour);
  Serial.print(":");
  sprintf(buffer, "%02d", minute);
  Serial.print(buffer);
  Serial.println(AMPM);
}


void readTime() {
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0));
  Wire.endTransmission();
  Wire.requestFrom(DS1307, 7);
  second = bcdToDec(Wire.read());
  minute = bcdToDec(Wire.read());
  hour = bcdToDec(Wire.read());
  weekday = bcdToDec(Wire.read());
  monthday = bcdToDec(Wire.read());
  month = bcdToDec(Wire.read());
  year = bcdToDec(Wire.read());
}
