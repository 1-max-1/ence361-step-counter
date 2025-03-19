#include "buttonsTask.h"
#include "displayTask.h"
#include "buttons.h"
#include "rgb.h"
#include "pwm.h"
#include "tim.h"

void buttonsTaskSetup() {
	buttons_init();
}

void button_task_execute() {
	buttons_update();

	if (buttons_checkButton(UP) == PUSHED) {
		uint8_t duty = pwm_getDutyCycle(&htim2, TIM_CHANNEL_3);
		duty = (duty == 100 ? 0 : duty + 25);
		pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, duty);
	}

	if (buttons_checkButton(DOWN) == PUSHED) {
		rgb_led_toggle(RGB_DOWN);
		toggleUSARTPrinting();
	}

	if (buttons_checkButton(LEFT) == PUSHED)
		rgb_led_toggle(RGB_LEFT);

	if (buttons_checkButton(RIGHT) == PUSHED)
		rgb_led_toggle(RGB_RIGHT);
}
