/**
 * goalChangeStateLogic.c
 *
 * state logic for when in state 3, GOAL CHANGE
 *
 * Author: Alex Pirie
 *
 */

#include <stdint.h>
#include <stdbool.h>

#include "joystick.h"
#include "rotPot.h"
#include "stepData.h"
#include "stateMachine.h"
#include "goalChangeStateLogic.h"

// Percentage
#define STATE_SWITCH_THRESHOLD 70
#define UNIT_SWITCH_THRESHOLD 70

// Number of steps
#define MIN_GOAL 500
#define MAX_GOAL 15000
#define GOAL_INCREMENT 500
#define HALF_GOAL_INCREMENT 250
#define HYSTERESIS_THRESHOLD 20

// Will be set to true once we are allowed to exit.
// Used to ignore the first release of the button,
// as this is left over from the action used to enter the state.
static bool canExitState = false;

uint16_t calculateTentativeGoal() {
	// Raw step goal based on how far the user has turned the pot
	uint16_t steps = (getRawPotVal() - getMinPotVal()) * (MAX_GOAL - MIN_GOAL) / (getMaxPotVal() - getMinPotVal()) + MIN_GOAL;

	uint16_t tentativeGoal = getTentativeGoal();

	// Add hysteresis to prevent flicker in the value - only update goal if outside hysteresis range
	uint16_t remainder = steps % GOAL_INCREMENT;
	if (remainder < HALF_GOAL_INCREMENT - HYSTERESIS_THRESHOLD || remainder > HALF_GOAL_INCREMENT + HYSTERESIS_THRESHOLD) {
		// We add half an increment to make the rounding calculation
		// round to the closest increment, instead of always down.
		steps += HALF_GOAL_INCREMENT;
		tentativeGoal = steps - (steps % GOAL_INCREMENT);
	}

	return tentativeGoal;
}

void goalChangeStateLogic() {
	uint16_t tentativeGoal = calculateTentativeGoal();
	setTentativeGoal(tentativeGoal);

	buttonState_t buttonState = getJoystickButtonState();
	if (buttonState == LONG_PRESSED) {
		setGoal(tentativeGoal);
		canExitState = false;
		exitGoalChangeState();
	} else if (buttonState == RELEASED) {
		if (canExitState) {
			canExitState = false;
			exitGoalChangeState();
		}
		else
			canExitState = true;
	}
}
