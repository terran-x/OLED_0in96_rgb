# 0.96" RGB OLED (SSD1357) for ESP-32D

Driver API library for 0.96" RGB OLED (SSD1357) to ESP32-WROOM-32D with adapter for Adafruit GFX Library

The Adafruit GFX view is configured for landscape orientation at 128x64. The SSD1357 driver keeps the panel's native 64x128 coordinate layout and rotates GFX coordinates into it.

4-wire SPI only. Leave the module's BS jumper at the factory default.

| OLED | ESP-32D GPIO |
| --- | --- |
| VCC | 3.3V |
| GND | GND |
| DIN | 23 (VSPI MOSI) |
| CLK | 18 (VSPI SCK) |
| CS | 5 |
| DC | 17 |
| RST | 16 |

Logic and power must both be 3.3V.
