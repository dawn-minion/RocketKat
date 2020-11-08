#include "asteroidimage.h"
#include "Asteroid.h"
#include "System.h"
#include "Display.h"

Asteroid::Asteroid() :
    Sprite(0x0000, (uint16_t*)asteroid_image.pixel_data, 32, 32) {
    auto posX = System.randInRange(DISPLAY_WIDTH);
    auto posY = System.randInRange(DISPLAY_HEIGHT);

    setPosition(posX, posY);

    auto startVelX = System.randInRange(50);
    auto startVelY = System.randInRange(50);
    auto negateX = System.randInRange(2);
    auto negateY = System.randInRange(2);

    xVel = (negateX ? startVelX * -1 : startVelX) / 1000.f;
    yVel = (negateY ? startVelY * -1 : startVelY) / 1000.f;
}
