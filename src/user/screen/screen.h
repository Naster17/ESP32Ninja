#ifndef _SCREEN_H
#define _SCREEN_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#include "drivers/dbus/dbus_driver.h"

static int _SCREEN_WIDTH = 128;
static int _SCREEN_HEIGHT = 160;
static int crat = 18;
static int maxSym = 21;

// custom colors
#define ST7735_GRAY 0x8410
#define ST7735_GRAY1 0x4208

class Screen
{
public:
    static Adafruit_ST7735 display;
    // vals
    static int brit; // brightness
    // func
    static bool init();
    static bool deinit();
    static void brightness(uint8_t stat);
    static void bootinfo();
    static void rotate(uint8_t m);
};

#endif