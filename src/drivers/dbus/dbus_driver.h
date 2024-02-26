#ifndef _DBUS_DRIVER_H
#define _DBUS_DRIVER_H

#include <Arduino.h>

#include "drivers/input/buttons/button_driver.h"
#include "drivers/bus/wifi/wifi_driver.h"
#include "drivers/bus/ble/ble_driver.h"
#include "drivers/gpio/ir/ir_driver.h"
#include "drivers/gpio/lora/lora_driver.h"
#include "drivers/bus/bluetooth/bluetooth_driver.h"


class DBus
{
public:
    static Drivers::Wifi wifi;
    static bool init();
};

#endif