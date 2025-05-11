/*
 * rgb.h
 * Module for controlling the rgb LED's on the RCAP board.
 *
 *  Created on: Dec 5, 2024
 *      Author: fsy13
 *
 *  Modified by: Max Hosking
 */

#ifndef _RGB_H_
#define _RGB_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
	RGB_LEFT,
	RGB_RIGHT,
	RGB_UP,
	RGB_DOWN,
	RGB_NUM_LEDS
} rgb_led_t;


typedef enum
{
	RGB_RED,
	RGB_GREEN,
	RGB_BLUE,
	RGB_NUM_COLOURS
} rgb_colour_t;

// Set led brightness on scale from 0 to 100 (ignores values >100).
// Brightness is not gamma-corrected so will appear non linear.
// Currently only allowed with DS3, does nothing if called with other LED's.
void rgb_led_set_brightness(rgb_led_t led, uint8_t brightness);

void rgb_led_set_state(rgb_led_t, bool);
void rgb_colour_set_state(rgb_colour_t, bool);
void rgb_led_toggle(rgb_led_t led);
void rgb_colour_toggle(rgb_colour_t colour);
void rgb_led_all_on(void);
void rgb_colour_all_on(void);
void rgb_led_all_off(void);
void rgb_colour_all_off(void);

#endif /* _RGB_H_ */
