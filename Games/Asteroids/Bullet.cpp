#include "bulletimage.h"
#include "Bullet.h"
#include "System.h"
#include "stm32f4xx_hal.h"

Bullet::Bullet() :
    Sprite(0x0000, (uint16_t*)bullet_image.pixel_data, 32, 32) {
    alive = false;
}

void Bullet::start(int x, int y, float xVel, float yVel) {
    startTick = HAL_GetTick();

    setPosition(x, y);
    alive = true;

    this->xVel = xVel;
    this->yVel = yVel;
}

void Bullet::tick() {
    if (!alive) {
        return;
    }

    if (HAL_GetTick() - startTick > lifetimeTicks) {
        destroy();
        return;
    }

    Sprite::tick();
}
