#include "gpio.h"

#include <stdint.h>

#include "joystickTask.h"
#include "blinkyTask.h"
#include "buttonsTask.h"

#define TICK_FREQUENCY_HZ 1000
#define HZ_TO_TICKS(FREQUENCY_HZ) (TICK_FREQUENCY_HZ/FREQUENCY_HZ)

#define BLINKY_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ / 2)
#define BUTTON_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ / 100)
#define JOYSTICK_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ / 150)

static uint32_t blinkyTaskNextRun = 0;
static uint32_t buttonTaskNextRun = 0;
static uint32_t joystickTaskNextRun = 0;

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
}

void app_setup(void) {
	buttonsTaskSetup();
	blinkyTaskSetup();

	blinkyTaskNextRun = HAL_GetTick() + BLINKY_TASK_PERIOD_TICKS;
	buttonTaskNextRun = HAL_GetTick() + BUTTON_TASK_PERIOD_TICKS;
}
