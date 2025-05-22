/*
 * rotPot.h
 *
 *  Created on: Apr 29, 2025
 *      Authors: Max Hosking
 *
 *  This module handles the potentiometer
 */

#ifndef _ROT_POT_H_
#define _ROT_POT_H_

#include <stdint.h>

// Returns raw potentiometer value from ADC
// Values are filtered with moving average
uint16_t getRawPotVal();

// Returns the maximum possible value for this potentiometer
uint16_t getMaxPotVal();
// Returns the minimum possible value for this potentiometer
uint16_t getMinPotVal();

// Returns pot value as a percentage of the max value (0-100)
uint8_t getPotPercentage();

#endif /* _ROT_POT_H_ */
