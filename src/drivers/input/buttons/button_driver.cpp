#include "button_driver.h"

namespace Drivers
{
    bool Button::init()
    {
        rotate(0);
        pinMode(BUTTON_UP, INPUT_PULLUP);
        pinMode(BUTTON_DOWN, INPUT_PULLUP);
        pinMode(BUTTON_LEFT, INPUT_PULLUP);
        pinMode(BUTTON_RIGHT, INPUT_PULLUP);
        pinMode(BUTTON_OK, INPUT_PULLUP);
        pinMode(BUTTON_FREE, INPUT); // input only + extern pullup rezistor
        return true;
    }

    void Button::rotate(uint8_t orient)
    {
        // horizon
        if (orient == 1)
        {
            BUTTON_UP = BUTTON_RIGHT_PIN;
            BUTTON_DOWN = BUTTON_LEFT_PIN;
            BUTTON_LEFT = BUTTON_UP_PIN;
            BUTTON_RIGHT = BUTTON_DOWN_PIN;
            BUTTON_OK = BUTTON_OK_PIN;
            BUTTON_FREE = BUTTON_FREE_PIN;
        }
        // vertical default
        else
        {
            BUTTON_UP = BUTTON_UP_PIN;
            BUTTON_DOWN = BUTTON_DOWN_PIN;
            BUTTON_LEFT = BUTTON_LEFT_PIN;
            BUTTON_RIGHT = BUTTON_RIGHT_PIN;
            BUTTON_OK = BUTTON_OK_PIN;
            BUTTON_FREE = BUTTON_FREE_PIN;
        }
    }

    uint8_t Button::updates()
    {

        const uint8_t defStatus = 1; // status if button unpressed (in my case if pressed is 0)
        const uint8_t delayTime = 200;

        uint32_t currentTime = millis();
        static uint32_t tmr = 0;
        static uint32_t lastTmr = 0;
        static uint8_t lastStatus = 0;
        static uint8_t counter = 0;

        const uint8_t buttonPins[] = {BUTTON_UP, BUTTON_DOWN, BUTTON_LEFT, BUTTON_RIGHT, BUTTON_OK, BUTTON_FREE};
        const uint8_t buttonCodes[] = {UP_PRESS, DOWN_PRESS, LEFT_PRESS, RIGHT_PRESS, OK_PRESS, FREE_PRESS};
        const uint8_t buttonLongCodes[] = {UP_LONG_PRESS, DOWN_LONG_PRESS, LEFT_LONG_PRESS, RIGHT_LONG_PRESS, OK_LONG_PRESS, FREE_LONG_PRESS};

#ifdef DEBUG
        static uint32_t debugTmr = 0;
        if (currentTime - debugTmr >= 10000)
        {
            Serial.println("====Buttons=====");
            Serial.println(digitalRead(BUTTON_UP));
            Serial.println(digitalRead(BUTTON_DOWN));
            Serial.println(digitalRead(BUTTON_LEFT));
            Serial.println(digitalRead(BUTTON_RIGHT));
            Serial.println(digitalRead(BUTTON_OK));
            Serial.println(digitalRead(BUTTON_FREE));
            Serial.println("================");

            debugTmr = millis();
        }
#endif

        for (uint8_t i = 0; i < sizeof(buttonPins); ++i)
        {

            if (digitalRead(buttonPins[i]) != defStatus && currentTime - tmr >= delayTime)
            {
                tmr = currentTime;

                if (currentTime - lastTmr >= 220)
                {
                    counter = 0;
                    lastTmr = currentTime;
                }

                if (lastStatus == buttonCodes[i])
                    counter++;
                else
                {
                    counter = 0;
                    lastStatus = buttonCodes[i];
                }

                if (counter == 2)
                {
                    counter = 0;
                    return buttonLongCodes[i];
                }
                else
                    return buttonCodes[i];
            }
        }
        return EMPTY_PRESS;
    }
}