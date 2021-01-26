#ifndef MOONPRINT_HOTEND_H
#define MOONPRINT_HOTEND_H

#include "config.h"
#include <Arduino.h>
#include "LCD.h"

class HotEnd {

public:
    HotEnd();

    static float getTemperature();

    /**
     * Set target temperature to specified temperature.
     * @param temp Specified temperature.
     */
    void setTemperature(float temp);

    /**
     * Tries to get to target temperature via PID controller.
     * Shuts down heating when temperature is below MIN_TEMP or over MAX_TEMP.
     * @param lcd LCD where the current temperature will be printed.
     * @return True when the temperature average for the last 6,25 seconds is in 15% of target temperature.
     */
    bool update(LCD &lcd);

private:
    float targetTemperature = 0;
    float currentTemp = 0;

    unsigned long lastProbe = 0;
    float values[25];
    float arraySum = 0;
    float mv = 0;

    // Higher error bigger output
    float Kp = DKp;
    // Integral error over time
    float Ki = DKi;
    // Change in error (delta error)
    float Kd = DKd;
    // Bias
    float b = Bias;
};

#endif //MOONPRINT_HOTEND_H
