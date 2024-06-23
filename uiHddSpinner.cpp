#include "uiHddSpinner.h"



void showHddUse()
{
  static lv_style_t stHddUseLabelStyle;
  lv_style_init(&stHddUseLabelStyle);
  lv_style_set_text_font(&stHddUseLabelStyle, &ubuntu_16);
  labelHdddUsePrcnt = lv_label_create(lv_scr_act());
  char str[10];
  sprintf(str, "%d", hddUseMem); 
  lv_label_set_text_fmt(labelHdddUsePrcnt, str);

  if (hddUseMem < 10) lv_obj_set_pos(labelHdddUsePrcnt, 362, 144);
  if ((hddUseMem >= 10) && (hddUseMem < 100)) lv_obj_set_pos(labelHdddUsePrcnt, 358, 144);
  if (hddUseMem == 100) lv_obj_set_pos(labelHdddUsePrcnt, 353, 144);

  
  lv_color_t colour;
  colour.ch.red   = 116;
  colour.ch.green = 172;
  colour.ch.blue  = 253;
  lv_style_set_text_color(&stHddUseLabelStyle, colour);
  lv_obj_add_style(labelHdddUsePrcnt, &stHddUseLabelStyle, LV_PART_MAIN);
}

void reshowHddUse()
{
  char str[10];
  sprintf(str, "%d", hddUseMem); 
  lv_label_set_text_fmt(labelHdddUsePrcnt, str);
  if (hddUseMem < 10) lv_obj_set_pos(labelHdddUsePrcnt, 362, 144);
  if ((hddUseMem >= 10) && (hddUseMem < 100)) lv_obj_set_pos(labelHdddUsePrcnt, 358, 144);
  if (hddUseMem == 100) lv_obj_set_pos(labelHdddUsePrcnt, 353, 144);
}

void showHddSpinner(bool reshow)
{
  int prcnt = hddUseMem;
  if (prcnt > 100) prcnt = 100;
  int angle = (prcnt * 360)/100;  
  if (angle == 360) angle -= 2; 
  spinnerHDD = lv_spinner_create(lv_scr_act(), 0, angle);
  lv_obj_set_size(spinnerHDD, 100, 55);
  lv_obj_set_pos(spinnerHDD, 340, 128);

   uint32_t desired_thickness = 7; 
   lv_obj_set_style_arc_width(spinnerHDD, desired_thickness, LV_PART_INDICATOR); 
   lv_obj_set_style_arc_width(spinnerHDD, desired_thickness, LV_PART_MAIN);
   if (!reshow) showHddUse();
   else reshowHddUse();
}

void reshowHddSpinner()
{
  lv_obj_del(spinnerHDD);
  showHddSpinner(true);
}
