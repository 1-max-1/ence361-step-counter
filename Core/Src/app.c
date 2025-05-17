/**
 * app.c
 *
 * Authors: Max Hosking, Alex Pirie
 *
 * The app module is the highest level module and handles task scheduling.
 */


#include <stdint.h>

#include "gpio.h"

#include "joystick.h"
#include "buzzer.h"
#include "buttons.h"
#include "blinkyTask.h"
#include "displayTask.h"
#include "adcTask.h"
#include "stateLogicTask.h"
#include "usartPrintingTask.h"
#include "stepData.h"
#include "testModeStateLogic.h"
#include "stepTrackTask.h"
#include "goalProgressIndication.h"
#include "imu_lsm6ds.h"
#include "taskScheduler.h"
#include "noiseFiltering.h"

void appSetup(void) {
	blinkyTaskSetup();
	joystickSetup();
	displayTaskSetup();
	stepDataSetup();
	buttons_init();
	buzzer_init();
	setupGoalProgressIndicators();
	initializeIMU();
	initializeFilters();

	registerTask(&blinkyTaskExecute, 2);
	registerTask(&buttons_update, 100);
	registerTask(&joystickUpdate, 100);
	registerTask(&displayTaskExecute, 8);
	registerTask(&adcTaskExecute, 150);
	registerTask(&executeStateLogicTask, 100);
	registerTask(&usartPrintingExecute, 2);
	registerTask(&updateGoalProgressIndicators, 10);
	registerTask(&executeStepTrackTask, 100);
}

void appMain(void) {
	schedulerUpdate();
}
