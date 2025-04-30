/*
 * usartPrinting.c
 *
 *  Authors: Alex Pirie
 *
 *  handles displaying adc values over USART
 */
#include "usartPrinting.h"

void sendADCValToUSART(uint16_t pot, uint16_t x, uint16_t y) {
	char buf3[30];
	snprintf(buf3, 30, "Pot: %u, X: %u, Y: %u\r\n", pot, x, y);
	HAL_UART_Transmit(&huart2, (uint8_t*)buf3, strlen(buf3), 1000);
	//printf("Pot: %u, X: %u, Y: %u\r\n", x, y);
}
