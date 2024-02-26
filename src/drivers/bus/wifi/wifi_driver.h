#ifndef _WIFI_DRIVER_H
#define _WIFI_DRIVER_H

#include "settings.h"

#include <WiFi.h>
#include <vector>
// #include <stdio.h>
// #include <string.h>

#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "esp_netif.h"
#include "esp_event.h"

namespace Drivers
{

    class Wifi
    {
    public:
        static bool init();
        // gets
        // bool getStatus();
        // void getBSSID(uint8_t item, uint8_t *list);
        // // scans
        static std::vector<String> scan_aps(std::vector<String> vec);
        static std::vector<String> scan_aps_async(std::vector<String> vec);
        // // sets
        // void setScanTimeout(int milis);
        static void set_tx_power(wifi_power_t power);
        static void set_rate(bool status);
        static bool get_rate();
        // wifi_power_t getTxPower();
    };
    extern Wifi wifi;
}

namespace Attack
{

    class Wifi
    {
    public:
        static void init();
        static void send_deauth_frame(uint8_t bssid[6], int channel, String dst_mac_str);
        static void send_deauth_frame(uint8_t bssid[6], int channel, uint8_t mac[6]);
    };
}

// extern AttackWiFi attackWiFi;

#endif
