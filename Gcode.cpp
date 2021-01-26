#include "Gcode.h"

Gcode::Gcode() {

}

GcodeCommand Gcode::getData(String Gcode) {

    // G1   X123.123 Y134.132 Z123.163 E000.000
    gcC.eSetCurrentPos = false;
    gcC.xSetCurrentPos = false;
    gcC.ySetCurrentPos = false;
    gcC.zSetCurrentPos = false;

    if(Gcode.substring(0,4) == "G1  ") {
        gcC.x = Gcode.substring(6, 12).toFloat();
        gcC.y = Gcode.substring(15, 21).toFloat();
        gcC.z = Gcode.substring(24, 30).toFloat();
        gcC.e = Gcode.substring(33, 39).toFloat();

    } else if(Gcode.substring(0, 4) == "M109" || Gcode.substring(0, 4) == "M104") {
        gcC.temp = Gcode.substring(6, 9).toInt();
    } else if(Gcode.substring(0, 4) == "G92 ") {

        if(Gcode[4] == 'E') {
            gcC.eSetCurrentPos = true;
            gcC.e = Gcode.substring(5, 12).toFloat();
        } else if(Gcode[4] == 'X') {
            gcC.xSetCurrentPos = true;
            gcC.x = Gcode.substring(5, 12).toFloat();
        } else if(Gcode[4] == 'Y') {
            gcC.ySetCurrentPos = true;
            gcC.y = Gcode.substring(5, 12).toFloat();
        } else if(Gcode[4] == 'Z') {
            gcC.zSetCurrentPos = true;
            gcC.z = Gcode.substring(5, 12).toFloat();
        }
    }

    return gcC;
}
