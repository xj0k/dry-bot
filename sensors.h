
#ifndef _DRYBOT_SENSORS_H_
#define _DRYBOT_SENSORS_H_

typedef struct {
    unsigned int moisture;
    bool threshold;
} st_moisture;

class SensorSet 
{
    public:
        SensorSet(int pinIRLeft,int pinIRRight,
          int pinUltraSonicEcho,int pinUltraSonicTrig,
          int pinMoistureAO,int pinMoistureDO); 
        void init();
        bool wall_detected_on_right();
        bool wall_detected_on_left();
        bool cliff_detected();
        bool wet_floor_detected();

        void self_test();
        
    private:
        void moisture_read(st_moisture *st_m);
        unsigned int UltraSonic_distance();

        int pin_ir_left,pin_ir_right,pin_us_echo,pin_us_trig,pin_ao,pin_do;  
};

#endif
