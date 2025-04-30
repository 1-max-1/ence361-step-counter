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
#include <stdio.h>

#include "joystick.h"
#include "rotPot.h"
#include "stepData.h"
#include "stateMachine.h"
#include "goalChangeStateLogic.h"

#define STATE_SWITCH_THRESHOLD 70 // percent
#define UNIT_SWITCH_THRESHOLD 70 // percent
#define GOAL_INCREMENT_PERCENT 3.4482 // percent
#define GOAL_INCREMENT_STEPS 500 // steps
#define GOAL_INCREMENT_OFFSET 500 // steps

// Will be set to true once we are allowed to exit.
// Used to ignore the first release of the button,
// as this is left over from the action used to enter the state.
static bool canExitState = false;

void goalChangeStateLogic() {
	uint8_t potPercentage = getPotPercentage();
	uint16_t tentativeGoal = (GOAL_INCREMENT_STEPS * (uint8_t)(potPercentage / GOAL_INCREMENT_PERCENT)) + GOAL_INCREMENT_OFFSET;
	setTentativeGoal(tentativeGoal);
	printf("%u\r\n", potPercentage);

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
