#include "MPU.h"
#include "main.h"
#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;

void MPUClass::init() {
	uint8_t reset = 1 << 7;
	HAL_I2C_Mem_Write(&hi2c1, deviceAddress, 0x6B, 1, &reset, 1, 1000);

	HAL_Delay(50);

	// Hold interrupt until read - clear on any read - active high - push pull output
	uint8_t intPinConfig = 0x20;
	HAL_I2C_Mem_Write(&hi2c1, deviceAddress, intPinConfigReg, 1, &intPinConfig, 1, 1000);
	
	// 5Hz update
	uint8_t accelConfig = 0x1;
	HAL_I2C_Mem_Write(&hi2c1, deviceAddress, accelConfigReg, 1, &accelConfig, 1, 1000);
	
	// Interrupt only on new data ready
	uint8_t intEnableConfig = 0x1;
	HAL_I2C_Mem_Write(&hi2c1, deviceAddress, intEnableReg, 1, &intEnableConfig, 1, 1000);

	readData();
}

void MPUClass::readData() {
	if (!dmaInProgress) {
		dmaInProgress = true;
		HAL_I2C_Mem_Read_DMA(&hi2c1, deviceAddress, accelReg, 14, dmaData, sizeof dmaData);
	}
}

void MPUClass::dmaComplete() {
	dmaInProgress = false;

	const int16_t* dmaConvData = reinterpret_cast<int16_t*>(dmaData);

	accelX = dmaConvData[0];
	accelY = dmaConvData[1];
	accelZ = dmaConvData[2];

	dieTemp = (dmaConvData[3] / 340) + 37;

	gyroX = dmaConvData[4];
	gyroY = dmaConvData[5];
	gyroZ = dmaConvData[6];
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == AccelInt_Pin) {
		MPU6050.readData();
	}
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	if (hi2c == &hi2c1) {
		MPU6050.dmaComplete();
	}
}

MPUClass MPU6050;
