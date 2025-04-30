/*
 * hapticFeedback.c
 *
 *  Created on: Apr 28, 2025
 *      Authors: Max Hosking, Alex Pirie
 *
 *  This hardware module allows control of the haptic feedback motor.
 */


#include "hapticFeedback.h"

#include "gpio.h"

void setHapticMotorState(bool state) {
	GPIO_PinState pinState = state ? GPIO_PIN_SET : GPIO_PIN_RESET;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, pinState);
}
