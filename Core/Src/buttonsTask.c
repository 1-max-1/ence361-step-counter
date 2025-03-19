#include "buttonsTask.h"
#include "displayTask.h"

#include "buttons.h"
#include "rgb.h"
#include "tim.h"
#include "pwm.h"

void incrementDS3PWM() {
	uint8_t duty = pwm_getDutyCycle(&htim2, TIM_CHANNEL_3);
	duty = (duty == 100 ? 0 : duty + 10);
	pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, duty);
}

void buttonsTaskSetup() {
	buttons_init();
	rgb_led_all_off();
	rgb_colour_all_on();
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
}

void button_task_execute() {
	buttons_update();

	if (buttons_checkButton(UP) == PUSHED) {
		incrementDS3PWM();
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
