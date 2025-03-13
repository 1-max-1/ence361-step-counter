#include "blinkyTask.h"
#include "rgb.h"
#include "gpio.h"
#include "tim.h"

void blinkyTaskSetup() {
	rgb_led_all_off();
	rgb_colour_all_on();
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
}

void blinky_task_execute() {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

}
