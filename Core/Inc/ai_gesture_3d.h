/*
 * ai_sharp_sensor.h
 *
 *  Created on: 22 sty 2022
 *      Author: piotr
 */

#ifndef INC_AI_GESTURE_3D_H_
#define INC_AI_GESTURE_3D_H_

#define DATA_BUFFER_SIZE			300
#define NUMBER_OF_RECORDS			100
#define TX_BUFFER_SIZE				30
#define TASK_TIME_MS				10

void ai_train_data_collect(void);
void ai_gesture_detect(void);

#endif /* INC_AI_GESTURE_3D_H_ */
