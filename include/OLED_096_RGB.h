#ifndef OLED_096_RGB_H
#define OLED_096_RGB_H

#include <Arduino.h>
#include <SPI.h>
#include <stdint.h>

class OLED_096_RGB {
public:
    static constexpr uint8_t WIDTH = 64;
    static constexpr uint8_t HEIGHT = 128;

    static constexpr uint16_t RED = 0xF800;
    static constexpr uint16_t GREEN = 0x07E0;
    static constexpr uint16_t BLUE = 0x001F;
    static constexpr uint16_t BLACK = 0x0000;
    static constexpr uint16_t WHITE = 0xFFFF;
    static constexpr uint16_t YELLOW = 0xFFE0;

    OLED_096_RGB(int8_t cs = 5, int8_t dc = 17, int8_t rst = 16,
                 int8_t sck = 18, int8_t mosi = 23);

    bool begin();
    void clear(uint16_t color = BLACK);
    void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color);
    void drawPixel(uint8_t x, uint8_t y, uint16_t color);
    void blit(const uint16_t *buffer);

private:
    static constexpr uint8_t COL_OFFSET = 0x20;
    static constexpr uint32_t SPI_HZ = 8000000;

    int8_t _cs;
    int8_t _dc;
    int8_t _rst;
    int8_t _sck;
    int8_t _mosi;
    SPISettings _spi;

    void reset();
    void initReg();
    void writeCommand(uint8_t cmd);
    void writeData(uint8_t data);
    void writeDataBuffer(const uint8_t *data, size_t len);
    void setWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
    void beginRamWrite();
    void fillWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color);
};

#endif
