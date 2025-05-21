/**
 * buzzer.c
 *
 * Authors: Alex Pirie
 *
 * This is a driver for the buzzer for a boolean output at 2 frequencies
 */

#include "buzzer.h"
#include "pwm.h"
#include "tim.h"

// setup buzzer pwm
void buzzerInit() {
	HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1); // buzzer works with a supplied pwm frequency
}

// start buzzer based on selected pitch
void buzzerStart(buzzerPitch_t pitch) {
	switch(pitch) {
	case BUZZER_PITCH_LOW: // volume of buzzer is adjusted via duty cycle
		pwm_setDutyCycle(&htim16, TIM_CHANNEL_1, 20);
		break;
	case BUZZER_PITCH_HIGH:
		pwm_setDutyCycle(&htim16, TIM_CHANNEL_1, 50);
		break;
	}
}

// stop buzzer
void buzzerStop() {
	pwm_setDutyCycle(&htim16, TIM_CHANNEL_1, 0);
}
