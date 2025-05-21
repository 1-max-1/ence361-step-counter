/**
 * stepTrackTask.h
 *
 * This task handles step increments from SW1 and the IMU. High level.
 */

#include "noiseFiltering.h"
#include "imu_lsm6ds.h"
#include "stepTrackTask.h"
#include "buttons.h"
#include "buttonStates.h"
#include "stepData.h"
#include "stateMachine.h"
#include "buzzer.h"
#include "stm32c0xx_hal.h"

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define SW1_STEP_INCREMENT 80
#define LINEAR_SENSITIVITY 0.061
#define STEP_THRESHOLD 1080000

static bool stepDetected;

#define AVG_N 100
#define VAR_THRESHOLD 35000000000
#define VAR_N 50
#define MIN_STEP_PERIOD 300 // min time between step detections (ms)
#define MIN_PEAK_DIFF 40000

static uint32_t mags[VAR_N];
static uint16_t curIndex = 0;
static uint32_t mags2[AVG_N];
static uint16_t curIndex2 = 0;
static uint64_t sum = 0;
static uint32_t pastAccelerationMagnitude = 0;
static uint64_t pastAverage = 0;
static uint32_t timeOfLastStep = 0;
static uint32_t lastPeak = 0;

static bool inited = false;

void initStepTrack(uint32_t accelerationMagnitude) {
	/*int16_t acc_x = getImuXAccel();
	int16_t acc_y = getImuYAccel();
	int16_t acc_z = getImuZAccel();
	uint32_t accelerationMagnitude = acc_x*acc_x + acc_y*acc_y + acc_z*acc_z;*/

	//printf("INIT  %lu\r\n", accelerationMagnitude);
	for (uint16_t i = 0; i < VAR_N; i++) {
		mags[i] = accelerationMagnitude;
	}
	for (uint16_t i = 0; i < AVG_N; i++) {
		mags2[i] = accelerationMagnitude;
	}
}

void steps(uint32_t accelerationMagnitude) {
	if (!inited) {
		initStepTrack(accelerationMagnitude);
		inited = true;
	}

	//sum += accelerationMagnitude - mags[curIndex];
	mags[curIndex] = accelerationMagnitude;
	curIndex++;
	if (curIndex == VAR_N)
		curIndex = 0;

	mags2[curIndex2] = accelerationMagnitude;
	curIndex2++;
	if (curIndex2 == AVG_N)
		curIndex2 = 0;

	uint64_t bigSum = 0;
	for (uint16_t i = 0; i < AVG_N; i++) {
		bigSum += mags2[i];
	}
	uint64_t bigAvg = bigSum / AVG_N;

	sum = 0;
	for (uint16_t i = 0; i < VAR_N; i++) {
		sum += mags[i];
	}
	uint64_t nvar = 0;
	uint64_t avg = sum / VAR_N;
	for (uint16_t i = 0; i < VAR_N; i++) {
		uint32_t diff = 0;
		if (mags[i] > bigAvg)
			diff = mags[i] - bigAvg;
		else
			diff = bigAvg - mags[i];

		uint64_t squared = diff * diff;
		nvar += squared;
	}

	uint32_t tickVal = HAL_GetTick();
	printf("%lu,%llu,%llu,%lu\r\n", accelerationMagnitude, bigAvg, nvar, tickVal);

	if (accelerationMagnitude < bigAvg && pastAccelerationMagnitude >= pastAverage) {
		printf("CROSSING,%lu,%llu\r\n", tickVal, nvar);
	}

	if (accelerationMagnitude > lastPeak) {
		lastPeak = accelerationMagnitude;
	}

	if (accelerationMagnitude <= pastAccelerationMagnitude && accelerationMagnitude < bigAvg && pastAccelerationMagnitude >= pastAverage && nvar > VAR_THRESHOLD && tickVal - timeOfLastStep >= MIN_STEP_PERIOD && lastPeak - accelerationMagnitude >= MIN_PEAK_DIFF) {
		incrementSteps();
		timeOfLastStep = tickVal;
		lastPeak = 0;
		printf("STEP,%lu\r\n", tickVal);
	}

	pastAccelerationMagnitude = accelerationMagnitude;
	pastAverage = bigAvg;
}

void executeStepTrackTask() {
	int16_t acc_x = getImuXAccel();
	int16_t acc_y = getImuYAccel();
	int16_t acc_z = getImuZAccel();

	// Filter x, y, & z data and multiply by linear sensitivity to convert each into mg
	int16_t filteredX = filterValue(acc_x, 0) * LINEAR_SENSITIVITY;
	int16_t filteredY = filterValue(acc_y, 1) * LINEAR_SENSITIVITY;
	int16_t filteredZ = filterValue(acc_z, 2) * LINEAR_SENSITIVITY;

	uint32_t accelerationMagnitude = filteredX*filteredX + filteredY*filteredY + filteredZ*filteredZ;

	// Milestone spec says dont allow step increment when in set goal state
	if (getState() != SET_GOAL && buttonsCheckButton(UP_BUTTON) == PRESSED) {
		setSteps(getSteps() + SW1_STEP_INCREMENT);
	}

	/*if ((accelerationMagnitude > STEP_THRESHOLD) && !stepDetected) {
		incrementSteps();
		stepDetected = true;
	} else if ((accelerationMagnitude < STEP_THRESHOLD) && stepDetected) {
		stepDetected = false;
	}*/

	steps(accelerationMagnitude);

	/*if (isStep())
		buzzerStart(HIGH);
	else
		buzzerStop();*/
}

