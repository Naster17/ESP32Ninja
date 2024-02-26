#include "screen.h"

Adafruit_ST7735 Screen::display(TFT_CS, TFT_DC, TFT_RST);
int Screen::brit = 200;

bool Screen::init()
{
    brightness(brit);
    display.initR(INITR_BLACKTAB);
    display.setTextColor(ST7735_WHITE);
    display.setTextSize(1);
    bootinfo();
    return true;
}

bool Screen::deinit()
{
    brightness(0);
    display.initR(INITR_BLACKTAB);
    display.enableDisplay(false);
    return true;
}

void Screen::bootinfo()
{
    display.fillScreen(ST7735_BLACK);
    display.println("wewe");
}

// 50, 100, 150, 200, 250 or analog 0-254
void Screen::brightness(uint8_t stat)
{
    pinMode(TFT_LED, OUTPUT);
    analogWrite(TFT_LED, stat); // Включаем подсветку
}

void Screen::rotate()
{
    if (SCREEN_HEIGHT == 160)
    {
        Drivers::Button::rotate(1);
        display.setRotation(1);
        SCREEN_WIDTH = 160;
        SCREEN_HEIGHT = 128;
        crat = 14; // max ITEMS on display
        maxSym = 26;
    }
    else
    {
        Drivers::Button::rotate(0);
        display.setRotation(0);
        SCREEN_WIDTH = 128;
        SCREEN_HEIGHT = 160;
        crat = 18; // max ITEMS on display
        maxSym = 21;
    }
}