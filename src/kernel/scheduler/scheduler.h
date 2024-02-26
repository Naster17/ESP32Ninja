#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#include "drivers/dbus/dbus_driver.h"
#include "user/screen/menu/menu.h"

class Scheduler
{
public:
    static void initd();
    // wifi
    static void schedul_wifi_scan(std::vector<String> &vectorWifi);
    static void stop_wifi_scan();
    // ble
    static void schedul_ble_sour_apple();
    static void stop_ble_sour_apple();
};

#endif