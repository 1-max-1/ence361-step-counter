/*
 * stateMachine.h
 *
 *  Created on: Apr 30, 2025
 *      Author: Max Hosking
 *
 *  The state machine keeps track of the current state and
 *  handles movement between state.
 */

#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include <stdbool.h>

// Most states exist in the main loop, and the user can cycle through them.
// There is currently one state SET_GOAl which can be accessed through button press,
// this is outside the main loop
typedef enum {
	CURRENT_STEPS = 0,
	GOAL_PROGRESS,
	DISTANCE_TRAVELLED,
	SET_GOAL
} state_t;

// Transitions to next state in the main loop.
// Does nothing if the current state is not in the main loop.
void incrementState();
// See incrementState()
void decrementState();
state_t getState();

// Enters the SET_GOAL state. No sanity checks, can be called anywhere.
void enterGoalChangeState();
// Exits SET_GOAL back into the GOAL_PROGRESS state. No sanity checks, can be called anywhere.
void exitGoalChangeState();

void setTestModeEnable(bool);
bool isTestModeEnabled();

#endif /* _STATE_MACHINE_H_ */
