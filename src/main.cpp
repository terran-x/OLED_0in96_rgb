#include <Arduino.h>
#include "OLED_096_RGB.h"
#include "OLED_096_GFX.h"

static OLED_096_RGB oled;
static OLED_096_GFX gfx(oled);

void setup() {
    Serial.begin(115200);
    delay(200);
    Serial.println("OLED_096_RGB begin");

    oled.begin();

    gfx.fillScreen(OLED_096_RGB::BLACK);
    gfx.drawRect(0, 0, gfx.width(), gfx.height(), OLED_096_RGB::WHITE);
    gfx.fillRect(4, 4, gfx.width() - 8, 18, OLED_096_RGB::BLUE);

    gfx.setTextColor(OLED_096_RGB::WHITE, OLED_096_RGB::BLUE);
    gfx.setTextSize(1);
    gfx.setCursor(8, 10);
    gfx.print("UI");

    gfx.setTextColor(OLED_096_RGB::GREEN, OLED_096_RGB::BLACK);
    gfx.setCursor(8, 32);
    gfx.println("GFX adapter");
    gfx.setCursor(8, 44);
    gfx.println("64x128");

    gfx.drawCircle(32, 90, 16, OLED_096_RGB::RED);
    gfx.fillCircle(32, 90, 6, OLED_096_RGB::YELLOW);

    Serial.println("GFX UI demo complete");
}

void loop() {}
