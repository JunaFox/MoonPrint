#include "moon_print.h"

void MoonPrint::setup() {
    //x.goToPos(100, 5000);
}

void MoonPrint::run() {
    if(Serial.available()) {
        String Gcode = Serial.readString();
        GcodeCommand gcC = gc.getData(Gcode);

        // Calculate speed of axes
        float maxMove = 0;
        auto distanceX = float(gcC.x * STEPS_PER_MM_X - oldGcC.x * STEPS_PER_MM_X);
        auto distanceY = float(gcC.y * STEPS_PER_MM_Y - oldGcC.y * STEPS_PER_MM_Y);
        auto distanceZ = float(gcC.z * STEPS_PER_MM_Z - oldGcC.z * STEPS_PER_MM_Z);
        auto distanceE = float(gcC.e * STEPS_PER_MM_E - oldGcC.e * STEPS_PER_MM_E);
        maxMove = max(maxMove, distanceX);
        maxMove = max(maxMove, distanceY);
        maxMove = max(maxMove, distanceZ);
        maxMove = max(maxMove, distanceE);

        // Tell axes what to do
        x.goToPos(gcC.x, maxMove / distanceX * 5000);
        y.goToPos(gcC.y, maxMove / distanceY * 5000);
        z.goToPos(gcC.z, maxMove / distanceZ * 5000);
        e.goToPos(gcC.e, maxMove / distanceE * 5000);
        /*Serial.println("X: " + String(gcC.x) + " Y: " + String(gcC.y) + " Z: " + String(gcC.z) +
                          " E: " + String(gcC.e) + "Temp" + String(gcC.temp));*/
    }

    // Move axes to position
    x.move();
    y.move();
    z.move();
    e.move();
}
