#include "scheduler.h"

void Scheduler::initd()
{
    Menu::main_menu();
}

static TaskHandle_t scanTaskHandle = NULL;

void scanTask(void *parameter)
{
    std::vector<String> *wifiVectorPtr = reinterpret_cast<std::vector<String> *>(parameter);
    if (wifiVectorPtr != nullptr)
    {
        wifiVectorPtr->clear();
        *wifiVectorPtr = DBus::wifi.scan_aps(*wifiVectorPtr);
    }
    vTaskDelete(NULL);
}

void Scheduler::schedul_wifi_scan(std::vector<String> &vectorWifi)
{

    xTaskCreatePinnedToCore(
        scanTask,                              // Функция задачи
        "ScanTask",                            // Имя задачи
        10000,                                 // Размер стека задачи
        reinterpret_cast<void *>(&vectorWifi), // Параметр задачи
        1,                                     // Приоритет задачи
        &scanTaskHandle,                       // Дескриптор для управления задачей
        0);                                    // Ядро, на котором будет выполняться задача (0 или 1)

    // return vectorWifi;
}

void Scheduler::stop_wifi_scan()
{
    vTaskSuspend(scanTaskHandle);
    vTaskDelete(scanTaskHandle);
    scanTaskHandle = NULL;
}

void Scheduler::schedul_ble_sour_apple()
{
}