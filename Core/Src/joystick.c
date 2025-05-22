/**
 * joystick.c
 *
 * Authors: Max Hosking, Alex Pirie
 *
 * This is a hardware module exposing functions to interact with the joystick
 */

#include <stdint.h>
#include <stdbool.h>

#include "joystick.h"
#include "adcTask.h"
#include "buttonStates.h"

#include "gpio.h"
#include "stm32c0xx_hal.h"

//parameters needed for the specific joystick mounted to our RCAP board
#define NUM_BUT_POLLS 3
#define NUM_BUT_POLLS_LONG_PRESS 100
#define JOYSTICK_LEFT_OUTER_VAL 4045
#define JOYSTICK_LEFT_INNER_VAL 2300
#define JOYSTICK_RIGHT_OUTER_VAL 240
#define JOYSTICK_RIGHT_INNER_VAL 2090
#define JOYSTICK_UP_OUTER_VAL 315
#define JOYSTICK_UP_INNER_VAL 2200
#define JOYSTICK_DOWN_OUTER_VAL 4095
#define JOYSTICK_DOWN_INNER_VAL 2400

typedef struct
{
	// Constant config
	GPIO_TypeDef* port;
	uint16_t pin;
	GPIO_PinState normalState;

	// Runtime properties
	GPIO_PinState state;
	uint8_t newStateCount;
	bool hasChanged;
	uint8_t heldCount;
} joystickButtonProperties_t;

joystickButtonProperties_t joystickButton;

static uint16_t joystickX;
static uint16_t joystickY;

void joystickInit() {
	joystickButton.port = GPIOB;
	joystickButton.pin = GPIO_PIN_1;
	joystickButton.normalState = GPIO_PIN_RESET;
}

void joystickUpdate() {
	joystickY = adcTaskGetJoystickY();
	joystickX = adcTaskGetJoystickX();

	GPIO_PinState rawButtonState = HAL_GPIO_ReadPin(joystickButton.port, joystickButton.pin);

	// We must be in the different state for a certain number of polls to be considered "new state"
    if (rawButtonState != joystickButton.state) {
    	joystickButton.newStateCount++;
    	if (joystickButton.newStateCount >= NUM_BUT_POLLS) {
    		joystickButton.state = rawButtonState;
    		joystickButton.hasChanged = true;	// Reset flag so getJoystickButtonState() returns the new state
    		joystickButton.newStateCount = 0;
    		joystickButton.heldCount = 0;
    	}
    // Once pressed, now we can track how long its being held for
    } else if (joystickButton.state != joystickButton.normalState && joystickButton.heldCount < NUM_BUT_POLLS_LONG_PRESS) {
    	joystickButton.heldCount++;
    } else if (joystickButton.heldCount == NUM_BUT_POLLS_LONG_PRESS) { // Now entering the long_press state
    	joystickButton.hasChanged = true;
    	joystickButton.heldCount++; // Increment once more to avoid re-triggering this if statement
    } else {
    	joystickButton.newStateCount = 0;
    }
}

buttonState_t getJoystickButtonState() {
	// If we've changed since the last time this function has called, then we can return the state
	// Otherwise no change to avoid apparent "repeated presses"
	if (joystickButton.hasChanged) {
		joystickButton.hasChanged = false;
		if (joystickButton.state == joystickButton.normalState) {
			return RELEASED;
		// Holding for many polls means user is trying for a long press
		} else if (joystickButton.heldCount >= NUM_BUT_POLLS_LONG_PRESS) {
			return LONG_PRESSED;
		} else {
			return PRESSED;
		}
	}
	return NO_CHANGE;
}

/**
 * Return poewr as a range from 0-100, with zero being in the middle at rest, and 100% at either end.
 * Must consider the uinner and outer thresholds as these are not always the same for the joystick.
 */

uint16_t getXPower() {
	uint16_t xPercentage = 0;
	if (joystickX >= JOYSTICK_LEFT_INNER_VAL) {
		xPercentage = (joystickX - JOYSTICK_LEFT_INNER_VAL) * 100 / (JOYSTICK_LEFT_OUTER_VAL - JOYSTICK_LEFT_INNER_VAL);
	} else if (joystickX <= JOYSTICK_RIGHT_INNER_VAL) {
		xPercentage = (JOYSTICK_RIGHT_INNER_VAL - joystickX) * 100 / (JOYSTICK_RIGHT_INNER_VAL - JOYSTICK_RIGHT_OUTER_VAL);
	}
	return xPercentage;
}

uint16_t getYPower() {
	uint16_t yPercentage = 0;
	if (joystickY >= JOYSTICK_DOWN_INNER_VAL) {
		yPercentage = (joystickY - JOYSTICK_DOWN_INNER_VAL) * 100 / (JOYSTICK_DOWN_OUTER_VAL - JOYSTICK_DOWN_INNER_VAL);
	} else if (joystickY <= JOYSTICK_UP_INNER_VAL) {
		yPercentage = (JOYSTICK_UP_INNER_VAL - joystickY) * 100 / (JOYSTICK_UP_INNER_VAL - JOYSTICK_UP_OUTER_VAL);
	}
	return yPercentage;
}

/**
 * Directionality is just measuring if joystick is beyond threshold in each direction
 */

 xDirection_t getXDirection() {
	xDirection_t xDirection = JOYSTICK_RESTX;
	if (joystickX >= JOYSTICK_LEFT_INNER_VAL) {
		xDirection = JOYSTICK_LEFT;
	} else if (joystickX <= JOYSTICK_RIGHT_INNER_VAL) {
		xDirection = JOYSTICK_RIGHT;
	}
	return xDirection;
}

 yDirection_t getYDirection() {
	yDirection_t yDirection = JOYSTICK_RESTY;
	if (joystickY >= JOYSTICK_DOWN_INNER_VAL) {
		yDirection = JOYSTICK_DOWN;
	} else if (joystickY <= JOYSTICK_UP_INNER_VAL) {
		yDirection = JOYSTICK_UP;
	}
	return yDirection;
}
