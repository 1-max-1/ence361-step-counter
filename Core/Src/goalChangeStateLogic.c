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
#define HALF_GOAL_INCREMENT 250 // To avoid division
#define HYSTERESIS_THRESHOLD 20

// Will be set to true once we are allowed to exit.
// Used to ignore the first release of the joystick button,
// as this is left over from the previous action used to enter the state.
static bool canExitState = false;

// Calculates the new goal based on how far the user has moved the potentiometer
uint16_t calculateTentativeGoal() {
	// Raw step goal based on how far the user has turned the pot
	uint16_t steps = (getRawPotVal() - getMinPotVal()) * (MAX_GOAL - MIN_GOAL) / (getMaxPotVal() - getMinPotVal()) + MIN_GOAL;

	uint16_t tentativeGoal = getTentativeGoal();

	// Add hysteresis to prevent flicker in the value - only update goal if outside hysteresis range
	uint16_t remainder = steps % GOAL_INCREMENT;
	if (remainder < HALF_GOAL_INCREMENT - HYSTERESIS_THRESHOLD || remainder > HALF_GOAL_INCREMENT + HYSTERESIS_THRESHOLD) {
		// We add half an increment to make the rounding calculation
		// round to the closest increment, instead of always rounding down.
		steps += HALF_GOAL_INCREMENT;
		tentativeGoal = steps - (steps % GOAL_INCREMENT);
	}

	return tentativeGoal;
}

void goalChangeStateLogic() {
	// Tentative goal needed as new goal may not always be selected, allows for rollback to previous goal
	uint16_t tentativeGoal = calculateTentativeGoal();
	setTentativeGoal(tentativeGoal);

	buttonState_t buttonState = getJoystickButtonState();
	// Long press confirms the goal
	if (buttonState == LONG_PRESSED) {
		setGoal(tentativeGoal);
		canExitState = false; // Reset flag for next time we enter this state
		exitGoalChangeState();
	} else if (buttonState == RELEASED) {
		// Short press and release cancels the operation, but only leave the state if this is a new release.
		// i.e. ignore the initial release left over from when we entered this state
		if (canExitState) {
			canExitState = false;
			exitGoalChangeState();
		}
		else
			canExitState = true;
	}
}
