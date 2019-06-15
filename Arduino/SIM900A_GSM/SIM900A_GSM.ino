#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8);

void setup()
{
  mySerial.begin(9600);               // the GPRS baud rate   
  Serial.begin(9600);    // the GPRS baud rate 
  delay(1000);
}


void loop()
{
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 't':
      SendTextMessage();
      break;
    case 'r':
      RecieveTextMessage();
      break;
  }

 if (mySerial.available()>0)
   Serial.write(mySerial.read());
}

///SendTextMessage()
///this function is to send a sms
 void SendTextMessage()
{
  mySerial.println("AT+CMGF=1");    //Because we want to send the SMS in text mode
  delay(100);
  mySerial.println("AT+CMGS=\"+91******\"\r"); // change to the phone number you using 
  delay(100);
  mySerial.println("A test message!");//the content of the message
  delay(100);
  
  mySerial.println((char)26);//the ASCII code of the ctrl+z is 26
  delay(100);
}

///RecieveTextMessage()
///this function is to show received a sms
 void RecieveTextMessage()
{
  mySerial.println("AT+CMGF=1\r");
  delay(2000);
  
  //mySerial.println("AT+CNMI=2,2,0,0,0");
  //delay(200);
   
  //mySerial.println("AT+CSCS=\"GSM\"\r");
  //delay(100);
   mySerial.println("AT+CMGD=1,4"); // delete all SMS
   delay(100);
  mySerial.println("AT+CMGL=\"ALL\"\r"); // to read ALL the SMS in text mode
  delay(200);
  //mySerial.println("AT+CMGR=3\r");//  to read the SMS in text mode from location x
  //delay(100);
}

