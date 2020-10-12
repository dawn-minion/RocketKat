#include <memory>
#include "Asteroids.h"
#include "Sprite.h"
#include "Player.h"
#include "Display.h"
#include "vector"
#include "stm32f4xx_hal.h"

void Asteroids::play() {
    std::vector<std::unique_ptr<Sprite>> sprites;

    sprites.push_back(std::make_unique<Player>());

    uint32_t lastTick = HAL_GetTick();

    while (1) {
        if (HAL_GetTick() != lastTick) {
            static_cast<Player*>(sprites[0].get())->tick();

            for (auto &sprite : sprites) {
                sprite->tick();
            }

            display.draw(sprites);
            lastTick = HAL_GetTick();
        }
    }
}
