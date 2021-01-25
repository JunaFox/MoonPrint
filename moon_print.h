#ifndef _MOON_PRINT_H_
#define _MOON_PRINT_H_

#include <Arduino.h>
#include "Gcode.h"
#include "Axis.h"
#include "config.h"

class MoonPrint {

public:
    void run();
    void setup();

private:
    Gcode gc;
    Axis x = Axis(STEP_PIN_X, DIR_PIN_X, ENABLE_PIN_X, MIN_PIN_X, MAX_PIN_X, STEPS_PER_MM_X);
};

#endif //_MOON_PRINT_H_
