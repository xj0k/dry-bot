

#include "util.h"

#include "move.h"

static const int MOTOR_SPEED_SLOW=70, 
                MOTOR_SPEED_MID=120,
                 MOTOR_SPEED_HIGH=200;
static const int 
                MOTOR_BACK_MILLS=300,
                MOTOR_TURN_90_MILLS=600,
                MOTOR_TURNAROUND_MILLS=1500,
                MOTOR_MV_MILLS=50;


BotCart::BotCart(int pinMotorDirLeft,int pinMotorPWMLeft,int pinMotorDirRight,int pinMotorPWMRight)
{
    pin_dir_left = pinMotorDirLeft;
    pin_pwm_left = pinMotorPWMLeft;
    pin_dir_right = pinMotorDirRight;
    pin_pwm_right = pinMotorPWMRight;

    
}
void BotCart::init()
{
   pinMode(pin_dir_left, OUTPUT);  
    pinMode(pin_dir_right,OUTPUT); 

    debugln("motors inited.");
 
}

void BotCart::self_test()
{
  debugln("BotCart self test.");
  move_on(500);
}

void BotCart::stop()
{
  analogWrite(pin_pwm_left,0);
  analogWrite(pin_pwm_right,0);
}


static unsigned int angle2mills(unsigned int angle)
{
  return (unsigned int)(angle*(float)(MOTOR_TURN_90_MILLS/90));
}

void BotCart::turnright( int angle)
{
  ENTER();
  motor_drive(pin_dir_left,pin_pwm_left,true,MOTOR_SPEED_SLOW,0,angle2mills(angle)/2 );
  motor_drive(pin_dir_right,pin_pwm_right,false,MOTOR_SPEED_SLOW,0,angle2mills(angle)/2 );
}

void BotCart::turnleft( int angle)
{
  ENTER();
  //motor_drive(pin_dir_right,pin_pwm_right,true,MOTOR_SPEED_SLOW,0,angle2mills(angle));

  motor_drive(pin_dir_left,pin_pwm_left,false,MOTOR_SPEED_SLOW,0,angle2mills(angle)/2 );
  motor_drive(pin_dir_right,pin_pwm_right,true,MOTOR_SPEED_SLOW,0,angle2mills(angle)/2 );
}

void BotCart::backright( int angle)
{
  ENTER();
  motor_drive(pin_dir_right,pin_pwm_right,false,MOTOR_SPEED_SLOW,0,angle2mills(angle) );
}

void BotCart::backleft( int angle)
{
  ENTER();
  motor_drive(pin_dir_left,pin_pwm_left,false,MOTOR_SPEED_SLOW,0,angle2mills(angle));
}

void BotCart::turnaround()
{
  ENTER();
   // turn left
   motor_drive(pin_dir_right,pin_pwm_right,true,MOTOR_SPEED_SLOW,0,MOTOR_TURN_90_MILLS);
   // delay to reduce inertia
  delay(500);
  // back left
  motor_drive(pin_dir_left,pin_pwm_left,false,MOTOR_SPEED_SLOW,0,MOTOR_TURN_90_MILLS);
  stop();
}

void BotCart::turnaround_backwards()
{
  ENTER();
  // back left
  motor_drive(pin_dir_left,pin_pwm_left,false,MOTOR_SPEED_SLOW,0,MOTOR_TURN_90_MILLS);
   // delay to reduce inertia
  delay(500);
   // turn left
   motor_drive(pin_dir_right,pin_pwm_right,true,MOTOR_SPEED_SLOW,0,MOTOR_TURN_90_MILLS);
  stop();
}

void BotCart::move_(bool dir, int mills)
{
  static bool last_left_move = false;
  bool left_comp = false;

  // debug("BotCart::move_  ");debugln(mills);
  // both motors should run simultaneously.
  // but if the mills is pretty small, say 50ms, then the start order matters.
  if(last_left_move) {
    motor_drive(pin_dir_right,pin_pwm_right,dir,MOTOR_SPEED_SLOW,0,0);  
    motor_drive(pin_dir_left,pin_pwm_left,dir,MOTOR_SPEED_SLOW,0,0);
  } else {
    motor_drive(pin_dir_left,pin_pwm_left,dir,MOTOR_SPEED_SLOW,0,0);
    motor_drive(pin_dir_right,pin_pwm_right,dir,MOTOR_SPEED_SLOW,0,0);
  }
  last_left_move = !last_left_move;
  
  if(0!=mills) {
    delay(mills);  
    stop();
    
    if(left_comp) {
      // debugln("make up for left motor.");
      motor_drive(pin_dir_left,pin_pwm_right,dir,MOTOR_SPEED_SLOW,0,8);  
    }
  }
}

void BotCart::move_on(int mills)
{
  move_(true,mills);
}


void BotCart::backwards(int mills)
{

  ENTER();
    // MOTOR_SPEED_SLOW
  move_(false,mills);  
}


void BotCart::motor_drive(int pinDir, int pinPWM, bool dir, unsigned int speed, int distance=0, int mills=0 )
{
  // sadly, I have mounted the drives with wrong heading direction.So we have to reverse the intended direction.
   int hl = dir ? HIGH:LOW;  // HIGH & LOW are actually 1 and 0;
  //int hl = dir ? LOW:HIGH; 

  ENTER();
  // debug("mills:");debugln(mills);
     
  digitalWrite(pinDir,hl);
  analogWrite(pinPWM,speed);

  // will not stop if 0 mills is given.
  if(0!=mills) {
    delay(mills);  
    stop();
  }
  
}
