/**
 * buttonControlTask.c
 *
 * Authors: Max Hosking, Alex Pirie
 *
 * This task allows control of the white LED's through button presses
 * Also can toggle ADC value printing
 */

#include "buttonControlTask.h"
#include "displayTask.h"

#include "buttons.h"
#include "rgb.h"
#include "tim.h"
#include "pwm.h"
#include "usartPrintingTask.h"


#define DUTY_CYCLE_INCREMENT 10


// Increment pwm duty cycle for the DS3 led
void incrementDS3PWM() {
	uint8_t duty = pwm_getDutyCycle(&htim2, TIM_CHANNEL_3);
	duty = (duty == 100 ? 0 : duty + DUTY_CYCLE_INCREMENT);
	pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, duty);
}

void buttonControlTaskSetup() {
	buttons_init();
	rgb_led_all_off();
	rgb_colour_all_on(); // White
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
}

void buttonControlTaskExecute() {

	buttons_update();

	if (buttons_checkButton(UP_BUTTON) == PRESSED) {
		incrementDS3PWM();
	}

	if (buttons_checkButton(DOWN_BUTTON) == PRESSED) {
		rgb_led_toggle(RGB_DOWN);
		toggleUsartPrinting();
	}

	if (buttons_checkButton(LEFT_BUTTON) == PRESSED) {
		rgb_led_toggle(RGB_LEFT);
	}

	if (buttons_checkButton(RIGHT_BUTTON) == PRESSED) {
		rgb_led_toggle(RGB_RIGHT);
	}
}
