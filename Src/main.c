/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
uint8_t segmentA = 0;
uint8_t segmentB = 0;
uint8_t segmentC = 0;
uint8_t segmentD = 0;
uint8_t segmentE = 0;
uint8_t segmentF = 0;
uint8_t segmentG = 0;


uint8_t numbers[10][7] = {
	{1,1,1,1,1,1,0},
	{0,1,1,0,0,0,0},
	{1,1,0,1,1,0,1},
	{1,1,1,1,0,0,1},
	{0,1,1,0,0,1,1},
	{1,0,1,1,0,1,1},
	{1,0,1,1,1,1,1},
	{1,1,1,0,0,0,0},
	{1,1,1,1,1,1,1},
	{1,1,1,1,0,1,1}
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void sendNumberToDisplay(uint8_t, uint8_t);
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
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim6);
	uint8_t segment = 1;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
		switch(segment) {
			case 0:
				sendNumberToDisplay(segmentG, segment);
				segment = 1;
				break;
			case 1:
				sendNumberToDisplay(segmentF, segment);
				segment = 2;
				break;
			case 2:
				sendNumberToDisplay(segmentE, segment);
				segment = 3;
				break;
			case 3:
				sendNumberToDisplay(segmentD, segment);
				segment = 4;
				break;
			case 4:
				sendNumberToDisplay(segmentC, segment);
				segment = 5;
				break;
			case 5:
				sendNumberToDisplay(segmentB, segment);
				segment = 6;
				break;
			case 6:
				sendNumberToDisplay(segmentA, segment);
				segment = 0;
		}
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV4;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void sendNumberToDisplay(uint8_t number, uint8_t segment) 
{
	HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(D0_GPIO_Port, D0_Pin, (numbers[number][0] == 1 ? GPIO_PIN_SET: GPIO_PIN_RESET));
	HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, (numbers[number][1] == 1 ? GPIO_PIN_SET: GPIO_PIN_RESET));
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, (numbers[number][2] == 1 ? GPIO_PIN_SET: GPIO_PIN_RESET));
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, (numbers[number][3] == 1 ? GPIO_PIN_SET: GPIO_PIN_RESET));
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, (numbers[number][4] == 1 ? GPIO_PIN_SET: GPIO_PIN_RESET));
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, (numbers[number][5] == 1 ? GPIO_PIN_SET: GPIO_PIN_RESET));
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, (numbers[number][6] == 1 ? GPIO_PIN_SET: GPIO_PIN_RESET));
	if (segment == 1 || segment == 3)
	{
		HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, GPIO_PIN_RESET);
	}
	
	HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, ((segment & 0x01) == 0x01 ? GPIO_PIN_SET: GPIO_PIN_RESET));
	HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, ((segment & 0x02) == 0x02 ? GPIO_PIN_SET: GPIO_PIN_RESET));
	HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, ((segment & 0x04) == 0x04 ? GPIO_PIN_SET: GPIO_PIN_RESET));
	
	HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);
	
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	segmentA++;
	
	if (segmentA >= 10) {
			segmentA = 0;
			segmentB++;
	}
	
	if (segmentB >= 10) {
			segmentB = 0;
			segmentC++;
	}
	
	if (segmentC >= 10) {
			segmentC = 0;
			segmentD++;
	}
	
	if (segmentD >= 10) {
			segmentD = 0;
			segmentE++;
	}
	
	if (segmentE >= 6) {
			segmentE = 0;
			segmentF++;
	}
	
	if (segmentF >= 10) {
			segmentF = 0;
			segmentG++;
	}
	
	if (segmentG >= 6) {
			segmentG = 0;
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
