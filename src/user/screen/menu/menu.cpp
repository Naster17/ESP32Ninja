#include "menu.h"

bool frame = true;

uint8_t min(uint8_t a, uint8_t b)
{
    return (a < b) ? a : b;
}

void Menu::main_menu()
{
    static int mainPos = 0;
    status_line(ST7735_GRAY1);
    uint8_t response = base_menu_logic("Main", Drivers::Button::updates(), mainMenuI, mainPos, true);

    // Ok
    if (response == OK_PRESS && mainMenuI[mainPos] == "WiFi")
        menu_wifi();

    if (response == OK_PRESS && mainMenuI[mainPos] == "Bluetooth")
    {
        menu_bluetooth();
    }
    if (response == OK_PRESS && mainMenuI[mainPos] == "BLE")
        menu_ble();

    if (response == OK_PRESS && mainMenuI[mainPos] == "IR")
        menu_ir();

    if (response == OK_PRESS && mainMenuI[mainPos] == "LoRa")
        menu_lora();

    if (response == OK_PRESS && mainMenuI[mainPos] == "Apps")
        menu_apps();
}

uint8_t Menu::status_bar(uint8_t buttonEvent, String text)
{
    static uint8_t posH = 0;

    switch (buttonEvent)
    {
    case RIGHT_PRESS:
        posH++;
        frame = true;
        break;
    case LEFT_PRESS:
        posH--;
        frame = true;
        break;
    case FREE_PRESS:
        posH = 0;
        frame = true;
        return FREE_PRESS;
    case DOWN_PRESS:
        posH = 0;
        frame = true;
        return DOWN_PRESS;
    case OK_PRESS:
        if (posH == 1)
        {
            brit = (brit == 250) ? 50 : brit + 50;
            brightness(brit);
        }
        if (posH == 2)
        {
            rotate();
        }
        else if (posH == 3)
            ESP.restart();

        posH = 0;
        frame = true;
        break;
    default:
        break;
    }

    if (frame)
    {
        display.fillRect(0, 0, SCREEN_WIDTH, 12, ST7735_GRAY1); // aka 10 : 11-1pixel fill
        display.drawFastHLine(0, 12, SCREEN_WIDTH, ST7735_WHITE);

        // bat
        display.drawBitmap(SCREEN_WIDTH - 21, 1, battery1_img, 20, 10, ST7735_BLACK);
        if (posH == 5)
            display.drawRect(SCREEN_WIDTH - 22, 0, 22, 12, ST7735_RED);

        // bluetooth
        display.drawBitmap(SCREEN_WIDTH - 32, 1, bluetooth_img, 10, 10, ST7735_BLACK);
        if (posH == 4)
            display.drawRect(SCREEN_WIDTH - 33, 0, 12, 12, ST7735_RED);

        // reboot
        display.drawBitmap(SCREEN_WIDTH - 43, 1, reboot_img, 10, 10, ST7735_BLACK);
        if (posH == 3)
            display.drawRect(SCREEN_WIDTH - 44, 0, 12, 12, ST7735_RED);

        // rotate
        display.drawBitmap(SCREEN_WIDTH - 54, 1, rotate_img, 10, 10, ST7735_BLACK);
        if (posH == 2)
            display.drawRect(SCREEN_WIDTH - 55, 0, 12, 12, ST7735_RED);

        // brit
        display.drawBitmap(SCREEN_WIDTH - 65, 1, brit_img, 10, 10, ST7735_BLACK);
        if (posH == 1)
            display.drawRect(SCREEN_WIDTH - 66, 0, 12, 12, ST7735_RED);
    }
    return 0;
}

void Menu::status_line(int color = ST7735_BLACK)
{
    if (frame)
        display.fillRect(0, SCREEN_HEIGHT - 2, SCREEN_WIDTH, 2, color); // last 3 pixels in down
}

///

void Menu::menu_bluetooth()
{
    int pos = 0;
    frame = true;
    std::vector<String> input_vec = {"________"};
    while (true)
    {
        uint8_t response = base_menu_logic("WiFi", Drivers::Button::updates(), input_vec, pos, true);

        if (response == FREE_PRESS)
            break;

        if (response == OK_PRESS)
            num_keyboard();
    }
}

String Menu::num_keyboard()
{
    frame = true;
    int posX = 0;
    int posY = 0;
    bool run = true;
    while (run)
    {
        uint8_t events = Drivers::Button::updates();
        status_bar((posX < 0) ? events : 0, "wewe");

        if (frame)
        {
            int positions_rect[][2] = {{0, 75}, {42, 75}, {84, 75}, {0, 96}, {42, 96}, {84, 96}, {0, 117}, {42, 117}, {84, 117}, {0, 138}, {42, 138}, {84, 138}};

            for (int i = 0; i < 12; i++)
            {
                display.drawRect(positions_rect[i][0], positions_rect[i][1], 42, 22, ST7735_GRAY1);
                display.fillRect(positions_rect[i][0], positions_rect[i][1], 40, 20, ST7735_GRAY);
            }

            display.drawRect(positions_rect[posY][0], positions_rect[posX][1], 42, 22, ST7735_GRAY1);
            display.fillRect(positions_rect[posY][0], positions_rect[posX][1], 40, 20, ST7735_WHITE);

            display.setTextSize(2);
            display.setTextColor(ST7735_BLACK);
            int positions[][2] = {{15, 79}, {58, 79}, {100, 79}, {15, 100}, {58, 100}, {100, 100}, {15, 121}, {58, 121}, {100, 121}, {15, 142}, {58, 142}, {100, 142}};

            for (int i = 0; i < 12; i++)
            {
                display.setCursor(positions[i][0], positions[i][1]);

                if (positions[i][0] == 15 && positions[i][1] == 142)
                    display.print("*");

                else if (positions[i][0] == 58 && positions[i][1] == 142)
                    display.print(0);

                else if (positions[i][0] == 100 && positions[i][1] == 142)
                    display.print("#");

                else
                    display.print(i + 1);
            }

            frame = false;
        }

        switch (events)
        {
        case UP_PRESS:
            frame = true;
            posX -= 1;
            break;
        case DOWN_PRESS:
            frame = true;
            posX += 1;
            break;
        case LEFT_PRESS:
            frame = true;
            posY -= 1;
            break;
        case RIGHT_PRESS:
            frame = true;
            posY += 1;
            break;
        case FREE_PRESS:
            display.setTextSize(1);
            display.setTextColor(ST7735_WHITE);
            run = false;
            return "";
            break;
        case OK_PRESS:
            frame = true;
            break;
        }
    }
}

///

void Menu::menu_wifi()
{
    int pos = 0;
    frame = true;
    while (true)
    {
        uint8_t response = base_menu_logic("WiFi", Drivers::Button::updates(), mainWifiI, pos, true);

        if (response == FREE_PRESS)
            break;

        if (response == OK_PRESS && mainWifiI[pos] == "Scan")
            menu_scan_aps();
        if (response == OK_PRESS && mainWifiI[pos] == "WPS Listner")
            menu_wps();
        if (response == OK_PRESS && mainWifiI[pos] == "Settings")
            menu_settings_wifi();
    }
}

void Menu::print(String text)
{
    display.fillScreen(ST7735_BLACK);
    display.setTextColor(ST7735_GREEN);
    display.println("\n" + text + "\n");
    display.setTextColor(ST7735_WHITE);
}

void Menu::menu_wps()
{
    Attack::Wifi::wps_listner();
    int pos = 0;
    size_t old_size = 0;
    frame = true;
    while (true)
    {
        std::vector<String> wps_data = Attack::Wifi::wps_updates();
        if (old_size != wps_data.size())
        {
            frame = true;
            old_size = wps_data.size();
        }
        uint8_t response = base_menu_logic("WiFi", Drivers::Button::updates(), wps_data, pos, true);

        if (response == OK_PRESS && wps_data.size() > 0)
            print(wps_data[pos]);

        if (response == FREE_PRESS)
        {
            Attack::Wifi::wps_attack_stop();
            break;
        }
    }
}

void Menu::menu_scan_aps()
{
    int pos = 0;

    std::vector<String> vectorWifi;
    std::vector<String> vectorWifiOld;

    Scheduler::schedul_wifi_scan(vectorWifi);

    while (true)
    {

        if (vectorWifi.size() > 0)
        {
            display.fillScreen(ST7735_BLACK);
            frame = true;
            vectorWifiOld = vectorWifi;

            if (DBus::wifi.get_rate())
                Scheduler::schedul_wifi_scan(vectorWifi);
            else
                vectorWifi.clear();
        }

        uint8_t response = base_menu_logic("Rate: " + (String)DBus::wifi.get_rate(), Drivers::Button::updates(), vectorWifiOld, pos, true);

        if (response == OK_PRESS && vectorWifiOld.size() > 0)
            menu_ap(vectorWifiOld[pos], pos);

        if (response == FREE_PRESS)
        {
            // Scheduler::stop_wifi_scan();
            Drivers::Wifi::deinit();
            break;
        }
    }
}

void Menu::menu_ap(String AP, int &apos)
{
    // Secure Network|-32dbm|11|WPA2|11:22:33:44:55:66|1:0
    int pos = 0;
    std::vector<String> data;
    for (int i = 0, start = 0; i < AP.length(); i++)
    {
        if (AP.charAt(i) == '|')
        {
            data.push_back(AP.substring(start, i));
            start = i + 1;
        }
        else if (i == AP.length() - 1)
        {
            data.push_back(AP.substring(start));
        }
    }

    // Draw info
    while (true)
    {

        if (frame)
        {
            display.fillScreen(ST7735_BLACK);
            display.println("");
            display.println(data[0]);
            display.println(data[4]);
            display.println(data[1] + " " + data[2] + "ch " + data[3]);
            display.print("WPS: ");
            display.println((data[5] == "1") ? "true" : "false");
        }

        uint8_t response = base_menu_logic(data[0], Drivers::Button::updates(), mainAPI, pos, false);

        if (response == FREE_PRESS)
        {
            display.fillScreen(ST7735_BLACK);
            break;
        }
        if (response == OK_PRESS && mainAPI[pos] == "Deauth")
        {

            menu_deauth_ap(data[4], data[2].toInt());
        }
    }
}

void Menu::menu_deauth_ap(String macStr, uint8_t channel)
{
    // //  куда = кто логика глушения перепутана местами куда в ff:ff... кто мак цели
    String dst_mac = "ff:ff:ff:ff:ff:ff";
    byte src_mac[6];
    // byte src_mac[6] = {0x3E, 0x52, 0xA1, 0x1E, 0x09, 0xA0};
    int packets = 0;
    for (int i = 0; i < 6; i++)
    {
        src_mac[i] = strtoul(macStr.substring(i * 3, i * 3 + 2).c_str(), NULL, 16);
    }

    // Serial.println(ieee80211_raw_frame_sanity_check(31337, 0, 0));
    Attack::Wifi::init();
    while (1)
    {
        uint8_t buttonEvent = Drivers::Button::updates();
        if (buttonEvent == FREE_PRESS)
            break;

        display.fillScreen(ST7735_BLACK);
        display.setCursor(0, 14);
        display.println("Deauthing: " + String(packets));
        Attack::Wifi::send_deauth_frame(src_mac, channel, dst_mac);
        delay(50);
        packets++;
    }
}

void Menu::menu_settings_wifi()
{
    int posHH = 0;
    int mapPos;
    bool printedRate[3] = {false};
    bool printedTXPower[9] = {false};

    while (1)
    {
        uint8_t response = base_menu_settings_logic("Settings", Drivers::Button::updates(), munuSettingWifiI, posHH, mapPos, true);

        // rate
        if (posHH == 0 && !printedRate[mapPos])
        {
            printedRate[mapPos] = true;

            if (mapPos == 0)
                DBus::wifi.set_rate(false);
            if (mapPos == 1)
                DBus::wifi.set_rate(true);

            for (int i = 0; i < 3; ++i)
            {
                if (i != mapPos)
                {
                    printedRate[i] = false;
                }
            }
        }
        // TX power
        if (posHH == 1 && !printedTXPower[mapPos])
        {
            if (mapPos == 0)
                DBus::wifi.set_tx_power(WIFI_POWER_19_5dBm);
            else if (mapPos == 1)
                DBus::wifi.set_tx_power(WIFI_POWER_19dBm);
            else if (mapPos == 2)
                DBus::wifi.set_tx_power(WIFI_POWER_17dBm);
            else if (mapPos == 3)
                DBus::wifi.set_tx_power(WIFI_POWER_15dBm);
            else if (mapPos == 4)
                DBus::wifi.set_tx_power(WIFI_POWER_13dBm);
            else if (mapPos == 5)
                DBus::wifi.set_tx_power(WIFI_POWER_11dBm);
            else if (mapPos == 6)
                DBus::wifi.set_tx_power(WIFI_POWER_7dBm);
            else if (mapPos == 7)
                DBus::wifi.set_tx_power(WIFI_POWER_5dBm);
            else if (mapPos == 8)
                DBus::wifi.set_tx_power(WIFI_POWER_2dBm);

            printedTXPower[mapPos] = true;

            for (int i = 0; i < 9; ++i)
                if (i != mapPos)
                    printedTXPower[i] = false;
        }

        if (response == FREE_PRESS)
            break;
    }
}

///

void Menu::menu_ir()
{
    int pos = 0;
    frame = true;
    while (true)
    {
        uint8_t response = base_menu_logic("IR", Drivers::Button::updates(), mainIrI, pos, true);

        if (response == OK_PRESS && mainIrI[pos] == "Send")
            Drivers::IR::transmitter();
        if (response == OK_PRESS && mainIrI[pos] == "Receive")
            Drivers::IR::receiver();

        if (response == FREE_PRESS)
            break;
    }
}

///

void Menu::menu_ble()
{
    int pos = 0;
    frame = true;
    while (true)
    {
        uint8_t response = base_menu_logic("BLE", Drivers::Button::updates(), mainBleI, pos, true);

        if (response == FREE_PRESS)
            break;

        // mainPos = -1 == crash

        if (response == OK_PRESS && mainBleI[pos] == "Scan")
            Serial.println("Scan ble");
        if (response == OK_PRESS && mainBleI[pos] == "Spam")
            menu_spam_ble();
    }
}

void Menu::menu_spam_ble()
{
    int pos = 0;
    frame = true;
    while (true)
    {
        uint8_t response = base_menu_logic("SPAM!", Drivers::Button::updates(), mainSpamBleI, pos, true);

        if (response == FREE_PRESS)
            break;

        // mainPos = -1 == crash

        if (response == OK_PRESS && mainSpamBleI[pos] == "Sour Apple")
            menu_sour_apple();
    }
}

void Menu::menu_sour_apple()
{
    display.fillScreen(ST7735_BLACK);
    int pos = 0;
    int count = 0;
    frame = true;
    Attack::BLE::init();
    uint32_t tmr = 0;
    while (true)
    {
        uint8_t response = Drivers::Button::updates();

        Attack::BLE::start_sour_apple();
        count++;

        if (millis() - tmr >= 500)
        {
            display.fillScreen(ST7735_BLACK);
            display.setCursor(0, 13);
            display.println("Sended: " + String(count));
            tmr = millis();
        }

        if (response == FREE_PRESS)
        {
            display.fillScreen(ST7735_BLACK);
            break;
        }
    }
}

///

void Menu::menu_lora()
{
    int pos = 0;
    frame = true;
    Drivers::Lora::init();
    while (true)
    {
        uint8_t response = base_menu_logic("LoRa", Drivers::Button::updates(), mainLoraI, pos, true);

        if (response == OK_PRESS && mainIrI[pos] == "Send")
            Drivers::Lora::send_lora_packet();
        if (response == OK_PRESS && mainIrI[pos] == "Receive")
            menu_lora_receive();

        if (response == FREE_PRESS)
            break;
    }
}

void Menu::menu_lora_receive()
{
}
///

void Menu::menu_apps()
{
    int pos = 0;
    frame = true;
    while (true)
    {
        uint8_t response = base_menu_logic("Apps", Drivers::Button::updates(), mainAppsI, pos, true);

        if (response == FREE_PRESS)
            break;

        // mainPos = -1 == crash

        if (response == OK_PRESS && mainAppsI[pos] == "System Check")
            menu_system_check();
        if (response == OK_PRESS && mainAppsI[pos] == "Tiktok Pad")
            Serial.println("Tiktik");
    }
}

void Menu::menu_system_check()
{
    int pos = 0;
    frame = true;

    while (true)
    {

        if (frame)
        {
            // if (wlan.getStatus())
            // {
            //     display.setCursor(0, 13);
            //     display.fillRect(0, 12, SCREEN_WIDTH, 8, ST7735_GREEN); // aka 10 : 11-1pixel fill
            //     display.println("WiFi");
            // }
            // else
            // {
            //     display.setCursor(0, 13);
            //     display.fillRect(0, 12, SCREEN_WIDTH, 8, ST7735_RED); // aka 10 : 11-1pixel fill
            //     display.drawFastHLine(0, 18, SCREEN_WIDTH, ST7735_GRAY1);
            //     display.println("WiFi");
            // }
        }

        uint8_t response = base_menu_logic("Check", Drivers::Button::updates(), emptyVector, pos, true);

        if (response == FREE_PRESS)
            break;
    }
}

/// Logics

uint8_t Menu::base_menu_logic(String MenuName, uint8_t buttonEvent, const std::vector<String> &vec, int &pos, bool clearDisplay)
{
    static int page = 0;

    status_bar((pos < 0) ? buttonEvent : 0, MenuName);

    if (frame)
    {
        display.setCursor(0, 14);

        for (uint8_t i = page; i < min(page + crat, (uint8_t)vec.size()); i++)
        {
            const String &currentStr = vec[i];
            uint8_t maxChar = (i == pos) ? maxSym - 2 : maxSym;
            display.print((i == pos) ? "> " : "");
            display.println(currentStr.substring(0, min(currentStr.length(), maxChar)));
        }
        frame = false;
    }

    switch (buttonEvent)
    {
    case UP_PRESS:
        frame = true;
        if (clearDisplay)
            display.fillScreen(ST7735_BLACK);
        pos--;
        if (pos > 0) // if (pos > 0)
        {
            if (pos < page)
            { // Проверяем, если позиция выходит за верхнюю границу страницы
                if (page >= crat)
                {                 // Если мы не на первой странице
                    page -= crat; // Перемещаемся на предыдущую страницу
                }
                else
                {             // Если мы на первой странице
                    page = 0; // Перемещаемся к первой странице
                }
            }
        }
        else
        { // Ничего не деаем так как передаем в status bar
          // pos = vec.size() - 1;
          // page = (pos / crat) * crat; // Перемещаемся к последнему элементу на текущей странице
        }
        break;

    case DOWN_PRESS:
        frame = true;
        if (clearDisplay)
            display.fillScreen(ST7735_BLACK);
        if (pos < vec.size() - 1)
        {
            pos++;
            if (pos >= page + crat)
            {                 // Проверяем, если позиция выходит за нижнюю границу страницы
                page += crat; // Перемещаемся на следующую страницу
            }
        }
        else
        { // Если достигнут нижний конец списка
            pos = 0;
            page = 0; // Перемещаемся к первому элементу на первой странице
        }
        break;

    case OK_PRESS:
        frame = true;
        Serial.println("Menu ok");
        if (clearDisplay)
            display.fillScreen(ST7735_BLACK);
        if (pos >= 0)
            return OK_PRESS;

    case FREE_PRESS:
        frame = true;
        if (clearDisplay)
            display.fillScreen(ST7735_BLACK);
        pos = 0;
        page = 0;
        return FREE_PRESS;

    case FREE_LONG_PRESS:

        System::light_sleep();
        break;

    default:
        break;
    }

    return 0;
}

uint8_t Menu::base_menu_settings_logic(String MenuName, uint8_t buttonEvent, const std::map<String, std::vector<String>> &MenuI, int &pos, int &mapPos, bool clearDisplay)
{
    static int page = 0;

    // if pos < 0 forward buttons to status bar
    status_bar((pos < 0) ? buttonEvent : 0, MenuName);

    if (frame)
    {
        display.setCursor(0, 14);
        for (auto it = MenuI.begin(); it != MenuI.end(); ++it)
        {
            String current = it->first;
            // Добавление "> " к текущему элементу, если pos равен его позиции
            if (pos == std::distance(MenuI.begin(), it))
            {
                mapPos = (mapPos < it->second.size() && mapPos >= 0) ? mapPos : 0;
                current = "> " + current;

                for (int i = 0; i < maxSym - (current.length() + it->second[mapPos].length() + 4); i++)
                    current += " ";

                display.println(current + "< " + it->second[mapPos] + " >");
            }

            else
            {
                for (int i = 0; i < maxSym - (current.length() + it->second[0].length() + 4); ++i)
                {
                    current += " ";
                }
                display.println(current + "< " + it->second[0] + " >");
            }
        }
        frame = false;
    }

    switch (buttonEvent)
    {
    case UP_PRESS:
        frame = true;
        mapPos = 0;
        if (clearDisplay)
            display.fillScreen(ST7735_BLACK);
        pos--;
        if (pos > 0) // if (pos > 0)
        {
            if (pos < page)
            { // Проверяем, если позиция выходит за верхнюю границу страницы
                if (page >= crat)
                {                 // Если мы не на первой странице
                    page -= crat; // Перемещаемся на предыдущую страницу
                }
                else
                {             // Если мы на первой странице
                    page = 0; // Перемещаемся к первой странице
                }
            }
        }
        else
        { // Ничего не деаем так как передаем в status bar

            // pos = vec.size() - 1;
            // page = (pos / crat) * crat; // Перемещаемся к последнему элементу на текущей странице
        }
        break;

    case DOWN_PRESS:
        frame = true;
        mapPos = 0;
        if (clearDisplay)
            display.fillScreen(ST7735_BLACK);
        if (pos < MenuI.size() - 1)
        {
            pos++;
            if (pos >= page + crat)
            {                 // Проверяем, если позиция выходит за нижнюю границу страницы
                page += crat; // Перемещаемся на следующую страницу
            }
        }
        else
        { // Если достигнут нижний конец списка
            pos = 0;
            page = 0; // Перемещаемся к первому элементу на первой странице
        }
        break;

    case LEFT_PRESS:
        frame = true;
        if (clearDisplay)
            display.fillScreen(ST7735_BLACK);
        mapPos--;
        break;

    case RIGHT_PRESS:
        frame = true;
        if (clearDisplay)
            display.fillScreen(ST7735_BLACK);
        mapPos++;
        break;

        // case OK_PRESS:
        //     if (clearDisplay)
        //         display.fillScreen(ST7735_BLACK);
        //     if (pos >= 0)
        //         return OK_PRESS;

    case FREE_PRESS:
        frame = true;
        if (clearDisplay)
            display.fillScreen(ST7735_BLACK);
        return FREE_PRESS;

    default:
        break;
    }

    return 0;
}