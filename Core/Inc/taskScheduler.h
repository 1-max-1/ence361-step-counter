/**
 * taskScheduler.h
 *
 * Handles the execution of tasks
 */

#ifndef _TASK_SCHEDULER_H_
#define _TASK_SCHEDULER_H_

#include <stdint.h>
#include <stdbool.h>

// Pointer to top level function that runs all code for the task
typedef void (*taskFunction_t)();

/**
 * Will register the specified task function with the scheduler.
 * The scheduler will try and run the task at the specified frequency.
 * Will return false if the task could not be scheduled - this means the maximum number of tasks was reached.
 */
bool registerTask(taskFunction_t taskFunc, uint16_t freq);

// Update/tick the scheduler. Call this in the main loop
void schedulerUpdate();

#endif // _TASK_SCHEDULER_H_
