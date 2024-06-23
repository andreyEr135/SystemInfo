#include "globals.h"

// LGFX
LGFX tft;

// Display
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);
  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
  tft.endWrite();
  lv_disp_flush_ready(disp);
}

// Sensor
/*void my_touch_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  uint16_t touchX, touchY;
  bool touched = tft.getTouch(&touchX, &touchY);
  if (!touched)
  {
    data->state = LV_INDEV_STATE_REL;
  }
  else
  {
    data->state = LV_INDEV_STATE_PR;
    data->point.x = touchX;
    data->point.y = touchY;
  }
}*/

// Parameters
// WiFi
bool wifiConnectOld = false;
bool wifiConnect = false;
String upSpeed = "";
String dlSpeed = "";

// RAM
int ramUsagePrcnt = 0;
String ramAllMem = "";
String ramUseMem = "";

// DataTime
String dateStr = "";
String timeStr = "";

// HDD
int hddUseMem = 0;
String hddAllMem = "";
String hddFreeMem = "";

// Volume
int volume = 0;

// CPU
int cpuLoad = 0;
String cpuTemp = "";
