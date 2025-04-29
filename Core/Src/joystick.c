/**
 * joystick.c
 *
 * Authors: Max Hosking, Alex Pirie
 *
 * This task stores values from the ADC connected to the joystick
 */

#include "joystick.h"

#include "gpio.h"
#include "adc.h"

#define JOYSTICK_LEFT_OUTER_VAL 4045
#define JOYSTICK_LEFT_INNER_VAL 2300
#define JOYSTICK_RIGHT_OUTER_VAL 240
#define JOYSTICK_RIGHT_INNER_VAL 2090
#define JOYSTICK_UP_OUTER_VAL 315
#define JOYSTICK_UP_INNER_VAL 2200
#define JOYSTICK_DOWN_OUTER_VAL 4095
#define JOYSTICK_DOWN_INNER_VAL 2400

static uint16_t raw_adc[2];


void joystickExecute() {
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 2);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {

}

uint16_t getXRaw() {
	return raw_adc[1];
}

uint16_t getYRaw() {
	return raw_adc[0];
}

uint16_t getXPower() {
	uint16_t xPercentage = 0;

	if (raw_adc[1] >= JOYSTICK_LEFT_INNER_VAL) {
		xPercentage = (raw_adc[1] - JOYSTICK_LEFT_INNER_VAL) * 100 / (JOYSTICK_LEFT_OUTER_VAL - JOYSTICK_LEFT_INNER_VAL);
	} else if (raw_adc[1] <= JOYSTICK_RIGHT_INNER_VAL) {
		xPercentage = (JOYSTICK_RIGHT_INNER_VAL - raw_adc[1]) * 100 / (JOYSTICK_RIGHT_INNER_VAL - JOYSTICK_RIGHT_OUTER_VAL);
	}
	return xPercentage;
}

uint16_t getYPower() {
	uint16_t yPercentage = 0;

	if (raw_adc[0] >= JOYSTICK_DOWN_INNER_VAL) {
		yPercentage = (raw_adc[0] - JOYSTICK_DOWN_INNER_VAL) * 100 / (JOYSTICK_DOWN_OUTER_VAL - JOYSTICK_DOWN_INNER_VAL);
	} else if (raw_adc[0] <= JOYSTICK_UP_INNER_VAL) {
		yPercentage = (JOYSTICK_UP_INNER_VAL - raw_adc[0]) * 100 / (JOYSTICK_UP_INNER_VAL - JOYSTICK_UP_OUTER_VAL);
	}
	return yPercentage;
}

 xDirection_t getXDirection() {
	 xDirection_t xDirection = RESTX;

	if (raw_adc[1] >= JOYSTICK_LEFT_INNER_VAL) {
		xDirection = LEFT;
	} else if (raw_adc[1] <= JOYSTICK_RIGHT_INNER_VAL) {
		xDirection = RIGHT;
	}
	return xDirection;
}

 yDirection_t getYDirection() {
	 yDirection_t yDirection = RESTY;

	if (raw_adc[0] >= JOYSTICK_DOWN_INNER_VAL) {
		yDirection = DOWN;
	} else if (raw_adc[0] <= JOYSTICK_UP_INNER_VAL) {
		yDirection = UP;
	}
	return yDirection;
}


