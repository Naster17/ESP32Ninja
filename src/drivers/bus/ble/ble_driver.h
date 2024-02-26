#ifndef _BLE_DRIVER_H
#define _BLE_DRIVER_H

#include <NimBLEDevice.h>

namespace Attack
{
    class BLE
    {
    private:
        static NimBLEServer *pServer;

    public:
        static NimBLEAdvertisementData adv_sour_apple();
        static NimBLEAdvertisementData advXiaomiBuds3Pro();
        static void init();
        static void start_sour_apple();
    };

}

#endif