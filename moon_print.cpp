#include "moon_print.h"

void MoonPrint::setup() {
    //x.goToPos(100, 5000);
}

/* Test
 * G1   X050.000 Y000.000 Z000.000 E000.000;
 * G1   X000.000 Y050.000 Z000.000 E000.000;
 */

void MoonPrint::run() {

    hotEnd.update(lcd);
    //hotEnd.setTemperature(100);

    // if no next line is available
    if(gcC.x == newGcC.x && gcC.y == newGcC.y && gcC.z == newGcC.z && gcC.e == newGcC.e &&
       gcC.temp == newGcC.temp) {
            // if data is waiting
            if (Serial.available()) {
                // store a bite of data
                Gcode += char(Serial.read());
                // if all data got stored
                if (Gcode.indexOf('\n') != -1) {
                    newGcC = gc.getData(Gcode);
                    Gcode = "";
                }

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

        // Calculate distances
        float maxMove = 0;
        auto distanceX = abs(newGcC.x * STEPS_PER_MM_X - gcC.x * STEPS_PER_MM_X);
        auto distanceY = abs(newGcC.y * STEPS_PER_MM_Y - gcC.y * STEPS_PER_MM_Y);
        auto distanceZ = abs(newGcC.z * STEPS_PER_MM_Z - gcC.z * STEPS_PER_MM_Z);
        auto distanceE = abs(newGcC.e * STEPS_PER_MM_E - gcC.e * STEPS_PER_MM_E);
        // Get max movement distance
        maxMove = max(maxMove, distanceX);
        maxMove = max(maxMove, distanceY);
        maxMove = max(maxMove, distanceZ);
        maxMove = max(maxMove, distanceE);

        // check if z axis is moving and change speed because z axis can't move as fast
        if(distanceZ != 0) {
            gcC = newGcC;
            // Tell axes what to do
            x.goToPos(gcC.x, maxMove / distanceX * MAX_STEPPER_SPEED_Z);
            y.goToPos(gcC.y, maxMove / distanceY * MAX_STEPPER_SPEED_Z);
            z.goToPos(gcC.z, maxMove / distanceZ * MAX_STEPPER_SPEED_Z);
            e.goToPos(gcC.e, maxMove / distanceE * MAX_STEPPER_SPEED_Z);
        } else {
            gcC = newGcC;
            // Tell axes what to do
            x.goToPos(gcC.x, maxMove / distanceX * MAX_STEPPER_SPEED);
            y.goToPos(gcC.y, maxMove / distanceY * MAX_STEPPER_SPEED);
            z.goToPos(gcC.z, maxMove / distanceZ * MAX_STEPPER_SPEED_Z);
            e.goToPos(gcC.e, maxMove / distanceE * MAX_STEPPER_SPEED);
        }
    }
}
