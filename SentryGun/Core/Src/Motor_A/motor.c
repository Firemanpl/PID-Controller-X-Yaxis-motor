/*
 * motor.c
 *
 *  Created on: 24 lut 2022
 *      Author: strka
 */
#include "main.h"

void motor_update_count(motor_str *m, TIM_HandleTypeDef *tim) {

	int LastTimerCounter = 0; //uint16_t
	int TimerDif = __HAL_TIM_GET_COUNTER(tim) - LastTimerCounter;
	if (TimerDif >= 4 || TimerDif <= -4) {
		TimerDif /= 4;
		m->pulse_count += (int8_t) TimerDif;
		LastTimerCounter = __HAL_TIM_GET_COUNTER(tim);
	}
}

void calibrate_motor(motor_str *mA, motor_str *mB, TIM_HandleTypeDef *timA,
		TIM_HandleTypeDef *timB, uint8_t pwm, uint8_t *calibrate_end) {
	mA->actual_PWM = pwm;
	mB->actual_PWM = pwm;
	uint8_t calibratedA, calibratedB;
	uint8_t block1, block2;
//            Motor - A
		if (HAL_GPIO_ReadPin(GPIOA, M1KY_010A_Pin) == GPIO_PIN_SET) {
			L298N_5AD_set_motor_Breake(mA, timA);
			block1 = 1;
		} else {
			L298N_5AD_set_motor(mA, timA);
			if (HAL_GPIO_ReadPin(GPIOA, M1KY_010B_Pin) == GPIO_PIN_SET) {
				if (mA->motorDirection == Direct) {
					mA->motorDirection = Reverse;
				} else {
					mA->motorDirection = Direct;
				}
			}
			if (block1 = 1) {
				uint32_t savedTimeA;
				uint32_t actualTimeA = HAL_GetTick();
				uint32_t differenceTimeA = actualTimeA - savedTimeA;
				if (differenceTimeA >= 2000) {
					if (HAL_GPIO_ReadPin(GPIOA, M1KY_010A_Pin) == GPIO_PIN_RESET) {
						mA->motorDirection = Reverse;
					} else {
						calibratedA = 1;
					}
					savedTimeA = actualTimeA ;
					block1 = 0;
				}
			}
		}
//            Motor - B
	if (HAL_GPIO_ReadPin(GPIOB, M2KY_010A_Pin) == GPIO_PIN_SET) {
		L298N_5AD_set_motor_Breake(mB, timB);
		block2 = 1;
	} else {
		L298N_5AD_set_motor(mB, timB);
		if (HAL_GPIO_ReadPin(GPIOB, M2KY_010B_Pin) == GPIO_PIN_SET) {
			if (mB->motorDirection == Direct) {
				mB->motorDirection = Reverse;
			} else {
				mB->motorDirection = Direct;
			}
		}
		if (block2 = 1) {
			uint32_t savedTimeB;
			uint32_t actualTimeB = HAL_GetTick();
			uint32_t differenceTimeB = actualTimeB - savedTimeB;
			if (differenceTimeB >= 2000) {
				if (HAL_GPIO_ReadPin(GPIOB, M2KY_010A_Pin) == GPIO_PIN_RESET) {
					mB->motorDirection = Reverse;
				} else {
					calibratedB = 1;
				}
				savedTimeB = actualTimeB ;
				block2 = 0;
			}
		}
	}

}

