#pragma once

#include <stdint.h>

class Sprite {
protected:
	int x = 0, y = 0;
	int xVel = 0, yVel = 0;
	int height = 0, width = 0;
	const uint16_t *imageData = nullptr;
	uint16_t transparency = 0;

public:
	Sprite(uint16_t transparency, const uint16_t *data, int height, int width);
	void setPosition(int x, int y);
	int getX() __attribute__((pure));
	int getY() __attribute__((pure));
	int getHeight() __attribute__((pure));
	int getWidth() __attribute__((pure));
	bool withinBounds(int x, int y) __attribute__((pure));
	bool isCollision(Sprite& sprite) __attribute__((pure));
	uint16_t getPixelAt(int x, int y) __attribute__((pure));
	bool isTransparent(int x, int y) __attribute__((pure));
	void tick();
};
