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

void adcTaskUpdate() {
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 3); //adc values are a register for the configured devices; this updates the register
}

uint16_t adcTask_getRotPot() {
	return raw_adc[0];
}

uint16_t adcTask_getJoystickY() {
	return raw_adc[1];
}

uint16_t adcTask_getJoystickX() {
	return raw_adc[2];
}
