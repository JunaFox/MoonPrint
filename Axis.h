#ifndef MOONPRINT_AXIS_H
#define MOONPRINT_AXIS_H

#include <Arduino.h>

/**
 * Represents a axis
 */
class Axis {

public:
    Axis(short int stepPin, short int dirPin, short int enablePin, short int minPin, short int maxPin, float stepsPerMm, bool direction);

    /**
     * Set values for G-code execution.
     * @param pos G-code Position for this axis.
     * @param speed Speed of movement.
     */
    void goToPos(float pos, float speed);

    /**
     * Executes the movement.
     */
    bool move();

    /**
     * Moves in one direction.
     * @param direction Direction.
     */
    void step(bool direction);

private:
    // Pin-out
    const short int stepPin, dirPin, enablePin, minPin, maxPin;

    //
    unsigned int isPos = 0, solPos = 0;
    float stepSpeed = 5000;
    unsigned long int timeLastStep = 0;
    bool direction;

    // Needed steps per mm
    const float stepsPerMm;
};

#endif //MOONPRINT_AXIS_H
