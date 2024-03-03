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
#include "esp_wps.h"

#define ESP_WPS_MODE WPS_TYPE_PBC
#define ESP_MANUFACTURER "ESPRESSIF"
#define ESP_MODEL_NUMBER "ESP32"
#define ESP_MODEL_NAME "ESPRESSIF IOT"
#define ESP_DEVICE_NAME "ESP STATION"

namespace Drivers
{

    class Wifi
    {
    public:
        static void init();
        static void deinit();
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
        static void wps_config();
        static void wps_start();
        static void wps_stop();
        static void wps_event(WiFiEvent_t event, arduino_event_info_t info);
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
        static void start_deauth(String mac_str, uint8_t channel);
        static void stop_deauth();
        static void set_deauth_count(int count);
        static void set_deauth_delay(int timeout);
        static int get_deauth_count();
        static int get_deauth_delay();
        static void send_deauth_frame(uint8_t bssid[6], int channel, String dst_mac_str);
        static void send_deauth_frame(uint8_t bssid[6], int channel, uint8_t mac[6]);
        static void wps_listner();
        static std::vector<String> wps_updates();
        static void wps_attack_stop();
    };
}

// extern AttackWiFi attackWiFi;

#endif
