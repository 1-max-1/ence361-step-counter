/*
 * displayTask.h
 *
 *  Authors: Max Hosking, Alex Pirie
 *
 *  This task handles displaying the joystick values on the LCD screen,
 *  and also displaying them on the computer by printing over serial.
 */

#ifndef _DISPLAY_TASK_H_
#define _DISPLAY_TASK_H_

void displayTaskSetup();
void displayTaskExecute();

// Toggles whether joystick values will be printed over the USART connection
void toggleUSARTPrinting();

#endif
