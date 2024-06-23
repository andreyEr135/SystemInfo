#include "serialCore.h"


serialCore::serialCore()
{
  Serial.begin(115200);
}
void serialCore::getSerialData()
{
  String data = Serial.readStringUntil('\n');
  if (data.indexOf(wifiConnectStr) >= 0)
  {
    data = data.substring(data.indexOf(wifiConnectStr) + wifiConnectStr.length() + 1);
    if (data == "1") wifiConnect = true;
    else wifiConnect = false;
  }

  if (data.indexOf(wifiUpSpeedStr) >= 0)
  {
    data = data.substring(data.indexOf(wifiUpSpeedStr) + wifiUpSpeedStr.length() + 1);
    upSpeed = data;
  }

  if (data.indexOf(wifiDlSpeedStr) >= 0)
  {
    data = data.substring(data.indexOf(wifiDlSpeedStr) + wifiDlSpeedStr.length() + 1);
    dlSpeed = data;
    offActLed();
  }

  if (data.indexOf(ramUsageStr) >= 0)
  {
    data = data.substring(data.indexOf(ramUsageStr) + ramUsageStr.length() + 1);
    ramUsagePrcnt = atoi(data.c_str());
  }

  if (data.indexOf(ramAllStr) >= 0)
  {
    data = data.substring(data.indexOf(ramAllStr) + ramAllStr.length() + 1);
    ramAllMem = data + "mb";
  }

  if (data.indexOf(ramUseStr) >= 0)
  {
    data = data.substring(data.indexOf(ramUseStr) + ramUseStr.length() + 1);
    ramUseMem = data + "mb";
  }

  if (data.indexOf(dateDev) >= 0)
  {
    data = data.substring(data.indexOf(dateDev) + dateDev.length() + 1);
    dateStr = data;
  }

  if (data.indexOf(timeDev) >= 0)
  {
    data = data.substring(data.indexOf(timeDev) + timeDev.length() + 1);
    timeStr = data;
  }

  if (data.indexOf(hddUseMemStr) >= 0)
  {
    data = data.substring(data.indexOf(hddUseMemStr) + hddUseMemStr.length() + 1);
    hddUseMem = atoi(data.c_str());
  }

  if (data.indexOf(hddAllMemStr) >= 0)
  {
    data = data.substring(data.indexOf(hddAllMemStr) + hddAllMemStr.length() + 1);
    hddAllMem = data + "gb";
  }

  if (data.indexOf(hddFreeMemStr) >= 0)
  {
    data = data.substring(data.indexOf(hddFreeMemStr) + hddFreeMemStr.length() + 1);
    hddFreeMem = data + "gb";
  }

  if (data.indexOf(volumeStr) >= 0)
  {
    data = data.substring(data.indexOf(volumeStr) + volumeStr.length() + 1);
    volume = atoi(data.c_str());
  }

  if (data.indexOf(cpuLoadStr) >= 0)
  {
    onActLed();
    data = data.substring(data.indexOf(cpuLoadStr) + cpuLoadStr.length() + 1);
    cpuLoad = atoi(data.c_str());
  }

  if (data.indexOf(cpuTempStr) >= 0)
  {
    data = data.substring(data.indexOf(cpuTempStr) + cpuTempStr.length() + 1);
    cpuTemp = data + "°C";
  }

}


