/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "motor.h"
#include "L298N_5AD.h"
#include "pid_controller.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define M1PWM_Direct_Pin GPIO_PIN_5
#define M1PWM_Direct_GPIO_Port GPIOA
#define M2E_OUT_A_Pin GPIO_PIN_6
#define M2E_OUT_A_GPIO_Port GPIOA
#define M2E_OUT_B_Pin GPIO_PIN_7
#define M2E_OUT_B_GPIO_Port GPIOA
#define M1E_OUT_A_Pin GPIO_PIN_8
#define M1E_OUT_A_GPIO_Port GPIOA
#define M1E_OUT_B_Pin GPIO_PIN_9
#define M1E_OUT_B_GPIO_Port GPIOA
#define M2KY_010B_Pin GPIO_PIN_14
#define M2KY_010B_GPIO_Port GPIOA
#define M2KY_010A_Pin GPIO_PIN_15
#define M2KY_010A_GPIO_Port GPIOA
#define M1PWM_Reverse_Pin GPIO_PIN_3
#define M1PWM_Reverse_GPIO_Port GPIOB
#define M1KY_010B_Pin GPIO_PIN_4
#define M1KY_010B_GPIO_Port GPIOB
#define M1KY_010A_Pin GPIO_PIN_5
#define M1KY_010A_GPIO_Port GPIOB
#define M2PWM_Direct_Pin GPIO_PIN_6
#define M2PWM_Direct_GPIO_Port GPIOB
#define M2PWM_Reverse_Pin GPIO_PIN_7
#define M2PWM_Reverse_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
