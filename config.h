//
// Created by maxim on 25/01/2021.
//

#ifndef MOONPRINT_CONFIG_H
#define MOONPRINT_CONFIG_H

//Max stepper motor speed
#define MAX_STEPPER_SPEED 500
#define MAX_STEPPER_SPEED_Z 2000

//Stepper Motor X axis
#define STEP_PIN_X 25
#define DIR_PIN_X 23
#define ENABLE_PIN_X 27

#define STEPS_PER_MM_X 83.5782

//End stops X axis
#define MIN_PIN_X 22
#define MAX_PIN_X 24


//Stepper Motor Y axis
#define STEP_PIN_Y 31
#define DIR_PIN_Y 33
#define ENABLE_PIN_Y 29

#define STEPS_PER_MM_Y 83.5782

//End stops Y axis
#define MIN_PIN_Y 26
#define MAX_PIN_Y 28


//Stepper Motor Z axis
#define STEP_PIN_Z 37
#define DIR_PIN_Z 39
#define ENABLE_PIN_Z 35

#define STEPS_PER_MM_Z 163.7795

//End stops Z axis
#define MIN_PIN_Z 30
#define MAX_PIN_Z 32


//Stepper Motor E axis
#define STEP_PIN_E 43
#define DIR_PIN_E 45
#define ENABLE_PIN_E 41

#define STEPS_PER_MM_E 100.5221

//End stops E axis
#define MIN_PIN_E 0
#define MAX_PIN_E 0

//NTC Pin
#define NTC_PIN 8
#define RESISTOR 4700

//Hot end
#define HOT_END_PIN 2
#define FAN_PIN 3
#define MAX_TEMP 250
#define MIN_TEMP 0
#define DKp 18
#define DKi 0.2
#define DKd 40
#define Bias 100


#define ABSZERO 273.15
#define MAXANALOGREAD 1023.0

//LCD Pins
#define LCD_RS_PIN 20
#define LCD_ENABLE_PIN 17
#define LCD_D4_PIN 16
#define LCD_D5_PIN 21
#define LCD_D6_PIN 5
#define LCD_D7_PIN 6

#endif //MOONPRINT_CONFIG_H
