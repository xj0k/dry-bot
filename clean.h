
#ifndef _DRYBOT_CLEAN_H_
#define _DRYBOT_CLEAN_H_

#include <Servo.h>

class Cleaner
{
  public:
    Cleaner(int pinServoFront,int pinServoBack);
    void init();
    void start_clean(int times);
    void end_clean();

    void self_test();
  private:
    int pin_servo_front,pin_servo_back;
    Servo servoFront;
    Servo servoBack;
};

#endif
