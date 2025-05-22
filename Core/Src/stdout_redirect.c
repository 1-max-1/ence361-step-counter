/**
 * stdout_redirect.c
 * Author: Max Hosking
 * Allows printf() to be used to transmit data over the serial connection
 */

#include "usart.h"

int __io_putchar(int ch) {
	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
	return ch;
}
