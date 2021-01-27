#include "moon_print.h"

void MoonPrint::setup() {
    //x.goToPos(100, 5000);
}

/* Test
 * G1   X050.000 Y000.000 Z000.000 E000.000;
 * G1   X000.000 Y050.000 Z000.000 E000.000;
 */

void MoonPrint::run() {

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

            } else if (millis() - timeLastSend >= 400) {
                Serial.println("OK");
                timeLastSend = millis();
            }
        }

    // Move axes to position
    bool X = x.move();
    bool Y = y.move();
    bool Z = z.move();
    bool E = e.move();
    bool Temp = true;
    if(gcC.temp != 0)
        Temp = hotEnd.update(lcd);
    else {
        hotEnd.setTemperature(0);
        hotEnd.update(lcd);
    }

    if(X && Y && Z && E && Temp) {

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

        // G92
        {
            if(newGcC.eSetCurrentPos) {
                newGcC.eSetCurrentPos = false;
                e.setCurrentPos(newGcC.e);
                e.goToPos(newGcC.e, 10000);
                Serial.print(newGcC.e);
            } else if(newGcC.xSetCurrentPos) {
                newGcC.xSetCurrentPos = false;
                x.setCurrentPos(newGcC.x);
                x.goToPos(newGcC.x, 10000);
                Serial.print(newGcC.x);
            } else if(newGcC.ySetCurrentPos) {
                newGcC.ySetCurrentPos = false;
                y.setCurrentPos(newGcC.y);
                y.goToPos(newGcC.y, 10000);
                Serial.print(newGcC.y);
            } else if(newGcC.zSetCurrentPos) {
                newGcC.zSetCurrentPos = false;
                z.setCurrentPos(newGcC.z);
                z.goToPos(newGcC.z, 10000);
                Serial.print(newGcC.z);
            }
        }

        gcC = newGcC;
        // check if z axis is moving and change speed because z axis can't move as fast
        if(distanceZ != 0) {
            // Tell axes what to do
            x.goToPos(gcC.x, float(maxMove / distanceX * MAX_STEPPER_SPEED_Z));
            y.goToPos(gcC.y, float(maxMove / distanceY * MAX_STEPPER_SPEED_Z));
            z.goToPos(gcC.z, float(maxMove / distanceZ * MAX_STEPPER_SPEED_Z));
            e.goToPos(gcC.e, float(maxMove / distanceE * MAX_STEPPER_SPEED_Z));
        } else {
            // Tell axes what to do
            x.goToPos(gcC.x, float(maxMove / distanceX * MAX_STEPPER_SPEED));
            y.goToPos(gcC.y, float(maxMove / distanceY * MAX_STEPPER_SPEED));
            z.goToPos(gcC.z, float(maxMove / distanceZ * MAX_STEPPER_SPEED_Z));
            e.goToPos(gcC.e, float(maxMove / distanceE * MAX_STEPPER_SPEED));
        }

        // update temperature target
        hotEnd.setTemperature(float(gcC.temp));
    }
}
