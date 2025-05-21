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

typedef enum {KM=0, YD} distanceUnit_t;

typedef enum {PERCENT=0, RATIO} goalUnit_t;

//initialise stepData
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
//Returns percentage of goal completed
uint16_t getGoalPercent();
//Returns total distance traveled based on set unit
float getDistance();
//Returns current unit of distance
distanceUnit_t getDistanceUnit();
//Returns current goal unit
goalUnit_t getGoalUnit();
//Toggles distance unit
void toggleDistanceUnit();
//Toggles goal unit
void toggleGoalUnit();
//Updates tentative new goal value
void setTentativeGoal(uint16_t newTentativeGoal);
//Returns tentative goal
uint16_t getTentativeGoal();


#endif
