/**
 * stepTrackTask.h
 *
 * This task handles step increments from SW1 and the IMU. High level.
 */

#include "stepTrackTask.h"

#include "buttons.h"
#include "buttonStates.h"
#include "stepData.h"

#define SW1_STEP_INCREMENT 80

void executeStepTrackTask() {
	if (buttons_checkButton(UP_BUTTON) == PRESSED) {
		setSteps(getSteps() + SW1_STEP_INCREMENT);
	}
}
