#include "OLED_096_GFX.h"

#include <utility>

OLED_096_GFX::OLED_096_GFX(OLED_096_RGB &oled)
    : Adafruit_GFX(OLED_096_RGB::WIDTH, OLED_096_RGB::HEIGHT), _oled(oled) {}

void OLED_096_GFX::mapToNative(int16_t &x, int16_t &y) const {
    switch (rotation) {
    case 1:
        std::swap(x, y);
        x = WIDTH - 1 - x;
        break;
    case 2:
        x = WIDTH - 1 - x;
        y = HEIGHT - 1 - y;
        break;
    case 3:
        std::swap(x, y);
        y = HEIGHT - 1 - y;
        break;
    default:
        break;
    }
}

void OLED_096_GFX::drawPixel(int16_t x, int16_t y, uint16_t color) {
    if ((x < 0) || (y < 0) || (x >= _width) || (y >= _height)) {
        return;
    }

    mapToNative(x, y);
    _oled.drawPixel(static_cast<uint8_t>(x), static_cast<uint8_t>(y), color);
}

void OLED_096_GFX::fillScreen(uint16_t color) {
    _oled.clear(color);
}

void OLED_096_GFX::writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    fillRect(x, y, w, h, color);
}

void OLED_096_GFX::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    if (w <= 0 || h <= 0) {
        return;
    }

    if (x < 0) {
        w += x;
        x = 0;
    }
    if (y < 0) {
        h += y;
        y = 0;
    }
    if ((x >= _width) || (y >= _height)) {
        return;
    }
    if (x + w > _width) {
        w = _width - x;
    }
    if (y + h > _height) {
        h = _height - y;
    }
    if (w <= 0 || h <= 0) {
        return;
    }

    int16_t x0 = x;
    int16_t y0 = y;
    int16_t x1 = x + w - 1;
    int16_t y1 = y + h - 1;
    mapToNative(x0, y0);
    mapToNative(x1, y1);

    if (x0 > x1) {
        std::swap(x0, x1);
    }
    if (y0 > y1) {
        std::swap(y0, y1);
    }

    _oled.fillRect(static_cast<uint8_t>(x0), static_cast<uint8_t>(y0),
                   static_cast<uint8_t>(x1 - x0 + 1), static_cast<uint8_t>(y1 - y0 + 1),
                   color);
}

void OLED_096_GFX::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    fillRect(x, y, 1, h, color);
}

void OLED_096_GFX::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    fillRect(x, y, w, 1, color);
}
