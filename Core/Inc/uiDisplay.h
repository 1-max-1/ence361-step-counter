/*
 * uiDisplay.h
 *
 *  Created on: Apr 29, 2025
 *      Authors: Max Hosking, Alex Pirie
 *
 * This module handles the high level UI layout for each of the states.
 */

#ifndef _UI_DISPLAY_H_
#define _UI_DISPLAY_H_

#include <stdbool.h>

// Initializes the screen
void initUIDisplay();
void showTestModeMessage(bool enabled);

// This page shows goal as a percentage or a ratio of steps
void renderGoalPage();
// This page shows the number of steps taken
void renderStepsTakenPage();
// This page shows the distance travelled in yards or km
void renderDistanceTravelledPage();
// This page displays when the user is changing their goal
void renderGoalChangePage();

#endif /* _UI_DISPLAY_H_ */
