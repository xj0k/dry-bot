
// Motor test with OpenJumper Motor controller shield (with L298P chipset)


int pinDir1 = 11; // direction control for motor 1.
int pinPWM1 = 10; // speed control for motor 1.

int pinDir2 = 12;
int pinPWM2 = 13;

// slow, motor will not run under this speed.
// It takes 1200mills to turn 90degrees with speed setting at 60.
static const int normal_speed = 80;
static const int normal_turn_mills = 600;



#ifndef debug
#define debugln Serial.println
#define debug Serial.print
#endif

unsigned int angle2mills(unsigned int angle)
{
  return (unsigned int)(angle*(float)(normal_turn_mills/90));
}

void tryAll()
{
  int i = 0;
  for(i=1;i<16;i++) {
    pinMode(i,OUTPUT);  
  }
  for(i=1;i<16;i++){
      digitalWrite(i,HIGH);
    analogWrite(i+1,100);
    delay(1000);
  }
}
void setup() 
{ 
    //return;
    Serial.begin(9600);
    Serial.println("motor test begin");
    //tryAll();
    //return;
    
    pinMode(pinDir1, OUTPUT);  
    pinMode(pinDir2,OUTPUT); 
    
} 



void loop() 
{ 
  //return;
   Serial.println("running");
   
   test_speed3();
  // test_turn();
   // test_start_stop();
   
}

// left/right
// forwards: 11/10
// backwards: 22/21
void test_speed3()
{

  
  motor1_drive_mills(true,200,0);
  motor2_drive_mills(true,200,0);  
  delay(1500);
  motor_stop();
  delay(3000);
  return;
  
  delay(500);
  motor1_drive_mills(false,200,0);
  motor2_drive_mills(false,200,0);  
  delay(500);
  motor_stop();
  
    delay(500);

}

void test_speed2()
{
  if(1) {
  motor1_drive_mills(true,66,0);
  motor2_drive_mills(true,60,0);  
  delay(2000);
  motor_stop();
  delay(1000);
  motor1_drive_mills(true,66,0);
  motor2_drive_mills(true,60,0);  
      delay(2000);

    motor_stop();
  
  delay(5000);

  motor1_drive_mills(false,66,0);
  motor2_drive_mills(false,63,0);  
  delay(2000);
  
  motor_stop();
    delay(1000);

  motor1_drive_mills(false,65,0);
  motor2_drive_mills(false,63,0);  
  
  delay(2000);
    motor_stop();
     delay(2000);
  } else {
  
   for (int i=0;i<3;i++) {
    motor1_drive_mills(false,65,0);
     motor2_drive_mills(false,60,0);  
    delay(500);
      motor_stop();
      delay(1000);
    }
  }
  
  delay(2000000); 
}

void motor_stop()
{
  analogWrite(pinPWM1,0);
  analogWrite(pinPWM2,0);
}

void move_on()
{

}

void turnleft(unsigned int angle)
{
  debugln("turnning left ... ");
  motor2_drive(true,normal_speed);
  unsigned int m = angle2mills(angle);
  debug("angle2mills:");debugln(m);
  delay(m);
  motor_stop();
}

void turnright(unsigned int angle)
{
  debugln("turnning right ... ");
  motor1_drive(true,normal_speed);
  unsigned int m = angle2mills(angle);
  debug("angle2mills:");debugln(m);
  delay(m);
  motor_stop();
}

void backright(unsigned int angle)
{
  debugln("turnning back right ... ");
  motor2_drive(false,normal_speed);
  unsigned int m = angle2mills(angle);
  debug("angle2mills:");debugln(m);
  delay(m);
  motor_stop();
}

void backleft(unsigned int angle)
{
  debugln("turnning back left ... ");
  motor1_drive(false,normal_speed);
  unsigned int m = angle2mills(angle);
  debug("angle2mills:");debugln(m);
  delay(m);
  motor_stop();
}

void turnaround()
{
  debugln("turnning around forwards ... ");
  turnleft(90);
  delay(300);
  backleft(90);
  motor_stop();
}
void turn_backaround()
{
  debugln("turnning around backwards ... ");
  backleft(90);
  delay(300);
  turnleft(90);
  motor_stop();
}

void test_turn()
{
  debugln("test turn.");
  
  turnleft(90);
  delay(1000);
  turnright(90);
  delay(1000);
  backleft(90);
  delay(1000);
  backright(90);
  delay(1000);
  
  turnaround();
  delay(1000); 
  turn_backaround();
  delay(1000); 

  delay(1000);
}
  
void test_start_stop()
{
  Serial.println("start motor");
  motor1_drive(true,normal_speed);
  motor2_drive(true,normal_speed);
  delay(500);
  motor_stop();  
  Serial.println("stop motor");
  delay(1000);
}

void test1()
{
  int value;
  for(value = 0 ; value <= 255; value+=5) 
  { 
    Serial.print("motor test ");
    Serial.println(value);
    motor1_drive(true, value);
    delay(30); 
   } 
}


void motor_drive(int pinDir, int pinPWM, bool dir, unsigned int speed, int distance=0, int mills=0 )
{
  // sadly, I have mounted the drives with wrong heading direction.So we have to reverse the intended direction.
  // int hl = dir ? HIGH:LOW;  // HIGH & LOW are actually 1 and 0;
  int hl = dir ? LOW:HIGH; 
     
  digitalWrite(pinDir,hl);
  analogWrite(pinPWM,speed);

  // will not stop if 0 mills is given.
  if(0!=mills) {
    delay(mills);  
    analogWrite(pinPWM,0);
  }
  
}

void motor1_drive_mills(bool dir, unsigned int speed,int mills)
{
  motor_drive(pinDir1,pinPWM1,dir,speed,0,mills);
}

void motor2_drive_mills(bool dir, unsigned int speed,int mills)
{
  motor_drive(pinDir2,pinPWM2,dir,speed,0,mills);
}

void motor1_drive(bool dir, unsigned int speed)
{
  motor_drive(pinDir1,pinPWM1,dir,speed,0,0);
}

void motor2_drive(bool dir, unsigned int speed)
{
  motor_drive(pinDir2,pinPWM2,dir,speed,0,0);
}
