

#include "util.h"
#include "layout.h"


// student version.
 const int
    pinButton = 5,
    pinIRLeft=3,
    pinIRRight=2,

    pinUltraSonicEcho=22,
    pinUltraSonicTrig=23,

    pinServoFB=7,
    pinServoHL=8,
    pinServoHand=6,
    pinServoSite=9,

    pinMotorDirLeft=13,
    pinMotorPWMLeft=11,
    pinMotorDirRight=12,
    pinMotorPWMRight=10,

    pinMoistureAO=0,    // analog pin. unknown
    pinMoistureDO=24;

/*
 * new version bot
 const int
    pinButton = 12,
    pinIRLeft=13,
    pinIRRight=10,

    pinUltraSonicEcho=2,
    pinUltraSonicTrig=3,

    pinServoFB=9,
    pinServoHL=8,
    pinServoHand=10,
    pinServoSite=11,

    pinMotorDirLeft=4,
    pinMotorPWMLeft=5,
    pinMotorDirRight=7,
    pinMotorPWMRight=6,

    pinMoistureAO=2,    // analog pin.
    pinMoistureDO=13;
*/    
void layout_print()
{
    debugln("ports layout:");
    debug("     IRLeft->"); debugln(pinIRLeft);
    debug("     IRRIght->"); debugln(pinIRRight);
    debug("     UltraSonicEcho->"); debugln(pinUltraSonicEcho);
    debug("");
}

/*  old configuratinos.
const int
    pinButton = 11,
    pinIRLeft=13,
    pinIRRight=10,

    pinUltraSonicEcho=2,
    pinUltraSonicTrig=3,

    pinServoFB=9,
    pinServoHL=8,

    pinMotorDirLeft=4,
    pinMotorPWMLeft=5,
    pinMotorDirRight=7,
    pinMotorPWMRight=6,

    pinMoistureAO=2,    // analog pin.
    pinMoistureDO=12;

    */
