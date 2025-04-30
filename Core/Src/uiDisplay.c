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
#include "stepData.h"

#include <stdint.h>
#include <stdio.h>

// Number of characters, including null-terminator.
// Change this if we use longer unit strings or more digits in the data number.
#define LONGEST_DATA_STRING 12

// All pages share same basic layout
void renderGenericLayout(char* title, uint16_t data, char* unit) {
	ssd1306_Fill(Black);
	ssd1306_SetCursor(0, 10);
	ssd1306_WriteString(title, Font_7x10, White);

	char buf[LONGEST_DATA_STRING];
	snprintf(buf, LONGEST_DATA_STRING, "%u %s", data, unit);
	ssd1306_SetCursor(0, 25);
	ssd1306_WriteString(buf, Font_7x10, White);
	ssd1306_UpdateScreen();
}

void renderGoalPage() {
	if (getGoalUnit() == PERCENT) {
		renderGenericLayout("Goal progress:", getGoalPercent(), "%");
	} else {
		char ratioBuf[LONGEST_DATA_STRING];
		snprintf(ratioBuf, LONGEST_DATA_STRING, "/%u", getGoal());
		renderGenericLayout("Goal progress:", getSteps() , ratioBuf);
	}
}

void renderStepsTakenPage() {
	renderGenericLayout("Steps taken:", getSteps(), "steps");
}

void renderDistanceTravelledPage() {
	if (getDistanceUnit() == KM) {
		renderGenericLayout("Distance traveled:", getDistance(), "km");
	} else {
		renderGenericLayout("Distance traveled:", getDistance(), "yards");
	}
}

void renderGoalChangePage() {
	renderGenericLayout("New goal:", getTentativeGoal(), "steps");
}
