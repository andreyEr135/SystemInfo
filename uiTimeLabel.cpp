#include "uiTimeLabel.h"
#include <TimeLib.h>

void showTimeLabel()
{
  static lv_style_t stTimeLabelStyle;
  lv_style_init(&stTimeLabelStyle);
  lv_style_set_text_font(&stTimeLabelStyle, &ubuntu_24);
  labelTime = lv_label_create(lv_scr_act());
  if (timeStr == "") lv_label_set_text_fmt(labelTime, "--:--");
  else 
  {
    lv_label_set_text_fmt(labelTime, timeStr.c_str());
  }
  lv_obj_set_pos(labelTime, 379, 70);
  
  lv_color_t colour;
  colour.ch.red   = 116;
  colour.ch.green = 172;
  colour.ch.blue  = 253;
  lv_style_set_text_color(&stTimeLabelStyle, colour);
  lv_obj_add_style(labelTime, &stTimeLabelStyle, LV_PART_MAIN);
}

void reshowTimeLabel()
{
  if (timeStr == "") lv_label_set_text_fmt(labelTime, "--:--");
  else 
  {
    lv_label_set_text_fmt(labelTime, timeStr.c_str());
  }
}
