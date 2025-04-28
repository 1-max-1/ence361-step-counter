/*
 * hapticFeedback.c
 *
 *  Created on: Apr 28, 2025
 *      Authors: Max Hosking, Alex Pirie
 */


#include "hapticFeedback.h"

#include "gpio.h"

void setState(bool state) {
	GPIO_PinState pinState = state ? GPIO_PIN_SET : GPIO_PIN_RESET;
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, pinState);
}
