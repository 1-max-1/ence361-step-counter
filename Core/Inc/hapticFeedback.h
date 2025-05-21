/*
 * hapticFeedback.h
 *
 *  Created on: Apr 28, 2025
 *      Authors: Max Hosking, Alex Pirie
 *
 *  This hardware module allows control of the haptic feedback motor.
 */

#ifndef _HAPTIC_FEEDBACK_H_
#define _HAPTIC_FEEDBACK_H_

#include <stdbool.h>

// Enables or disables the haptic motor
void setHapticMotorState(bool state);

#endif /* _HAPTIC_FEEDBACK_H_ */
