/**
 * stepData.h
 *
 * for tracking all data relating to step counter including
 * steps taken, goal, goal percentage, distance travelled
 *
 * Author: Alex Pirie
 *
 */

#include <stdio.h>
#include <stdint.h>

#ifndef _STEPDATA_H_
#define _STEPDATA_H_

typedef enum {KM=0, YD} distanceUnit_t

typedef enum {PERCENT=0, RATIO} goalUnit_t

//initialise stepData
void stepDataSetup();
//Returns number of steps taken
uint16_t getSteps();
//Increments running step count
void incrementSteps();
//Updates current goal to newGoal
void setGoal(uint16_t newGoal);
//Returns percentage of goal completed
uint16_t getGoalPercent();
//Returns total distance travelled based on set unit
uint16_t getDistance();
//Returns current unit of distance
distanceUnit_t getDistanceUnit();
//Returns current goal unit
goalUnit_t getGoalUnit();
//Toggles distance unit
void toggleDistanceUnit();
//Toggles goal unit
void toggleGoalUnit();


#endif
