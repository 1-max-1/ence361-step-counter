#include "blinkyTask.h"
#include "gpio.h"

void blinkyTaskSetup() {
	;
}

void blinky_task_execute() {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
