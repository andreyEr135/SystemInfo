#include "uiHddLabel.h"

void showHddLabel()
{
  static lv_style_t stHddLabelStyle;
  lv_style_init(&stHddLabelStyle);
  lv_style_set_text_font(&stHddLabelStyle, &ubuntu_24);
  labelHDD = lv_label_create(lv_scr_act());
  lv_label_set_text_fmt(labelHDD, "HDD");
  lv_obj_set_pos(labelHDD, 415, 138);
  
  lv_color_t colour;
  colour.ch.red   = 116;
  colour.ch.green = 172;
  colour.ch.blue  = 253;
  lv_style_set_text_color(&stHddLabelStyle, colour);
  lv_obj_add_style(labelHDD, &stHddLabelStyle, LV_PART_MAIN);
}

