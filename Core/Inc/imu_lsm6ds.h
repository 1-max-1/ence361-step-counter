/*
 * imu_lsm6ds.h
 *
 *  Created on: Nov 27, 2024
 *      Author: fsy13
 *      Modified by: Alex Pirie
 *
 *  Handles reading and writing to IMU, exposes convenience functions
 */

#ifndef _IMU_LSM6DS_H_
#define _IMU_LSM6DS_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum {
	FUNC_CFG_ACCESS = 0x01U,
	SENSOR_SYNC_TIME_FRAME = 0x04U,
	SENSOR_SYNC_RES_RATIO,
	FIFO_CTRL1,
	FIFO_CTRL2,
	FIFO_CTRL3,
	FIFO_CTRL4,
	FIFO_CTRL5,
	DRDY_PULSE_CFG_G,
	INT1_CTRL = 0x0DU,
	INT2_CTRL,
	WHO_AM_I,
	CTRL1_XL,
	CTRL2_G,
	CTRL3_C,
	CTRL4_C,
	CTRL5_C,
	CTRL6_C,
	CTRL7_G,
	CTRL8_XL,
	CTRL9_XL,
	CTRL10_C,
	MASTER_CONFIG,
	WAKE_UP_SRC,
	TAP_SRC,
	D6D_SRC,
	STATUS_REG,
	OUT_TEMP_L = 0x20U,
	OUT_TEMP_H,
	OUTX_L_G,
	OUTX_H_G,
	OUTY_L_G,
	OUTY_H_G,
	OUTZ_L_G,
	OUTZ_H_G,
	OUTX_L_XL,
	OUTX_H_XL,
	OUTY_L_XL,
	OUTY_H_XL,
	OUTZ_L_XL,
	OUTZ_H_XL,
	SENSORHUB1_REG,
	SENSORHUB2_REG,
	SENSORHUB3_REG,
	SENSORHUB4_REG,
	SENSORHUB5_REG,
	SENSORHUB6_REG,
	SENSORHUB7_REG,
	SENSORHUB8_REG,
	SENSORHUB9_REG,
	SENSORHUB10_REG,
	SENSORHUB11_REG,
	SENSORHUB12_REG,
	FIFO_STATUS1,
	FIFO_STATUS2,
	FIFO_STATUS3,
	FIFO_STATUS4,
	FIFO_DATA_OUT_L,
	FIFO_DATA_OUT_H,
	TIMESTAMP0_REG,
	TIMESTAMP1_REG,
	TIMESTAMP2_REG,
	STEP_TIMESTAMP_L = 0x49U,
	STEP_TIMESTAMP_H,
	STEP_COUNTER_L,
	STEP_COUNTER_H,
	SENSORHUB13_REG,
	SENSORHUB14_REG,
	SENSORHUB15_REG,
	SENSORHUB16_REG,
	SENSORHUB17_REG,
	SENSORHUB18_REG,
	FUNC_SRC1,
	FUNC_SRC2,
	WRIST_TILT_IA,
	TAP_CFG = 0x58U,
	TAP_THS_6D,
	INT_DUR2,
	WAKE_UP_THS,
	WAKE_UP_DUR,
	FREE_FALL,
	MD1_CFG,
	MD2_CFG,
	MASTER_CMD_CODE,
	SENS_SYNC_SPI_ERROR_CODE,
	OUT_MAG_RAW_X_L = 0x66U,
	OUT_MAG_RAW_X_H,
	OUT_MAG_RAW_Y_L,
	OUT_MAG_RAW_Y_H,
	OUT_MAG_RAW_Z_L,
	OUT_MAG_RAW_Z_H,
	X_OFS_USR = 0x73U,
	Y_OFS_USR,
	Z_OFS_USR
} imu_register_t; // IMU register addresses

// Standard options
#define CTRL1_XL_HIGH_PERFORMANCE 0xA0U
#define CTRL2_G_HIGH_PERFORMANCE 0xA0U
#define CTRL10_C_ENABLE_PEDO 0x14U

void imuInit();

void imu_lsm6ds_write_byte(imu_register_t register_address, uint8_t value);

uint8_t imu_lsm6ds_read_byte(imu_register_t register_address);

//returns imu x-axis acceleration
int16_t getImuXAccel();

//returns imu y-axis acceleration
int16_t getImuYAccel();

//returns imu z-axis acceleration
int16_t getImuZAccel();

// Testing step detection included in IMU chip (NOT IN USE FOR FINAL TESTING)
bool inbuiltStepDetected();

#endif /* _IMU_LSM6DS_H_ */
