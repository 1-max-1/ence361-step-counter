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

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define SW1_STEP_INCREMENT 80
#define LINEAR_SENSITIVITY 0.061
#define STEP_THRESHOLD 1100000

static bool stepDetected;

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
	if (getState() != SET_GOAL && buttons_checkButton(UP_BUTTON) == PRESSED) {
		setSteps(getSteps() + SW1_STEP_INCREMENT);
	}

	if ((accelerationMagnitude > STEP_THRESHOLD) && !stepDetected) {
		incrementSteps();
		stepDetected = true;
	}

	if ((accelerationMagnitude < STEP_THRESHOLD) && stepDetected) {
		stepDetected = false;
	}
}

