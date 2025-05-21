/*
 * goalProgressIndicationTask.c
 *
 *  Created on: May 1, 2025
 *      Author: Max Hosking
 *
 *  This task tracks goal progression, and uses LED's and buzzers to inform the user of the progress.
 */

#include "goalProgressIndicationTask.h"
#include "stm32c0xx_hal.h"
#include "stepData.h"
#include "buzzer.h"
#include "hapticFeedback.h"
#include "rgb.h"

#include <stdbool.h>
#include <stdint.h>

// Will ensure buzzer only goes once when we first reach the goal
static bool goalSurpassed = false;
static uint32_t timeOfBuzzerStart = 0; // Ticks (ms) when buzzer is first triggered
static bool buzzerOn = false;

// Buzz duration in milliseconds
#define NOTIFICATION_DURATION 800

void goalProgressIndicationInit() {
	rgb_led_all_off();
	rgb_colour_all_on(); // White
}

// Will clear the flag if the goal changes, so that the notification can be re-triggered
static void resetNotificationIfRequired() {
	if (getSteps() < getGoal())
		goalSurpassed = false;
}

// If the goal is reached then we cant start the notification for a certain duration.
// Turn off buzzer after this duration has passed.
// The notification could be re-triggered if step count was to decrease and increase again.
static void updateBuzzerNotification() {
	if (!goalSurpassed && getSteps() >= getGoal()) {
		goalSurpassed = true;
		buzzerOn = true;
		buzzerStart(BUZZER_PITCH_HIGH);
		setHapticMotorState(true);
		timeOfBuzzerStart = HAL_GetTick();
	} else if (buzzerOn && HAL_GetTick() - timeOfBuzzerStart >= NOTIFICATION_DURATION) {
		buzzerOn = false;
		buzzerStop();
		setHapticMotorState(false);
	}
}

// Light up to 4 LED's depending on goal progress
static void updateLEDs() {
	uint16_t goalProgress = 100 * getSteps() / getGoal();
	uint16_t ds3Brightness = 100 * goalProgress / 25;
	if (ds3Brightness > 100) ds3Brightness = 100; // Clamp to 100% because PWM only goes to 100% duty cycle
	rgb_led_set_brightness(RGB_UP, ds3Brightness);

	rgb_led_set_state(RGB_RIGHT, goalProgress >= 50);
	rgb_led_set_state(RGB_DOWN, goalProgress >= 75);
	rgb_led_set_state(RGB_LEFT, goalProgress >= 100);
}

void goalProgressIndicationUpdate() {
	resetNotificationIfRequired();
	updateBuzzerNotification();
	updateLEDs();
}
