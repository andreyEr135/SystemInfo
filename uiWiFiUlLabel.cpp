#include "uiWiFiUlLabel.h"

void showWiFiUlLabel()
{
  lv_style_init(&stWiFiUlLabelStyle);
  lv_style_set_text_font(&stWiFiUlLabelStyle, &ubuntu_20);
  labelWiFiUL = lv_label_create(lv_scr_act());
  String str = "U: ";
  if (upSpeed == "") str += "0mb/s";
  else str += upSpeed;
  
  lv_label_set_text_fmt(labelWiFiUL, str.c_str());
  lv_obj_set_pos(labelWiFiUL, 18, 52);
  
  lv_color_t colour;
  colour.ch.red   = 116;
  colour.ch.green = 172;
  colour.ch.blue  = 253;
  lv_style_set_text_color(&stWiFiUlLabelStyle, colour);
  lv_obj_add_style(labelWiFiUL, &stWiFiUlLabelStyle, LV_PART_MAIN);
}

void reshowWiFiUlLabel()
{
  String str = "U: ";
  if (upSpeed == "") str += "0mb/s";
  else str += upSpeed;

  lv_label_set_text_fmt(labelWiFiUL, str.c_str());
}
