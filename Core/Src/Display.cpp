#include <stdint.h>
#include <string.h>
#include "Display.h"
#include "stm32f4xx_hal.h"
#include "main.h"

#define DELAY 0x80
#define COL0(r, g, b) ((((r) >> 3) << 11) | (((g) >> 2) << 5) | ((b) >> 3))
#define COL(c) COL0((c >> 16) & 0xff, (c >> 8) & 0xff, c & 0xff)

const uint8_t font8[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x5e, 0x00, 0x00, 0x00, 
0x00, 0x0e, 0x00, 0x0e, 0x00, 0x00, 
0x28, 0xfe, 0x28, 0xfe, 0x28, 0x00, 
0x4c, 0x92, 0xff, 0x92, 0x64, 0x00, 
0x02, 0x65, 0x12, 0x48, 0xa6, 0x40, 
0x6c, 0x92, 0x92, 0x6c, 0xa0, 0x00, 
0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x7c, 0x82, 0x00, 0x00, 
0x00, 0x00, 0x82, 0x7c, 0x00, 0x00, 
0x54, 0x38, 0x10, 0x38, 0x54, 0x00, 
0x10, 0x10, 0x7c, 0x10, 0x10, 0x00, 
0x00, 0x00, 0x90, 0x70, 0x00, 0x00, 
0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 
0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 
0x00, 0x60, 0x10, 0x08, 0x06, 0x00, 
0x00, 0x3c, 0x42, 0x42, 0x3c, 0x00, 
0x00, 0x44, 0x7e, 0x40, 0x00, 0x00, 
0x00, 0x44, 0x62, 0x52, 0x4c, 0x00, 
0x00, 0x42, 0x4a, 0x4e, 0x32, 0x00, 
0x30, 0x28, 0x24, 0x7e, 0x20, 0x00, 
0x00, 0x4e, 0x4a, 0x4a, 0x32, 0x00, 
0x00, 0x3c, 0x4a, 0x4a, 0x30, 0x00, 
0x00, 0x02, 0x62, 0x12, 0x0e, 0x00, 
0x00, 0x34, 0x4a, 0x4a, 0x34, 0x00, 
0x00, 0x0c, 0x52, 0x52, 0x3c, 0x00, 
0x00, 0x00, 0x6c, 0x6c, 0x00, 0x00, 
0x00, 0x00, 0x96, 0x76, 0x00, 0x00, 
0x10, 0x28, 0x28, 0x44, 0x44, 0x00, 
0x28, 0x28, 0x28, 0x28, 0x28, 0x00, 
0x44, 0x44, 0x28, 0x28, 0x10, 0x00, 
0x00, 0x02, 0x59, 0x09, 0x06, 0x00, 
0x3c, 0x42, 0x5a, 0x56, 0x08, 0x00, 
0x78, 0x14, 0x12, 0x14, 0x78, 0x00, 
0x7e, 0x4a, 0x4a, 0x4a, 0x34, 0x00, 
0x00, 0x3c, 0x42, 0x42, 0x24, 0x00, 
0x00, 0x7e, 0x42, 0x42, 0x3c, 0x00, 
0x00, 0x7e, 0x4a, 0x4a, 0x42, 0x00, 
0x00, 0x7e, 0x0a, 0x0a, 0x02, 0x00, 
0x00, 0x3c, 0x42, 0x52, 0x34, 0x00, 
0x00, 0x7e, 0x08, 0x08, 0x7e, 0x00, 
0x00, 0x42, 0x7e, 0x42, 0x00, 0x00, 
0x20, 0x40, 0x42, 0x3e, 0x02, 0x00, 
0x00, 0x7e, 0x08, 0x14, 0x62, 0x00, 
0x00, 0x7e, 0x40, 0x40, 0x40, 0x00, 
0x7e, 0x04, 0x18, 0x04, 0x7e, 0x00, 
0x00, 0x7e, 0x04, 0x08, 0x7e, 0x00, 
0x3c, 0x42, 0x42, 0x42, 0x3c, 0x00, 
0x00, 0x7e, 0x12, 0x12, 0x0c, 0x00, 
0x00, 0x3c, 0x52, 0x62, 0xbc, 0x00, 
0x00, 0x7e, 0x12, 0x12, 0x6c, 0x00, 
0x00, 0x24, 0x4a, 0x52, 0x24, 0x00, 
0x02, 0x02, 0x7e, 0x02, 0x02, 0x00, 
0x00, 0x3e, 0x40, 0x40, 0x3e, 0x00, 
0x00, 0x1e, 0x70, 0x70, 0x1e, 0x00, 
0x7e, 0x20, 0x18, 0x20, 0x7e, 0x00, 
0x42, 0x24, 0x18, 0x24, 0x42, 0x00, 
0x06, 0x08, 0x70, 0x08, 0x06, 0x00, 
0x00, 0x62, 0x52, 0x4a, 0x46, 0x00, 
0x00, 0x7e, 0x42, 0x42, 0x00, 0x00, 
0x00, 0x06, 0x08, 0x10, 0x60, 0x00, 
0x00, 0x42, 0x42, 0x7e, 0x00, 0x00, 
0x08, 0x04, 0x02, 0x04, 0x08, 0x00, 
0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 
0x00, 0x00, 0x02, 0x04, 0x00, 0x00, 
0x00, 0x30, 0x48, 0x48, 0x78, 0x00, 
0x00, 0x7e, 0x48, 0x48, 0x30, 0x00, 
0x00, 0x30, 0x48, 0x48, 0x48, 0x00, 
0x00, 0x30, 0x48, 0x48, 0x7e, 0x00, 
0x00, 0x30, 0x68, 0x58, 0x50, 0x00, 
0x00, 0x10, 0x7c, 0x12, 0x04, 0x00, 
0x00, 0x18, 0xa4, 0xa4, 0x78, 0x00, 
0x00, 0x7e, 0x08, 0x08, 0x70, 0x00, 
0x00, 0x48, 0x7a, 0x40, 0x00, 0x00, 
0x00, 0x40, 0x84, 0x7d, 0x00, 0x00, 
0x00, 0x7e, 0x10, 0x28, 0x40, 0x00, 
0x00, 0x42, 0x7e, 0x40, 0x00, 0x00, 
0x78, 0x08, 0x30, 0x08, 0x70, 0x00, 
0x00, 0x78, 0x08, 0x08, 0x70, 0x00, 
0x00, 0x30, 0x48, 0x48, 0x30, 0x00, 
0x00, 0xfc, 0x24, 0x24, 0x18, 0x00, 
0x00, 0x18, 0x24, 0x24, 0xfc, 0x00, 
0x00, 0x78, 0x10, 0x08, 0x10, 0x00, 
0x00, 0x50, 0x58, 0x68, 0x28, 0x00, 
0x00, 0x08, 0x3e, 0x48, 0x20, 0x00, 
0x00, 0x38, 0x40, 0x40, 0x78, 0x00, 
0x00, 0x18, 0x60, 0x60, 0x18, 0x00, 
0x38, 0x40, 0x30, 0x40, 0x38, 0x00, 
0x00, 0x48, 0x30, 0x30, 0x48, 0x00, 
0x00, 0x5c, 0xa0, 0xa0, 0x7c, 0x00, 
0x00, 0x48, 0x68, 0x58, 0x48, 0x00, 
0x00, 0x08, 0x36, 0x41, 0x00, 0x00, 
0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 
0x00, 0x41, 0x36, 0x08, 0x00, 0x00, 
0x00, 0x08, 0x04, 0x08, 0x04, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

extern SPI_HandleTypeDef hspi2;

uint8_t fb[168 * 128];

const uint16_t palette[] = {
    COL(0x000000), // 0
    COL(0xffffff), // 1
    COL(0xff2121), // 2
    COL(0xff93c4), // 3
    COL(0xff8135), // 4
    COL(0xfff609), // 5
    COL(0x249ca3), // 6
    COL(0x78dc52), // 7
    COL(0x003fad), // 8
    COL(0x87f2ff), // 9
    COL(0x8e2ec4), // 10
    COL(0xa4839f), // 11
    COL(0x5c406c), // 12
    COL(0xe5cdc4), // 13
    COL(0x91463d), // 14
    COL(0x000000), // 15
};

static const uint8_t initCmds[] = {
    ST7735_SWRESET,   DELAY,  //  1: Software reset, 0 args, w/delay
      120,                    //     150 ms delay
    ST7735_SLPOUT ,   DELAY,  //  2: Out of sleep mode, 0 args, w/delay
      120,                    //     500 ms delay
    ST7735_INVOFF , 0      ,  // 13: Don't invert display, no args, no delay
    ST7735_INVCTR , 1      ,  // inverse, riven
      0x03,
    ST7735_COLMOD , 1      ,  // 15: set color mode, 1 arg, no delay:
      0x05,                  //     16-bit color
    ST7735_GMCTRP1, 16      , //  1: Magical unicorn dust, 16 args, no delay:
      0x02, 0x1c, 0x07, 0x12,
      0x37, 0x32, 0x29, 0x2d,
      0x29, 0x25, 0x2B, 0x39,
      0x00, 0x01, 0x03, 0x10,
    ST7735_GMCTRN1, 16      , //  2: Sparkles and rainbows, 16 args, no delay:
      0x03, 0x1d, 0x07, 0x06,
      0x2E, 0x2C, 0x29, 0x2D,
      0x2E, 0x2E, 0x37, 0x3F,
      0x00, 0x00, 0x02, 0x10,
    ST7735_NORON  ,    DELAY, //  3: Normal display on, no args, w/delay
      10,                     //     10 ms delay
    ST7735_DISPON ,    DELAY, //  4: Main screen turn on, no args w/delay
      10,
    0, 0 // END
};

void Display::sendCmdSeq(const uint8_t *buf) {
    char cmdBuf[20] = {};
    while (*buf) {
        cmdBuf[0] = *buf++;
        int v = *buf++;
        int len = v & ~DELAY;
        // note that we have to copy to RAM
        memcpy(cmdBuf + 1, buf, len);
        sendCmd((uint8_t*)cmdBuf, len + 1);
        buf += len;
        if (v & DELAY) {
            HAL_Delay(*buf++);
        }
    }
}

void Display::setCS(bool value) {
    HAL_GPIO_WritePin(DisplayCS_GPIO_Port, DisplayCS_Pin, static_cast<GPIO_PinState>(value));
}

void Display::setDC(bool value) {
    HAL_GPIO_WritePin(DisplayDC_GPIO_Port, DisplayDC_Pin, static_cast<GPIO_PinState>(value));
}

void Display::setBacklight(bool value) {
    HAL_GPIO_WritePin(DisplayBL_GPIO_Port, DisplayBL_Pin, static_cast<GPIO_PinState>(value));
}

void Display::reset() {
    HAL_GPIO_WritePin(DisplayRst_GPIO_Port, DisplayRst_Pin, GPIO_PIN_RESET);
    HAL_Delay(20);
    HAL_GPIO_WritePin(DisplayRst_GPIO_Port, DisplayRst_Pin, GPIO_PIN_SET);
    HAL_Delay(20);
}

void Display::sendCmd(uint8_t* buf, int len) {
    this->setDC(0);
    this->setCS(0);

    auto result = HAL_SPI_Transmit(&hspi2, buf, 1, 1000);

    this->setDC(1);

    len--;
    buf++;
    if (len > 0) {
        result = HAL_SPI_Transmit(&hspi2, buf, len, 1000);
    }

    this->setCS(1);
}

void Display::configure(uint8_t madctl, uint32_t frmctr1) {
    uint8_t cmd0[] = {ST7735_MADCTL, madctl};
    uint8_t cmd1[] = {ST7735_FRMCTR1, (uint8_t)(frmctr1 >> 16), (uint8_t)(frmctr1 >> 8),
                      (uint8_t)frmctr1};
    this->sendCmd(cmd0, sizeof(cmd0));
    this->sendCmd(cmd1, cmd1[3] == 0xff ? 3 : 4);
}

void Display::setAddrWindow(int x, int y, int w, int h) {
    uint8_t cmd0[] = {ST7735_RASET, 0, (uint8_t)x, 0, (uint8_t)(x + w - 1)};
    uint8_t cmd1[] = {ST7735_CASET, 0, (uint8_t)y, 0, (uint8_t)(y + h - 1)};
    this->sendCmd(cmd1, sizeof(cmd1));
    this->sendCmd(cmd0, sizeof(cmd0));
}

void Display::printch(int x, int y, int col, const uint8_t *fnt) {
    for (int i = 0; i < 6; ++i) {
        uint8_t *p = fb + (x + i) * DISPLAY_HEIGHT + y;
        uint8_t mask = 0x01;
        for (int j = 0; j < 8; ++j) {
            if (*fnt & mask)
                *p = col;
            p++;
            mask <<= 1;
        }
        fnt++;
    }
}

void Display::draw() {
    char cmd[] = {ST7735_RAMWR};
    sendCmd(cmd, 1);

    this->setDC(1);
    this->setCS(0);

    uint8_t *p = fb;
    for (int i = 0; i < DISPLAY_WIDTH; ++i) {
        for (int j = 0; j < DISPLAY_HEIGHT; ++j) {
            uint16_t color = palette[*p++ & 0xf];
            uint8_t cc[] = {color >> 8, color & 0xff};
            HAL_SPI_Transmit(&hspi2, cc, 2, 1000);
        }
    }

    this->setCS(1);
}

void Display::print(int x, int y, int col, const char *text) {
    int x0 = x;
    while (*text) {
        char c = *text++;
        if (c == '\r')
            continue;
        if (c == '\n') {
            x = x0;
            y += 10;
            continue;
        }

        if (c < ' ')
            c = '?';
        if (c >= 0x7f)
            c = '?';
        c -= ' ';
        printch(x, y, col, &font8[c * 6]);
        x += 6;
    }
}

void drawBar(int y, int h, int c) {
    for (int x = 0; x < DISPLAY_WIDTH; ++x) {
        memset(fb + x * DISPLAY_HEIGHT + y, c, h);
    }
}

void Display::init() {
    setCS(1);
    setDC(1);
    reset();

    sendCmdSeq(initCmds);

    setBacklight(1);

    uint32_t cfg0 = 0x40;
    uint32_t frmctr1 = 0x16; 
    uint32_t palXOR = (cfg0 & 0x1000000) ? 0xffffff : 0x000000;
    uint32_t madctl = cfg0 & 0xff; // 64
    uint32_t offX = (cfg0 >> 8) & 0xff; // 0
    uint32_t offY = (cfg0 >> 16) & 0xff; // 0

    configure(madctl, frmctr1);
    setAddrWindow(offX, offY, DISPLAY_WIDTH, DISPLAY_HEIGHT);

    memset(fb, 0, sizeof fb);

    drawBar(0, 52, 7);
    drawBar(107, 14, 4);
    print(5, 70, 1, "Hallo!");
    print(3, 110, 1, "Hoe gaat het er mee?");
    draw();
}
