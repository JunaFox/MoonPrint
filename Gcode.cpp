#include "Gcode.h"

Gcode::Gcode() {

}

GcodeCommand Gcode::getData(String &Gcode) {

    // G1   X123.123 Y134.132 Z123.163 E000.000
    if(Gcode.substring(0,4) == "G1  ") {
        gcC.x = Gcode.substring(6, 12).toFloat();
        gcC.y = Gcode.substring(15, 21).toFloat();
        gcC.z = Gcode.substring(24, 30).toFloat();
        gcC.e = Gcode.substring(33, 39).toFloat();

    }else if (Gcode.substring(0, 4) == "M109" || Gcode.substring(0, 4) == "M104") {
        gcC.temp = Gcode.substring(6, 9).toInt();
    }

    return gcC;
}
