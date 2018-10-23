

/*
  Use a button to simluate onoff switch.
*/

#include "onoff.h"
#include "util.h"

OnoffSwitch::OnoffSwitch(int pin)
{
    pinButton = pin;
}
void OnoffSwitch::init()
{
    pinMode(pinButton,INPUT);
    cur_onoff = false;
}


bool OnoffSwitch::isOn()
{
    int b = digitalRead(pinButton);
  
    if( 1== b && 0==cur_btn_val) {
        cur_onoff = !cur_onoff;
        debug("onoff status switched. Now is:");
        debugln(cur_onoff);
    } 
    cur_btn_val = b;
    return cur_onoff;
}

void OnoffSwitch::self_test()
{
    debugln("OnoffSwitch self test.");
    debug("status:");debugln(digitalRead(pinButton));
}