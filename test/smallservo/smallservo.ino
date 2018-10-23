
// test No.4 small servo. without control panel.
// test pass with mg90s.

#include <Servo.h>

const int pinServo = 6;
Servo myServo;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("Servo test begins");
  
  myServo.attach(pinServo);

}

void loop() {
  // put your main code here, to run repeatedly:
  //test1();
 // test2();
}
void test2()
{
  Serial.println("turn 90");
  myServo.write(0);
  delay(1000);  
  myServo.write(90);
  delay(500);
}
void test1()
{
  Serial.println("test on.");
  myServo.write(0);
  delay(1500);
  myServo.write(160);
  delay(1000);
    
}
