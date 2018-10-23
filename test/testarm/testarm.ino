
// test No.4 small servo. without control panel.
// test pass with mg90s.

#include <Servo.h>

const int pinServoFront = 8;
const int pinServoBack = 9;

// intial position of the arms.
// 90-> straight, 180->up , 0 down.
const int frontInitialPos = 10;
// 180-> horizontal back, 90: vertical up
const int backInitialPos = 180;  

Servo servoFront;
Servo servoBack;

void setup() {
  Serial.begin(9600);
  Serial.println("Arm test begins");
  
  servoFront.attach(pinServoFront);
  servoBack.attach(pinServoBack);

  servoFront.write(frontInitialPos);
  servoBack.write(backInitialPos);
}

unsigned int mcnt = 1;
unsigned int tcnt = 0;
void loop() {
 
 // testServoBack();
 //testServoFront();
 if(tcnt < mcnt) {
  Serial.print("doing test No.");
  Serial.println(tcnt);
  testClean();
  tcnt++;
  if(tcnt==mcnt) {
    Serial.println("tests all done.");
  }
 } else {
  delay(1000); 
 }
}

void testClean()
{
  Serial.println("simulating floor clean motion.");
  /*
   * Serial.println("first back to folded postion");
  servoBack.write(backInitialPos);
  servoFront.write(180);
  delay(3000);
  */

  Serial.println("set to clean-ready postion");
  servoBack.write(180);
  servoFront.write(10);
  delay(2000);

  Serial.println("cleaning...");
  for(int i=0;i<3;i++) {
    Serial.print(i);
    Serial.print(",");
    servoFront.write(25);
    delay(500);
    servoFront.write(10);
    delay(500);
  }

  Serial.println(" done!");
  Serial.println("return to folded postion");
  servoBack.write(backInitialPos);
  servoFront.write(10);
  delay(2000);
}


void testServoFront()
{
  Serial.println("Running front arm test");
  servoFront.write(frontInitialPos);
  delay(500);  
  servoFront.write(90);
  delay(500);  
  servoFront.write(180);
  delay(500);
}
void testServoBack()
{
  Serial.println("Running back arm test.");
  servoBack.write(backInitialPos);
  delay(1000);
  // return;
  servoBack.write(90);
  delay(1000);
}
