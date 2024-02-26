#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#include "kernel/system/system.h"
#include "kernel/scheduler/scheduler.h"



void setup()
{
    System::init();

}

void loop()
{
    Scheduler::initd();
}
