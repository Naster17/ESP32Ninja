#ifndef _BLUETOOTH_DRIVER_H
#define _BLUETOOTH_DRIVER_H

// #include <BleKeyboard.h>
#include <Arduino.h>
#include <NimBLEDevice.h>

// #define USE_NIMBLE

namespace Drivers
{
    class Blue
    {
    public:
        static void init_keyboard();
        static void test();
    };
}

#endif