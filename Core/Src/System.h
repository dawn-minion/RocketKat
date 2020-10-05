#include <stdint.h>

class SystemClass {
private:
	uint16_t light = 0;
	float temperature = 0;
	uint32_t adcData[2] = {};
	bool dmaInProgress = false;

public:
	void dmaComplete();
	void init();
	void getData();
	uint16_t getLightValue();
	float getTemperature();
};

extern SystemClass System;
