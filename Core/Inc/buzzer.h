#ifndef _BUZZER_H
#define _BUZZER_H


typedef enum pitch {LOW = 0, HIGH} buzzerPitch_t;

void buzzer_init();

void buzzer_start(buzzerPitch_t pitch);

void buzzer_stop();

#endif
