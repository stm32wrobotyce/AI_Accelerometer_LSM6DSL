/*
 * lsm6dsl.h
 *
 *  Created on: 19 lis 2021
 *      Author: piotr
 */

#ifndef INC_LSM6DSL_H_
#define INC_LSM6DSL_H_

#include "main.h"

#define LSM6DSL_ACCE_DATA_SIZE				6
#define LSM6DSL_GYRO_DATA_SIZE				6

#define LSM6DSL_I2C_ADDR     				0xD6
#define LSM6DSL_ID            				0x6A

#define LSM6DSL_WHO_AM_I      				0x0F
#define LSM6DSL_CTRL1_XL      				0x10
#define LSM6DSL_CTRL2_G       				0x11
#define LSM6DSL_CTRL3_C       				0x12
#define LSM6DSL_CTRL4_C       				0x13
#define LSM6DSL_CTRL5_C       				0x14
#define LSM6DSL_CTRL6_C       				0x15
#define LSM6DSL_CTRL7_G       				0x16
#define LSM6DSL_CTRL8_XL      				0x17
#define LSM6DSL_CTRL9_XL      				0x18
#define LSM6DSL_CTRL10_C      				0x19

#define LSM6DSL_STATUS_REG                  0x1E

#define LSM6DSL_OUT_TEMP_L                  0x20
#define LSM6DSL_OUT_TEMP_H                  0x21
#define LSM6DSL_OUTX_L_G                    0x22
#define LSM6DSL_OUTX_H_G                    0x23
#define LSM6DSL_OUTY_L_G                    0x24
#define LSM6DSL_OUTY_H_G                    0x25
#define LSM6DSL_OUTZ_L_G                    0x26
#define LSM6DSL_OUTZ_H_G                    0x27
#define LSM6DSL_OUTX_L_XL                   0x28
#define LSM6DSL_OUTX_H_XL                   0x29
#define LSM6DSL_OUTY_L_XL                   0x2A
#define LSM6DSL_OUTY_H_XL                   0x2B
#define LSM6DSL_OUTZ_L_XL                   0x2C
#define LSM6DSL_OUTZ_H_XL                   0x2D

#define LSM6DSL_ACC_SENSITIVITY_FS_2G   	0.061f
#define LSM6DSL_ACC_SENSITIVITY_FS_4G   	0.122f
#define LSM6DSL_ACC_SENSITIVITY_FS_8G   	0.244f
#define LSM6DSL_ACC_SENSITIVITY_FS_16G  	0.488f

#define LSM6DSL_GYRO_SENSITIVITY_FS_125DPS    4.375f
#define LSM6DSL_GYRO_SENSITIVITY_FS_250DPS    8.750f
#define LSM6DSL_GYRO_SENSITIVITY_FS_500DPS   17.500f
#define LSM6DSL_GYRO_SENSITIVITY_FS_1000DPS  35.000f
#define LSM6DSL_GYRO_SENSITIVITY_FS_2000DPS  70.000f

typedef enum {
  LSM6DSL_2g       = 0,
  LSM6DSL_16g      = 1,
  LSM6DSL_4g       = 2,
  LSM6DSL_8g       = 3
} lsm6dsl_fs_xl_t;

typedef enum {
  LSM6DSL_XL_ODR_OFF      =  0,
  LSM6DSL_XL_ODR_12Hz5    =  1,
  LSM6DSL_XL_ODR_26Hz     =  2,
  LSM6DSL_XL_ODR_52Hz     =  3,
  LSM6DSL_XL_ODR_104Hz    =  4,
  LSM6DSL_XL_ODR_208Hz    =  5,
  LSM6DSL_XL_ODR_416Hz    =  6,
  LSM6DSL_XL_ODR_833Hz    =  7,
  LSM6DSL_XL_ODR_1k66Hz   =  8,
  LSM6DSL_XL_ODR_3k33Hz   =  9,
  LSM6DSL_XL_ODR_6k66Hz   = 10,
  LSM6DSL_XL_ODR_1Hz6     = 11
} lsm6dsl_odr_xl_t;

typedef enum {
  LSM6DSL_250dps     = 0,
  LSM6DSL_125dps     = 1,
  LSM6DSL_500dps     = 2,
  LSM6DSL_1000dps    = 4,
  LSM6DSL_2000dps    = 6
} lsm6dsl_fs_g_t;

typedef enum {
  LSM6DSL_GY_ODR_OFF    =  0,
  LSM6DSL_GY_ODR_12Hz5  =  1,
  LSM6DSL_GY_ODR_26Hz   =  2,
  LSM6DSL_GY_ODR_52Hz   =  3,
  LSM6DSL_GY_ODR_104Hz  =  4,
  LSM6DSL_GY_ODR_208Hz  =  5,
  LSM6DSL_GY_ODR_416Hz  =  6,
  LSM6DSL_GY_ODR_833Hz  =  7,
  LSM6DSL_GY_ODR_1k66Hz =  8,
  LSM6DSL_GY_ODR_3k33Hz =  9,
  LSM6DSL_GY_ODR_6k66Hz = 10
} lsm6dsl_odr_g_t;

typedef union
{
	uint8_t bytes[LSM6DSL_ACCE_DATA_SIZE];

	struct __attribute__((packed))
	{
	  int16_t x;
	  int16_t y;
	  int16_t z;
	};
}LSM6DSL_AxesRaw_t;

typedef struct
{
  int32_t x;
  int32_t y;
  int32_t z;
} LSM6DSL_Axes_t;

void lsm6dsl_init(void);
void lsm6dsl_get_accel_axis(LSM6DSL_Axes_t *axes);
void lsm6dsl_get_gyro_axis(LSM6DSL_Axes_t *axes);

void lsm6dsl_write(uint8_t reg, uint8_t *data, uint32_t size);
void lsm6dsl_read(uint8_t reg, uint8_t *data, uint32_t size);

#endif /* INC_LSM6DSL_H_ */
