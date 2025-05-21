/*
 * goalNotification.c
 *
 *  Created on: May 1, 2025
 *      Author: Max Hosking
 *
 *  This task tracks goal progression, and uses LED's and buzzers to inform the user.
 */

#include "goalProgressIndication.h"
#include "stm32c0xx_hal.h"
#include "stepData.h"
#include "buzzer.h"
#include "hapticFeedback.h"
#include "rgb.h"

#include <stdbool.h>
#include <stdint.h>

static bool notificationTriggered = false;
static uint32_t timeOfBuzzerStart = 0; // Ticks (ms) when buzzer is first triggered
static bool buzzerOn = false;

// In milliseconds
#define NOTIFICATION_DURATION 800

void setupGoalProgressIndicators() {
	rgb_led_all_off();
	rgb_colour_all_on();
}

// Will clear the flag if the goal changes, so that the notification can be re-triggered
static void resetNotificationIfRequired() {
	if (getSteps() < getGoal())
		notificationTriggered = false;
}

static void updateBuzzerNotification() {
	if (!notificationTriggered && getSteps() >= getGoal()) {
		notificationTriggered = true;
		buzzerOn = true;
		buzzerStart(HIGH);
		setHapticMotorState(true);
		timeOfBuzzerStart = HAL_GetTick();
	} else if (buzzerOn && HAL_GetTick() - timeOfBuzzerStart >= NOTIFICATION_DURATION) {
		buzzerOn = false;
		buzzerStop();
		setHapticMotorState(false);
	}
}

static void updateLEDs() {
	uint16_t goalProgress = 100 * getSteps() / getGoal();
	if (goalProgress > 100) goalProgress = 100;

	uint16_t ds3Brightness = 100 * goalProgress / 25;
	if (ds3Brightness > 100) ds3Brightness = 100;
	rgb_led_set_brightness(RGB_UP, ds3Brightness);

	rgb_led_set_state(RGB_RIGHT, goalProgress >= 50);
	rgb_led_set_state(RGB_DOWN, goalProgress >= 75);
	rgb_led_set_state(RGB_LEFT, goalProgress == 100);
}

void updateGoalProgressIndicators() {
	resetNotificationIfRequired();
	updateBuzzerNotification();
	updateLEDs();
}
