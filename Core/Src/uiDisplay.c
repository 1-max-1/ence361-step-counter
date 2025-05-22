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
#include <stdbool.h>

// Number of characters, including null-terminator.
// Change this if we use longer unit strings or more digits in the data number.
#define LONGEST_DATA_STRING 15

void initUIDisplay() {
	ssd1306_Init();
}

static bool displayTestModeMessage = false;

void showTestModeMessage(bool enabled) {
	displayTestModeMessage = enabled;
}

// All pages share same basic layout
void renderGenericLayout(char* title, char* dataString) {
	ssd1306_Fill(Black);

	// Layout of pages consists of title and data
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(title, Font_7x10, White);
	ssd1306_SetCursor(0, 15);
	ssd1306_WriteString(dataString, Font_7x10, White);

	if (displayTestModeMessage) {
		ssd1306_SetCursor(0, 48);
		ssd1306_WriteString("(Test mode on)", Font_6x8, White);
	}

	ssd1306_UpdateScreen();
}

// Creates data string from integer and renders the layout
void renderGenericLayoutWithInt(char* title, char* dataFormatString, uint16_t data, char* unit) {
	char buf[LONGEST_DATA_STRING];
	snprintf(buf, LONGEST_DATA_STRING, dataFormatString, data, unit);
	renderGenericLayout(title, buf);
}

// Creates data string from float and renders the layout
void renderGenericLayoutWithFloat(char* title, char* dataFormatString, float data, char* unit) {
	char buf[LONGEST_DATA_STRING];
	snprintf(buf, LONGEST_DATA_STRING, dataFormatString, data, unit);
	renderGenericLayout(title, buf);
}

void renderGoalPage() {
	if (getGoalUnit() == UNIT_PERCENT) { // Percentage
		char unitString[9];
		snprintf(unitString, 9, "of %u", getGoal());
		renderGenericLayoutWithInt("Goal progress:", "%u%% %s", getGoalPercent(), unitString);
	} else { // Ratio
		char unitString[8];
		snprintf(unitString, 8, "/ %u", getGoal());
		renderGenericLayoutWithInt("Goal progress:", "%u %s", getSteps() , unitString);
	}
}

void renderStepsTakenPage() {
	renderGenericLayoutWithInt("Steps taken:", "%u %s", getSteps(), "steps");
}

void renderDistanceTravelledPage() {
	if (getDistanceUnit() == UNIT_KM) { // km
		renderGenericLayoutWithFloat("Distance traveled:", "%0.2f %s", getDistance(), "km");
	} else { // yards
		renderGenericLayoutWithFloat("Distance traveled:", "%0.0f %s", getDistance(), "yards");
	}
}

void renderGoalChangePage() {
	renderGenericLayoutWithInt("New goal:", "%u %s", getTentativeGoal(), "steps");
}
