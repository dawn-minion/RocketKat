#include "Asteroids.h"
#include "Sprite.h"
#include "Player.h"
#include "Asteroid.h"
#include "Display.h"
#include "stm32f4xx_hal.h"

void Asteroids::play() {
    Player player;
    Asteroid asteroid1, asteroid2, asteroid3;

    Sprite *sprites[4] = {&player, &asteroid1, &asteroid2, &asteroid3};

    uint32_t lastTick = HAL_GetTick();

    while (1) {
        if (HAL_GetTick() >= lastTick + 2) {
            player.tick();
            asteroid1.tick();
            asteroid2.tick();
            asteroid3.tick();

            display.draw(&sprites[0], sizeof (sprites) / sizeof (sprites[0]));
            lastTick = HAL_GetTick();
        }
    }
}
