#ifndef _ADCTASK_H_
#define _ADCTASK_H_


//Update adc register
void adcTaskUpdate();

//Return adc value for potentiometer
uint16_t adcTask_getRotPot();

//return adc value for joystick y-axis
uint16_t adcTask_getJoystickY();

//return adc value for joystick x-axis
uint16_t adcTask_getJoystickX();

#endif
