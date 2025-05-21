#include "noiseFiltering.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int16_t* pastValues;
	int16_t* tapValues;
	uint8_t currentIndex;
	uint8_t bufferLength;
	int32_t currentSum;
	bool fillBufferWithFirstValue;
	bool destroyed;
} noiseFilter_t;

#define NUM_FILTERS 4
static noiseFilter_t noiseFilters[NUM_FILTERS];

noiseFilter_t createFilter(int16_t* coeffs, uint8_t bufferLength, bool fillBufferWithFirstValue) {
	noiseFilter_t newFilter = {
		.pastValues = calloc(bufferLength, sizeof(int16_t)),
		.tapValues = calloc(bufferLength, sizeof(int16_t)),
		.currentIndex = 0,
		.bufferLength = bufferLength,
		.currentSum = 0,
		.fillBufferWithFirstValue = fillBufferWithFirstValue,
		.destroyed = false
	};

	for (uint16_t i = 0; i < bufferLength; i++) {
		newFilter.tapValues[i] = coeffs[i];
	}

	return newFilter;
}

void destroyFilter(uint8_t filterID) {
	noiseFilter_t *filter = &noiseFilters[filterID];
	free(filter->pastValues);
	filter->pastValues = NULL;
	free(filter->tapValues);
	filter->tapValues = NULL;
}

void filtersInit() {
	int16_t imuFilterCoeffs[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	noiseFilters[0] = createFilter(imuFilterCoeffs, 40, true);
	noiseFilters[1] = createFilter(imuFilterCoeffs, 40, true);
	noiseFilters[2] = createFilter(imuFilterCoeffs, 40, true);

	int16_t filter3Coeffs[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	noiseFilters[3] = createFilter(filter3Coeffs, 15, true);
}

int16_t filterValue(int16_t inputVal, uint8_t filterID) {
	noiseFilter_t *filter = &noiseFilters[filterID];

	// We can't use a filter if its been free()'d.
	// This shouldn't happen anyway but if it does this will make related bugs easier to find.
	if (!filter->destroyed) {

		// Can fill the buffer immediately to avoid the initial slow rise of the average value
		if (filter->fillBufferWithFirstValue) {
			for (uint16_t i = 0; i < filter->bufferLength; i++) {
				filter->pastValues[i] = inputVal;
			}

			filter->currentSum = filter->bufferLength * inputVal;
			filter->fillBufferWithFirstValue = false;
		}

		filter->currentSum += (inputVal - filter->pastValues[filter->currentIndex]);
		filter->pastValues[filter->currentIndex] = inputVal;
		filter->currentIndex = (filter->currentIndex + 1) % filter->bufferLength;
	}

	return filter->currentSum / filter->bufferLength;
}
