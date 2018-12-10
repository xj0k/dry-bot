
// draft version of dry-bot
// 


#include "move.h"
#include "sensors.h"
#include "clean.h"
#include "util.h"
#include "onoff.h"
#include "layout.h"

#define DRYBOT_VERSION "0.53"


Cleaner cleaner(pinServoFB,pinServoHL,pinServoHand,pinServoSite);
BotCart bot_cart(pinMotorDirLeft,pinMotorPWMLeft,pinMotorDirRight,pinMotorPWMRight);
SensorSet sensor_set(pinIRLeft,pinIRRight,pinUltraSonicEcho,pinUltraSonicTrig,pinMoistureAO,pinMoistureDO);
OnoffSwitch onoff_ctrl(pinButton);

bool self_test = false;
bool is_test_run = false;

unsigned int bot_backwards_mills = 100;
void setup()
{
    Serial.begin(9600);
    Serial.print("Drybot version:");Serial.println(DRYBOT_VERSION);
    //delay(100000);
    
    dry_bot_init();

    if(self_test) {
        do_self_test();
    }
}


void loop()
{
    if(self_test) {
        delay(100000);
        return;
    }
    
    if(is_test_run) {
        run_test();
        return;
    }
        
    dry_bot_run();

}

// components self check
// just move a little bit and read all sensors.
void do_self_test()
{
    ENTER();
    
    //sensor_set.self_test();
    cleaner.self_test();
    //bot_cart.self_test();
    //onoff_ctrl.self_test();
    
}

// write single test code here.
void run_test()
{
  
    //cleaner.do_clean_auto(0);
   // cleaner.self_test();
#if 0
    if(sensor_set.cliff_detected()){
        debugln("cliff deteced.");
    }
    if(sensor_set.wet_floor_detected()) {
        debugln("wet floor detected.");
        do_clean();
    }
 #endif 

    delay(5000);
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
    debugln("start cleaning, move to right place first.");
    bot_cart.move_on(300);
    delay(500);
    cleaner.do_clean_auto(0);   

    //return;
    debugln("move on cleanning.");
    bot_cart.move_on(200);
    delay(300);
    cleaner.do_clean_auto(0);
}

void dry_bot_run2()
{
    static bool inform = true;
    static unsigned int last_wet_detected = 0;
    const unsigned int min_clean_interval = 3000;

#if 1
    // 检测是否按下了按钮，是否处于连续按压按钮状态
    if (true!=onoff_ctrl.isOn()){
        if(inform) {
            bot_cart.stop();
          debugln("waiting for command. press button to start moving.");
          inform = false;
        }
        delay(100);
        return;            
    }
    inform = true;
#endif

    // 是否检测到了潮湿地面
    // 如果连续两次检测之间间隔的时间很短，说明我们还处于上一次检测、清理的过程之中，就不启动下一次清扫
    if(sensor_set.wet_floor_detected()) {
        debugln("wet floor detected.");
        bot_cart.stop();
        
        unsigned int mi = millis();
        if(mi-last_wet_detected < min_clean_interval) {
            debugln("should be the same place we just cleaned, ingore it.");
        } else {
          do_clean();  // this takes some time.
          last_wet_detected = millis();
        }
    }

    // 是否处于台阶上方
    if(sensor_set.cliff_detected()) {
        bot_cart.turnaround_backwards();
    }

    // 是否检测到左面的障碍物
    if(sensor_set.wall_detected_on_left()){
        bot_cart.stop();
        bot_cart.backwards(bot_backwards_mills);
        bot_cart.backright(60);
    }

    // 是否检测到右面的障碍物
    if(sensor_set.wall_detected_on_right()){
        bot_cart.stop();
        bot_cart.backwards(bot_backwards_mills);
        bot_cart.backleft(60);
    }

    // 没有障碍物、没有台阶、没有潮湿地面，则前进很小的距离
    bot_cart.move_on(0);
    //delayMicroseconds(1000);
    //delay(30);
}

void dry_bot_run()
{
    static bool inform = true;
    static unsigned int last_wet_detected = 0;
    const unsigned int min_clean_interval = 3000;

#if 1
    // 检测是否按下了按钮，是否处于连续按压按钮状态
    if (true!=onoff_ctrl.isOn()){
        if(inform) {
          debugln("waiting for command. press button to start moving.");
          inform = false;
        }
        delay(100);
        return;            
    }
    inform = true;
#endif

    // 是否检测到了潮湿地面
    // 如果连续两次检测之间间隔的时间很短，说明我们还处于上一次检测、清理的过程之中，就不启动下一次清扫
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

    // 是否处于台阶上方
    if(sensor_set.cliff_detected()) {
        bot_cart.turnaround_backwards();
    }

    // 是否检测到左面的障碍物
    if(sensor_set.wall_detected_on_left()){
        bot_cart.backwards(bot_backwards_mills);
        bot_cart.backright(60);
    }

    // 是否检测到右面的障碍物
    if(sensor_set.wall_detected_on_right()){
        bot_cart.backwards(bot_backwards_mills);
        bot_cart.backleft(60);
    }

    // 没有障碍物、没有台阶、没有潮湿地面，则前进很小的距离
    bot_cart.move_on(80);
    //delayMicroseconds(1000);
    //delay(30);
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


//  --- code for demo
/*
int cur_onoff = 0; // 当前开关状态
int cur_btn_val = 0;// 当前按钮状态
bool is_button_on()
{
    int pinButton = 6;
    int b = digitalRead(pinButton);

    if (LOW==b) {
        // 没有按开关
        return false;
    }
    // 按下开关了
    if(HIGH = cur_btn_val) {
        // 连续按压： 一次按压可能因为用力比较大或持续时间比较长，而被识别为多次连续按压
        // 对于多次按压，仅处理第一次，后续的都会被忽略
        // 如果当前按钮值是HIGH，说明按钮处于连续按压状态，忽略本次按压
        return false;
    }

    // 检测到一次有效按压
    // 因为是单个按钮，所以每一次按压都是切换开关状态，而不是简单的变成开或关（HIGH or LOW）
    cur_onoff = !cur_onoff;
      
    cur_btn_val = b;    // 保存这一次连续按压过程中的按钮状态
    return cur_onoff;
}
*/

/*
void do_clean_old()
{
  
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


void dry_bot_run_with_comment()
{

    // 检测是否按下了按钮，是否处于连续按压按钮状态
    if (true!=is_button_on()){
        delay(100);
        return;            
    }
    
    // 是否检测到了潮湿地面
    // 如果连续两次检测之间间隔的时间很短，说明我们还处于上一次检测、清理的过程之中，就不启动下一次清扫
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

    // 是否处于台阶上方
    if(sensor_set.cliff_detected()) {
        bot_cart.turnaround_backwards();
    }

    // 是否检测到左面的障碍物
    if(sensor_set.wall_detected_on_left()){
        bot_cart.backwards(bot_backwards_mills);
        bot_cart.backright(60);
    }

    // 是否检测到右面的障碍物
    if(sensor_set.wall_detected_on_right()){
        bot_cart.backwards(bot_backwards_mills);
        bot_cart.backleft(60);
    }

    // 没有障碍物、没有台阶、没有潮湿地面，则前进很小的距离
    bot_cart.move_on(60);
    delay(30);

}

*/
