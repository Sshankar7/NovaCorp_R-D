int irsensor1 = 6;
int led1 = 13;

void setup()
   {
       pinMode(irsensor1 , INPUT);
       pinMode(led1, OUTPUT);
    }

void loop()
{

    int readsen = digitalRead( irsensor1 );
       if( readsen == HIGH )
     {
       digitalWrite(led1, HIGH);
     }
else
     {
       digitalWrite(led1, !HIGH);
      }
delay(1);
}