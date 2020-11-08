#pragma once

#include "Sprite.h"
#include <stdint.h>

class Bullet : public Sprite {
private:
    const unsigned int lifetimeTicks = 1000;
    uint32_t startTick = 0;
public:
    Bullet();
    void start(int x, int y, float xVel, float yVel);
    void tick();
};
