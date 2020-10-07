#pragma once

#include <stdint.h>

class Sprite {
private:
	int x = 0, y = 0;
	int height = 0, width = 0;
	uint16_t *imageData = nullptr;
	uint16_t transparency = 0;

public:
	Sprite();
	Sprite(uint16_t transparency, uint16_t *data, int height, int width);
	void setPosition(int x, int y);
	int getX();
	int getY();
	int getHeight();
	int getWidth();
	bool withinBounds(int x, int y);
	bool isCollision(Sprite& sprite);
	uint16_t getPixelAt(int x, int y);
	bool isTransparent(int x, int y);
};
