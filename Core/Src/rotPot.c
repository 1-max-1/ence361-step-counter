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

#include <stdint.h>
#include <stdio.h>

#define POT_MIN 106
#define POT_MAX 4095



uint16_t getRawPotVal() {
	return adcTask_getRotPot();
}

uint8_t getPotPercentage() {
	uint16_t val = adcTask_getRotPot();
	// In case of glitch
	if (val > POT_MAX)
		val = POT_MAX;
	else if (val < POT_MIN)
		val = POT_MIN;

	return 100 * (val - POT_MIN) / (POT_MAX - POT_MIN);
}
