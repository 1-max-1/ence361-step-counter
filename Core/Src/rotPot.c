/*
 * rotPot.h
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
	return adcTask_getRotPot();
}

uint8_t getPotPercentage() {
	uint16_t rawVal = getRawPotVal();

	// In case of electrical glitch
	if (rawVal > POT_MAX)
		rawVal = POT_MAX;
	else if (rawVal < POT_MIN)
		rawVal = POT_MIN;

	// rawVal will never go over POT_MAX (4095) so can safely cast to int16_t
	int16_t val = filterValue((int16_t)rawVal, 3);
	return 100 * (val - POT_MIN) / (POT_MAX - POT_MIN); // Compute percentage of 100
}
