#include <DS3232RTC.h>
#include <Streaming.h>
#include <Time.h>
#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial gsmSerial(10,11);

String str, input, offInp;
int indexNo, lastIndexNo;
int hrs, mins, secs;

void setup(void)
{
  
    Serial.begin(19200);
    delay(200);
    gsmSerial.begin(19200);
    delay(5000);
    setSyncProvider(RTC.get);
    Serial << F("RTC Sync");
    if (timeStatus() != timeSet) Serial << F(" FAIL!");
    Serial << endl;
    pinMode(A0,OUTPUT);
    pinMode(A1,OUTPUT);
    pinMode(A2,OUTPUT);
    pinMode(A3,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(9,OUTPUT);
    ReceiveTextMessage();
}

void loop(void)
{
  
  if(gsmSerial.available()>0)
  {
      str = gsmSerial.readString();
      indexNo = str.indexOf('*');
      lastIndexNo = str.lastIndexOf('#');
      input = str.substring(indexNo+1,lastIndexNo);
      input.toUpperCase();
      digitalClockDisplay();
      Serial.println(input);
      if(input == "ON") {
          analogWrite(5,64);
          analogWrite(6,64);
          analogWrite(9,64);
          analogWrite(A0,64);
          analogWrite(A1,64);
          analogWrite(A2,64);
          analogWrite(A3,64);
          delay(10000);
          analogWrite(5,128);
          analogWrite(6,128);
          analogWrite(9,128);
          analogWrite(A0,128);
          analogWrite(A1,128);
          analogWrite(A2,128);
          analogWrite(A3,128);
          delay(10000);
          analogWrite(5,255);
          analogWrite(6,255);
          analogWrite(9,255);
          analogWrite(A0,255);
          analogWrite(A1,255);
          analogWrite(A2,255);
          analogWrite(A3,255);}
      else if(input == "OFF") {
          analogWrite(5,0);
          analogWrite(6,0);
          analogWrite(9,0);
          analogWrite(A0,0);
          analogWrite(A1,0);
          analogWrite(A2,0);
          analogWrite(A3,0);
          
          }
          
      else if(input.startsWith("ONS"))
        {
          int indexPos = input.indexOf(':');
    hrs = input.substring(3,indexPos).toInt();
    int midIndexPos = input.indexOf(':', indexPos+1);
    mins = input.substring(indexPos+1,midIndexPos).toInt();
    int lastIndexPos = input.lastIndexOf(';');
    secs = input.substring(midIndexPos+1,lastIndexPos).toInt();
          if(hour() == hrs && minute() == mins && second() == secs) {
            analogWrite(5,64);
            analogWrite(6,64);
          analogWrite(9,64);
          analogWrite(A0,64);
          analogWrite(A1,64);
          analogWrite(A2,64);
          analogWrite(A3,64);
          delay(10000);
          analogWrite(5,128);
          analogWrite(6,128);
          analogWrite(9,128);
          analogWrite(A0,128);
          analogWrite(A1,128);
          analogWrite(A2,128);
          analogWrite(A3,128);
          delay(10000);
          analogWrite(5,255);
          analogWrite(6,255);
          analogWrite(9,255);
          analogWrite(A0,255);
          analogWrite(A1,255);
          analogWrite(A2,255);;
          }
        }
        else if((int)input.indexOf('#') == 0 && (int)input.lastIndexOf('*') == input.length()-1)
        {
          indexNo = input.indexOf('#');
          lastIndexNo = input.lastIndexOf('*');
          offInp = input.substring(indexNo+1,lastIndexNo);
          Serial.println(offInp);
          int indexPos = offInp.indexOf(':');
          hrs = offInp.substring(0,indexPos).toInt();
          int midIndexPos = offInp.indexOf(':', indexPos+1);
          mins = offInp.substring(indexPos+1,midIndexPos).toInt();
          int lastIndexPos = offInp.lastIndexOf(';');
          secs = offInp.substring(midIndexPos+1,lastIndexPos).toInt();
            if(hour() == hrs && minute() == mins && second() == secs){
              analogWrite(5,0);
              analogWrite(6,0);
              analogWrite(9,0);
              analogWrite(A0,0);
              analogWrite(A1,0);
              analogWrite(A2,0);
              analogWrite(A3,0);
          }
        }
        setDateTime();
  } gsmSerial.flush();
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

 void SendTextMessage()
{
  Serial << F("AT+CMGF=1") << endl;
  delay(100);
  Serial << F("AT+CMGS=\"+919801392602\"\r") << endl; 
  delay(100);
  Serial << F("A test message!") << endl;//the content of the message
  delay(100);
  
  Serial.println((char)26);//the ASCII code of the ctrl+z is 26
  delay(100);
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
              Serial << F("RTC set to: ");
              printDateTime(t);
              Serial << endl;
        }
    }
}

//print date and time to Serial
void printDateTime(time_t t)
{
    printDate(t);
    Serial << ' ';
    printTime(t);
}

//print time to Serial
void printTime(time_t t)
{
    printI00(hour(t), ':');
    printI00(minute(t), ':');
    printI00(second(t), ' ');
}

//print date to Serial
void printDate(time_t t)
{
    printI00(day(t), 0);
    Serial << monthShortStr(month(t)) << _DEC(year(t));
}

//Print an integer in "00" format (with leading zero),
//followed by a delimiter character to Serial.
//Input value assumed to be between 0 and 99.
void printI00(int val, char delim)
{
    if (val < 10) Serial << '0';
    Serial << _DEC(val);
    if (delim > 0) Serial << delim;
    return;
}
void digitalClockDisplay(void)
{
    if(input == "TIMERTC") {
    // digital clock display of the time
    Serial.print(hour());
    printDigits(minute());
    printDigits(second());
    Serial.print(' ');
    Serial.print(day());
    Serial.print(' ');
    Serial.print(month());
    Serial.print(' ');
    Serial.print(year()); 
    Serial.println(); }
}
void printDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    Serial.print(':');
    if(digits < 10)
        Serial.print('0');
    Serial.print(digits);
}
