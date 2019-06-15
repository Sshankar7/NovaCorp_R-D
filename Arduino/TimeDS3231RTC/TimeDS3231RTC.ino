#include <config.h>
#include <Time.h>
#include <Wire.h>
#include <DS3231RTC.h> // A simple DS3231 Library meant for use with Time.h also implements temp readings
 
void setup() {
 Serial.begin(9600);
 setSyncProvider(RTC.get); // the function to get the time from the RTC
 if(timeStatus()!= timeSet)
 Serial.println("Unable to sync with the RTC");
 else
 Serial.println("RTC has set the system time");
}
 
void loop()
{
 digitalClockDisplay();
 delay(1000);
}
 
void digitalClockDisplay(){
 // digital clock display of the time
 Serial.print(hour());
 printDigits(minute());
 printDigits(second());
 Serial.print(" ");
 Serial.print(day());
 Serial.print(" ");
 Serial.print(month());
 Serial.print(" ");
 Serial.print(year());
 Serial.print(" ");
 Serial.print(RTC.getTemp()); //These last few lines are the only other change to the the Time.h example!
 Serial.print((char)223);
 Serial.print('C');
 Serial.println();
}
 
void printDigits(int digits){
 // utility function for digital clock display: prints preceding colon and leading 0
 Serial.print(":");
 if(digits < 10)
 Serial.print('0');
 Serial.print(digits);
}
