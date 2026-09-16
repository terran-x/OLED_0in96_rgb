#include "OLED_096_RGB.h"

OLED_096_RGB::OLED_096_RGB(int8_t cs, int8_t dc, int8_t rst, int8_t sck, int8_t mosi)
    : _cs(cs),
      _dc(dc),
      _rst(rst),
      _sck(sck),
      _mosi(mosi),
      _spi(SPI_HZ, MSBFIRST, SPI_MODE3) {}

bool OLED_096_RGB::begin() {
    pinMode(_cs, OUTPUT);
    pinMode(_dc, OUTPUT);
    pinMode(_rst, OUTPUT);
    digitalWrite(_cs, HIGH);
    digitalWrite(_dc, HIGH);

    SPI.begin(_sck, -1, _mosi, _cs);

    reset();
    initReg();
    delay(200);
    writeCommand(0xAF);
    return true;
}

void OLED_096_RGB::reset() {
    digitalWrite(_rst, HIGH);
    delay(100);
    digitalWrite(_rst, LOW);
    delay(100);
    digitalWrite(_rst, HIGH);
    delay(100);
}

void OLED_096_RGB::writeCommand(uint8_t cmd) {
    SPI.beginTransaction(_spi);
    digitalWrite(_dc, LOW);
    digitalWrite(_cs, LOW);
    SPI.write(cmd);
    digitalWrite(_cs, HIGH);
    SPI.endTransaction();
}

void OLED_096_RGB::writeData(uint8_t data) {
    SPI.beginTransaction(_spi);
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
    SPI.write(data);
    digitalWrite(_cs, HIGH);
    SPI.endTransaction();
}

void OLED_096_RGB::writeDataBuffer(const uint8_t *data, size_t len) {
    SPI.beginTransaction(_spi);
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
    SPI.writeBytes(data, len);
    digitalWrite(_cs, HIGH);
    SPI.endTransaction();
}

void OLED_096_RGB::initReg() {
    // Byte-for-byte Waveshare OLED_InitReg: every byte is sent as a command.
    static const uint8_t kInit[] = {
        0xFD, 0x12,
        0xAE,
        0x15, 0x20, 0x5F,
        0x75, 0x00, 0x7F,
        0xA0, 0x60, 0x00,
        0xA1, 0x00,
        0xA2, 0x00,
        0xB1, 0x84,
        0xB3, 0x20,
        0xB6, 0x01,
        0xBB, 0x00,
        0xBE, 0x07,
        0xC7, 0x0F,
        0xC1, 0x32, 0x29, 0x53,
        0xCA, 0x7F,
    };

    for (size_t i = 0; i < sizeof(kInit); i++) {
        writeCommand(kInit[i]);
    }
}

void OLED_096_RGB::setWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
    writeCommand(0x15);
    writeData(COL_OFFSET + x0);
    writeData(COL_OFFSET + x1);
    writeCommand(0x75);
    writeData(y0);
    writeData(y1);
}

void OLED_096_RGB::beginRamWrite() {
    writeCommand(0x5C);
}

void OLED_096_RGB::fillWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color) {
    setWindow(x0, y0, x1, y1);
    beginRamWrite();

    const uint8_t hi = static_cast<uint8_t>(color >> 8);
    const uint8_t lo = static_cast<uint8_t>(color & 0xFF);
    uint8_t chunk[256];
    for (size_t i = 0; i < sizeof(chunk); i += 2) {
        chunk[i] = hi;
        chunk[i + 1] = lo;
    }

    const uint32_t pixels =
        static_cast<uint32_t>(x1 - x0 + 1) * static_cast<uint32_t>(y1 - y0 + 1);
    uint32_t remaining = pixels * 2;
    while (remaining > 0) {
        const size_t n = remaining > sizeof(chunk) ? sizeof(chunk) : remaining;
        writeDataBuffer(chunk, n);
        remaining -= n;
    }
}

void OLED_096_RGB::clear(uint16_t color) {
    fillWindow(0, 0, WIDTH - 1, HEIGHT - 1, color);
}

void OLED_096_RGB::fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color) {
    if (w == 0 || h == 0 || x >= WIDTH || y >= HEIGHT) {
        return;
    }

    const uint8_t x1 = (x + w > WIDTH) ? (WIDTH - 1) : static_cast<uint8_t>(x + w - 1);
    const uint8_t y1 = (y + h > HEIGHT) ? (HEIGHT - 1) : static_cast<uint8_t>(y + h - 1);
    fillWindow(x, y, x1, y1, color);
}

void OLED_096_RGB::drawPixel(uint8_t x, uint8_t y, uint16_t color) {
    if (x >= WIDTH || y >= HEIGHT) {
        return;
    }

    setWindow(x, y, x, y);
    beginRamWrite();

    const uint8_t pixel[2] = {
        static_cast<uint8_t>(color >> 8),
        static_cast<uint8_t>(color & 0xFF),
    };
    writeDataBuffer(pixel, sizeof(pixel));
}

void OLED_096_RGB::blit(const uint16_t *buffer) {
    setWindow(0, 0, WIDTH - 1, HEIGHT - 1);
    beginRamWrite();

    uint8_t chunk[256];
    const uint32_t pixels = static_cast<uint32_t>(WIDTH) * HEIGHT;
    uint32_t i = 0;
    while (i < pixels) {
        size_t n = 0;
        while (n < sizeof(chunk) && i < pixels) {
            const uint16_t color = buffer[i++];
            chunk[n++] = static_cast<uint8_t>(color >> 8);
            chunk[n++] = static_cast<uint8_t>(color & 0xFF);
        }
        writeDataBuffer(chunk, n);
    }
}
