/*
 * usartPrinting.h
 *
 *  Authors: Alex Pirie, Max Hosking
 *
 *	Module for debugging only.
 *  Handles displaying values over USART
 */

#include "usartPrintingTask.h"
#include "usart.h"
#include "adcTask.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "stateMachine.h"

static bool printToUART = false;

void toggleUsartPrinting() {
	printToUART = !printToUART;
}

void usartPrintingExecute() {
	/*if (printUART) {
		char buf3[35];
		snprintf(buf3, 35, "Pot: %u, X: %u, Y: %u\r\n", adcTask_getRotPot(), adcTask_getJoystickX(), adcTask_getJoystickY());
		HAL_UART_Transmit(&huart2, (uint8_t*)buf3, strlen(buf3), 1000);
		//printf("Pot: %u, X: %u, Y: %u\r\n", x, y);
	}*/

	//printf("State: %d, Test: %d\r\n", getState(), isTestModeEnabled());
}
