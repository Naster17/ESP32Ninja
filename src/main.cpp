#include "kernel/system/system.h"
#include "kernel/scheduler/scheduler.h"
#include "filesystem/filesystem.h"

void setup()
{
  System::init();
}

void loop()
{
  Scheduler::initd();
}

