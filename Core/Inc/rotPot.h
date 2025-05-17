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

uint16_t getRawPotVal();
uint16_t getMaxPotVal();
uint16_t getMinPotVal();
uint8_t getPotPercentage();

#endif /* _ROT_POT_H_ */
