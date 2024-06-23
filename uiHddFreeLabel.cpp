#include "uiHddFreeLabel.h"

void showHddFreeLabel()
{
  lv_style_init(&stHddFreeLabelStyle);
  lv_style_set_text_font(&stHddFreeLabelStyle, &ubuntu_20);
  labelHddFree = lv_label_create(lv_scr_act());
  String str = "Free: ";
  if (hddFreeMem == "") str += "0gb";
  else str += hddFreeMem;
  
  lv_label_set_text_fmt(labelHddFree, str.c_str());
  lv_obj_set_pos(labelHddFree, 350, 259);
  
  lv_color_t colour;
  colour.ch.red   = 116;
  colour.ch.green = 172;
  colour.ch.blue  = 253;
  lv_style_set_text_color(&stHddFreeLabelStyle, colour);
  lv_obj_add_style(labelHddFree, &stHddFreeLabelStyle, LV_PART_MAIN);
}

void reshowHddFreeLabel()
{
  String str = "Free: ";
  if (hddFreeMem == "") str += "0gb";
  else str += hddFreeMem;

  lv_label_set_text_fmt(labelHddFree, str.c_str());
}
