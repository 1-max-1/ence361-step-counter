/**
 * taskScheduler.h
 *
 * Handles the execution of tasks
 */

#include "taskScheduler.h"
#include "stm32c0xx_hal.h"

#include <stdint.h>
#include <stdbool.h>

// Maximum number of tasks that can be registered
#define MAX_NUM_TASKS 20

#define TICK_FREQUENCY_HZ 1000
#define HZ_TO_TICKS(FREQUENCY_HZ) (TICK_FREQUENCY_HZ/FREQUENCY_HZ)

typedef struct {
	taskFunction_t taskFunc;
	uint32_t ticksInterval;
	uint32_t nextRun;
} task_t;

task_t registeredTasks[MAX_NUM_TASKS];
uint8_t nextTaskID = 0; // Next slot to be used

// Initializes an instance of the task struct
task_t createTaskObject(taskFunction_t taskFunc, uint16_t freq) {
	uint32_t interval = HZ_TO_TICKS(freq);
	task_t task = {
		.taskFunc = taskFunc,
		.ticksInterval = interval,
		.nextRun = HAL_GetTick() + interval
	};
	return task;
}

bool registerTask(taskFunction_t taskFunc, uint16_t freq) {
	if (nextTaskID == MAX_NUM_TASKS)
		return false;

	registeredTasks[nextTaskID] = createTaskObject(taskFunc, freq);
	nextTaskID++;
	return true;
}

void schedulerUpdate() {
	// Time triggered scheduler - check every task.
	// Each task has the next time it is meant to be run.
	// If this time is reached, we can run it.

	for (uint8_t taskNum = 0; taskNum < nextTaskID; taskNum++) {
		task_t* task = &registeredTasks[taskNum];

		uint32_t ticks = HAL_GetTick();
		if (ticks > task->nextRun) {
			task->taskFunc();
			task->nextRun += task->ticksInterval;
		}
	}
}
