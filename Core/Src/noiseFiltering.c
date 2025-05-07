#include <noiseFiltering.h>
#include <stdint.h>

typedef struct {
	int16_t pastValues[30];
	int16_t tapValues[30];
	uint8_t currentIndex;
	uint8_t bufferLength;
	int16_t currentAverage;
} noiseFiltering_t;

static noiseFiltering_t noiseFilters[3] = {
	 {
		.pastValues = {0},
		.tapValues = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		.currentIndex = 0,
		.bufferLength = 30,
		.currentAverage = 0
	 },

	 {
		.pastValues = {0},
		.tapValues = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		.currentIndex = 0,
		.bufferLength = 30,
		.currentAverage = 0
	 },

	 {
		.pastValues = {0},
		.tapValues = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		.currentIndex = 0,
		.bufferLength = 30,
		.currentAverage = 0
	 }
};

int16_t filterValue(int16_t processValue, uint8_t filterID) {
	noiseFiltering_t *filter = &noiseFilters[filterID];
	filter->currentAverage += (processValue - filter->pastValues[filter->currentIndex]) / filter->bufferLength;
	filter->pastValues[filter->currentIndex] = processValue;
	filter->currentIndex = (filter->currentIndex + 1) % filter->bufferLength;
	return filter->currentAverage;
}
