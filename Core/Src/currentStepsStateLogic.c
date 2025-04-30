/**
 * currentSteps.c
 *
 * state logic for when in state 0, CURRENT STEPS
 *
 * Author: Alex Pirie
 *
 */
#include <stdint.h>
#include "joystick.h"
#include "stepData.h"
#include "stateMachine.h"

#define STATE_SWITCH_THRESHOLD 70 //percent

void currentStepsStateLogic() {
	uint8_t xPower = getXPower(); // gets percentage of joystick deflection in x-axis
	if (xPower > STATE_SWITCH_THRESHOLD) { // if above threshold for state change increment or decrement state based on direction
		if (getXDirection() == LEFT) {
			decrementState();
		} else {
			incrementState();
		}
	}
}

