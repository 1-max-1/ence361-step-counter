/*
 * goalProgressIndication.h
 *
 *  Created on: May 1, 2025
 *      Author: Max Hosking
 *
 *  This task tracks goal progression, and uses LED's and buzzers to inform the user.
 */

#ifndef _GOAL_PROGRESS_INDICATION_H_
#define _GOAL_PROGRESS_INDICATION_H_

// Initialize the task
void setupGoalProgressIndicators();

// Schedule this as a task. Will check for goal completion and notify user if required.
// Will also update indicator LED's accordingly
void updateGoalProgressIndicators();

#endif /* _GOAL_PROGRESS_INDICATION_H_ */
