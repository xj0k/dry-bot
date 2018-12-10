
#ifndef _DRYBOT_CLEAN_H_
#define _DRYBOT_CLEAN_H_

#include <Servo.h>

class Cleaner
{
  public:
    Cleaner(int pinServoFB,int pinServoHL,int pinServoHand,int pinServoSite);

    void init();
    void start_clean(int times);
    void end_clean();
    void do_clean_auto(int mode);

    void self_test();
  private:
    int pin_servo_fb,pin_servo_hl,pin_servo_hand,pin_servo_site;
    Servo servoFB;
    Servo servoHL;
    Servo servoHand;
    Servo servoSite;

    void spin_hand_();
    void fold_arm_();
};

#endif
