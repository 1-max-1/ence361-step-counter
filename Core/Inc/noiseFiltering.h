/**
 * noiseFiltering.h
 *
 * Authors: Max Hosking, Alex Pirie
 *
 * This module provides an implementation of a moving average filter to use for generic int16_t data.
 */

#ifndef _NOISE_FILTERING_H_
#define _NOISE_FILTERING_H_

#include <stdint.h>

// Will initialize all filters and assign the memory needed for them
void filtersInit();

// Call to process a value. The new filter average will be computed and returned.
int16_t filterValue(int16_t processValue, uint8_t filterID);

// Free's the memory associated with the specified filter.
// The filter cannot be updated/used after it has been destroyed
void destroyFilter(uint8_t filterID);

#endif // _NOISE_FILTERING_H_
