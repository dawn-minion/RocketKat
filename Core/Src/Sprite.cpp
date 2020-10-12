#include "Sprite.h"
#include <string.h>

Sprite::Sprite(uint16_t transparency, const uint16_t* data, int height, int width) {
	this->transparency = transparency;
	imageData = data;
	this->height = height;
	this->width = width;
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
	if (x > this->width || y > this->height) {
		return 0;
	}

	return imageData[(x + (y * 16))];
}

bool Sprite::isTransparent(int x, int y) {
	return getPixelAt(x, y) == transparency;
}

bool Sprite::withinBounds(int x, int y) {
	return x > (this->x - (width / 2)) && x < (this->x + (width / 2)) &&
		   y > (this->y - (height / 2)) && y < (this->y + (height / 2));
}

bool Sprite::isCollision(Sprite& sprite) {
	return sprite.withinBounds(getX() - (getWidth() / 2), getY() + (getHeight() / 2)) ||
		   sprite.withinBounds(getX() + (getWidth() / 2), getY() + (getHeight() / 2)) ||
		   sprite.withinBounds(getX() - (getWidth() / 2), getY() - (getHeight() / 2)) ||
		   sprite.withinBounds(getX() + (getWidth() / 2), getY() - (getHeight() / 2));
}

int Sprite::getHeight() {
	return height;
}

int Sprite::getWidth() {
	return width;
}

void Sprite::tick() {
	setPosition(getX() + xVel, getY() + yVel);
}
