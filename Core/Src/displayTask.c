#include "displayTask.h"
#include "joystickTask.h"

#include "ssd1306_conf.h"
#include "ssd1306_fonts.h"
#include "ssd1306.h"
#include "usart.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define JOYSTICK_LEFT_OUTER_VAL 4095
#define JOYSTICK_LEFT_INNER_VAL 2300
#define JOYSTICK_RIGHT_OUTER_VAL 133
#define JOYSTICK_RIGHT_INNER_VAL 2090
#define JOYSTICK_UP_OUTER_VAL 237
#define JOYSTICK_UP_INNER_VAL 2200
#define JOYSTICK_DOWN_OUTER_VAL 4095
#define JOYSTICK_DOWN_INNER_VAL 2400

static bool printJoystickValToUSART = false;

void toggleUSARTPrinting() {
	printJoystickValToUSART = !printJoystickValToUSART;
}

void displayTaskSetup() {
	ssd1306_Init();
	ssd1306_SetCursor(0, 0);
}

void displayADCValues(uint16_t x, uint16_t y) {
	ssd1306_SetCursor(0, 0);
	char buf[10];
	snprintf(buf, 10, "X: %u ", x);
	ssd1306_WriteString(buf, Font_7x10, White);

	ssd1306_SetCursor(0, 13);
	char buf2[10];
	snprintf(buf2, 10, "Y: %u ", y);
	ssd1306_WriteString(buf2, Font_7x10, White);
}

void displayJoystickState(uint16_t x, uint16_t y) {
	uint16_t xPercentage = 0;
	uint16_t yPercentage = 0;
	const char* xString = "Rest";
	const char* yString = "Rest";

	if (x >= JOYSTICK_LEFT_INNER_VAL) {
		xString = "Left";
		xPercentage = (x - JOYSTICK_LEFT_INNER_VAL) * 100 / (JOYSTICK_LEFT_OUTER_VAL - JOYSTICK_LEFT_INNER_VAL);
	} else if (x <= JOYSTICK_RIGHT_INNER_VAL) {
		xString = "Right";
		xPercentage = (JOYSTICK_RIGHT_INNER_VAL - x) * 100 / (JOYSTICK_RIGHT_INNER_VAL - JOYSTICK_RIGHT_OUTER_VAL);
	}

	if (y >= JOYSTICK_DOWN_INNER_VAL) {
		yString = "Down";
		yPercentage = (y - JOYSTICK_DOWN_INNER_VAL) * 100 / (JOYSTICK_DOWN_OUTER_VAL - JOYSTICK_DOWN_INNER_VAL);
	} else if (y <= JOYSTICK_UP_INNER_VAL) {
		yString = "Up";
		yPercentage = (JOYSTICK_UP_INNER_VAL - y) * 100 / (JOYSTICK_UP_INNER_VAL - JOYSTICK_UP_OUTER_VAL);
	}

	char buf1[18];
	snprintf(buf1, 18, "X: %s  %u%%   ", xString, xPercentage);
	ssd1306_SetCursor(0, 40);
	ssd1306_WriteString(buf1, Font_7x10, White);

	char buf2[18];
	snprintf(buf2, 18, "Y: %s  %u%%   ", yString, yPercentage);
	ssd1306_SetCursor(0, 53);
	ssd1306_WriteString(buf2, Font_7x10, White);
}

void sendADCValToUSART(uint16_t x, uint16_t y) {
	char buf3[21];
	snprintf(buf3, 21, "X: %u, Y: %u\r\n", x, y);
	HAL_UART_Transmit(&huart2, (uint8_t*)buf3, strlen(buf3), 1000);
	//printf("X: %u, Y: %u\r\n", x, y);
}

void displayTaskExecute() {
	uint16_t x = getX();
	uint16_t y = getY();

	displayADCValues(x, y);
	displayJoystickState(x, y);
	ssd1306_UpdateScreen();

	if (printJoystickValToUSART) {
		sendADCValToUSART(x, y);
	}
}
