/*
 * L298N_5AD.h
 *
 *  Created on: 24 lut 2022
 *      Author: strka
 */

#ifndef SRC_L298N_5AD_H_
#define SRC_L298N_5AD_H_

void L298N_5AD_init(TIM_HandleTypeDef *);
void L298N_5AD_set_motor(motor_str *,TIM_HandleTypeDef *);
void L298N_5AD_set_motor_Breake(motor_str *,TIM_HandleTypeDef *);


#endif /* SRC_L298N_5AD_H_ */
