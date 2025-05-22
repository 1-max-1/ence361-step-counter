/**
 * joystick.h
 *
 * Authors: Max Hosking, Alex Pirie
 *
 * This is a hardware module exposing functions to interact with the joystick
 */

#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include <stdint.h>

#include "buttonStates.h"

typedef enum {JOYSTICK_RESTX=0, JOYSTICK_LEFT, JOYSTICK_RIGHT} xDirection_t;
typedef enum {JOYSTICK_RESTY=0, JOYSTICK_UP, JOYSTICK_DOWN} yDirection_t;

void joystickInit();
//poll joystick ADC
void joystickUpdate();
//Return % deflection in x-axis. 0% is rest, 100% can be in either direction.
uint16_t getXPower();
//Return % deflection in y-axis. 0% is rest, 100% can be in either direction.
uint16_t getYPower();
//Return direction in x-axis
xDirection_t getXDirection();
//Return direction in y-axis
yDirection_t getYDirection();
//Return joystick button state
buttonState_t getJoystickButtonState();

#endif
