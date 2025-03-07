#include "blinkyTask.h"
#include "rgb.h"
#include "gpio.h"

void blinkyTaskSetup() {
	rgb_led_all_off();
	rgb_colour_all_on();
}

void blinky_task_execute() {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
