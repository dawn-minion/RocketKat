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

    while (1) {
        static_cast<Player*>(sprites[0].get())->tick();

        for (auto &sprite : sprites) {
            sprite->tick();
        }

        display.draw(sprites);
        HAL_Delay(50);
    }
}
