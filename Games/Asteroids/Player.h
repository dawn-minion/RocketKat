#pragma once

#include "Sprite.h"
#include "System.h"

class Player : public Sprite {
private:
    int lastTick = 0;
    Buttons lastBtn;
public:
    Player();
    void tick();
};
