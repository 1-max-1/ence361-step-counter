/*
 * uiDisplay.c
 *
 *  Created on: Apr 29, 2025
 *      Authors: Max Hosking, Alex Pirie
 *
 *  This module handles the high level UI layout for each of the states.
 */


#include "uiDisplay.h"

#include "ssd1306_conf.h"
#include "ssd1306_fonts.h"
#include "ssd1306.h"

#include <stdint.h>
#include <stdio.h>

// Number of characters, including null-terminator.
// Change this if we use longer unit strings or more digits in the data number.
#define LONGEST_DATA_STRING 12

// All pages share same basic layout
void renderGenericLayout(char* title, uint16_t data, char* unit) {
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(title, Font_11x18, White);

	char buf[LONGEST_DATA_STRING];
	snprintf(buf, LONGEST_DATA_STRING, "%u %s", data, unit);
	ssd1306_SetCursor(0, 40);
	ssd1306_WriteString(buf, Font_11x18, White);
}

void renderGoalPage() {
	// TODO: get current steps data
	renderGenericLayout("Goal progress:", 0, "%");
}

void renderStepsTakenPage() {
	// TODO: get current steps data
	renderGenericLayout("Steps taken:", 0, "steps");
}

void renderDistanceTravelledPage() {
	char* unit = 1 ? "km" : "miles";
	// TODO: get current steps data
	renderGenericLayout("Distance traveled:", 0, unit);
}
