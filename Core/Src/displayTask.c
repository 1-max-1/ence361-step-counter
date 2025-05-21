/*
 * displayTask.c
 *
 *  Authors: Alex Pirie
 *
 *  This task handles choosing the currently displayed UI page based on
 *  the state of the program determined in the state machine
 */

#include "displayTask.h"
#include "stateMachine.h"
#include "uiDisplay.h"

void displayTaskSetup() {
	initUIDisplay();
}

void displayTaskExecute() {
	// Will enable or disable "test mode active" on screen, helpful for testers
	showTestModeMessage(isTestModeEnabled());

	// Actual UI rendering is done elsewhere to decouple the display code from the desicion code
	state_t currentState = getState();
	if (currentState == CURRENT_STEPS) {
		renderStepsTakenPage();
	} else if (currentState == GOAL_PROGRESS) {
		renderGoalPage();
	} else if (currentState == DISTANCE_TRAVELLED) {
		renderDistanceTravelledPage();
	} else {
		renderGoalChangePage();
	}
}
