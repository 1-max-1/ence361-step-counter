/**
 * stepData.h
 *
 * for tracking all data relating to step counter including
 * steps taken, goal, goal percentage, distance travelled
 *
 * Author: Alex Pirie
 *
 */

#include "stepData.h"

#include <stdio.h>
#include <stdint.h>

//for conversions between steps and unit of distance
#define STEP_DISTANCE_KM 0.0009f
#define STEP_DISTANCE_YD 0.9843f

static uint16_t stepCount;
static distanceUnit_t distUnit;
static goalUnit_t goalUnit;
static uint16_t currentGoal;
static uint16_t tentativeGoal;

void stepDataInit() {
	stepCount = 0;
	distUnit = UNIT_KM;
	goalUnit = UNIT_PERCENT;
	currentGoal = 1000;
	tentativeGoal = 1000;
}

uint16_t getSteps() {
	return stepCount; //needed for various functions such as displaying and goal progress indication
}

void setSteps(uint16_t steps) {
	stepCount = steps;
}

void incrementSteps() {
	stepCount++; //allows steps to be incremented by various triggers
}

void setGoal(uint16_t newGoal) {
	currentGoal = newGoal;
}

uint16_t getGoal() {
	return currentGoal;
}

uint16_t getGoalPercent() {
	// Add 0.5 to round, otherwise it would only round down
	uint16_t goalPercent = 100.0f * (float)stepCount / (float)currentGoal + 0.5f;
	return goalPercent;
}

float getDistance() {
	if (distUnit == UNIT_KM) {
		return stepCount * STEP_DISTANCE_KM;
	} else {
		return stepCount * STEP_DISTANCE_YD;
	}
}

distanceUnit_t getDistanceUnit() {
	return distUnit;
}

goalUnit_t getGoalUnit () {
	return goalUnit;
}

void toggleDistanceUnit() {
	if (distUnit == UNIT_KM) {
		distUnit = UNIT_YD;
	} else {
		distUnit = UNIT_KM;
	}
}

void toggleGoalUnit() {
	if (goalUnit == UNIT_PERCENT) {
		goalUnit = UNIT_RATIO;
	} else {
		goalUnit = UNIT_PERCENT;
	}
}

void setTentativeGoal(uint16_t newTentativeGoal) {
	tentativeGoal = newTentativeGoal;
}

uint16_t getTentativeGoal() {
	return tentativeGoal;
}
