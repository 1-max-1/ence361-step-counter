/*
 * testModeStateLogic.h
 *
 *  Created on: Apr 30, 2025
 *      Author: Max Hosking
 *
 *  This module contains the logic for the "test mode".
 *  This is kind of like a state, it can occur at any time and can be used to manually set the number of steps.
 */

#include "testModeStateLogic.h"
#include "buttons.h"
#include "stateMachine.h"
#include "joystick.h"
#include "stepData.h"
#include "rgb.h"

#include "stm32c0xx_hal.h"

#include <stdint.h>
#include <stdbool.h>

// Max time in ms between double tap of SW2, to trigger test mode
#define TEST_MODE_TRIGGER_TIMEOUT 500

// As a fraction of the current goal
#define INCREMENT_SPEED_SCALER 450

/**
 * The user must press SW2 twice in quick succession to trigger test mode.
 * As they press it for the first time, this variable will store the current time.
 * This allows to check how long it's been if they press it again.
 */
uint32_t startTimeOfTriggerAttempt = 0;

// True if the user has pressed button once and we still haven't timed out
bool waitingForSecondPress = false;

void testModeInit() {
	rgb_colour_on(RGB_BLUE);
}

void checkForTestModeTrigger() {
	if (buttons_checkButton(DOWN_BUTTON) == PRESSED) {
		if (waitingForSecondPress) {
			toggleTestMode();
			rgb_led_toggle(RGB_DOWN);
		}
		else {
			startTimeOfTriggerAttempt = HAL_GetTick();
			waitingForSecondPress = true;
		}
	}

	// Can only wait so long before new presses are no longer considered the "second press"
	if (waitingForSecondPress && HAL_GetTick() - startTimeOfTriggerAttempt >= TEST_MODE_TRIGGER_TIMEOUT) {
		waitingForSecondPress = false;
	}
}

void testModeStateLogic() {
	// Only increment step if the joystick is not at rest
	yDirection_t yDirection = getYDirection();
	if (yDirection != RESTY) {

		// The step increment changes based on how much we are pushing the joystick by
		uint16_t currentGoal = getGoal();
		int16_t fullIncrement = currentGoal / INCREMENT_SPEED_SCALER;
		// Dont let increment go below 2, otherwise the scaled increment
		// can get truncated to 0 if the joystick is not forced hard
		if (fullIncrement < 2)
			fullIncrement = 2;

		int16_t scaledIncrement = fullIncrement * getYPower() / 100;
		if (yDirection == DOWN)
			scaledIncrement *= -1;

		// In test mode we cannot go past the goal (as per spec M2.3)
		int16_t newStepCount = getSteps() + scaledIncrement;
		if (newStepCount < 0)
			newStepCount = 0;
		else if (newStepCount > currentGoal)
			newStepCount = currentGoal;

		setSteps(newStepCount);
	}
}
