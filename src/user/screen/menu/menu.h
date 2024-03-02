#ifndef _MENU_H
#define _MENU_H

#include "user/screen/screen.h"
#include "menu_lists.h"
#include "assets/images.h"
#include "kernel/scheduler/scheduler.h"
#include "kernel/system/system.h"

class Menu : private Screen
{
public:
    static uint8_t base_menu_logic(String MenuName, uint8_t buttonEvent, const std::vector<String> &vec, int &pos, bool clearDisplay);
    static uint8_t base_menu_settings_logic(String MenuName, uint8_t buttonEvent, const std::map<String, std::vector<String>> &MenuI, int &pos, int &mapPos, bool clearDisplay);

    static void print(String text);

    static void main_menu();
    static uint8_t status_bar(uint8_t buttonEvent, String text);
    static void status_line(int color);
    // menus
    static void menu_wifi();
    static void menu_wps(); 
    static void menu_scan_aps();
    static void menu_real_time_scan_aps();
    static void menu_ap(String AP, int &apos);
    static void menu_deauth_ap(String macStr, uint8_t channel);
    static void menu_settings_wifi();
    // Ir
    static void menu_ir();
    // ble
    static void menu_ble();
    static void menu_spam_ble();
    static void menu_sour_apple();
    // lora
    static void menu_lora();
    static void menu_lora_receive();
    // apps
    static void menu_apps();
    static void menu_system_check();
};

#endif