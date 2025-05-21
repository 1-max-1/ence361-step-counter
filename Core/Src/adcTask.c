/**
 * adcTask.c
 * This task handles the ADC and uses DMA to get the values.
 * Authors: Max Hosking, Alex Pirie
 */

#include <stdint.h>
#include "adc.h"

// DMA will store ADC values here
static uint16_t raw_adc[3];

void adcTaskUpdate() {
	//adc values are a register for the configured devices; this updates the register
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 3);
}

uint16_t adcTaskGetRotPot() {
	return raw_adc[0];
}

uint16_t adcTaskGetJoystickY() {
	return raw_adc[1];
}

uint16_t adcTaskGetJoystickX() {
	return raw_adc[2];
}
