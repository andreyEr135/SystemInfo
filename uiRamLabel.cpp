#include "uiRamLabel.h"

void showRamLabel()
{
  static lv_style_t stRamLabelStyle;
  lv_style_init(&stRamLabelStyle);
  lv_style_set_text_font(&stRamLabelStyle, &ubuntu_24);
  labelRAM = lv_label_create(lv_scr_act());
  lv_label_set_text_fmt(labelRAM, "RAM");
  lv_obj_set_pos(labelRAM, 16, 138);
  
  lv_color_t colour;
  colour.ch.red   = 116;
  colour.ch.green = 172;
  colour.ch.blue  = 253;
  lv_style_set_text_color(&stRamLabelStyle, colour);
  lv_obj_add_style(labelRAM, &stRamLabelStyle, LV_PART_MAIN);
}
