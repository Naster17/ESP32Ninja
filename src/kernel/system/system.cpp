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
            return INIT_ERROR_BUTTONS;

        if (!Screen::init())
            return INIT_ERROR_SCREEN;

        return true;
    }

    bool wake_up()
    {
        status = true;
        Screen::init();
        delay(300);
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