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
#define LONGEST_DATA_STRING 15

// All pages share same basic layout
void renderGenericLayout(char* title, char* dataString) {
	ssd1306_Fill(Black);
	ssd1306_SetCursor(0, 10);
	ssd1306_WriteString(title, Font_7x10, White);

	ssd1306_SetCursor(0, 25);
	ssd1306_WriteString(dataString, Font_7x10, White);
	ssd1306_UpdateScreen();
}

void renderGenericLayoutWithInt(char* title, char* dataFormatString, uint16_t data, char* unit) {
	char buf[LONGEST_DATA_STRING];
	snprintf(buf, LONGEST_DATA_STRING, dataFormatString, data, unit);
	renderGenericLayout(title, buf);
}

void renderGenericLayoutWithFloat(char* title, char* dataFormatString, float data, char* unit) {
	char buf[LONGEST_DATA_STRING];
	snprintf(buf, LONGEST_DATA_STRING, dataFormatString, data, unit);
	renderGenericLayout(title, buf);
}

void renderGoalPage() {
	if (getGoalUnit() == PERCENT) {
		char unitString[9];
		snprintf(unitString, 9, "of %u", getGoal());
		renderGenericLayoutWithInt("Goal progress:", "%u%% %s", getGoalPercent(), unitString);
	} else {
		char unitString[8];
		snprintf(unitString, 8, "/ %u", getGoal());
		renderGenericLayoutWithInt("Goal progress:", "%u %s", getSteps() , unitString);
	}
}

void renderStepsTakenPage() {
	renderGenericLayoutWithInt("Steps taken:", "%u %s", getSteps(), "steps");
}

void renderDistanceTravelledPage() {
	if (getDistanceUnit() == KM) {
		renderGenericLayoutWithFloat("Distance traveled:", "%0.2f %s", getDistance(), "km");
	} else {
		renderGenericLayoutWithFloat("Distance traveled:", "%0.0f %s", getDistance(), "yards");
	}
}

void renderGoalChangePage() {
	renderGenericLayoutWithInt("New goal:", "%u %s", getTentativeGoal(), "steps");
}
