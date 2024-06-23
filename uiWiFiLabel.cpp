#include "uiWiFiLabel.h"

void showWiFiLabel()
{
  static lv_style_t stWiFiLabelStyle;
  lv_style_init(&stWiFiLabelStyle);
  lv_style_set_text_font(&stWiFiLabelStyle, &ubuntu_24);
  labelWiFi = lv_label_create(lv_scr_act());
  lv_label_set_text_fmt(labelWiFi, "WIFI");
  lv_obj_set_pos(labelWiFi, 24, 21);
  
  lv_color_t colour;
  colour.ch.red   = 116;
  colour.ch.green = 172;
  colour.ch.blue  = 253;
  lv_style_set_text_color(&stWiFiLabelStyle, colour);
  lv_obj_add_style(labelWiFi, &stWiFiLabelStyle, LV_PART_MAIN);
}
