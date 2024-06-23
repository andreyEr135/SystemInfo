#include "uiRamUseLabel.h"

void showRamUseLabel()
{
  lv_style_init(&stRamUseLabelStyle);
  lv_style_set_text_font(&stRamUseLabelStyle, &ubuntu_20);
  labelRamUse = lv_label_create(lv_scr_act());
  String str = "Use: ";
  if (ramUseMem == "") str += "0mb";
  else str += ramUseMem;
  
  lv_label_set_text_fmt(labelRamUse, str.c_str());
  lv_obj_set_pos(labelRamUse, 18, 259);
  
  lv_color_t colour;
  colour.ch.red   = 116;
  colour.ch.green = 172;
  colour.ch.blue  = 253;
  lv_style_set_text_color(&stRamUseLabelStyle, colour);
  lv_obj_add_style(labelRamUse, &stRamUseLabelStyle, LV_PART_MAIN);
}

void reshowRamUseLabel()
{
  String str = "Use: ";
  if (ramUseMem == "") str += "0mb";
  else str += ramUseMem;

  lv_label_set_text_fmt(labelRamUse, str.c_str());
}
