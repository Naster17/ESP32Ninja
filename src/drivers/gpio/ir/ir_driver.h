#ifndef _IR_DRIVER_H
#define _IR_DRIVER_H

#include "settings.h"

#ifdef ENABLE_IR

#include <Arduino.h>
#include <assert.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <IRremoteESP8266.h>
#include <IRac.h>
#include <IRtext.h>
#include <IRutils.h>

namespace Drivers
{
    class IR
    {
    public:
        static bool init();
        static void receiver();
        static void transmitter();
    };
}

#endif
#endif