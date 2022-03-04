/*
 * L298N_5AD.c
 *
 *  Created on: 24 lut 2022
 *      Author: strka
 */
#include "main.h"


void L298N_5AD_set_motor(motor_str *m,TIM_HandleTypeDef *tim){
	if(m->motorDirection == Direct){
		__HAL_TIM_SetCompare(tim, TIM_CHANNEL_1, m->actual_PWM);
		__HAL_TIM_SetCompare(tim, TIM_CHANNEL_2, 0);
	}else if(m->motorDirection == Reverse){
		__HAL_TIM_SetCompare(tim, TIM_CHANNEL_2, m->actual_PWM);
		__HAL_TIM_SetCompare(tim, TIM_CHANNEL_1, 0);
	}

void L298N_5AD_set_motor_Breake(motor_str *m,TIM_HandleTypeDef *tim){
		__HAL_TIM_SetCompare(tim, TIM_CHANNEL_ALL, 999);
	}
}
void L298N_5AD_init(TIM_HandleTypeDef *tim){

	HAL_TIMEx_PWMN_Start(tim, TIM_CHANNEL_ALL);
}


