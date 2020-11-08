#include "Player.h"
#include "playerImage.h"
#include "System.h"
#include "Display.h"
#include "Asteroid.h"
#include <math.h>
#include <string.h>

Player::Player() :
        Sprite(0xFFFF, shipImage, 16, 16) {
    setPosition(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
    memcpy(shipImage, reinterpret_cast<const uint16_t*>(playerImage.pixel_data), sizeof shipImage);
}

void Player::rotate()
{
    const uint16_t* originalImage = reinterpret_cast<const uint16_t*>(playerImage.pixel_data);
    const float sinx = sin(rotationAngle/180.0 * M_PI);
    const float cosx = cos(rotationAngle/180.0 * M_PI);
    const int xCenter = 8;
    const int yCenter = 8;

    for (int x=0;x<16;x++) {
        int xt = x - xCenter;

        float xtCosx = xt * cosx;
        float xtSinx = xt * sinx;

        for (int y=0;y<16;y++) {
            int yt = y - yCenter;
            int xRotate = round(xtCosx - (yt*sinx)) + xCenter;
            int yRotate = round((yt*cosx) + xtSinx) + yCenter;

            if ((xRotate >= 0) && (xRotate < 16) && (yRotate >= 0) && yRotate < 16) {
                shipImage[(x * 16) + y] = originalImage[(xRotate * 16) + yRotate];
            } else {
                shipImage[(x * 16) + y] = 0xFFFF;
            }
        }
    }
}

void Player::tick(Sprite** asteroids, size_t count) {
    Sprite::tick();

    if (System.buttonIsPressed(Buttons::Up) && yVel > -3.f) {
        yVel -= 0.001f * cosf(rotationAngle/180.0f * M_PI);
        xVel += 0.001f * sinf(rotationAngle/180.0f * M_PI);
    } else if (System.buttonIsPressed(Buttons::Down) && yVel < 3.f) {
        yVel += 0.001f * cosf(rotationAngle/180.0f * M_PI);
        xVel -= 0.001f * sinf(rotationAngle/180.0f * M_PI);
    }
    if (System.buttonIsPressed(Buttons::Left)) {
        rotationAngle -= 0.3f;
        rotate();
    } else if (System.buttonIsPressed(Buttons::Right)) {
        rotationAngle += 0.3f;
        rotate();
    }
    if (System.buttonIsPressed(Buttons::B) && HAL_GetTick() - lastBulletTime > 250) {
        Bullet* bullet = getNextBullet();

        if (bullet != nullptr) {
            lastBulletTime = HAL_GetTick();

            bullet->start(
                getX(),
                getY(),
                0.2f * sinf(rotationAngle/180.0f * M_PI),
                -0.2f * cosf(rotationAngle/180.0f * M_PI)
            );
        }
    }

    if (rotationAngle > 360 || rotationAngle < -360) {
        rotationAngle = 0.f;
    }

    for (auto &bullet : bullets) {
        if (!bullet.isAlive()) {
            continue;
        }

        for (size_t i = 0; i < count; i++) {
            if (asteroids[i]->isAlive() && bullet.isCollision(*asteroids[i])) {
                static_cast<Asteroid*>(asteroids[i])->destroy();
                bullet.destroy();
                break;
            }
        }
        bullet.tick();
    }
}

void Player::loadSprites(Sprite** sprites){
    for (size_t i=0; i< bullets.size(); i++) {
        sprites[i] = &bullets[i];
    }
}

Bullet* Player::getNextBullet() {
    for (size_t i = 0; i < bullets.size(); i++) {
        if (!bullets[i].isAlive()) {
            return &bullets[i];
        }
    }

    return nullptr;
}
