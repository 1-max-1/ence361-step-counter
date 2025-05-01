/*
 * goalNotification.h
 *
 *  Created on: May 1, 2025
 *      Author: Max Hosking
 *
 *  This module tracks when the goal is reached and when to notify the user (with buzzer)
 */

#ifndef _GOAL_NOTIFICATION_H_
#define _GOAL_NOTIFICATION_H_

// Schedule as task. Will check for goal completion and notify user if required.
void goalNotificationUpdate();

#endif /* _GOAL_NOTIFICATION_H_ */
