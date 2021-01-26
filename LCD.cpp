#include "LCD.h"

LCD::LCD() : lcd(LCD_RS_PIN, LCD_ENABLE_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN) {
    // Set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
}

void LCD::print(int column, int line, const String& text) {

    if(millis() - lastFrame >= 250) {
        // Set the cursor to column, line
        lcd.setCursor(column, line);

        // Print
        lcd.print(text);

        // Save time when frame was drawn
        lastFrame = millis();
    }
}