/*
 * goalNotification.c
 *
 *  Created on: May 1, 2025
 *      Author: Max Hosking
 *
 *  This module tracks when the goal is reached and when to notify the user (with buzzer)
 */

#include "goalNotification.h"

#include "stm32c0xx_hal.h"
#include "stepData.h"
#include "buzzer.h"
#include "hapticFeedback.h"

#include <stdbool.h>
#include <stdint.h>

static bool notificationTriggered = false;
static uint32_t timeOfBuzzerStart = 0; // Ticks (ms) when buzzer is first triggered
static bool buzzerOn = false;

// In milliseconds
#define NOTIFICATION_DURATION 800

// Will clear the flag if the goal changes, so that the notification can be re-triggered again.
static void resetNotificationIfRequired() {
	if (getSteps() < getGoal())
		notificationTriggered = false;
}

void goalNotificationUpdate() {
	resetNotificationIfRequired();

	if (!notificationTriggered && getSteps() >= getGoal()) {
		notificationTriggered = true;
		buzzerOn = true;
		buzzer_start(HIGH);
		setHapticMotorState(true);
		timeOfBuzzerStart = HAL_GetTick();
	} else if (buzzerOn && HAL_GetTick() - timeOfBuzzerStart >= NOTIFICATION_DURATION) {
		buzzerOn = false;
		buzzer_stop();
		setHapticMotorState(false);
	}
}
