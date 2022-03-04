/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include<stdio.h>
#include<string.h>
//#include "usbd_cdc_if.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

uint8_t ReceivedData[40]; // Tablica przechowujaca odebrane dane
uint8_t ReceivedDataFlag = 0; // Flaga informujaca o odebraniu danych
uint32_t message[150];
char *endXarg;
int FireFlag;
long long int target_Xaxis, target_Yaxis;
uint8_t optoelectric_sensor_handler[3];
motor_str motorA,motorB;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USB_DEVICE_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	L298N_5AD_init(&htim2); //motor init
	L298N_5AD_init(&htim4); //motor init
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
	PID_Init(&motorA, MOTOR_A_Kp, MOTOR_A_Ki, MOTOR_A_Kd, 0, 999); //enter values kp,ki,kd into PID contoller
	PID_Init(&motorB, MOTOR_A_Kp, MOTOR_A_Ki, MOTOR_A_Kd, 0, 999); //enter values kp,ki,kd into PID contoller
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
		motor_update_count(&motorA,&htim1); // tick counting encoder for motor A
		motor_update_count(&motorB,&htim3); // tick counting encoder for motor B
		receive_usb_message(&target_Xaxis, &target_Yaxis); //recive message form CDC USB
		PID_calculate(&motorA); // pid calculate algorithm for motor A
		PID_calculate(&motorB); // pid calculate algorithm for motor B
		L298N_5AD_set_motor(&motorA,&htim2); // set PWM motor A
		L298N_5AD_set_motor(&motorA,&htim4); // set pwm motor B
		motorA.set_target = target_Xaxis; //
		motorB.set_target = target_Yaxis;
		sprintf(message, "EC(A):%d PWM(A):%d Target(A):%d Direction(A):%d\n\rEC(B):%d PWM(B):%d Target(B):%d Direction(B):%d\n\r",(int) motorA.pulse_count, (int) motorA.actual_PWM, (int)motorA.set_target,(int) motorA.motorDirection,(int) motorB.pulse_count, (int) motorB.actual_PWM, (int)motorB.set_target,(int) motorB.motorDirection);
		CDC_Transmit_FS(message, strlen(message));
		//sprintf(message, "EC(B):%d PWM(B):%d Target(B):%d Direction(B):%d\n\r",(int) motorB.pulse_count, (int) motorB.actual_PWM, (int)motorB.set_target,(int) motorB.motorDirection);
		//CDC_Transmit_FS(message, strlen(message));
		HAL_Delay(100);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void receive_usb_message(long long int *x, int *y) {
	if (ReceivedDataFlag == 1) {
		ReceivedDataFlag = 0;
		if (ReceivedData[0] == 'X' && strstr(ReceivedData, "Y")) {
			*x = strtol(ReceivedData + 1, &endXarg, 10);
			*y = strtol(endXarg + 1, NULL, 10);
			sprintf(message, "OK X=%d Y=%d\n\r", *x, *y);
		} else if (ReceivedData[0] == 'C') {
			//calibrate motor function not added yet
			sprintf(message, "Calibration in progress...");
		} else if (ReceivedData[0] == 'F') {
			FireFlag++;
			sprintf(message, "OK");
		} else {
			sprintf(message, "BAD_SYNTAX!");
		}
		CDC_Transmit_FS(message, strlen(message));
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

