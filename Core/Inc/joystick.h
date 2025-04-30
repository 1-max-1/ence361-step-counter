/**
 * joystick.h
 *
 * Authors: Max Hosking, Alex Pirie
 *
 * This task stores values from the ADC connected to the joystick
 */

#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_
#include <stdint.h>

typedef enum {RESTX=0, LEFT, RIGHT} xDirection_t;
typedef enum {RESTY=0, UP, DOWN} yDirection_t;
typedef enum {NO_CHANGE=0, RELEASED, PRESSED, LONG_PRESSED} joystickButtonState_t;

void joystickSetup();
//poll joystick ADC
void joystickUpdate();
// Return ADC value for x-axis
uint16_t getXRaw();
// Return ADC value for y-axis
uint16_t getYRaw();
//Return % deflection in x-axis
uint16_t getXPower();
//Return % deflection in y-axis
uint16_t getYPower();
//Return direction in x-axis
xDirection_t getXDirection();
//Return direction in y-axis
yDirection_t getYDirection();
//Return joystick button state
joystickButtonState_t getJoystickButtonState();

#endif
