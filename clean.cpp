

#include <Servo.h>

#include "util.h"

#include "clean.h"


// intial position of the arms.
// 10 & 180 is clean point
// 180 & 90 is folded point.
static const int 
  fbInitialPos = 10, 
  hlInitialPos = 60,
  handInitialPos = 0,
  siteInitialPos = 90;

  // hand:0~180, site:60~120, hl:0, fb:0~90
  /* clean pos
    site:90
    FB:0->90
    hand:0->180
  */
 static const int
  fbCleanPos = 70,
  hlCleanPos = 30,
  handCleanPosStart = 0, handCleanPosEnd = 180,
  siteCleanPos = 90;
  

Cleaner::Cleaner(int pinServoFB,int pinServoHL,int pinServoHand,int pinServoSite) 
{  
  pin_servo_fb = pinServoFB;
  pin_servo_hl = pinServoHL;
  pin_servo_hand = pinServoHand;
  pin_servo_site = pinServoSite;
}

void Cleaner::init()
{
  servoFB.attach(pin_servo_fb);
  servoHL.attach(pin_servo_hl);
  servoHand.attach(pin_servo_hand);
  servoSite.attach(pin_servo_site);

  debugln("initializing arm Hand");
  servoHand.write(handInitialPos);
  delay(200);
  fold_arm_();
  return;

  debugln("initializing arm FB");
  servoFB.write(fbInitialPos);
  delay(200);
  
  debugln("initializing arm HB");
  servoHL.write(hlInitialPos);
    delay(200);



  debugln("initializing arm site");
  servoSite.write(siteInitialPos);

  delay(200);

  debugln("clean arm inited.");
}

void Cleaner::spin_hand_()
{
  int i = 0;
  debugln("spin hand ");

  for(i=0;i<4;i++) {
    servoHand.write(handCleanPosStart);
    delay(500);
    servoHand.write(handCleanPosEnd);
    delay(500);
  } 
}


void Cleaner::fold_arm_()
{
  debugln("fold arm");

  servoFB.write(5);
  servoHL.write(35);
  delay(1000);
}

// mode: reserve for future use.
void Cleaner::do_clean_auto(int mode)
{

  ENTER();

if(1== mode) {
  // complex mode.

  // spin hand in the middle position
  debugln("clean in the middle");
  servoFB.write(70);
  delay(500);
  spin_hand_();  
  servoFB.write(10);
  delay(1000);

  // right
  debugln("clean on the right");
  servoSite.write(70);
  delay(1000);
  servoFB.write(70);
  delay(1000);
  spin_hand_();
  servoFB.write(10);
  delay(1000);

  // left
  debugln("clean on the left");
  servoSite.write(110);
  delay(1000);
  servoFB.write(70);
  delay(1000);
  spin_hand_();
  servoFB.write(10);
  delay(1000);
}

 // near middle
  debugln("clean in near field");
  servoSite.write(90);
  delay(500);
  servoFB.write(50);
  delay(500);
  servoHL.write(10);
  spin_hand_();
  servoHL.write(hlInitialPos);
  servoFB.write(10);
  delay(1000);

   // near right
   fold_arm_();  
  debugln("clean in near right");
  servoSite.write(30);
  delay(500);
  servoFB.write(50);
  delay(500);
  servoHL.write(10);
  spin_hand_();
  servoHL.write(hlInitialPos);
  servoFB.write(10);
  delay(1000);

  // near left
  fold_arm_();
  debugln("clean in near left");
  servoSite.write(110);
  delay(500);
  servoFB.write(50);
  delay(500);
  servoHL.write(10);
  spin_hand_();
  servoHL.write(hlInitialPos);
  servoFB.write(10);
  delay(1000);

}

void Cleaner::self_test()
{
  debugln("cleaner self test.");
  
  fold_arm_();

 debugln("site 90");
  servoSite.write(90);
  delay(1000);
  debugln("site 30");
  servoSite.write(30);
  delay(1000);
  
 

    debugln("site 110");

  servoSite.write(110);
  delay(1000);
  
  //debugln("do_clean_auto test");
  //do_clean_auto(0);
  //debugln("back arm servo test.");
  
  //servoHL.write(60);
  //debugln("front arm servo test.");
  //servoFB.write(60);

  delay(2000);
}


// --- obselete code --
void Cleaner::start_clean(int times=10)
{
  if(0) {
    unsigned int back_angle = 120, front_angle=90;
    unsigned int steps = 10;
   // back: from 120 to 180
   // front: from 90 to 10
   servoHL.write(back_angle);
   servoFB.write(front_angle);

   for (int i=0;i<steps;i++) {
      int bi = back_angle + 6*i ;
      int fi = front_angle - 6*i ;
      servoHL.write(bi);
      debugln(bi);
      delay(100);
      //servoFB.write(fi);
      
      debugln(fi);
      delay(100);
   }
   
    return;
  }
  
    ENTER();  
  debugln("set to clean-ready postion");
  servoHL.write(180);
  servoFB.write(10);
  delay(2000);

  debugln("cleaning...");
  for(int i=0;i<times;i++) {
    Serial.print(i);
    Serial.print(",");
    servoFB.write(25);
    delay(300);
    if(i==times-1) {
      servoFB.write(10);
    } else {
      servoFB.write(5);
      }
    delay(800);
  }
}

void Cleaner::end_clean()
{
  ENTER();
  debugln("Done cleaning. Return to intial postion");
  servoHL.write(fbInitialPos);
  servoFB.write(hlInitialPos);
  delay(2000);

}
