#pragma once

#include <stdint.h>

class MPUClass {
private:
	const uint16_t deviceAddress = 0x68;
	const uint8_t intPinConfigReg = 0x37;
	const uint8_t intEnableReg = 0x38;
	const uint8_t userCtrlReg = 0x6A;
	const uint8_t accelReg = 0x3B;
	uint8_t dmaData[14] = {};
	int16_t accelX = 0, accelY = 0, accelZ = 0;
	int16_t gyroX = 0, gyroY = 0, gyroZ = 0;

	void startRead();

public:
	void init();
	void readData();
	void getAccelData(int16_t& x, int16_t& y, int16_t& z);
	void getGyroData(int16_t& x, int16_t& y, int16_t& z);
};

extern MPUClass MPU6050; 
