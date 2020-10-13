#pragma once

#include "Sprite.h"
#include "System.h"

class Player : public Sprite {
private:
    int lastTick = 0;
    Buttons lastBtn;
    float rotationAngle = 0.f;
    uint16_t shipImage[16*16];

    void rotate();
public:
    Player();
    void tick();
};
