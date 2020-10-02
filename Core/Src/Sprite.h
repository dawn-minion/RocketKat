#pragma once

#include <stdint.h>

class Sprite {
private:
	int x, y;
	uint16_t imageData[16*16];
	uint16_t transparency;

public:
	Sprite();
	Sprite(uint16_t transparency, uint16_t data[16*16]);
	void setPosition(int x, int y);
	int getX();
	int getY();
	uint16_t getPixelAt(int x, int y);
	bool isTransparent(int x, int y);
};
