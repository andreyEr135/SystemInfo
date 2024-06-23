#include "uiRamUsedLabel.h"

void showRamUsedLabel()
{
  static lv_style_t stRamUsedLabelStyle;
  lv_style_init(&stRamUsedLabelStyle);
  lv_style_set_text_font(&stRamUsedLabelStyle, &ubuntu_24);
  labelRamUsed = lv_label_create(lv_scr_act());
  lv_label_set_text_fmt(labelRamUsed, "RAM USED");
  lv_obj_set_pos(labelRamUsed, 16, 212);
  
  lv_color_t colour;
  colour.ch.red   = 116;
  colour.ch.green = 172;
  colour.ch.blue  = 253;
  lv_style_set_text_color(&stRamUsedLabelStyle, colour);
  lv_obj_add_style(labelRamUsed, &stRamUsedLabelStyle, LV_PART_MAIN);
}
