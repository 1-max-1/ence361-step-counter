/**
 * currentStepsStateLogic.c
 *
 * state logic for when in state 0, CURRENT STEPS
 *
 * Author: Alex Pirie
 *
 */

#include "currentStepsStateLogic.h"
#include "joystick.h"
#include "stepData.h"
#include "stateMachine.h"

#include <stdbool.h>
#include <stdint.h>

#define STATE_SWITCH_THRESHOLD 70 // percent

// Use this so that the sideways joystick action from the previous state has no effect on this state.
// We will only be able to get out of this state once the user has released and re-pushed the joystick.
static bool canExitState = false;

static void checkForStateChange() {
	uint8_t xPower = getXPower(); // gets percentage of joystick deflection in x-axis
	if (xPower > STATE_SWITCH_THRESHOLD) { // if above threshold for state change increment or decrement state based on direction
		canExitState = false;
		if (getXDirection() == JOYSTICK_LEFT) {
			decrementState();
		} else {
			incrementState();
		}
	}
}

void currentStepsStateLogic() {
	// Don't allow state to keep changing while joystick held
	if (canExitState) {
		checkForStateChange();
	} else if (getXDirection() == JOYSTICK_RESTX) {
		canExitState = true;
	}
}

