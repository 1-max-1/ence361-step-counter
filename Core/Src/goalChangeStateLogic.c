/**
 * goalChangeStateLogic.c
 *
 * state logic for when in state 3, GOAL CHANGE
 *
 * Author: Alex Pirie
 *
 */
#include <stdint.h>
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

void goalChangeStateLogic() {
	uint8_t potPercentage = getPotPercentage();
	uint16_t tentativeGoal = (GOAL_INCREMENT_STEPS * (uint8_t)(potPercentage / GOAL_INCREMENT_PERCENT)) + GOAL_INCREMENT_OFFSET;
	setTentativeGoal(tentativeGoal);

	if (getJoystickButtonState() == LONG_PRESSED) {
		setGoal(tentativeGoal);
		exitGoalChangeState();
	} else if (getJoystickButtonState() == RELEASED) {
		exitGoalChangeState();
	}
}
