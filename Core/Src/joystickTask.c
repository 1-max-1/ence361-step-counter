#include "joystickTask.h"

#include "gpio.h"
#include "adc.h"

static uint16_t raw_adc[2];

void joystick_task_execute() {
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
