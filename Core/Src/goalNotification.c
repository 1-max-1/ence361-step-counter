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

// In milliseconds
#define NOTIFICATION_DURATION 1200

// Will clear the flag if the goal changes, so that the notification can be re-triggered again.
static void resetNotificationIfRequired() {
	if (getSteps() < getGoal())
		notificationTriggered = false;

	// TODO: (maybe) reset flag if goal is lowered but step count still surpasses it.
	// i.e. buzzer goes again if goal changes.
}

void goalNotificationUpdate() {
	resetNotificationIfRequired();

	if (!notificationTriggered && getSteps() >= getGoal()) {
		notificationTriggered = true;
		buzzer_start(HIGH);
		setHapticMotorState(true);
		timeOfBuzzerStart = HAL_GetTick();
	} else if (notificationTriggered && HAL_GetTick() - timeOfBuzzerStart >= NOTIFICATION_DURATION) {
		buzzer_stop();
		setHapticMotorState(false);
	}
}
