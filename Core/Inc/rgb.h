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
void rgbLEDSetBrightness(rgb_led_t led, uint8_t brightness);

// Turn LED on or off
void rgbLEDSetState(rgb_led_t, bool);
// Toggles LED state
void rgbLEDToggle(rgb_led_t led);
// Turn on a specific colour for all LED's
void rgbColourSetState(rgb_colour_t, bool);
// Toggle on a specific colour for all LED's
void rgbColourToggle(rgb_colour_t colour);

// Turn all LED's on
void rgbLEDSetStateAll(bool state);
// Turn all colours on
void rgbColourSetStateAll(bool state);

#endif /* _RGB_H_ */
