#include "uiRamSpinner.h"



void showRamUse()
{
  static lv_style_t stRamUseLabelStyle;
  lv_style_init(&stRamUseLabelStyle);
  lv_style_set_text_font(&stRamUseLabelStyle, &ubuntu_16);
  labelRamUsePrcnt = lv_label_create(lv_scr_act());
  char str[10];
  sprintf(str, "%d", ramUsagePrcnt); 
  lv_label_set_text_fmt(labelRamUsePrcnt, str);

  if (ramUsagePrcnt < 10) lv_obj_set_pos(labelRamUsePrcnt, 105, 144);
  if ((ramUsagePrcnt >= 10) && (ramUsagePrcnt < 100)) lv_obj_set_pos(labelRamUsePrcnt, 103, 144);
  if (ramUsagePrcnt == 100) lv_obj_set_pos(labelRamUsePrcnt, 98, 144);

  
  lv_color_t colour;
  colour.ch.red   = 116;
  colour.ch.green = 172;
  colour.ch.blue  = 253;
  lv_style_set_text_color(&stRamUseLabelStyle, colour);
  lv_obj_add_style(labelRamUsePrcnt, &stRamUseLabelStyle, LV_PART_MAIN);
}

void reshowRamUse()
{
  char str[10];
  sprintf(str, "%d", ramUsagePrcnt); 
  lv_label_set_text_fmt(labelRamUsePrcnt, str);
  if (ramUsagePrcnt < 10) lv_obj_set_pos(labelRamUsePrcnt, 105, 144);
  if ((ramUsagePrcnt >= 10) && (ramUsagePrcnt < 100)) lv_obj_set_pos(labelRamUsePrcnt, 103, 144);
  if (ramUsagePrcnt == 100) lv_obj_set_pos(labelRamUsePrcnt, 98, 144);
}

void showRamSpinner(bool reshow)
{
  int prcnt = ramUsagePrcnt;
  if (prcnt > 100) prcnt = 100;
  int angle = (prcnt * 360)/100;  
  if (angle == 360) angle -= 2; 
  spinnerRAM = lv_spinner_create(lv_scr_act(), 0, angle);
  lv_obj_set_size(spinnerRAM, 100, 55);
  lv_obj_set_pos(spinnerRAM, 85, 128);

   uint32_t desired_thickness = 7; 
   lv_obj_set_style_arc_width(spinnerRAM, desired_thickness, LV_PART_INDICATOR); 
   lv_obj_set_style_arc_width(spinnerRAM, desired_thickness, LV_PART_MAIN);
   if (!reshow) showRamUse();
   else reshowRamUse();
}

void reshowRamSpinner()
{
  lv_obj_del(spinnerRAM);
  showRamSpinner(true);
}
