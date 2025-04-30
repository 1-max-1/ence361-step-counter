/*
 * displayTask.h
 *
 *  Authors: Alex Pirie
 *
 *  This task handles displaying the pages for each state of the step counter
 *  based on the state of the program determined in the state machine
 */

#include "displayTask.h"
#include "stateMachine.h"
#include "uiDisplay.h"
#include "ssd1306.h"

void displayTaskSetup() {
	ssd1306_Init();
}

void displayTaskExecute() {
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
