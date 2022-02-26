/*
 * L298N_5AD.c
 *
 *  Created on: 24 lut 2022
 *      Author: strka
 */
#include "main.h"

TIM_HandleTypeDef htim2;

void L298N_5AD_set_motorA(motor_str *m){
	if(m->set_target>=0){
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, m->actual_PWM);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 0);
	}else if(m->set_target<=0){
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, m->actual_PWM);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, 0);
	}

void L298N_5AD_set_motorA_Breake(){
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_ALL, 999);
	}
}
void L298N_5AD_init(){

	HAL_TIMEx_PWMN_Start(&htim2, TIM_CHANNEL_ALL);
}


