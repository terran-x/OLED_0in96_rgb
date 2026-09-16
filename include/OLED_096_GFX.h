#ifndef OLED_096_GFX_H
#define OLED_096_GFX_H

#include <Adafruit_GFX.h>
#include "OLED_096_RGB.h"

class OLED_096_GFX : public Adafruit_GFX {
public:
    explicit OLED_096_GFX(OLED_096_RGB &oled);

    void drawPixel(int16_t x, int16_t y, uint16_t color) override;
    void fillScreen(uint16_t color) override;
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override;
    void writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override;
    void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) override;
    void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) override;

private:
    OLED_096_RGB &_oled;

    void mapToNative(int16_t &x, int16_t &y) const;
};

#endif
