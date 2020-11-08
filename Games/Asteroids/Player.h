#pragma once

#include "Sprite.h"
#include "System.h"
#include "Bullet.h"
#include <array>

class Player : public Sprite {
private:
    int lastTick = 0;
    uint32_t lastBulletTime = 0;
    Buttons lastBtn;
    float rotationAngle = 0.f;
    uint16_t shipImage[16*16];
    std::array<Bullet, 5> bullets;

    void rotate();
public:
    Player();
    void tick(Sprite** asteroids, size_t count);
    constexpr size_t numBullets() { return bullets.size(); }
    void loadSprites(Sprite** sprites);
    Bullet* getNextBullet();
};
