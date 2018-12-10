#include <Servo.h>

int pinFB = 8,
  pinHL = 4,
  pinClaw = 10,
  pinSite = 9;
  
Servo servoFB; // front and backwards
Servo servoHL; // high and low
Servo servoClaw,servoSite;

void arm();

void setup()
{
  Serial.begin(9600);
  Serial.println("servo arm test started.");
  /*
  servoFB.attach(pinFB,530,2600);
  servoHL.attach(pinHL,530,2600);
  servoClaw.attach(pinClaw,530,2600);
  servoSite.attach(pinSite,530,2600);
  */
    servoFB.attach(pinFB,530,2600);
  servoHL.attach(pinHL,530,2600);
  servoClaw.attach(pinClaw);
  servoSite.attach(pinSite,530,2600);

}

void loop()
{
  return;
  Serial.print("servo running");
  Serial.print(" ");
  Serial.println();
  //armClaw();
  armSite();
   //testAll();
}

void testAll()
{
  Serial.println("forwards & backwards.");
  servoFB.write(180);
  delay(1000);
  servoFB.write(90);
  delay(1000);
//return;
  Serial.println("high & low.");
  servoHL.write(0);
  delay(1000);
  servoHL.write(90);
   delay(1000);
   return;
   
  Serial.println("spin hand.");
  servoClaw.write(180);
  delay(1000);
  servoClaw.write(0);
   delay(2000);

  Serial.println("spin site.");
  servoSite.write(90);
  delay(1000);
  servoSite.write(0);
   delay(5000);
}


void armSite()
{
  int starta=-60,enda=120;
  Serial.println(starta);
  servoSite.write( starta );
  delay( 2000 );
  Serial.println(enda);
  servoSite.write( enda );
  delay( 2000 );
}

void armClaw()
{
  int starta=180,enda=0;
  Serial.println(starta);
  servoClaw.write( starta );
  delay( 2000 );
  Serial.println(enda);
  servoClaw.write( enda );
  delay( 2000 );
}

void armFB()
{
  servoFB.write( 90 );
  delay( 2000 );
  servoFB.write( 0 );
  delay( 2000 );
}
void armHL()
{
  servoHL.write( 90 );
  delay( 1000 );
  servoHL.write( 0 );
  delay( 1000 );
}
