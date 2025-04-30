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

void potentiometerUpdate();
uint16_t getRawPotVal();
uint8_t getPotPercentage();

#endif /* _ROT_POT_H_ */
