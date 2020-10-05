#include "System.h"
#include "stm32f4xx_hal.h"
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

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	System.getData();
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
	System.dmaComplete();
}

SystemClass System;
