#include "uiRamAllLabel.h"

void showRamAllLabel()
{
  lv_style_init(&stRamAllLabelStyle);
  lv_style_set_text_font(&stRamAllLabelStyle, &ubuntu_20);
  labelRamAll = lv_label_create(lv_scr_act());
  String str = "All: ";
  if (ramAllMem == "") str += "0mb";
  else str += ramAllMem;
  
  lv_label_set_text_fmt(labelRamAll, str.c_str());
  lv_obj_set_pos(labelRamAll, 18, 239);
  
  lv_color_t colour;
  colour.ch.red   = 116;
  colour.ch.green = 172;
  colour.ch.blue  = 253;
  lv_style_set_text_color(&stRamAllLabelStyle, colour);
  lv_obj_add_style(labelRamAll, &stRamAllLabelStyle, LV_PART_MAIN);
}

void reshowRamAllLabel()
{
  String str = "All: ";
  if (ramAllMem == "") str += "0mb";
  else str += ramAllMem;

  lv_label_set_text_fmt(labelRamAll, str.c_str());
}
