/**
 * adcTask.h
 * This task handles the ADC and uses DMA to get the values.
 * Authors: Max Hosking, Alex Pirie
 */

#ifndef _ADC_TASK_H_
#define _ADC_TASK_H_

// Activate ADC, values will be read from register when available.
void adcTaskUpdate();

//Return adc value for potentiometer
uint16_t adcTaskGetRotPot();

//return adc value for joystick y-axis
uint16_t adcTaskGetJoystickY();

//return adc value for joystick x-axis
uint16_t adcTaskGetJoystickX();

#endif // _ADC_TASK_H_
