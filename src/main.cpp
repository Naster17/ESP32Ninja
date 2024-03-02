#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#include "kernel/system/system.h"
#include "kernel/scheduler/scheduler.h"

#include <SD.h>
#include "FS.h"
#include "SPI.h"
#define SD_CS_PIN 5

void setup()
{
    System::init();

    // while (true)
    // {
    //     /* code */
    // delay(1000);
    // SD.begin(SD_CS_PIN);

    // uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    // Serial.printf("SD Card Size: %lluMB\n", cardSize);
    // }
}

void loop()
{
    Scheduler::initd();
}
