/**
 * joystickTask.h
 *
 * Authors: Max Hosking, Alex Pirie
 *
 * This task stores values from the ADC connected to the joystick
 */

#ifndef _JOYSTICK_TASK_H_
#define _JOYSTICK_TASK_H_

#include <stdint.h>

void joystickTaskSetup();
void joystickTaskExecute();

// Return ADC value for x-axis
uint16_t getX();
// Return ADC value for y-axis
uint16_t getY();

#endif
