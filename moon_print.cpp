#include "moon_print.h"

void MoonPrint::setup() {
    x.goToPos(100, 5000);
}

void MoonPrint::run() {
    /*if(Serial.available()) {
        String Gcode = Serial.readString();
        GcodeCommand gcC = gc.getData(Gcode);
        Serial.println("X: " + String(gcC.x) + " Y: " + String(gcC.y) + " Z: " + String(gcC.z) +
                          " E: " + String(gcC.e) + "Temp" + String(gcC.temp));
    }*/
    x.move();
}
