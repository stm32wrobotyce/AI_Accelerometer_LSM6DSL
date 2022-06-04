/*
 * ai_sharp_sensor.c
 *
 *  Created on: 22 sty 2022
 *      Author: piotr
 */

#include "app_x-cube-ai.h"
#include "usart.h"
#include <stdbool.h>
#include <stdio.h>

#include "ai_gesture_3d.h"
#include "lsm6dsl.h"

volatile bool button_is_pushed = false;

void ai_sharp_train_data_collect(void)
{
	uint8_t tx_buffer[TX_BUFFER_SIZE] = {0};
	static uint32_t data_in[DATA_BUFFER_SIZE];

	LSM6DSL_Axes_t accel_axes;
	static uint32_t counter = 0;
	int32_t size = 0;

	static uint32_t time_cnt = 0;

	if(time_cnt == 0)
		time_cnt = HAL_GetTick();

	if((HAL_GetTick() - time_cnt) > TASK_TIME_MS)
	{
		time_cnt = HAL_GetTick();

		lsm6dsl_get_accel_axis(&accel_axes);

		for(uint32_t i=0; i<(DATA_BUFFER_SIZE-3); i+=3 )
		{
			data_in[i] = data_in[i+3];
			data_in[i+1] = data_in[i+4];
			data_in[i+2] = data_in[i+5];
		}

		data_in[DATA_BUFFER_SIZE-3] = accel_axes.x;
		data_in[DATA_BUFFER_SIZE-2] = accel_axes.y;
		data_in[DATA_BUFFER_SIZE-1] = accel_axes.z;

		counter++;

		if(button_is_pushed == true)
		{
			counter = NUMBER_OF_RECORDS;
		}

		if(counter >= NUMBER_OF_RECORDS)
		{
			counter = 0;

			for (int var = 0; var < DATA_BUFFER_SIZE; ++var)
			{
				size = sprintf((char *)tx_buffer, "%d,", (int)data_in[var]);
				HAL_UART_Transmit(&huart2, tx_buffer, size, 10);
			}

			if(button_is_pushed == true)
			{
				size = sprintf((char *)tx_buffer, "1\n");
				button_is_pushed = false;
			}
			else
			{
				size = sprintf((char *)tx_buffer, "0\n");
			}

			HAL_UART_Transmit(&huart2, tx_buffer, size, 1);
		}
	}
}

void ai_gesture_detect(void)
{
	static uint32_t time_cnt = 0;

	if(time_cnt == 0)
		time_cnt = HAL_GetTick();

	if((HAL_GetTick() - time_cnt) > TASK_TIME_MS)
	{
		time_cnt = HAL_GetTick();
		MX_X_CUBE_AI_Process();
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == B1_Pin)
	{
		button_is_pushed = true;
	}
}

