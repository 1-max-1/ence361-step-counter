/*
 * usartPrinting.h
 *
 *  Authors: Alex Pirie
 *
 *  handles displaying adc values over USART
 */

#ifndef _USART_PRINTING_H_
#define _USART_PRINTING_H_

void sendADCValToUSART(uint16_t pot, uint16_t x, uint16_t y);

#endif
