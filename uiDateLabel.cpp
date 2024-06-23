#include "uiDateLabel.h"
#include <TimeLib.h>

void showDateLabel()
{
  static lv_style_t stDateLabelStyle;
  lv_style_init(&stDateLabelStyle);
  lv_style_set_text_font(&stDateLabelStyle, &ubuntu_24);
  labelDate = lv_label_create(lv_scr_act());
  if (dateStr == "") lv_label_set_text_fmt(labelDate, "--/--/----");
  else 
  {
    lv_label_set_text_fmt(labelDate, dateStr.c_str());
  }
  lv_obj_set_pos(labelDate, 330, 21);
  
  lv_color_t colour;
  colour.ch.red   = 116;
  colour.ch.green = 172;
  colour.ch.blue  = 253;
  lv_style_set_text_color(&stDateLabelStyle, colour);
  lv_obj_add_style(labelDate, &stDateLabelStyle, LV_PART_MAIN);
}

void reshowDateLabel()
{
  if (dateStr == "") lv_label_set_text_fmt(labelDate, "--/--/----");
  else 
  {
    lv_label_set_text_fmt(labelDate, dateStr.c_str());
  }
}
