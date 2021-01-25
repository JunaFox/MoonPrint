#include "Axis.h"

Axis::Axis(short stepPin, short dirPin, short enablePin, short minPin, short maxPin, float stepsPerMm, bool direction)
           : stepPin(stepPin), dirPin(dirPin), enablePin(enablePin), minPin(minPin),
             maxPin(maxPin), stepsPerMm(stepsPerMm) {

    // Set pin modes for stepper motor
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(enablePin, OUTPUT);

    this->direction = direction;
}

void Axis::goToPos(float pos, float speed) {
    solPos = int(pos * stepsPerMm);
    stepSpeed = speed;
}

bool Axis::move() {
    // step when last step is done
    if(micros() - timeLastStep >= stepSpeed) {
        if (solPos > isPos) {
            digitalWrite(dirPin, direction);

            // do a step
            digitalWrite(stepPin, HIGH);
            digitalWrite(stepPin, LOW);

            ++isPos;
        } else if (solPos < isPos) {
            digitalWrite(dirPin, !direction);

            // do a step
            digitalWrite(stepPin, HIGH);
            digitalWrite(stepPin, LOW);

            --isPos;
        }

        // save step time
        timeLastStep = micros();
    }

    if (solPos == isPos)
        return true;
    else
        return false;
}

void Axis::step(bool direction) {

    // step when last step is done
    if(micros() - timeLastStep >= stepSpeed) {
        // set direction
        digitalWrite(dirPin, direction);

        // do a step
        digitalWrite(stepPin, HIGH);
        digitalWrite(stepPin, LOW);

        // save step time
        timeLastStep = micros();
    }
}
