String str, input;
int indexNo, lastIndexNo;
int hrs, mins, secs;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0)
  {
    str = Serial.readString();
    if((int)str.indexOf('*') == 0 && (int)str.lastIndexOf('#') == str.length()-1)
    {
      indexNo = str.indexOf('*');
      lastIndexNo = str.lastIndexOf('#');
      input = str.substring(indexNo+1,lastIndexNo);
      input.toUpperCase();
      if(input == "ON")
          digitalWrite(13,HIGH);
      else if(input == "OFF")
          digitalWrite(13,LOW);
          //Have to verify the condition according to RTC Output
      else if((int)input.indexOf(':') == 2)
        {
          iTrim();
          if(hour() == hrs && minute() == mins && second() == secs)
              digitalWrite(13,HIGH);
        }
        else if((int)str.indexOf('#') == 0 && (int)str.lastIndexOf('*') == str.length()-1)
        {
          indexNo = str.indexOf('#');
        lastIndexNo = str.lastIndexOf('*');
        input = str.substring(indexNo+1,lastIndexNo);
        input.toUpperCase();
            iTrim();
            if(hour() == hrs && minute() == mins && second() == secs)
              digitalWrite(13,LOW);
        }
    }
    else
    {
      Serial.println("Incorrect Input Format Received: ");
      Serial.println(str);
    }
  }
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
