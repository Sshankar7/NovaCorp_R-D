String str,input;
int len,hrs,mins,secs;
int indexNo,lastIndexNo;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
  {
      str = Serial.readString();
      Serial.print("INPUT: ");
      Serial.println(str);
      len = str.length();
      Serial.print("Input Length: ");
      Serial.println(len);

      indexNo = str.indexOf('*');
      lastIndexNo = str.lastIndexOf('#');
      input = str.substring(indexNo+1,lastIndexNo);
      input.toUpperCase();
      len =  input.length();
      if(len==3)
          Serial.println("ON");
      else if(len==4)
          Serial.println("OFF");
          //Have to verify the condition according to RTC Output
      else if(len > 6)
        {
          iTrim();
          Serial.print("Hr: ");
          Serial.println(hrs);
          Serial.print("Mins: ");
          Serial.println(mins);
          Serial.print("Secs: ");
          Serial.println(secs);
        }
        else if((int)input.indexOf('#') == 0 && (int)input.lastIndexOf('*') == str.length()-1)
        {
          indexNo = str.indexOf('#');
        lastIndexNo = str.lastIndexOf('*');
        input = str.substring(indexNo+1,lastIndexNo);
        input.toUpperCase();
            iTrim();
//            if(hour() == hrs && minute() == mins && second() == secs)
              digitalWrite(6,LOW);
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
