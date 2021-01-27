#ifndef MOONPRINT_GCODE_H
#define MOONPRINT_GCODE_H

#include <Arduino.h>
#include "Axis.h"

struct GcodeCommand {
    float x = 0;
    bool xSetCurrentPos = false;
    float y = 0;
    bool ySetCurrentPos = false;
    float z = 0;
    bool zSetCurrentPos = false;
    float e = 0;
    bool eSetCurrentPos = false;
    int temp = 0;
};

class Gcode {

public:
    Gcode();

    /**
     * Takes a G-code line and processes it.
     * First 4 for Command. Example ("G1    X123.123 Y134.132 Z123.163 E123.183")
     * @param G-code line.
     * @return Position and temperature.
     */
    GcodeCommand getData(String Gcode);

private:
    GcodeCommand gcC;
};

#endif //MOONPRINT_GCODE_H
