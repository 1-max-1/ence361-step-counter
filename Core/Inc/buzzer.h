#ifndef _BUZZER_H
#define _BUZZER_H

//varies volume of buzzer
typedef enum pitch {LOW = 0, HIGH} buzzerPitch_t;

//initialise buzzer
void buzzerInit();

//start buzzer either HIGH or LOW
void buzzerStart(buzzerPitch_t pitch);

//stop buzzer
void buzzerStop();

#endif
