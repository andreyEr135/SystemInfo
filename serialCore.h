#ifndef UISERIALCORE_H
#define UISERIALCORE_H

#include <iostream>
#include <string>

#include <Arduino.h>
#include "globals.h"
#include "uiActLed.h"



class serialCore
{
    public:
        serialCore();
        void getSerialData();
        void writeBoardInfo();
        bool readOk();

    private:
        // WiFi
        const String actStr = "Act";
        // WiFi
        const String wifiConnectStr = "WiFiStatus";
        const String wifiUpSpeedStr = "WifiUpSpeed";
        const String wifiDlSpeedStr = "WifiDlSpeed";

        // RAM
        const String ramUsageStr = "RamUsage";
        const String ramAllStr = "RamAll";
        const String ramUseStr = "RamUse";

        // DataTime
        const String dateDev = "DateStr";
        const String timeDev = "TimeStr";

        // HDD
        const String hddUseMemStr = "HddUseMem";
        const String hddAllMemStr = "HddAllMem";
        const String hddFreeMemStr = "HddFreeMem";

        // Volume
        const String volumeStr = "Volume";

        // CPU
        const String cpuLoadStr = "CpuLoad";
        const String cpuTempStr = "CpuTemp";

};

#endif 