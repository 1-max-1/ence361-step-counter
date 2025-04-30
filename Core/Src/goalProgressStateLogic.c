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

void goalProgressStateLogic() {
	uint8_t xPower = getXPower(); // gets percentage of joystick deflection in x-axis
	uint8_t yPower = getYPower(); // gets percentage of joystick deflection in y-axis
	if (xPower > STATE_SWITCH_THRESHOLD) { // if above threshold for state change increment or decrement state based on direction
		if (getXDirection() == LEFT) {
			decrementState();
		} else {
			incrementState();
		}
	}
	if (!isTestModeEnabled() && (yPower > UNIT_SWITCH_THRESHOLD)) { // if not in test mode and above threshold for unit change toggle goal unit
		toggleGoalUnit();
	}
	if (getJoystickButtonState() == LONG_PRESSED) { // if joystick button long pressed enter goal change state
		enterGoalChangeState();
	}
}
