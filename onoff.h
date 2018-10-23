
#ifndef _DRYBOT_ONOFF_H_

#define _DRYBOT_ONOFF_H_

class OnoffSwitch {
    public:
        OnoffSwitch(int pin);
        void init();
        bool isOn();

        void self_test();
        
    private:
        int pinButton;
        bool cur_onoff;
        int cur_btn_val;
};

#endif

