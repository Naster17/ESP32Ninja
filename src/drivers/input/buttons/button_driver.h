#ifndef _BUTTON_DRIVER_H
#define _BUTTON_DRIVER_H

#include <Arduino.h>
#include "settings.h"

namespace Drivers
{
    /*Current pins */
    static uint8_t BUTTON_UP;
    static uint8_t BUTTON_DOWN;
    static uint8_t BUTTON_LEFT;
    static uint8_t BUTTON_RIGHT;
    static uint8_t BUTTON_OK;
    static uint8_t BUTTON_FREE;

    class Button
    {
    public:
        static bool init();
        static void rotate(uint8_t orient);
        static uint8_t updates();
    };
}

#endif