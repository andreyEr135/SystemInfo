#include "uiWiFiDlLabel.h"

void showWiFiDlLabel()
{
  lv_style_init(&stWiFiDlLabelStyle);
  lv_style_set_text_font(&stWiFiDlLabelStyle, &ubuntu_20);
  labelWiFiDL = lv_label_create(lv_scr_act());
  String str = "D: ";
  if (dlSpeed == "") str += "0mb/s";
  else str += dlSpeed;
  
  lv_label_set_text_fmt(labelWiFiDL, str.c_str());
  lv_obj_set_pos(labelWiFiDL, 18, 80);
  
  lv_color_t colour;
  colour.ch.red   = 116;
  colour.ch.green = 172;
  colour.ch.blue  = 253;
  lv_style_set_text_color(&stWiFiDlLabelStyle, colour);
  lv_obj_add_style(labelWiFiDL, &stWiFiDlLabelStyle, LV_PART_MAIN);
}

void reshowWiFiDlLabel()
{
  String str = "D: ";
  if (dlSpeed == "") str += "0mb/s";
  else str += dlSpeed;

  lv_label_set_text_fmt(labelWiFiDL, str.c_str());
}
