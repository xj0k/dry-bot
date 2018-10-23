
#ifndef _DRYBOT_MOVE_H_
#define _DRYBOT_MOVE_H_

class BotCart
{
  public:
    BotCart(int pinDirLeft,int pinPWMLeft,int pinDirRight,int pinPWMRight);
    void init();
    void backwards(int mills);
    void move_on(int mills);
    void turnleft(int angle);
    void turnright(int angle);
    void backleft(int angle);
    void backright(int angle);
    void turnaround();
    void turnaround_backwards();
    void stop();

    void self_test();
  
  private:
    void motor_drive(int pinDir,int pinPWM, bool dir, unsigned int speed, int distance, int mills );
    void move_(bool dir, int mills);

    int pin_dir_left,pin_pwm_left,pin_dir_right,pin_pwm_right;

};


#endif
