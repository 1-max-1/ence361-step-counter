/**
 * goalProgressStateLogic.c
 *
 * state logic for when in state 1, GOAL PROGRESS
 *
 * Author: Alex Pirie
 *
 */

#include <stdint.h>

#include "goalProgressStateLogic.h"
#include "joystick.h"
#include "stepData.h"
#include "stateMachine.h"

#define STATE_SWITCH_THRESHOLD 70 // percent
#define UNIT_SWITCH_THRESHOLD 70 // percent

// Use this so that the sideways joystick action from the previous state has no effect on this state.
// We will only be able to get out of this state once the user has released and re-pushed the joystick.
static bool canExitState = false;

// Set back to true when the joystick is released.
// Used to ensure the unit only changes once for each joystick movement.
static bool canChangeUnit = true;

static void checkForStateChange() {
	// Change state when user moves joystick to left or right
	uint8_t xPower = getXPower();
	if (xPower > STATE_SWITCH_THRESHOLD) {
		canExitState = false;
		if (getXDirection() == LEFT) {
			decrementState();
		} else {
			incrementState();
		}
	}
}

void goalProgressStateLogic() {
	// Don't allow state to keep changing while joystick held
	if (canExitState) {
		checkForStateChange();
	} else if (getXDirection() == RESTX) {
		canExitState = true;
	}

	// User can change unit by moving joystick up & down
	// Disable this if in test mode, as test mode requires control of the joystick up/down
	uint8_t yPower = getYPower();
	if (canChangeUnit && !isTestModeEnabled() && (yPower > UNIT_SWITCH_THRESHOLD)) {
		// Don't allow unit to keep changing more than once while joystick held
		canChangeUnit = false;
		toggleGoalUnit();
	} else if (getYDirection() == RESTY) {
		canChangeUnit = true;
	}

	// if joystick button long pressed enter state where user can change the goal
	buttonState_t s = getJoystickButtonState();
	if (s == LONG_PRESSED) {
		enterGoalChangeState();
	}
}
