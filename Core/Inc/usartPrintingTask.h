/*
 * usartPrinting.h
 *
 *  Authors: Alex Pirie, Max Hosking
 *
 *	Module for debugging only.
 *  Handles displaying values over USART
 */

#ifndef _USART_PRINTING_H_
#define _USART_PRINTING_H_

// Enables or disables the printing of values
void toggleUsartPrinting();
// Runs the task
void usartPrintingExecute();

#endif // _USART_PRINTING_H_
