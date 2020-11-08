#include "Sprite.h"
#include "Display.h"
#include <string.h>

Sprite::Sprite(uint16_t transparency, const uint16_t* data, int height, int width) {
	this->transparency = transparency;
	imageData = data;
	this->height = height;
	this->width = width;
}

void Sprite::setPosition(float x, float y) {
	this->x = x;
	this->y = y;
}

int Sprite::getX() {
	return x;
}

int Sprite::getY() {
	return y;
}

float Sprite::getXf() {
	return x;
}

float Sprite::getYf() {
	return y;
}

uint16_t Sprite::getPixelAt(int x, int y) {
	if (x > this->width || y > this->height) {
		return 0;
	}

	return imageData[(x + (y * this->width))];
}

bool Sprite::isTransparent(int x, int y) {
	return getPixelAt(x, y) == transparency;
}

bool Sprite::withinBounds(int x, int y) {
	return x > (this->x - (width / 2)) && x < (this->x + (width / 2)) &&
		   y > (this->y - (height / 2)) && y < (this->y + (height / 2));
}

bool Sprite::isCollision(Sprite& sprite) {
	auto centerX = getWidth() / 2;
	auto centerY = getHeight() / 2;
	bool withinBox = sprite.withinBounds(getX() - centerX, getY() + centerY) ||
		   sprite.withinBounds(getX() + centerX, getY() + centerY) ||
		   sprite.withinBounds(getX() - centerX, getY() - centerY) ||
		   sprite.withinBounds(getX() + centerX, getY() - centerY);

	if (withinBox) {
		for (int x = 0; x < getWidth(); x++) {
			for (int y = 0; y < getHeight(); y++) {
				if (isTransparent(x, y)) {
					continue;
				}

				int windowX = getX() - centerX + x;
				int windowY = getY() - centerY + y;
				int otherX = sprite.getX() - windowX + sprite.getWidth() / 2;
				int otherY = sprite.getY() - windowY + sprite.getHeight() / 2;

				if (otherX >= 0 && otherX < sprite.getWidth() &&
					otherY >= 0 && otherY < sprite.getHeight() &&
					!sprite.isTransparent(otherX, otherY)) {
					return true;
				}
			}
		}
	}

	return false;
}

int Sprite::getHeight() {
	return height;
}

int Sprite::getWidth() {
	return width;
}

void Sprite::tick() {
	setPosition(getXf() + xVel, getYf() + yVel);

    if (getY() >= DISPLAY_HEIGHT) {
        setPosition(getX(), 1);
    } else if (getY() <= 0) {
        setPosition(getX(), DISPLAY_HEIGHT - 1);
    }
    if (getX() >= DISPLAY_WIDTH) {
        setPosition(1, getY());
    } else if (getX() <= 0) {
        setPosition(DISPLAY_WIDTH - 1, getY());
    }
}

bool Sprite::isAlive() {
	return alive;
}

void Sprite::destroy() {
    xVel = 0;
    yVel = 0;
    alive = false;
}
