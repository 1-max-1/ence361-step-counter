#include "gpio.h"

#include <stdint.h>

#include "joystickTask.h"
#include "blinkyTask.h"
#include "buttonsTask.h"
#include "displayTask.h"

#define TICK_FREQUENCY_HZ 1000
#define HZ_TO_TICKS(FREQUENCY_HZ) (TICK_FREQUENCY_HZ/FREQUENCY_HZ)

#define BLINKY_TASK_PERIOD_TICKS HZ_TO_TICKS(2)
#define BUTTON_TASK_PERIOD_TICKS HZ_TO_TICKS(100)
#define JOYSTICK_TASK_PERIOD_TICKS HZ_TO_TICKS(150)
#define DISPLAY_TASK_PERIOD_TICKS HZ_TO_TICKS(4)

static uint32_t blinkyTaskNextRun = 0;
static uint32_t buttonTaskNextRun = 0;
static uint32_t joystickTaskNextRun = 0;
static uint32_t displayTaskNextRun = 0;

void app_main(void) {
	uint32_t ticks = HAL_GetTick();

	if (ticks > blinkyTaskNextRun) {
		blinky_task_execute();
		blinkyTaskNextRun += BLINKY_TASK_PERIOD_TICKS;
	}

	if (ticks > buttonTaskNextRun) {
		button_task_execute();
		buttonTaskNextRun += BUTTON_TASK_PERIOD_TICKS;
	}

	if (ticks > joystickTaskNextRun) {
		joystick_task_execute();
		joystickTaskNextRun += JOYSTICK_TASK_PERIOD_TICKS;
	}

	if (ticks > displayTaskNextRun) {
		displayTaskExecute();
		displayTaskNextRun += DISPLAY_TASK_PERIOD_TICKS;
	}
}

void app_setup(void) {
	buttonsTaskSetup();
	blinkyTaskSetup();
	displayTaskSetup();


	blinkyTaskNextRun = HAL_GetTick() + BLINKY_TASK_PERIOD_TICKS;
	buttonTaskNextRun = HAL_GetTick() + BUTTON_TASK_PERIOD_TICKS;
	displayTaskNextRun = HAL_GetTick() + DISPLAY_TASK_PERIOD_TICKS;
	joystickTaskNextRun = HAL_GetTick() + JOYSTICK_TASK_PERIOD_TICKS;
}
