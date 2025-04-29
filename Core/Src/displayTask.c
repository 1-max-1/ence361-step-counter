/*
 * displayTask.h
 *
 *  Authors: Max Hosking, Alex Pirie
 *
 *  This task handles displaying the joystick values on the LCD screen,
 *  and also displaying them on the computer by printing over serial.
 */

#include "displayTask.h"
#include "joystick.h"

#include "ssd1306_conf.h"
#include "ssd1306_fonts.h"
#include "ssd1306.h"
#include "usart.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

// Maximum and minimum values for joystick positions
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

// Show raw ADC values on screen for x and y axes
void displayADCValues(uint16_t x, uint16_t y) {
	char buf[10];
	snprintf(buf, 10, "X: %u ", x);
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(buf, Font_7x10, White);

	char buf2[10];
	snprintf(buf2, 10, "Y: %u ", y);
	ssd1306_SetCursor(0, 13);
	ssd1306_WriteString(buf2, Font_7x10, White);
}

// Show joystick direction and percentage on screen, for x and y axes
void displayJoystickState(xDirection_t xDirection, uint16_t xPercentage, yDirection_t yDirection, uint16_t yPercentage) {
	const char* xString;
	const char* yString;

	if (xDirection == LEFT) {
		xString = "Left";
	} else if (xDirection == RIGHT) {
		xString = "Right";
	} else {
		xString = "Rest";
	}

	if (yDirection == UP) {
		yString = "Up";
	} else if (yDirection == DOWN) {
		yString = "Down";
	} else {
		yString = "Rest";
	}

	char buf1[19];
	snprintf(buf1, 19, "X: %s  %u%%   ", xString, xPercentage);
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
	uint16_t xRaw = getXRaw();
	uint16_t yRaw = getYRaw();
	xDirection_t xDir = getXDirection();
	yDirection_t yDir = getYDirection();
	uint16_t xPower = getXPower();
	uint16_t yPower = getYPower();

	displayADCValues(xRaw, yRaw);
	displayJoystickState(xDir, xPower, yDir, yPower);
	ssd1306_UpdateScreen();

	if (printJoystickValToUSART) {
		sendADCValToUSART(xRaw, yRaw);
	}
}
