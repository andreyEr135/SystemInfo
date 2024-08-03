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
        union _uData
        {
          struct 
          {
            uint cpu_load; // 4 byte
            uint cpu_temp; // 4 byte
            bool wifiStatus; // 1 byte
            char wifiDl[30]; // 30 byte
            char wifiUp[30]; // 30 byte
            uint ramStat; // 4 byte
            float ramAll; // 4 byte
            float ramUse; // 4 byte
            char date[40];
		        char time[40];
            uint hddStat; // 4 byte
            float hddAll; // 4 byte
            float hddFree; // 4 byte
            uint vol; // 4 byte 
          } data;
          char buf[180];
        };
        _uData uData;

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