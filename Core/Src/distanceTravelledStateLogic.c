#include "distanceTravelledStateLogic.h"
#include "joystick.h"
#include "stateMachine.h"
#include "stepData.h"

#include <stdint.h>

#define STATE_SWITCH_THRESHOLD 70 // Percentage
#define UNIT_SWITCH_THRESHOLD 70  // Percentage

void distanceTravelledStateLogic() {
	// Change state when user moves joystick to left or right
	if (getXPower() >= STATE_SWITCH_THRESHOLD) {
		if (getXDirection() == LEFT)
			decrementState();
		else
			incrementState();
	}

	// User can change unit by moving joystick up & down
	if (isTestModeEnabled() && getYPower() >= UNIT_SWITCH_THRESHOLD) {
		toggleDistanceUnit();
	}
}
