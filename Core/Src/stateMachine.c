/*
 * stateMachine.c
 *
 *  Created on: Apr 30, 2025
 *      Author: Max Hosking
 *
 *  The state machine keeps track of the current state and
 *  handles movement between state.
 */

#include "stateMachine.h"

#include <stdbool.h>

static bool testModeEnabled = false;

static state_t currentState = CURRENT_STEPS;
#define FINAL_STATE_IN_MAIN_LOOP DISTANCE_TRAVELLED

void incrementState() {
	// This function is only valid for the states in the main state loop
	if (currentState > FINAL_STATE_IN_MAIN_LOOP)
		return;

	currentState++;
	if (currentState > FINAL_STATE_IN_MAIN_LOOP)
		currentState = 0;
}

void decrementState() {
	// This function is only valid for the states in the main state loop
	if (currentState > FINAL_STATE_IN_MAIN_LOOP)
		return;

	currentState--;
	if (currentState < 0)
		currentState = FINAL_STATE_IN_MAIN_LOOP;
}

state_t getState() {
	return currentState;
}

void enterGoalChangeState() {
	currentState = SET_GOAL;
}

void exitGoalChangeState() {
	currentState = GOAL_PROGRESS;
}

void setTestModeEnable(bool enable) {
	testModeEnabled = enable;
}

bool isTestModeEnabled() {
	return testModeEnabled;
}
