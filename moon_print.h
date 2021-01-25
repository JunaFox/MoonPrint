#ifndef _MOON_PRINT_H_
#define _MOON_PRINT_H_

#include <Arduino.h>
#include "Gcode.h"
#include "Axis.h"
#include "config.h"
#include "HotEnd.h"

class MoonPrint {

public:
    void run();
    void setup();

private:
    Gcode gc;
    GcodeCommand oldGcC;
    GcodeCommand gcC;
    GcodeCommand newGcC;
    String Gcode;
    HotEnd hotEnd;
    Axis x = Axis(STEP_PIN_X, DIR_PIN_X, ENABLE_PIN_X, MIN_PIN_X, MAX_PIN_X, STEPS_PER_MM_X, true);
    Axis y = Axis(STEP_PIN_Y, DIR_PIN_Y, ENABLE_PIN_Y, MIN_PIN_Y, MAX_PIN_Y, STEPS_PER_MM_Y, false);
    Axis z = Axis(STEP_PIN_Z, DIR_PIN_Z, ENABLE_PIN_Z, MIN_PIN_Z, MAX_PIN_Z, STEPS_PER_MM_Z, true);
    Axis e = Axis(STEP_PIN_E, DIR_PIN_E, ENABLE_PIN_E, MIN_PIN_E, MAX_PIN_E, STEPS_PER_MM_E, true);

    // Last time "OK" was send
    unsigned long int timeLastSend = 0;
};

#endif //_MOON_PRINT_H_
