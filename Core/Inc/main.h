/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#define AccelInt_Pin GPIO_PIN_14
#define AccelInt_GPIO_Port GPIOC
#define AccelInt_EXTI_IRQn EXTI15_10_IRQn
#define LightSensor_Pin GPIO_PIN_2
#define LightSensor_GPIO_Port GPIOC
#define BtnB_Pin GPIO_PIN_3
#define BtnB_GPIO_Port GPIOC
#define BtnDown_Pin GPIO_PIN_5
#define BtnDown_GPIO_Port GPIOA
#define BtnUp_Pin GPIO_PIN_6
#define BtnUp_GPIO_Port GPIOA
#define BtnLeft_Pin GPIO_PIN_7
#define BtnLeft_GPIO_Port GPIOA
#define Temperature_Pin GPIO_PIN_5
#define Temperature_GPIO_Port GPIOC
#define FlashCS_Pin GPIO_PIN_1
#define FlashCS_GPIO_Port GPIOB
#define BtnRight_Pin GPIO_PIN_2
#define BtnRight_GPIO_Port GPIOB
#define DisplayRst_Pin GPIO_PIN_10
#define DisplayRst_GPIO_Port GPIOB
#define DisplayCS_Pin GPIO_PIN_12
#define DisplayCS_GPIO_Port GPIOB
#define SDDetect_Pin GPIO_PIN_8
#define SDDetect_GPIO_Port GPIOC
#define DisplayDC_Pin GPIO_PIN_8
#define DisplayDC_GPIO_Port GPIOA
#define SDCS_Pin GPIO_PIN_15
#define SDCS_GPIO_Port GPIOA
#define DisplayBL_Pin GPIO_PIN_3
#define DisplayBL_GPIO_Port GPIOB
#define LED_Pin GPIO_PIN_4
#define LED_GPIO_Port GPIOB
#define BtnA_Pin GPIO_PIN_9
#define BtnA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
