#include "system.h"

namespace System
{
    static bool status = true;

    void interrupt()
    {
        if (!status)
        {
            wake_up();
        }
    }

    bool init()
    {
        Serial.begin(9600);

        attachInterrupt(digitalPinToInterrupt(BUTTON_OK_PIN), interrupt, CHANGE);
        esp_sleep_enable_ext0_wakeup((gpio_num_t)BUTTON_OK_PIN, LOW);

        if (!Drivers::Button::init())
            Serial.println("Button init fail");

        if (!Screen::init())
            Serial.println("Screen init fail");

        if (!Fs::init())
            Serial.println("Fs init fail");

        return true;
    }

    bool wake_up()
    {
        status = true;
        delay(300);
        Screen::init();
        return true;
    }

    bool light_sleep()
    {
        status = false;
        Screen::deinit();
        esp_light_sleep_start();
        return true;
    }

} // namespace System