#include "Sprite.h"
#include <string.h>

Sprite::Sprite() {
	memset(imageData, 0, sizeof imageData);
}

Sprite::Sprite(uint16_t transparency, uint16_t data[16*16]) {
	this->transparency = transparency;
	memcpy(imageData, data, sizeof imageData);
}

void Sprite::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

int Sprite::getX() {
	return x;
}

int Sprite::getY() {
	return y;
}

uint16_t Sprite::getPixelAt(int x, int y) {
	return imageData[(x + (y * 16))];
}

bool Sprite::isTransparent(int x, int y) {
	return getPixelAt(x, y) == transparency;
}
