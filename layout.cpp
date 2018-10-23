

#include "util.h"
#include "layout.h"


// should be externed.
 const int
    pinButton = 11,
    pinIRLeft=13,
    pinIRRight=10,

    pinUltraSonicEcho=2,
    pinUltraSonicTrig=3,

    pinServoBack=9,
    pinServoFront=8,

    pinMotorDirLeft=4,
    pinMotorPWMLeft=5,
    pinMotorDirRight=7,
    pinMotorPWMRight=6,

    pinMoistureAO=2,
    pinMoistureDO=12;
    
void layout_print()
{
    debugln("ports layout:");
    debug("     IRLeft->"); debugln(pinIRLeft);
    debug("     IRRIght->"); debugln(pinIRRight);
    debug("     UltraSonicEcho->"); debugln(pinUltraSonicEcho);
    debug("");
}
