/**
 * joystickTask.h
 *
 * Authors: Max Hosking, Alex Pirie
 *
 * This task stores values from the ADC connected to the joystick
 */

#include "joystickTask.h"

#include "gpio.h"
#include "adc.h"

static uint16_t raw_adc[2];

void joystickTaskSetup() {
	; // No setup needed currently
}

void joystickTaskExecute() {
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 2);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {

}

uint16_t getX() {
	return raw_adc[1];
}

uint16_t getY() {
	return raw_adc[0];
}
