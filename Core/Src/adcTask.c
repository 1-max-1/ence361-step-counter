/*
 * adcTask.c
 *
 *  Created on: Apr 30, 2025
 *      Author: api57
 */
#include <stdint.h>
#include <stdbool.h>
#include "adc.h"

static uint16_t raw_adc[3];

void adcTaskExecute() {
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 3);
}

uint16_t getRotPot() {
	return raw_adc[0];
}

uint16_t getJoystickY() {
	return raw_adc[2];
}

uint16_t getJoystickX() {
	return raw_adc[1];
}
