#include "uiVolInfoLabel.h"

void showVolInfoLabel()
{
  static lv_style_t stVolInfoLabelStyle;
  lv_style_init(&stVolInfoLabelStyle);
  lv_style_set_text_font(&stVolInfoLabelStyle, &ubuntu_20);
  labelVolInfo = lv_label_create(lv_scr_act());

  char str[10];
  sprintf(str, "%d%%", volume);
  lv_label_set_text_fmt(labelVolInfo, str);
  lv_obj_set_pos(labelVolInfo, 430, 280);
  
  lv_color_t colour;
  colour.ch.red   = 116;
  colour.ch.green = 172;
  colour.ch.blue  = 253;
  lv_style_set_text_color(&stVolInfoLabelStyle, colour);
  lv_obj_add_style(labelVolInfo, &stVolInfoLabelStyle, LV_PART_MAIN);
}

void reshowVolInfoLabel()
{
  char str[10];
  sprintf(str, "%d%%", volume);
  lv_label_set_text_fmt(labelVolInfo, str);
}

