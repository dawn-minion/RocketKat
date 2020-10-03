#include "MPU.h"
#include "main.h"
#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;

void MPUClass::init() {
	// Hold interrupt until read - clear on any read - active high - push pull output
	uint8_t intPinConfig = 0x0C;
	HAL_I2C_Mem_Write(&hi2c1, deviceAddress, intPinConfigReg, 1, &intPinConfig, 1, 1000);
	
	// Interrupt only on new data ready
	uint8_t intEnableConfig = 0x01;
	HAL_I2C_Mem_Write(&hi2c1, deviceAddress, intEnableReg, 1, &intEnableConfig, 1, 1000);

	// Disable FIFO and external interfaces
	uint8_t userCtrlConfig = 0;
	HAL_I2C_Mem_Write(&hi2c1, deviceAddress, userCtrlReg, 1, &userCtrlConfig, 1, 1000);

	readData();
}

void MPUClass::readData() {
	HAL_I2C_Mem_Read_DMA(&hi2c1, deviceAddress, accelReg, 14, dmaData, sizeof dmaData);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == AccelInt_Pin) {
		MPU6050.readData();
	}
}

MPUClass MPU6050;
