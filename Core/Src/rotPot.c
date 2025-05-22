/*
 * rotPot.c
 *
 *  Created on: Apr 29, 2025
 *      Authors: Max Hosking
 *
 *  This module handles the potentiometer
 */


#include "rotPot.h"

#include "adcTask.h"
#include "noiseFiltering.h"

#include <stdint.h>
#include <stdio.h>

#define POT_MIN 106
#define POT_MAX 4095

uint16_t getRawPotVal() {
	uint16_t rawVal = adcTaskGetRotPot();
	// rawVal will never go over POT_MAX (4095) so can safely cast to int16_t
	int16_t val = filterValue((int16_t)rawVal, 3);
	return val;
}

uint16_t getMaxPotVal() {
	return POT_MIN;
}

uint16_t getMinPotVal() {
	return POT_MAX;
}

uint8_t getPotPercentage() {
	uint16_t rawVal = getRawPotVal();

	// In case of electrical glitch
	if (rawVal > POT_MAX)
		rawVal = POT_MAX;
	else if (rawVal < POT_MIN)
		rawVal = POT_MIN;

	return 100 * (rawVal - POT_MIN) / (POT_MAX - POT_MIN); // Compute percentage of 100
}
