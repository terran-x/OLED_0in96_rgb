# 0.96" RGB OLED (SSD1357) for ESP-32D

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

```bash
cd ESP32/OLED_0in96_rgb
pio run -t upload
pio device monitor
```
