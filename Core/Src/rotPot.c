/*
 * rotPot.h
 *
 *  Created on: Apr 29, 2025
 *      Authors: Max Hosking
 *
 *  This module handles the potentiometer
 */


#include "rotPot.h"

#include "adc.h"

#include <stdint.h>
#include <stdio.h>

static uint16_t raw_adc[3] = {0};
static uint16_t potVal = 0;

#define POT_MIN 106
#define POT_MAX 4095

void readPotValFromADC() {
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 3);
	potVal = raw_adc[0];
}

uint16_t getRawPotVal() {
	return potVal;
}

uint8_t getPotPercentage() {
	uint16_t val = potVal;

	// In case of glitch
	if (val > POT_MAX)
		val = POT_MAX;
	else if (val < POT_MIN)
		val = POT_MIN;

	return 100 * (val - POT_MIN) / (POT_MAX - POT_MIN);
}
