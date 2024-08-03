#include "serialCore.h"


serialCore::serialCore()
{
  Serial.begin(115200);
}
void serialCore::getSerialData()
{
  size_t sz = Serial.readBytes(uData.buf, sizeof(uData.buf));
  if (sz > 0)
  {
    if (backlight) countNoAct = 0;
    else {
      countNoAct = 0;
      backlight = true;
    }
    ledState = true; 
    wifiConnect = uData.data.wifiStatus;
    upSpeed = (String)uData.data.wifiUp;
    dlSpeed = (String)uData.data.wifiDl;
    ramUsagePrcnt = uData.data.ramStat;
    char str[30];
    memset(str, 0, sizeof(str));
    sprintf(str, "%.2fgb", uData.data.ramAll);
    ramAllMem = String(str);
    memset(str, 0, sizeof(str));
    sprintf(str, "%.2fgb", uData.data.ramUse);
    ramUseMem = String(str);
    dateStr = (String)uData.data.date;
    timeStr = (String)uData.data.time;
    hddUseMem = uData.data.hddStat;
    memset(str, 0, sizeof(str));
    sprintf(str, "%.0fgb", uData.data.hddAll);
    hddAllMem = String(str);
    memset(str, 0, sizeof(str));
    sprintf(str, "%.0fgb", uData.data.hddFree);
    hddFreeMem = String(str);
    volume = uData.data.vol;
    cpuLoad = uData.data.cpu_load;
    memset(str, 0, sizeof(str));
    sprintf(str, "%d°C", uData.data.cpu_temp);
    cpuTemp = String(str);  
  }

}

void serialCore::writeBoardInfo()
{
  Serial.println("SystemInfo Board");
}

bool serialCore::readOk()
{
  bool res = false;
  char buf[5];
  memset(buf,0,sizeof(buf));
  size_t sz = Serial.readBytes(buf, sizeof(buf));
  if (sz >= 2)
  {
    if ( (buf[0] == 'O') && (buf[1] == 'K')) res = true;
  }
  return res;
}


