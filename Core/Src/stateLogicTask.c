/*
 * stateLogicTask.c
 *
 *  Created on: Apr 30, 2025
 *      Author: Max Hosking
 *
 *  This task will decide which logic function to run depending on which state we are in.
 */

#include "stateLogicTask.h"

#include "stateMachine.h"

// All the logic functions for each state
#include "currentStepsStateLogic.h"
#include "distanceTravelledStateLogic.h"
#include "goalChangeStateLogic.h"
#include "goalProgressStateLogic.h"
#include "testModeStateLogic.h"

#include <stdint.h>

void (*logicFunctions[])() = {
	&currentStepsStateLogic,
	&goalProgressStateLogic,
	&distanceTravelledStateLogic,
	&goalChangeStateLogic
};

void executeStateLogicTask() {
	logicFunctions[(uint8_t)getState()]();

	checkForTestModeTrigger();

	if (isTestModeEnabled())
		testModeStateLogic();
}
