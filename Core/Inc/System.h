#include <stdint.h>
#include "main.h"

enum class Buttons {
	A,
	B,
	Up,
	Down,
	Left,
	Right
};

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
	bool buttonIsPressed(Buttons button);
};

extern SystemClass System;
