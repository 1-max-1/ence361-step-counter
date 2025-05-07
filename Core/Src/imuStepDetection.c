#include "imuStepDetection.h"
#include "noiseFiltering.h"
#include "imu_lsm6ds.h"
#include "stepData.h"

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define LINEAR_SENSITIVITY 0.061
#define STEP_THRESHOLD 1100000

static bool stepDetected;

void initializeIMUStepDetection() {
	// Enable accelerometer with high performance
	imu_lsm6ds_write_byte(CTRL1_XL, CTRL1_XL_HIGH_PERFORMANCE);
}

void processIMUData() {
	// Retrieve x acceleration data and convert to int16_t
	uint8_t acc_x_low = imu_lsm6ds_read_byte(OUTX_L_XL);
	uint8_t acc_x_high = imu_lsm6ds_read_byte(OUTX_H_XL);
	int16_t acc_x = (acc_x_high << 8) | acc_x_low;

	// Retrieve y acceleration data and convert to int16_t
	uint8_t acc_y_low = imu_lsm6ds_read_byte(OUTY_L_XL);
	uint8_t acc_y_high = imu_lsm6ds_read_byte(OUTY_H_XL);
	int16_t acc_y = (acc_y_high << 8) | acc_y_low;

	// Retrieve z acceleration data and convert to int16_t
	uint8_t acc_z_low = imu_lsm6ds_read_byte(OUTZ_L_XL);
	uint8_t acc_z_high = imu_lsm6ds_read_byte(OUTZ_H_XL);
	int16_t acc_z = (acc_z_high << 8) | acc_z_low;

	// Filter x, y, & z data and multiply by linear sensitivity to convert each into mg
	int16_t filteredX = filterValue(acc_x, 0) * LINEAR_SENSITIVITY;
	int16_t filteredY = filterValue(acc_y, 1) * LINEAR_SENSITIVITY;
	int16_t filteredZ = filterValue(acc_z, 2) * LINEAR_SENSITIVITY;

	uint32_t accelerationMagnitude = filteredX*filteredX + filteredY*filteredY + filteredZ*filteredZ;


	if ((accelerationMagnitude > STEP_THRESHOLD) && !stepDetected) {
		incrementSteps();
		stepDetected = true;
	}

	if ((accelerationMagnitude < STEP_THRESHOLD) && stepDetected) {
		stepDetected = false;
	}


	// printf("Magnitude: %lu\r\n", accelerationMagnitude);

}
