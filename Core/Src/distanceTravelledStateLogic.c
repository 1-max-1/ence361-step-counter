#include "distanceTravelledStateLogic.h"
#include "joystick.h"
#include "stateMachine.h"
#include "stepData.h"

#include <stdint.h>
#include <stdbool.h>

#define STATE_SWITCH_THRESHOLD 70 // Percentage
#define UNIT_SWITCH_THRESHOLD 70  // Percentage

// Use this so that the sideways joystick action from the previous state has no effect on this state.
// We will only be able to get out of this state once the user has let go of the joystick.
static bool canExitState = false;

// Set back to true when the joystick is released.
// Used to ensure the unit only changes once for each joystick movement.
static bool canChangeUnit = true;

static void checkForStateChange() {
	// Change state when user moves joystick to left or right
	if (getXPower() >= STATE_SWITCH_THRESHOLD) {
		canExitState = false;
		if (getXDirection() == LEFT)
			decrementState();
		else
			incrementState();
	}
}

void distanceTravelledStateLogic() {
	if (canExitState) {
		checkForStateChange();
	} else if (getXDirection() == RESTX) {
		canExitState = true;
	}

	// User can change unit by moving joystick up & down
	if (canChangeUnit && !isTestModeEnabled() && getYPower() >= UNIT_SWITCH_THRESHOLD) {
		canChangeUnit = false;
		toggleDistanceUnit();
	} else if (getYDirection() == RESTY) {
		canChangeUnit = true;
	}
}
