/*
 * pwm.h
 *
 * Allows modification of PWM duty cycles
 *
 *  Created on: Dec 18, 2024
 *      Author: fsy13
 */

#ifndef _PWM_H_
#define _PWM_H_

#include <stdint.h>
#include "tim.h"

void pwm_setDutyCycle(TIM_HandleTypeDef* tim, uint32_t tim_channel, uint8_t duty);
uint8_t pwm_getDutyCycle(TIM_HandleTypeDef* tim, uint32_t tim_channel);

#endif /* _PWM_H_ */
