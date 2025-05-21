/**
 * blinkyTask.c
 *
 * Authors: Max Hosking, Alex Pirie
 *
 * This task toggles the green onboard LED
 */

#include "blinkyTask.h"

#include "gpio.h"

void blinkyTaskExecute() {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
