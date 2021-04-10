/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define VSENSE_Pin GPIO_PIN_0
#define VSENSE_GPIO_Port GPIOA
#define TSENSE_Pin GPIO_PIN_1
#define TSENSE_GPIO_Port GPIOA
#define MOVINT2_Pin GPIO_PIN_2
#define MOVINT2_GPIO_Port GPIOA
#define MOVINT1_Pin GPIO_PIN_3
#define MOVINT1_GPIO_Port GPIOA
#define IRON_PWM_Pin GPIO_PIN_4
#define IRON_PWM_GPIO_Port GPIOA
#define LEDCLK_Pin GPIO_PIN_5
#define LEDCLK_GPIO_Port GPIOA
#define NOTUSED_Pin GPIO_PIN_6
#define NOTUSED_GPIO_Port GPIOA
#define LEDDATA_Pin GPIO_PIN_7
#define LEDDATA_GPIO_Port GPIOA
#define BTNC_Pin GPIO_PIN_1
#define BTNC_GPIO_Port GPIOB
#define BTN1_Pin GPIO_PIN_9
#define BTN1_GPIO_Port GPIOA
#define BTN2_Pin GPIO_PIN_10
#define BTN2_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
