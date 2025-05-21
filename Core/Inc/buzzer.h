/**
 * buzzer.c
 *
 * Authors: Alex Pirie
 *
 * This is a driver for the buzzer for a boolean output at 2 frequencies
 */

#ifndef _BUZZER_H
#define _BUZZER_H

//varies volume of buzzer
typedef enum pitch {BUZZER_PITCH_LOW = 0, BUZZER_PITCH_HIGH} buzzerPitch_t;

//initialise buzzer
void buzzerInit();

//start buzzer either high or low pitch
void buzzerStart(buzzerPitch_t pitch);

//stop buzzer
void buzzerStop();

#endif
