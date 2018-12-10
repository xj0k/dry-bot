

#include "util.h"
#include "sensors.h"

static const int MAX_CLIFF=12;  // bigger than this, we are facing a cliff. unit in cm.
static const int MAX_MOISTURE=2; // bigger than this, we've detected an wet area.

static const int moisture_degress = 100;
static int initial_readout = 0;
static int moisture_limit = 30;

SensorSet::SensorSet(int pinIRLeft,int pinIRRight,
    int pinUltraSonicEcho,int pinUltraSonicTrig,
    int pinMoistureAO,int pinMoistureDO)
{
    pin_ir_left = pinIRLeft;
    pin_ir_right = pinIRRight;
    pin_us_echo = pinUltraSonicEcho;
    pin_us_trig = pinUltraSonicTrig;
    pin_ao = pinMoistureAO;
    pin_do = pinMoistureDO;
}


// convert the analog readouts to a relative moisture:1~moisture_degress. 
// no longer be used since it creats confusion.
static unsigned int moisture_convert(int readout)
{
  unsigned int mMAX=1024, mMIN=245;
  unsigned int interval = (mMAX-mMIN)/moisture_degress;
  return ((mMAX-readout)/interval);
}

void SensorSet::init()
{
    pinMode(pin_ir_left,INPUT);
    pinMode(pin_ir_right,INPUT);

    pinMode(pin_us_trig,OUTPUT);
    pinMode(pin_us_echo,INPUT);

    pinMode(pin_ao, INPUT);
    pinMode(pin_do, INPUT); 

    delay(1000); // dealy to stablize the moisture sensor.
    initial_readout = analogRead(pin_ao);
    debug("initial moisture:");
    debugln(initial_readout);
    // debugln("->");
    // debugln(moisture_convert(initial_readout));
  
    debugln("All sensors inited.");
}




void SensorSet::moisture_read(st_moisture *st_m)
{
    int readout = analogRead(pin_ao);

#ifdef DEBUG_VERBOSE
    debug("moisture read:");debugln(readout);
#endif

    // st_m->moisture = moisture_convert(readout);
    st_m->moisture = (readout);
    st_m->threshold = digitalRead(pin_do)==0?true:false;
 
}

bool SensorSet::wet_floor_detected()
{
    ENTER();
    //return(false);
    st_moisture st_m;
    moisture_read(&st_m);
    debugln(st_m.moisture);

    // threshold is not easy to manipulate.
    if(0) {
      if(st_m.threshold) {
          debugln(" ----- wet floor detected. ----");
      }
    }
    
    if( st_m.moisture<initial_readout &&( (initial_readout-st_m.moisture)>=moisture_limit) ) {
      debugln("wet floor detect by AO read.");  
      // Todo:
      // water may drop onto the sensor, cause a always-cleanup status, 
      // so we should change the initial_readout to compromise this.
      
      // short time range may help us to detect this situation.
      // dirty fix, too absurd.
      initial_readout -= 0; // 0
      debug("initial moisture changed to:");
      debugln(initial_readout);
      
      return true;
    }
    return false;
}


unsigned int SensorSet::UltraSonic_distance() 
{
  float dist;
  ENTER();

  digitalWrite(pin_us_trig,LOW);
  delayMicroseconds(2);
  digitalWrite(pin_us_trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_us_trig,LOW);

  dist = pulseIn(pin_us_echo,HIGH)/58.00;

#ifdef DEBUG_VERBOSE  
  debug("UltraSonic_read:");debugln(dist);
#endif
    if(dist>200) {
        debug("UltraSonic read a invalid value, ignore this read.");
        return 0;
    }
  
  return (unsigned int)dist;
}


bool SensorSet::cliff_detected()
{
    return (UltraSonic_distance()>MAX_CLIFF) ? true:false;
    //return true;
}


static bool IR_blocked(int pin)
{
  int x = digitalRead(pin);
  bool blocked = x==0?true:false;
  return blocked;
}


bool SensorSet::wall_detected_on_left()
{
    return IR_blocked(pin_ir_left);
}
bool SensorSet::wall_detected_on_right()
{
    return IR_blocked(pin_ir_right);
}

void SensorSet::self_test()
{
    st_moisture st_m;

    debugln("sefl test on moisture sensor.");
    moisture_read(&st_m);
    debug("read:");
    debugln(st_m.moisture);

    debugln("self test on IR sensor.");
    debug("left:");debugln(digitalRead(pin_ir_left));
    debug("right:");debugln(digitalRead(pin_ir_right));

    debugln("seflt test on ultrasonic sensor.");
    debug("distance:");debugln(UltraSonic_distance());
}
