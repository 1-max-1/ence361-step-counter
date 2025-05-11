/*
 * rgb.c
 * Module for controlling the rgb LED's on the RCAP board.
 *
 *  Created on: Dec 5, 2024
 *      Author: fsy13
 *
 *  Modified by: Max Hosking
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "rgb.h"
#include "gpio.h"
#include "pwm.h"

// Allow timer data to be included in case we make more LED's pwm-capable in the future
typedef struct {
	GPIO_TypeDef* port;
	uint16_t pin;
	bool activeHigh;
	bool pwmEnabled;
	TIM_HandleTypeDef* tim;
	uint32_t timChannel;
} rgb_gpio_config_t;

const rgb_gpio_config_t RGB_LEDS[RGB_NUM_LEDS] = {
	[RGB_LEFT] = {
			.port = GPIOF,
			.pin = GPIO_PIN_3,
			.activeHigh = false,
			.pwmEnabled = false,
			.tim = NULL,
			.timChannel = 0
	},
	[RGB_DOWN] = {
			.port = GPIOC,
			.pin = GPIO_PIN_2,
			.activeHigh = false,
			.pwmEnabled = false,
			.tim = NULL,
			.timChannel = 0
	},
	[RGB_UP] = {
			.port = GPIOC,
			.pin = GPIO_PIN_6,
			.activeHigh = false,
			.pwmEnabled = true,
			.tim = &htim2,
			.timChannel = TIM_CHANNEL_3
	},
	[RGB_RIGHT] = {
			.port = GPIOC,
			.pin = GPIO_PIN_12,
			.activeHigh = false,
			.pwmEnabled = false,
			.tim = NULL,
			.timChannel = 0
	}
 };

const rgb_gpio_config_t RGB_COLOURS[RGB_NUM_COLOURS] = {
	[RGB_RED] = {
			.port = GPIOD,
			.pin = GPIO_PIN_3,
			.activeHigh = true,
			.pwmEnabled = false,
			.tim = NULL,
			.timChannel = 0
	},
	[RGB_GREEN] = {
			.port = GPIOD,
			.pin = GPIO_PIN_2,
			.activeHigh = true,
			.pwmEnabled = false,
			.tim = NULL,
			.timChannel = 0
	},
	[RGB_BLUE] = {
			.port = GPIOD,
			.pin = GPIO_PIN_4,
			.activeHigh = true,
			.pwmEnabled = false,
			.tim = NULL,
			.timChannel = 0
	},
 };

void rgb_led_set_state(rgb_led_t led, bool enabled) {
	if (RGB_LEDS[led].pwmEnabled) {
		rgb_led_set_brightness(led, enabled ? 100 : 0);
	} else {
		GPIO_PinState onState = RGB_LEDS[led].activeHigh ? GPIO_PIN_SET : GPIO_PIN_RESET;
		GPIO_PinState state = enabled ? onState : 1 - onState;
		HAL_GPIO_WritePin(RGB_LEDS[led].port, RGB_LEDS[led].pin, state);
	}
}

void rgb_led_set_brightness(rgb_led_t led, uint8_t brightness) {
	if (RGB_LEDS[led].pwmEnabled) {
		uint8_t duty = brightness > 100 ? 100 : brightness;
		printf("%u\r\n", duty);
		pwm_setDutyCycle(RGB_LEDS[led].tim, RGB_LEDS[led].timChannel, duty);
	}
}

void rgb_colour_set_state(rgb_colour_t colour, bool enabled) {
	if (!RGB_COLOURS[colour].pwmEnabled) {
		GPIO_PinState onState = RGB_COLOURS[colour].activeHigh ? GPIO_PIN_SET : GPIO_PIN_RESET;
		GPIO_PinState state = enabled ? onState : 1 - onState;
		HAL_GPIO_WritePin(RGB_COLOURS[colour].port, RGB_COLOURS[colour].pin, state);
	}
	// TODO: could add support for pwm-enabled colors
}

void rgb_led_toggle(rgb_led_t led) {
	if (RGB_LEDS[led].pwmEnabled) {
		uint8_t duty = pwm_getDutyCycle(RGB_LEDS[led].tim, RGB_LEDS[led].timChannel);
		rgb_led_set_brightness(led, duty == 0 ? 255 : 0);
	} else {
		HAL_GPIO_TogglePin(RGB_LEDS[led].port, RGB_LEDS[led].pin);
	}
}

void rgb_colour_toggle(rgb_colour_t colour) {
	HAL_GPIO_TogglePin(RGB_COLOURS[colour].port, RGB_COLOURS[colour].pin);
}


void rgb_led_all_on(void) {
	for (uint8_t i = 0; i < RGB_NUM_LEDS; i++) {
		rgb_led_set_state(i, true);
	}
}

void rgb_led_all_off(void) {
	for (uint8_t i = 0; i < RGB_NUM_LEDS; i++) {
		rgb_led_set_state(i, false);
	}
}

void rgb_colour_all_on(void) {
	for (uint8_t i = 0; i < RGB_NUM_COLOURS; i++) {
		rgb_colour_set_state(i, true);
	}
}

void rgb_colour_all_off(void) {
	for (uint8_t i = 0; i < RGB_NUM_COLOURS; i++) {
		rgb_colour_set_state(i, false);
	}
}
