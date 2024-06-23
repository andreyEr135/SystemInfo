#include "uiHddAllLabel.h"

void showHddAllLabel()
{
  lv_style_init(&stHddAllLabelStyle);
  lv_style_set_text_font(&stHddAllLabelStyle, &ubuntu_20);
  labelHddAll = lv_label_create(lv_scr_act());
  String str = "All: ";
  if (hddAllMem == "") str += "0gb";
  else str += hddAllMem;
  
  lv_label_set_text_fmt(labelHddAll, str.c_str());
  lv_obj_set_pos(labelHddAll, 350, 239);
  
  lv_color_t colour;
  colour.ch.red   = 116;
  colour.ch.green = 172;
  colour.ch.blue  = 253;
  lv_style_set_text_color(&stHddAllLabelStyle, colour);
  lv_obj_add_style(labelHddAll, &stHddAllLabelStyle, LV_PART_MAIN);
}

void reshowHddAllLabel()
{
  String str = "All: ";
  if (hddAllMem == "") str += "0gb";
  else str += hddAllMem;

  lv_label_set_text_fmt(labelHddAll, str.c_str());
}
