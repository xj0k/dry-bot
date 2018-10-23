void setup()
{
 Serial.begin(9600);
 Serial.println("blue tooth test starts.");
}
 
void loop()
{
  while(Serial.available())
   {
     char c=Serial.read();
      if(c=='A')
        {
          Serial.println("Hello I am amarino");
        }
   }
}
