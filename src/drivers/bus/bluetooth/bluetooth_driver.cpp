#include "bluetooth_driver.h"

// BleKeyboard bleKeyboard("Wewe");

namespace Drivers
{
    void Blue::init_keyboard()
    {
        Serial.println("Starting BLE work!");
        // bleKeyboard.begin();
    }

    void test()
    {
        while (true)
        {

            /* code */
            // if (bleKeyboard.isConnected())
            // {
            //     delay(8000);
            //     Serial.println("Sending 'Hello world'...");
            //     bleKeyboard.print("Hello world");

            //     delay(1000);

            //     Serial.println("Sending Enter key...");
            //     bleKeyboard.write(KEY_RETURN);

            //     delay(1000);

            //     Serial.println("Sending Play/Pause media key...");
            //     bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);

            //     delay(1000);

            //     //
            //     // Below is an example of pressing multiple keyboard modifiers
            //     // which by default is commented out.
            //     //
            //     /* Serial.println("Sending Ctrl+Alt+Delete...");
            //      bleKeyboard.press(KEY_LEFT_CTRL);
            //      bleKeyboard.press(KEY_LEFT_ALT);
            //      bleKeyboard.press(KEY_DELETE);
            //      delay(100);
            //      bleKeyboard.releaseAll();
            //      */
            // }
            // Serial.println("Waiting 5 seconds...");
            // delay(1000);
        }
    }

} // namespace Drivers
