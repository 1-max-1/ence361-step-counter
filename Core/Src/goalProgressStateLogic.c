/**
 * goalProgressStateLogic.c
 *
 * state logic for when in state 1, GOAL PROGRESS
 *
 * Author: Alex Pirie
 *
 */

#include <stdint.h>

#include "joystick.h"
#include "stepData.h"
#include "stateMachine.h"
#include "goalProgressStateLogic.h"

#define STATE_SWITCH_THRESHOLD 70 // percent
#define UNIT_SWITCH_THRESHOLD 70 // percent

// Use this so that the sideways joystick action from the previous state has no effect on this state.
// We will only be able to get out of this state once the user has let go of the joystick.
static bool canExitState = false;

// Set back to true when the joystick is released.
// Used to ensure the unit only changes once for each joystick movement.
static bool canChangeUnit = true;

static void checkForStateChange() {
	uint8_t xPower = getXPower();
	if (xPower > STATE_SWITCH_THRESHOLD) { // if above threshold for state change increment or decrement state based on direction
		canExitState = false;
		if (getXDirection() == LEFT) {
			decrementState();
		} else {
			incrementState();
		}
	}
}

void goalProgressStateLogic() {
	if (canExitState) {
		checkForStateChange();
	} else if (getXDirection() == RESTX) {
		canExitState = true;
	}

	// if not in test mode and above threshold for unit change toggle goal unit
	uint8_t yPower = getYPower();
	if (canChangeUnit && !isTestModeEnabled() && (yPower > UNIT_SWITCH_THRESHOLD)) {
		canChangeUnit = false;
		toggleGoalUnit();
	} else if (getYDirection() == RESTY) {
		canChangeUnit = true;
	}

	// if joystick button long pressed enter goal change state
	buttonState_t s = getJoystickButtonState();
	if (s == LONG_PRESSED) {
		enterGoalChangeState();
	}
}
