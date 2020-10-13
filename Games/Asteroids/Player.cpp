#include "Player.h"
#include "playerImage.h"
#include "System.h"
#include "Display.h"
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

void Player::tick() {
    if (System.buttonIsPressed(Buttons::Up) && yVel > -3.f) {
        yVel -= 0.001 * cos(rotationAngle/180.0 * M_PI);
        xVel += 0.001 * sin(rotationAngle/180.0 * M_PI);
    } else if (System.buttonIsPressed(Buttons::Down) && yVel < 3.f) {
        yVel += 0.001 * cos(rotationAngle/180.0 * M_PI);
        xVel -= 0.001 * sin(rotationAngle/180.0 * M_PI);
    }
    if (System.buttonIsPressed(Buttons::Left)) {
        rotationAngle -= 0.3;
        rotate();
    } else if (System.buttonIsPressed(Buttons::Right)) {
        rotationAngle += 0.3;
        rotate();
    }

    if (rotationAngle > 360 || rotationAngle < -360) {
        rotationAngle = 0.f;
    }

    if (getY() >= DISPLAY_HEIGHT) {
        setPosition(getX(), 1);
    } else if (getY() <= 0) {
        setPosition(getX(), DISPLAY_HEIGHT - 1);
    }
    if (getX() >= DISPLAY_WIDTH) {
        setPosition(1, getY());
    } else if (getX() <= 0) {
        setPosition(DISPLAY_WIDTH - 1, getY());
    }
}
