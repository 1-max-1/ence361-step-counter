/**
 * stepData.h
 *
 * for tracking all data relating to step counter including
 * steps taken, goal, goal percentage, distance traveled
 *
 * Authors: Alex Pirie, Max Hosking
 *
 */

#include <stdio.h>
#include <stdint.h>

#ifndef _STEP_DATA_H_
#define _STEP_DATA_H_

typedef enum {UNIT_KM=0, UNIT_YD} distanceUnit_t;
typedef enum {UNIT_PERCENT=0, UNIT_RATIO} goalUnit_t;

void stepDataInit();
//Returns number of steps taken
uint16_t getSteps();
// Manually set the number of steps taken
void setSteps(uint16_t steps);
//Increments running step count
void incrementSteps();

//Updates current goal to newGoal
void setGoal(uint16_t newGoal);
// Returns current goal, (number of steps)
uint16_t getGoal();
//Returns percentage of goal completed (0-100)
uint16_t getGoalPercent();
//Returns current goal unit
goalUnit_t getGoalUnit();
// Toggles goal display unit
void toggleGoalUnit();

// Returns total distance traveled based on currently set unit
float getDistance();
//Returns current distance display unit
distanceUnit_t getDistanceUnit();
//Toggles distance display unit
void toggleDistanceUnit();

//Updates tentative new goal value
//needed as new goal may not always be selected, allows for rollback to previous goal
void setTentativeGoal(uint16_t newTentativeGoal);
//Returns tentative goal
uint16_t getTentativeGoal();


#endif
