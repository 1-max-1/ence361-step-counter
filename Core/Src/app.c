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
#include "buttonControlTask.h"
#include "blinkyTask.h"
#include "displayTask.h"
#include "adcTask.h"
#include "stateLogicTask.h"

#define TICK_FREQUENCY_HZ 1000
#define HZ_TO_TICKS(FREQUENCY_HZ) (TICK_FREQUENCY_HZ/FREQUENCY_HZ)

#define BLINKY_TASK_PERIOD_TICKS HZ_TO_TICKS(2)
#define BUTTON_TASK_PERIOD_TICKS HZ_TO_TICKS(100)
#define JOYSTICK_PERIOD_TICKS HZ_TO_TICKS(100)
#define DISPLAY_TASK_PERIOD_TICKS HZ_TO_TICKS(4)
#define ADC_TASK_PERIOD_TICKS HZ_TO_TICKS(150)
#define LOGIC_TASK_PERIOD_TICKS HZ_TO_TICKS(100)

// Time (ticks) that the tasks are next scheduled for
static uint32_t blinkyTaskNextRun = 0;
static uint32_t buttonControlTaskNextRun = 0;
static uint32_t joystickNextRun = 0;
static uint32_t displayTaskNextRun = 0;
static uint32_t adcTaskNextRun = 0;
static uint32_t logicTaskNextRun = 0;

void appSetup(void) {
	buttonControlTaskSetup();
	blinkyTaskSetup();
	displayTaskSetup();
	joystickSetup();

	blinkyTaskNextRun = HAL_GetTick() + BLINKY_TASK_PERIOD_TICKS;
	buttonControlTaskNextRun = HAL_GetTick() + BUTTON_TASK_PERIOD_TICKS;
	displayTaskNextRun = HAL_GetTick() + DISPLAY_TASK_PERIOD_TICKS;
	joystickNextRun = HAL_GetTick() + JOYSTICK_PERIOD_TICKS;
	adcTaskNextRun = HAL_GetTick() + ADC_TASK_PERIOD_TICKS;
	logicTaskNextRun = HAL_GetTick() + LOGIC_TASK_PERIOD_TICKS;
}

void appMain(void) {
	uint32_t ticks = HAL_GetTick();

	if (ticks > blinkyTaskNextRun) {
		blinkyTaskExecute();
		blinkyTaskNextRun += BLINKY_TASK_PERIOD_TICKS;
	}

	if (ticks > buttonControlTaskNextRun) {
		buttonControlTaskExecute();
		buttonControlTaskNextRun += BUTTON_TASK_PERIOD_TICKS;
	}

	if (ticks > joystickNextRun) {
		joystickUpdate();
		joystickNextRun += JOYSTICK_PERIOD_TICKS;
	}

	if (ticks > displayTaskNextRun) {
		displayTaskExecute();
		displayTaskNextRun += DISPLAY_TASK_PERIOD_TICKS;
	}

	if (ticks > adcTaskNextRun) {
		adcTaskExecute();
		adcTaskNextRun += ADC_TASK_PERIOD_TICKS;
	}

	if (ticks > logicTaskNextRun) {
		executeStateLogicTask();
		logicTaskNextRun += LOGIC_TASK_PERIOD_TICKS;
	}
}
