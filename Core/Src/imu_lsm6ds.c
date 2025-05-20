/*
 * imu_lsm6ds.c
 *
 *  Created on: Nov 28, 2024
 *      Author: fsy13
 */

#include "imu_lsm6ds.h"
#include "spi.h"
#include <stdint.h>

// Hardware configuration
#define spi_hal_handler hspi2

void initializeIMU() {
	// Enable accelerometer with high performance
	imu_lsm6ds_write_byte(CTRL1_XL, CTRL1_XL_HIGH_PERFORMANCE);

	imu_lsm6ds_write_byte(CTRL10_C, 0b0011100);
}

void imu_lsm6ds_write_byte(imu_register_t register_address, uint8_t value)
{
	uint8_t write_buff[2] = {0};
	write_buff[0] = value;
	write_buff[1] = register_address;

	// Send one word = 16 bits, MSB first
	HAL_SPI_Transmit(&spi_hal_handler, write_buff, 1, HAL_MAX_DELAY);
}

uint8_t imu_lsm6ds_read_byte(imu_register_t register_address)
{
	// 16 bit transmission:
	// First byte is the register address on MOSI, with the read bit enabled.
	// Second byte is the data from slave on MISO.
	// Indexing in reverse order due to MSB first.

	uint8_t tx[2] = {0};
	uint8_t rx[2] = {0};

	tx[1] = register_address |= (1 << 7); // Set "Read" bit

	HAL_SPI_TransmitReceive(&spi_hal_handler, tx, rx, 1, HAL_MAX_DELAY);

	return rx[0];
}


int16_t getImuXAccel() {
	// Retrieve x acceleration data and convert to int16_t
	uint8_t acc_x_low = imu_lsm6ds_read_byte(OUTX_L_XL);
	uint8_t acc_x_high = imu_lsm6ds_read_byte(OUTX_H_XL);
	int16_t acc_x = (acc_x_high << 8) | acc_x_low;
	return acc_x;
}

int16_t getImuYAccel() {
	// Retrieve y acceleration data and convert to int16_t
	uint8_t acc_y_low = imu_lsm6ds_read_byte(OUTY_L_XL);
	uint8_t acc_y_high = imu_lsm6ds_read_byte(OUTY_H_XL);
	int16_t acc_y = (acc_y_high << 8) | acc_y_low;
	return acc_y;
}

int16_t getImuZAccel() {
	// Retrieve z acceleration data and convert to int16_t
	uint8_t acc_z_low = imu_lsm6ds_read_byte(OUTZ_L_XL);
	uint8_t acc_z_high = imu_lsm6ds_read_byte(OUTZ_H_XL);
	int16_t acc_z = (acc_z_high << 8) | acc_z_low;
	return acc_z;
}

bool isStep() {
	return imu_lsm6ds_read_byte(FUNC_SRC1) & (1 << 4);
}
