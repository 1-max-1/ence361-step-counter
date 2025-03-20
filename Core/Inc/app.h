/**
 * app.h
 *
 * Authors: Max Hosking, Alex Pirie
 *
 * The app module is the highest level module and handles task scheduling.
 */

#ifndef _APP_H_
#define _APP_H_

// Initialize all tasks
void appSetup(void);

// Schedule tasks, call this repeatedly
void appMain(void);

#endif
