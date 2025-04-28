/**
 * buzzer.c
 *
 * Authors: Alex Pirie
 *
 * This is a driver for the buzzer for a boolean output at 3 frequencies
 */

#include "buzzer.h"
#include "pwm.h"
#include "tim.h"

// setup buzzer pwm
void buzzer_init() {
	HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
}

// start buzzer based on selected pitch
void buzzer_start(buzzerPitch_t pitch) {
	switch(pitch) {
	case LOW:
		pwm_setDutyCycle(&htim16, TIM_CHANNEL_1, 20);
		break;
	case MED:
		pwm_setDutyCycle(&htim16, TIM_CHANNEL_1, 50);
		break;
	case HIGH:
		pwm_setDutyCycle(&htim16, TIM_CHANNEL_1, 80);
		break;
	}
}

// stop buzzer
void buzzer_stop() {
	pwm_setDutyCycle(&htim16, TIM_CHANNEL_1, 0);
}
