#include "moon_print.h"

void MoonPrint::setup() {
    //x.goToPos(100, 5000);
}

/* Test
 * G1   X050.000 Y000.000 Z000.000 E000.000;
 * G1   X000.000 Y050.000 Z000.000 E000.000;
 */

void MoonPrint::run() {
    if(gcC.x == newGcC.x && gcC.y == newGcC.y && gcC.z == newGcC.z && gcC.e == newGcC.e &&
       gcC.temp == newGcC.temp) {

            if (Serial.available()) {
                Gcode += char(Serial.read());
                if (Gcode.indexOf('\n') != -1) {
                    newGcC = gc.getData(Gcode);
                    Serial.println(String(newGcC.x) + " | " + String(newGcC.y));
                    Serial.println(Gcode);
                    Gcode = "";
                }
                /*Serial.println("X: " + String(gcC.x) + " Y: " + String(gcC.y) + " Z: " + String(gcC.z) +
                                  " E: " + String(gcC.e) + "Temp" + String(gcC.temp));*/
            } else if (millis() - timeLastSend >= 2000) {
                Serial.println("OK");
                timeLastSend = millis();
            }
        }

    // Move axes to position
    bool X = x.move();
    bool Y = y.move();
    bool Z = z.move();
    bool E = e.move();
    if(X && Y && Z && E) {
        // Calculate speed of axes
        float maxMove = 0;
        auto distanceX = abs(newGcC.x * STEPS_PER_MM_X - gcC.x * STEPS_PER_MM_X);
        auto distanceY = abs(newGcC.y * STEPS_PER_MM_Y - gcC.y * STEPS_PER_MM_Y);
        auto distanceZ = abs(newGcC.z * STEPS_PER_MM_Z - gcC.z * STEPS_PER_MM_Z);
        auto distanceE = abs(newGcC.e * STEPS_PER_MM_E - gcC.e * STEPS_PER_MM_E);
        maxMove = max(maxMove, distanceX);
        maxMove = max(maxMove, distanceY);
        maxMove = max(maxMove, distanceZ);
        maxMove = max(maxMove, distanceE);

        gcC = newGcC;
        // Tell axes what to do
        x.goToPos(gcC.x, maxMove / distanceX * 5000);
        y.goToPos(gcC.y, maxMove / distanceY * 5000);
        z.goToPos(gcC.z, maxMove / distanceZ * 5000);
        e.goToPos(gcC.e, maxMove / distanceE * 5000);
    }
}
