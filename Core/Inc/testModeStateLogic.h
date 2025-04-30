/*
 * testModeStateLogic.h
 *
 *  Created on: Apr 30, 2025
 *      Author: Max Hosking
 *
 *  This module contains the logic for the "test mode".
 *  This is kind of like a state, it can occur at any time and can be used to manually set the number of steps.
 */

#ifndef _TEST_MODESTATELOGIC_H_
#define _TEST_MODESTATELOGIC_H_

void testModeInit();

// Checks if the user is trying to get into test mode.
// If so, test mode will be enabled. Call as a task.
void checkForTestModeTrigger();

// Run logic for test mode, call as task
void testModeStateLogic();

#endif /* _TEST_MODESTATELOGIC_H_ */
