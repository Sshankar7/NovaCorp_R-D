#include <DS3232RTC.h>
#include <Streaming.h>
#include <Time.h>
#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial gsmSerial(10,11);

String str,input,offInp;
int indexNo,lastIndexNo,hrs,mins,secs,hor,mint,secn;
int del = 5000;

void setup(void)
{
    Serial.begin(19200);
    delay(200);
    gsmSerial.begin(19200);
    delay(6000);
    setSyncProvider(RTC.get);
    //Serial << F("RTC Sync");
    if (timeStatus() != timeSet) Serial << F(" FAIL!");
    Serial << endl;
    pinMode(A0,INPUT);
    pinMode(A1,INPUT);
    pinMode(A2,INPUT);
    pinMode(3,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    ReceiveTextMessage();
}

void loop(void)
{
    tmElements_t tm;
    RTC.read(tm);
    hor = tm.Hour;
    mint = tm.Minute;
    secn = tm.Second;
   // Serial << (hor) << (' ') << (mint) << endl;
  if(gsmSerial.available()>0)
  {
      str = gsmSerial.readString();
      indexNo = str.indexOf('*');
      lastIndexNo = str.lastIndexOf('#');
      input = str.substring(indexNo+1,lastIndexNo);
      input.toUpperCase();
      Serial.println(input);
      delayTime();
      digitalClockDisplay();
      if(input == "ON") {
          analogWrite(3,64);
          analogWrite(5,64);
          analogWrite(6,64);
          delay(del);
          analogWrite(3,128);
          analogWrite(5,128);
          analogWrite(6,128);
          delay(del);
          analogWrite(3,192);
          analogWrite(5,192);
          analogWrite(6,192);
          delay(del);
          analogWrite(3,255);
          analogWrite(5,255);
          analogWrite(6,255);
          sendTextMessage();
}
      else if(input == "OFF") {
          analogWrite(3,0);
          analogWrite(5,0);
          analogWrite(6,0);
          }
  }
      delayTime();
      if(input.startsWith("ONS"))
        {
          int indexPos = input.indexOf(':');
          hrs = input.substring(3,indexPos).toInt();
          int midIndexPos = input.indexOf(':', indexPos+1);
          mins = input.substring(indexPos+1,midIndexPos).toInt();
          int lastIndexPos = input.lastIndexOf(';');
          secs = input.substring(midIndexPos+1,lastIndexPos).toInt();
          
          //Serial << (hrs) << (' ') << (mins) << endl;
          if(hor == hrs && mint == mins && secn == secs) {
            analogWrite(3,64);
            analogWrite(5,64);
            analogWrite(6,64);
            delay(del);
            analogWrite(3,128);
            analogWrite(5,128);
            analogWrite(6,128);
            delay(del);
            analogWrite(3,192);
            analogWrite(5,192);
            analogWrite(6,192);
            delay(del);
            analogWrite(3,255);
            analogWrite(5,255);
            analogWrite(6,255); 
            sendTextMessage();
          }
        }
        else if((int)input.indexOf('#') == 0 && (int)input.lastIndexOf('*') == input.length()-1)
        {
          indexNo = input.indexOf('#');
          lastIndexNo = input.lastIndexOf('*');
          offInp = input.substring(indexNo+1,lastIndexNo);
          int indexPos = offInp.indexOf(':');
          hrs = offInp.substring(0,indexPos).toInt();
          int midIndexPos = offInp.indexOf(':', indexPos+1);
          mins = offInp.substring(indexPos+1,midIndexPos).toInt();
          int lastIndexPos = offInp.lastIndexOf(';');
          secs = offInp.substring(midIndexPos+1,lastIndexPos).toInt();
            if(hor == hrs && mint == mins && secn == secs){
              analogWrite(3,0);
              analogWrite(5,0);
              analogWrite(6,0);
          }
        }
        setDateTime();
}

void iTrim()
{
    int indexPos = input.indexOf(':');
    hrs = input.substring(0,indexPos).toInt();
    int midIndexPos = input.indexOf(':', indexPos+1);
    mins = input.substring(indexPos+1,midIndexPos).toInt();
    int lastIndexPos = input.lastIndexOf(';');
    secs = input.substring(midIndexPos+1,lastIndexPos).toInt();
}
void delayTime() {
  if(input.startsWith("DEL")) {
    del = input.substring(3,input.lastIndexOf(';')).toInt();
    }
  }
 void sendTextMessage()
{
  gsmSerial.println("AT+CMGF=1");
  delay(1000);
  gsmSerial.println("AT+CMGS=\"+918409915471\"\r"); 
  delay(1000);
  check(); //the content of the message
  delay(100);
  gsmSerial.println((char)26);//the ASCII code of the ctrl+z is 26
  delay(1000);
}

void ReceiveTextMessage()
{
  gsmSerial.println("AT+CMGF=1\r");
  delay(100);
  //Serial << F("AT+CMGL=ALL\r") <<  endl;
  //delay(1000);
  gsmSerial.println("AT+CNMI=1,2,0,0,0\r");
  delay(500);
}
void check() {
  int a = analogRead(A0);
  int b = analogRead(A1);
  int c = analogRead(A2);
  
  if (a >= 480 && a <=720 && b >= 480 && b <=720 && c >= 480 && c <=720)
  gsmSerial.println("All bulbs are ON!");
  else if (!(a >=480 && a<=720))
  gsmSerial.println("Bulbs at index are malfunctioning!");
  else if(!(b >=480 && b<=720))
  gsmSerial.println("Bulbs at middle are malfunctioning!");
  else if(!(c >=480 && c<=720))
  gsmSerial.println("Bulbs at last index are malfunctioning!");
  }
void setDateTime() 
{
    static time_t tLast;
    time_t t;
    tmElements_t tm;
        if (input.startsWith("RTC")) {
          int index1No = input.indexOf(',');
          int y = input.substring(3,index1No).toInt();
          int index2No = input.indexOf(',',index1No+1);
          int m = input.substring(index1No+1,index2No).toInt();
          int index3No = input.indexOf(',',index2No+1);
          int d = input.substring(index2No+1,index3No).toInt();
          int index4No = input.indexOf(',',index3No+1);
          int h = input.substring(index3No+1,index4No).toInt();
          int index5No = input.indexOf(',',index4No+1);
          int mi = input.substring(index4No+1,index5No).toInt();
          int index6No = input.lastIndexOf(',');
          int s = input.substring(index5No+1,index6No).toInt();
          
        if (y >=100 && y < 1000)
            Serial << F("Error: Year must be two digits or four digits!") << endl;
        else {
            if (y >= 1000)
              tm.Year = CalendarYrToTm(y);
            else //(y < 100)
                tm.Year = y2kYearToTm(y);
              tm.Month = m;
              tm.Day = d;
              tm.Hour = h;
              tm.Minute = mi;
              tm.Second = s;
              t = makeTime(tm);
              RTC.set(t);
              setTime(t);        
              gsmSerial.println("AT+CMGF=1");
              delay(1000);
              gsmSerial.println("AT+CMGS=\"+918409915471\"\r"); 
              delay(1000);
              gsmSerial << hour() << ':' << minute() << ':' << second() << ' ' << day() << ' ' << month() << year() << endl;
              delay(100);
              gsmSerial.println((char)26);//the ASCII code of the ctrl+z is 26
              delay(1000);
        }
    }
}

void digitalClockDisplay(void)
{
  if(input == "TIMERTC") {
    // digital clock display of the time
    gsmSerial.println("AT+CMGF=1");
    delay(1000);
    gsmSerial.println("AT+CMGS=\"+918409915471\"\r"); 
    delay(1000);
    gsmSerial << hour() << ':' << minute() << ':' << second() << ' ' << day() << ' ' << month() << year() << endl;
    delay(100);
    gsmSerial.println((char)26);//the ASCII code of the ctrl+z is 26
    delay(1000);
//    Serial.print(hour());
//    printDigits(minute());
//    printDigits(second());
//    Serial.print(' ');
//    Serial.print(day());
//    Serial.print(' ');
//    Serial.print(month());
//    Serial.print(' ');
//    Serial.print(year()); 
//    Serial.println();

    }
}

//void printDigits(int digits)
//{
//    // utility function for digital clock display: prints preceding colon and leading 0
//    Serial.print(':');
//    if(digits < 10)
//        Serial.print('0');
//    Serial.print(digits);
//}

