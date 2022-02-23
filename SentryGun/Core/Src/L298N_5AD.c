#include "main.h"
#include "L298N_5AD.h"
TIM_HandleTypeDef htim2, htim3;

void L298N_5AD_init(){
	L298N_5AD_setmotorA(0,Forward);
	HAL_TIMEx_PWMN_Start(&htim2, TIM_CHANNEL_3);
	HAL_TIMEx_PWMN_Start(&htim3,TIM_CHANNEL_3);
}
void L298N_5AD_set_motorA(uint16_t speed, L298N_5AD_Direction dir){
	if(speed >= htim2.Instance->ARR && dir==Forward){
		speed = htim2.Instance->ARR;
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, speed);
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, 0);
	}else if(speed >= htim3.Instance->ARR && dir==Reverse){
		speed = htim3.Instance->ARR;
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, speed);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 0);
	}else if(speed >= htim2.Instance->ARR && speed >= htim3.Instance->ARR && dir==Breake){
		speed = htim2.Instance->ARR;
		speed = htim3.Instance->ARR;
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, speed);
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, speed);
	}
void L298N_5AD_set_motorA_Breake(){
		speed = htim2.Instance->ARR;
		speed = htim3.Instance->ARR;
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, speed);
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, speed);
	}
}
