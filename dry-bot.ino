
// draft version of dry-bot
// 


#include "move.h"
#include "sensors.h"
#include "clean.h"
#include "util.h"
#include "onoff.h"
#include "layout.h"

#define DRYBOT_VERSION "0.0.8"


Cleaner cleaner(pinServoFront,pinServoBack);
BotCart bot_cart(pinMotorDirLeft,pinMotorPWMLeft,pinMotorDirRight,pinMotorPWMRight);
SensorSet sensor_set(pinIRLeft,pinIRRight,pinUltraSonicEcho,pinUltraSonicTrig,pinMoistureAO,pinMoistureDO);
OnoffSwitch onoff_ctrl(pinButton);

bool self_test = false;
bool no_run = false;
bool is_run_test = false;

void setup()
{
    Serial.begin(9600);
    debug("Drybot version:");debugln(DRYBOT_VERSION);
    
    dry_bot_init();

    if(self_test) {
        do_self_test();
    }
}


// initial configuration
unsigned int bot_backwards_mills = 100;
unsigned long bot_max_run_duration = 60000; // in milliseconds
unsigned long bot_run_start = 0;

void loop()
{
    if(self_test) {
        delay(1000);
        return;
    }
    
  
    if(!bot_run_start) {
        bot_run_start = millis();
    }
    
    if(no_run) {
        delay(1000);
        return;
    }
    if(is_run_test) {
        run_test();
        return;
    }
        
    dry_bot_run();

}

// write single test code here.
void run_test()
{
  //test_wet_floor();
  do_clean();
    //cleaner.start_clean(6);
    
    delay(100000);
}


// components self check
// just move a little bit and read all sensors.
void do_self_test()
{
    ENTER();
    
    sensor_set.self_test();
    cleaner.self_test();
    bot_cart.self_test();
    onoff_ctrl.self_test();
}

void clean_by_move(int repeats,int mills=100)
{
  for(int i=0;i<=repeats;i++) {
    bot_cart.backwards(mills*2);
    delay(100);
    bot_cart.move_on(mills);
    delay(100);
   }
}

void do_clean()
{
  if(0) {
    cleaner.start_clean(2);
    clean_by_move(2,200);
    cleaner.end_clean();

    return;
  }
  // move to right position first
  // but slowly
  for(int i=0;i<12;i++) {
    delay(20);
    bot_cart.move_on(60);  
  }
    
  cleaner.start_clean(5);
  clean_by_move(5);
  cleaner.end_clean();
  
  bot_cart.turnleft(40);
  cleaner.start_clean(3);
  clean_by_move(3);
  cleaner.end_clean();

  bot_cart.turnright(60);
  cleaner.start_clean(3);
  clean_by_move(3); 
  cleaner.end_clean();
  
  return;

  // leave the area.
    for(int j=0;j<10;j++) {
    bot_cart.backwards(60);  
  }
}


void dry_bot_run()
{
    static bool inform = true;
    static unsigned int last_wet_detected = 0;
    const unsigned int min_clean_interval = 5000;

    if (true!=onoff_ctrl.isOn()){
        if(inform) {
          debugln("waiting for command. press button to start moving.");
          inform = false;
        }
        delay(100);
        return;            
    }
    inform = true;

    if(sensor_set.wet_floor_detected()) {
        debugln("wet floor detected.");
        
        unsigned int mi = millis();
        if(mi-last_wet_detected < min_clean_interval) {
            debugln("should be the same place we just cleaned, ingore it.");
        } else {
          do_clean();  // this takes some time.
          last_wet_detected = millis();
        }
    }

    if(sensor_set.cliff_detected()) {
        bot_cart.turnaround_backwards();
    }

    if(sensor_set.wall_detected_on_left()){
        bot_cart.backwards(bot_backwards_mills);
        bot_cart.backright(60);
    }

    if(sensor_set.wall_detected_on_right()){
        bot_cart.backwards(bot_backwards_mills);
        bot_cart.backleft(60);
    }

    bot_cart.move_on(60);
    delay(30);

}

void dry_bot_init()
{
    debugln("Drybot starting ... ");
    
    bot_cart.init();
    sensor_set.init();
    cleaner.init();
    onoff_ctrl.init();

    debugln("Dry bot started.");

    layout_print();
}


// standstill, easy to debug.
void dry_bot_fixpoint_run()
{
     delay(300);

    if(sensor_set.wet_floor_detected()) {
        debugln("wet floor detected.");
        do_clean();
        
    }
   
    if(sensor_set.cliff_detected()) {
        debugln("cliff deteced,should turnaround");
    }

     if(sensor_set.wall_detected_on_left()){
        debugln("wall detected on left side. should turn right");
    }

    if(sensor_set.wall_detected_on_right()){
      debugln("wall detected on right side. should turn left");
      }

}

// --- single part test ---

void test_wet_floor()
{
  for(int i=0;i<10;i++) {
    sensor_set.wet_floor_detected();
    delay(2000);
  }
}

void test_motor()
{
   
   
   bot_cart.move_on(50);
   delay (1000);
   bot_cart.backwards(50);
   delay(1000);
 
   
   bot_cart.turnleft(60);
   delay(1000);
  bot_cart.turnright(60);
   delay(1000);
   
   bot_cart.backleft(60);
   delay(1000);
  bot_cart.backright(60);
   delay(1000);
   
   bot_cart.turnaround();
   delay(2000);  

  bot_cart.turnaround_backwards();
   delay(2000);  

}
