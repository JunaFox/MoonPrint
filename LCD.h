#ifndef MOONPRINT_LCD_H
#define MOONPRINT_LCD_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "config.h"

class LCD {

public:
    LCD();

    /**
     * Prints a String onto the specified LCD display
     * @param column Column
     * @param line Line
     * @param text Text that will be displayed
     */
    void print(int column, int line, const String& text);

private:
    LiquidCrystal lcd;

    // Last time a frame was drawn
    unsigned long lastFrame = 0;
};

#endif //MOONPRINT_LCD_H
