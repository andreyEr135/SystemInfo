#include "uiVolLabel.h"

void showVolLabel()
{
  static lv_style_t stVolLabelStyle;
  lv_style_init(&stVolLabelStyle);
  lv_style_set_text_font(&stVolLabelStyle, &ubuntu_20);
  labelVol = lv_label_create(lv_scr_act());
  lv_label_set_text_fmt(labelVol, "Vol");
  lv_obj_set_pos(labelVol, 258, 280);
  
  lv_color_t colour;
  colour.ch.red   = 116;
  colour.ch.green = 172;
  colour.ch.blue  = 253;
  lv_style_set_text_color(&stVolLabelStyle, colour);
  lv_obj_add_style(labelVol, &stVolLabelStyle, LV_PART_MAIN);
}

