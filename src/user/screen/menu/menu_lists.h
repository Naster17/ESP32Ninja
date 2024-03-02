#ifndef _MENU_LISTS_H
#define _MENU_LISTS_H

#include <map>
#include <vector>
#include <Arduino.h>

// Main
const std::vector<String> emptyVector;
const std::vector<String> mainMenuI = {"WiFi", "Bluetooth", "BLE", "IR", "LoRa", "RFID", "NFC", "Apps", "Explorer", "Settings"}; // strlen 1 symbol = 1
// Apps
const std::vector<String> mainAppsI = {"System Check", "Tiktok Pad"};
// WiFi
const std::vector<String> mainWifiI = {"Scan", "Deauth", "Probe", "Beacon", "WPS Listner", "EAPOL/PMKID", "Detect", "Raw Capture", "Settings"};
const std::vector<String> mainAPI = {"Deauth", "Probe", "Sniff", "EVIL AP", "PMKID", "EAPOL", "Add2Beacon"};
const std::vector<String> mainEAPOLI = {"Active capture", "Passive capture"};

const std::map<String, std::vector<String>> munuSettingWifiI = {
    {"Rate", {"Off", "On"}},
    {"TX Power", {"20dbm", "19dbm", "17dbm", "15dbm", "13dbm", "11dbm", "7dbm", "5dbm", "2dbm"}},
};
// Bluetooth
const std::vector<String> mainBuetootheI = {"Scan", "Detect", "Settings"};
const std::vector<String> mainDetectBluetoothI = {"Fliper Zero", "Pwn gochi", "Skimmers"};

// BLE
const std::vector<String> mainBleI = {"Spam", "Settings"};
const std::vector<String> mainSpamBleI = {"Sour Apple", "Xiaomi Buds"};
// IR
const std::vector<String> mainIrI = {"Send", "Receive", "Database", "Craft Packet", "Bruteforce"};
// LoRa
const std::vector<String> mainLoraI = {"Send", "Receive"};

#endif