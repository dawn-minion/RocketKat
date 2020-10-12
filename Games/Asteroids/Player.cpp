#include "Player.h"
#include "playerImage.h"
#include "System.h"
#include "Display.h"

Player::Player() :
        Sprite(0xFFFF, reinterpret_cast<const uint16_t*>(playerImage.pixel_data), 16, 16) {
    setPosition(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
}

void Player::tick() {
    if (System.buttonIsPressed(Buttons::Up) && yVel > -3.f) {
        yVel -= 0.001;
    } else if (System.buttonIsPressed(Buttons::Down) && yVel < 3.f) {
        yVel += 0.001;
    }

    if (getY() >= DISPLAY_HEIGHT) {
        setPosition(getX(), 1);
    } else if (getY() <= 0) {
        setPosition(getX(), DISPLAY_HEIGHT - 1);
    }
}
