/**
 * app.h
 *
 * Authors: Max Hosking, Alex Pirie
 *
 * The app module is the highest level module.
 * It initializes tasks and specifies the frequency of tasks.
 */


#include <goalProgressIndicationTask.h>
#include <stdint.h>

#include "gpio.h"

#include "joystick.h"
#include "buzzer.h"
#include "buttons.h"
#include "displayTask.h"
#include "adcTask.h"
#include "stateLogicTask.h"
#include "blinkyTask.h"
#include "usartPrintingTask.h"
#include "stepData.h"
#include "testModeStateLogic.h"
#include "stepTrackTask.h"
#include "imu_lsm6ds.h"
#include "taskScheduler.h"
#include "noiseFiltering.h"

void appSetup(void) {
	// Hardware
	joystickInit();
	buttonsInit();
	buzzerInit();
	imuInit();

	// Tasks
	displayTaskSetup();
	goalProgressIndicationInit();

	// Other modules
	stepDataInit();
	filtersInit();

	registerTask(&blinkyTaskExecute, 2);
	registerTask(&buttonsUpdate, 100);
	registerTask(&joystickUpdate, 100);
	registerTask(&displayTaskExecute, 8);
	registerTask(&adcTaskUpdate, 150);
	registerTask(&executeStateLogicTask, 100);
	//registerTask(&usartPrintingExecute, 2);
	registerTask(&goalProgressIndicationUpdate, 10);
	registerTask(&executeStepTrackTask, 100);
}

void appMain(void) {
	schedulerUpdate();
}
