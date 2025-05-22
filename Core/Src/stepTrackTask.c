/**
 * stepTrackTask.c
 *
 * This task handles step increments from SW1 and the IMU. High level.
 */

#include "stepTrackTask.h"
#include "noiseFiltering.h"
#include "imu_lsm6ds.h"
#include "buttons.h"
#include "buttonStates.h"
#include "stepData.h"
#include "stateMachine.h"
#include "stm32c0xx_hal.h"

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define SW1_STEP_INCREMENT 80
#define LINEAR_SENSITIVITY 0.061 // Converts IMU reading to mg-value

// Define 2 different sized circular buffers. The large one is used for calculating longer-term average,
// while the short buffer is used for more accurately detecting peaks by calculating short term variance.
#define BIG_BUFFER_SIZE 100
#define SMALL_BUFFER_SIZE 50
static uint32_t smallBuffer[SMALL_BUFFER_SIZE];
static uint32_t largeBuffer[BIG_BUFFER_SIZE];
static uint16_t smallBufIndex = 0;
static uint16_t largeBufIndex = 0;

#define VAR_THRESHOLD 35000000000 // Variance must be above this to turn on step detection
#define MIN_STEP_PERIOD 300 // min time between step detections (ms)
#define MIN_PEAK_DIFF 40000 // Will not detect a step if peak didn't reach at least this high above the average

// What the values were last task execution
static uint32_t lastAccelerationMagnitude = 0;
static uint64_t lastAverage = 0;
static uint32_t timeOfLastStep = 0;

// Highest value recorded since detecting a step. Resets once step is detected
static uint32_t lastPeak = 0;

// Set to true once they have been filled with first value
static bool buffersInitialized = false;

// Fills both buffers with the given magnitude. Useful for initialization
void fillBuffers(uint32_t accelerationMagnitude) {
	for (uint16_t i = 0; i < SMALL_BUFFER_SIZE; i++) {
		smallBuffer[i] = accelerationMagnitude;
	}
	for (uint16_t i = 0; i < BIG_BUFFER_SIZE; i++) {
		largeBuffer[i] = accelerationMagnitude;
	}
}

void updateBuffers(uint32_t accelerationMagnitude) {
	// To avoid a magnitude spike on boot, start buffers with all same value
	if (!buffersInitialized) {
		fillBuffers(accelerationMagnitude);
		buffersInitialized = true;
	}

	smallBuffer[smallBufIndex] = accelerationMagnitude;
	smallBufIndex++;
	if (smallBufIndex == SMALL_BUFFER_SIZE)
		smallBufIndex = 0;

	largeBuffer[largeBufIndex] = accelerationMagnitude;
	largeBufIndex++;
	if (largeBufIndex == BIG_BUFFER_SIZE)
		largeBufIndex = 0;
}

uint32_t getAccelMagnitude() {
	int16_t acc_x = getImuXAccel();
	int16_t acc_y = getImuYAccel();
	int16_t acc_z = getImuZAccel();

	// IMU quite noisy so filter x, y, & z data with moving average
	// Also convert to mg
	int16_t filteredX = filterValue(acc_x, 0) * LINEAR_SENSITIVITY;
	int16_t filteredY = filterValue(acc_y, 1) * LINEAR_SENSITIVITY;
	int16_t filteredZ = filterValue(acc_z, 2) * LINEAR_SENSITIVITY;

	return filteredX*filteredX + filteredY*filteredY + filteredZ*filteredZ;
}

// Increments steps by certain amount if SW1 is pressed
void checkSW1() {
	// Milestone spec says don't allow step increment when in set goal state
	if (getState() != SET_GOAL && buttonsCheckButton(UP_BUTTON) == PRESSED) {
		setSteps(getSteps() + SW1_STEP_INCREMENT);
	}
}

void executeStepTrackTask() {
	checkSW1();

	uint32_t accelerationMagnitude = getAccelMagnitude();
	updateBuffers(accelerationMagnitude);

	// Use big buffer to calculate long term average so it gets smoothed out
	uint64_t sum = 0;
	for (uint16_t i = 0; i < BIG_BUFFER_SIZE; i++) {
		sum += largeBuffer[i];
	}
	uint64_t currentAvg = sum / BIG_BUFFER_SIZE;

	// Use smaller buffer to calculate short term variance of peaks
	uint64_t nvar = 0;
	for (uint16_t i = 0; i < SMALL_BUFFER_SIZE; i++) {
		uint32_t diff = 0; // distance to mean value
		if (smallBuffer[i] > currentAvg)
			diff = smallBuffer[i] - currentAvg;
		else
			diff = currentAvg - smallBuffer[i];

		nvar += diff * diff;
	}

	if (accelerationMagnitude > lastPeak) { // Update current highest value
		lastPeak = accelerationMagnitude;
	}

	// Detect a step when we have peaked and are coming back down to cross the average
	bool crossedBelowAvg = accelerationMagnitude <= lastAccelerationMagnitude && accelerationMagnitude < currentAvg && lastAccelerationMagnitude >= lastAverage;
	// The peak must also be big enough, otherwise its just noise. Can look at variance and max height.
	bool sufficientPeak = nvar > VAR_THRESHOLD && lastPeak - accelerationMagnitude >= MIN_PEAK_DIFF;

	// And finally don't track steps that are too close because this will just be noise zig-zags
	uint32_t tickVal = HAL_GetTick();
	if (crossedBelowAvg && tickVal - timeOfLastStep >= MIN_STEP_PERIOD && sufficientPeak) {
		incrementSteps();
		timeOfLastStep = tickVal;
		lastPeak = 0;
	}

	lastAccelerationMagnitude = accelerationMagnitude;
	lastAverage = currentAvg;
}
