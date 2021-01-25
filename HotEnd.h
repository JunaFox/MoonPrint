#ifndef MOONPRINT_HOTEND_H
#define MOONPRINT_HOTEND_H

#include "config.h"
#include <Arduino.h>

class HotEnd {

public:
    HotEnd();

    float getTemperature();

    void setTemperature(float temp);

    void update();

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
