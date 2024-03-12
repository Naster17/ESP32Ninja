#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <Arduino.h>

#include "drivers/dbus/dbus_driver.h"
#include "user/screen/screen.h"
#include "filesystem/filesystem.h"

namespace System
{
    extern bool init();    
    extern bool wake_up();
    extern bool light_sleep(); 
    extern void interrupt();
}

#endif