

#include <Servo.h>

#include "util.h"

#include "clean.h"


// intial position of the arms.
// 10 & 180 is clean point
// 180 & 90 is folded point.
static const int frontInitialPos = 180;
static const int backInitialPos = 180; // old value:90

Cleaner::Cleaner(int pinServoFront,int pinServoBack) 
{  
  pin_servo_front = pinServoFront;
  pin_servo_back = pinServoBack;
}

void Cleaner::init()
{
  servoFront.attach(pin_servo_front);
  servoBack.attach(pin_servo_back);

  servoFront.write(frontInitialPos);
  servoBack.write(backInitialPos);
  delay(1000);

  debugln("clean arm inited.");
}

void Cleaner::start_clean(int times=10)
{
  if(0) {
    unsigned int back_angle = 120, front_angle=90;
    unsigned int steps = 10;
   // back: from 120 to 180
   // front: from 90 to 10
   servoBack.write(back_angle);
   servoFront.write(front_angle);

   for (int i=0;i<steps;i++) {
      int bi = back_angle + 6*i ;
      int fi = front_angle - 6*i ;
      servoBack.write(bi);
      debugln(bi);
      delay(100);
      //servoFront.write(fi);
      
      debugln(fi);
      delay(100);
   }
   
    return;
  }
  
    ENTER();  
  debugln("set to clean-ready postion");
  servoBack.write(180);
  servoFront.write(10);
  delay(2000);

  debugln("cleaning...");
  for(int i=0;i<times;i++) {
    Serial.print(i);
    Serial.print(",");
    servoFront.write(25);
    delay(300);
    if(i==times-1) {
      servoFront.write(10);
    } else {
      servoFront.write(5);
      }
    delay(800);
  }
}

void Cleaner::end_clean()
{
  ENTER();
  debugln("Done cleaning. Return to intial postion");
  servoBack.write(frontInitialPos);
  servoFront.write(backInitialPos);
  delay(2000);

}

void Cleaner::self_test()
{
  debugln("cleaner self test.");
  debugln("back arm servo test.");
  servoBack.write(60);
  debugln("front arm servo test.");
  servoFront.write(60);

  delay(2000);
}
