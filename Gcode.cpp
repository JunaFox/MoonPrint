#include "Gcode.h"

Gcode::Gcode() {

}

GcodeCommand Gcode::getData(String Gcode) {

    // G1    X123.123 Y134.132 Z123.163 E000.000
    gcC.eSetCurrentPos = false;
    gcC.xSetCurrentPos = false;
    gcC.ySetCurrentPos = false;
    gcC.zSetCurrentPos = false;

    if(Gcode.substring(0,5) == "G1   ") {
        gcC.x = Gcode.substring(7, 14).toFloat();
        gcC.y = Gcode.substring(16, 23).toFloat();
        gcC.z = Gcode.substring(25, 32).toFloat();
        gcC.e = Gcode.substring(34, 41).toFloat();

    } else if(Gcode.substring(0, 5) == "M109 " || Gcode.substring(0, 5) == "M104 ") {
        gcC.temp = Gcode.substring(6, 9).toInt();
    } else if(Gcode.substring(0, 5) == "G92  ") {

        if(Gcode[4] == 'E') {
            gcC.eSetCurrentPos = true;
            gcC.e = Gcode.substring(6, 13).toFloat();
        } else if(Gcode[4] == 'X') {
            gcC.xSetCurrentPos = true;
            gcC.x = Gcode.substring(6, 13).toFloat();
        } else if(Gcode[4] == 'Y') {
            gcC.ySetCurrentPos = true;
            gcC.y = Gcode.substring(6, 13).toFloat();
        } else if(Gcode[4] == 'Z') {
            gcC.zSetCurrentPos = true;
            gcC.z = Gcode.substring(6, 13).toFloat();
        }
    }

    return gcC;
}
