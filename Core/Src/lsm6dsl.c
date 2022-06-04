/*
 * lsm6dsl.c
 *
 *  Created on: 19 lis 2021
 *      Author: piotr
 */

#include "lsm6dsl.h"
#include "i2c.h"

#define I2C_INTERFACE				&hi2c1
#define	I2C_TIMEOUT					1

#define LSM6DSL_SET_ODR_XL(data)	(data << 4)
#define LSM6DSL_SET_FS_XL(data)		(data << 2)

#define LSM6DSL_SET_ODR_G(data)		(data << 4)
#define LSM6DSL_SET_FS_G(data)		(data << 1)

#define LSM6DSL_SET_AUTO_INC		(1 << 2)

void lsm6dsl_init(void)
{
	uint8_t data = 0;

	lsm6dsl_read(LSM6DSL_WHO_AM_I, &data, 1);

	if(LSM6DSL_ID != data)
	{
		return;
	}

	data = LSM6DSL_SET_ODR_XL(LSM6DSL_XL_ODR_208Hz) | LSM6DSL_SET_FS_XL(LSM6DSL_2g);
	lsm6dsl_write(LSM6DSL_CTRL1_XL, &data, 1);

	data = LSM6DSL_SET_ODR_G(LSM6DSL_GY_ODR_208Hz) | LSM6DSL_SET_FS_G(LSM6DSL_125dps);
	lsm6dsl_write(LSM6DSL_CTRL2_G, &data, 1);

	data = LSM6DSL_SET_AUTO_INC;
	lsm6dsl_write(LSM6DSL_CTRL3_C, &data, 1);
}

void lsm6dsl_get_accel_axis(LSM6DSL_Axes_t *axes)
{
	LSM6DSL_AxesRaw_t axes_raw;

	lsm6dsl_read(LSM6DSL_OUTX_L_XL, axes_raw.bytes, LSM6DSL_ACCE_DATA_SIZE);

	axes->x = (int32_t)((float)axes_raw.x * LSM6DSL_ACC_SENSITIVITY_FS_2G);
	axes->y = (int32_t)((float)axes_raw.y * LSM6DSL_ACC_SENSITIVITY_FS_2G);
	axes->z = (int32_t)((float)axes_raw.z * LSM6DSL_ACC_SENSITIVITY_FS_2G);
}

void lsm6dsl_get_gyro_axis(LSM6DSL_Axes_t *axes)
{
	LSM6DSL_AxesRaw_t axes_raw;

	lsm6dsl_read(LSM6DSL_OUTX_L_G, axes_raw.bytes, LSM6DSL_GYRO_DATA_SIZE);

	axes->x = (int32_t)((float)axes_raw.x * LSM6DSL_GYRO_SENSITIVITY_FS_125DPS);
	axes->y = (int32_t)((float)axes_raw.y * LSM6DSL_GYRO_SENSITIVITY_FS_125DPS);
	axes->z = (int32_t)((float)axes_raw.z * LSM6DSL_GYRO_SENSITIVITY_FS_125DPS);
}

void lsm6dsl_write(uint8_t reg, uint8_t *data, uint32_t size)
{
	HAL_I2C_Mem_Write(I2C_INTERFACE, LSM6DSL_I2C_ADDR, reg, 1, data, size, I2C_TIMEOUT);
}

void lsm6dsl_read(uint8_t reg, uint8_t *data, uint32_t size)
{
	HAL_I2C_Mem_Read(I2C_INTERFACE, LSM6DSL_I2C_ADDR, reg, 1, data, size, I2C_TIMEOUT);
}
