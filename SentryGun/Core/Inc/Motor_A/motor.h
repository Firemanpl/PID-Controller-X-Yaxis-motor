/*
 * motor.h
 *
 *  Created on: 24 lut 2022
 *      Author: strka
 */
#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

typedef struct
{
	long long int pulse_count;
	long long int set_target;
	int actual_PWM;
	float kp;
	float kd;
	float ki;
	int min;
	int max;
	int8_t motorDirection;
}motor_str;

enum Direction{
	Direct=1,
	Reverse=-1
};

void motor_update_count(motor_str *,TIM_HandleTypeDef *);

#endif /* INC_MOTOR_H_ */
