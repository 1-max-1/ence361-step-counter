/**
 * joystick.c
 *
 * Authors: Max Hosking, Alex Pirie
 *
 * This task stores values from the ADC connected to the joystick
 */
#include <stdint.h>
#include <stdbool.h>
#include "joystick.h"
#include "adcTask.h"

#include "gpio.h"

#include "stm32c0xx_hal.h"

#define NUM_BUT_POLLS 3
#define BUT_POLL_HZ 100
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

static uint16_t raw_adc[2];

joystickButtonProperties_t joystickButton;

void joystickSetup() {
	joystickButton.port = GPIOB;
	joystickButton.pin = GPIO_PIN_1;
	joystickButton.normalState = GPIO_PIN_RESET;
}

void joystickExecute() {
	raw_adc[0] = getJoystickY();
	raw_adc[1] = getJoystickX();

	GPIO_PinState rawState = HAL_GPIO_ReadPin(joystickButton.port, joystickButton.pin);

	// If reading is different from last confirmed state, increment counter
    if (rawState != joystickButton.state) {
    	joystickButton.newStateCount++;
    	// If count exceeds poll count, confirm change of state
    	if (joystickButton.newStateCount >= NUM_BUT_POLLS) {
    		joystickButton.state = rawState;
    		joystickButton.hasChanged = true;	// Reset by call to buttons_checkButton()
    		joystickButton.newStateCount = 0;
    		joystickButton.heldCount = 0;
    	}
    } else if (joystickButton.state != joystickButton.normalState && joystickButton.heldCount <= BUT_POLL_HZ) {
    	joystickButton.heldCount++;
    } else if (joystickButton.heldCount > BUT_POLL_HZ) {
    	joystickButton.hasChanged = true;
    } else {
    	joystickButton.newStateCount = 0;
    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {

}

uint16_t getXRaw() {
	return raw_adc[1];
}

uint16_t getYRaw() {
	return raw_adc[0];
}

uint16_t getXPower() {
	uint16_t xPercentage = 0;

	if (raw_adc[1] >= JOYSTICK_LEFT_INNER_VAL) {
		xPercentage = (raw_adc[1] - JOYSTICK_LEFT_INNER_VAL) * 100 / (JOYSTICK_LEFT_OUTER_VAL - JOYSTICK_LEFT_INNER_VAL);
	} else if (raw_adc[1] <= JOYSTICK_RIGHT_INNER_VAL) {
		xPercentage = (JOYSTICK_RIGHT_INNER_VAL - raw_adc[1]) * 100 / (JOYSTICK_RIGHT_INNER_VAL - JOYSTICK_RIGHT_OUTER_VAL);
	}
	return xPercentage;
}

uint16_t getYPower() {
	uint16_t yPercentage = 0;

	if (raw_adc[0] >= JOYSTICK_DOWN_INNER_VAL) {
		yPercentage = (raw_adc[0] - JOYSTICK_DOWN_INNER_VAL) * 100 / (JOYSTICK_DOWN_OUTER_VAL - JOYSTICK_DOWN_INNER_VAL);
	} else if (raw_adc[0] <= JOYSTICK_UP_INNER_VAL) {
		yPercentage = (JOYSTICK_UP_INNER_VAL - raw_adc[0]) * 100 / (JOYSTICK_UP_INNER_VAL - JOYSTICK_UP_OUTER_VAL);
	}
	return yPercentage;
}

 xDirection_t getXDirection() {
	 xDirection_t xDirection = RESTX;

	if (raw_adc[1] >= JOYSTICK_LEFT_INNER_VAL) {
		xDirection = LEFT;
	} else if (raw_adc[1] <= JOYSTICK_RIGHT_INNER_VAL) {
		xDirection = RIGHT;
	}
	return xDirection;
}

 yDirection_t getYDirection() {
	 yDirection_t yDirection = RESTY;

	if (raw_adc[0] >= JOYSTICK_DOWN_INNER_VAL) {
		yDirection = DOWN;
	} else if (raw_adc[0] <= JOYSTICK_UP_INNER_VAL) {
		yDirection = UP;
	}
	return yDirection;
}

 joystickButtonState_t getJoystickButtonState() {
	 if (joystickButton.hasChanged) {
		 joystickButton.hasChanged = false;
		 if (joystickButton.state == joystickButton.normalState) {
			 return RELEASED;
		 } else if (joystickButton.heldCount > BUT_POLL_HZ) {
			 return LONG_PRESSED;
		 } else {
			 return PRESSED;
		 }
	 }
 }


