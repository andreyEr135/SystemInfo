#include "uiCpuTempLabel.h"

void showCpuTempLabel()
{
  static lv_style_t stCpuTempLabelStyle;
  lv_style_init(&stCpuTempLabelStyle);
  lv_style_set_text_font(&stCpuTempLabelStyle, &ubuntu_24);
  labelCpuTemp = lv_label_create(lv_scr_act());
  if (cpuTemp == "") lv_label_set_text_fmt(labelCpuTemp, "0°C");
  else lv_label_set_text_fmt(labelCpuTemp, cpuTemp.c_str());
  lv_obj_set_pos(labelCpuTemp, 220, 90);
  
  lv_color_t colour;
  colour.ch.red   = 116;
  colour.ch.green = 172;
  colour.ch.blue  = 253;
  lv_style_set_text_color(&stCpuTempLabelStyle, colour);
  lv_obj_add_style(labelCpuTemp, &stCpuTempLabelStyle, LV_PART_MAIN);
}

void reshowCpuTempLabel()
{
  if (cpuTemp == "") lv_label_set_text_fmt(labelCpuTemp, "0°C");
  else lv_label_set_text_fmt(labelCpuTemp, cpuTemp.c_str());
}
