/**
 * app.h
 *
 * Authors: Max Hosking, Alex Pirie
 *
 * The app module is the highest level module.
 * It initializes tasks and specifies the frequency of tasks.
 */

#ifndef _APP_H_
#define _APP_H_

// Initializes and schedules all tasks
void appSetup(void);

// Main function, call from main loop
void appMain(void);

#endif
