/*
 * motor.h
 *
 *  Created on: 24 lut 2022
 *      Author: strka
 */
#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

//#include "pid_controller.h"

#define MOTOR_A_Kp					1.2
#define MOTOR_A_Ki					0.1
#define MOTOR_A_Kd					0.2
#define MOTOR_A_ANTI_WINDUP			1000

typedef struct
{
	TIM_HandleTypeDef *timer;	//timer obsługujący enkoder silnika
	long long int pulse_count;		//zliczone impulsy
	int measured_speed;		//obliczona prędkość silnika
	int set_target;			//zadana prędkość silnika
	int actual_PWM;			//wartość PWM
}motor_str;

//void motor_update_count(motor_str);

#endif /* INC_MOTOR_H_ */
