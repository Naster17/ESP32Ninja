#ifndef _FSYSTEM_H
#define _FSYSTEM_H

#include "settings.h"

#include <SD.h>
#include "FS.h"
#include "SPI.h"

class Fs
{
public:
    static bool init();
    static void list_dir(const char *dirname, uint8_t levels);
};

#endif