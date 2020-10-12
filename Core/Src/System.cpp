#include "System.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include <math.h>

extern ADC_HandleTypeDef hadc1;

void SystemClass::init() {
	HAL_ADC_Start_DMA(&hadc1, adcData, sizeof adcData / sizeof adcData[0]);
}

void SystemClass::dmaComplete() {
	float sensor = 4096.f * 10000 / static_cast<uint16_t>(adcData[0] >> 16) - 10000;
	temperature = (1.0 / ((logf(sensor / 10000) / 3300) + (1.0 / (25 + 273.5)))) - 273.5
;
	light = static_cast<uint16_t>(adcData[0] & 0xFFFF);

	dmaInProgress = false;
}

void SystemClass::getData() {
	if (!dmaInProgress) {
		HAL_ADC_Stop_DMA(&hadc1);
		HAL_ADC_Start_DMA(&hadc1, adcData, sizeof adcData / sizeof adcData[0]);
		dmaInProgress = true;
	}
}

bool SystemClass::buttonIsPressed(Buttons button) {
	switch(button) {
		case Buttons::A: {
			return static_cast<bool>(HAL_GPIO_ReadPin(BtnA_GPIO_Port, BtnA_Pin));
		}
		case Buttons::B: {
			return static_cast<bool>(HAL_GPIO_ReadPin(BtnB_GPIO_Port, BtnB_Pin));
		}
		case Buttons::Up: {
			return !static_cast<bool>(HAL_GPIO_ReadPin(BtnUp_GPIO_Port, BtnUp_Pin));
		}
		case Buttons::Down: {
			return !static_cast<bool>(HAL_GPIO_ReadPin(BtnDown_GPIO_Port, BtnDown_Pin));
		}
		case Buttons::Left: {
			return static_cast<bool>(HAL_GPIO_ReadPin(BtnLeft_GPIO_Port, BtnLeft_Pin));
		}
		case Buttons::Right: {
			return static_cast<bool>(HAL_GPIO_ReadPin(BtnRight_GPIO_Port, BtnRight_Pin));
		}
	}

	return false;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	System.getData();
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
	System.dmaComplete();
}

SystemClass System;
