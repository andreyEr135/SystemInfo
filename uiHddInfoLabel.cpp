#include "uiHddInfoLabel.h"

void showHddInfoLabel()
{
  static lv_style_t stHddInfoLabelStyle;
  lv_style_init(&stHddInfoLabelStyle);
  lv_style_set_text_font(&stHddInfoLabelStyle, &ubuntu_24);
  labelHddInfo = lv_label_create(lv_scr_act());
  lv_label_set_text_fmt(labelHddInfo, "HDD INFO");
  lv_obj_set_pos(labelHddInfo, 350, 212);
  
  lv_color_t colour;
  colour.ch.red   = 116;
  colour.ch.green = 172;
  colour.ch.blue  = 253;
  lv_style_set_text_color(&stHddInfoLabelStyle, colour);
  lv_obj_add_style(labelHddInfo, &stHddInfoLabelStyle, LV_PART_MAIN);
}

