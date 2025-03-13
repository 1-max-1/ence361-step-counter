#include "displayTask.h"
#include "joystickTask.h"

#include "ssd1306_conf.h"
#include "ssd1306_fonts.h"
#include "ssd1306.h"
#include "usart.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>

void displayTaskSetup() {
	ssd1306_Init();
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("Hello world!", Font_7x10, White);
}

void displayTaskExecute() {
	uint16_t x = getX();
	uint16_t y = getY();

	ssd1306_SetCursor(0, 15);
	char buf[10];
	snprintf(buf, 10, "X: %u ", x);
	ssd1306_WriteString(buf, Font_7x10, White);

	ssd1306_SetCursor(0, 30);
	char buf2[10];
	snprintf(buf2, 10, "Y: %u ", y);
	ssd1306_WriteString(buf2, Font_7x10, White);

	ssd1306_UpdateScreen();

	char buf3[21];
	snprintf(buf3, 21, "X: %u, Y: %u\r\n", x, y);
	//HAL_UART_Transmit(&huart2, (uint8_t*)buf3, strlen(buf3), 1000);
	printf("X: %u, Y: %u\r\n", x, y);
}
