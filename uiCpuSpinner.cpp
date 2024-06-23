#include "uiCpuSpinner.h"



void showCpuUse()
{
  static lv_style_t stCpuUseLabelStyle;
  lv_style_init(&stCpuUseLabelStyle);
  lv_style_set_text_font(&stCpuUseLabelStyle, &ubuntu_24);
  labelCpuUsePrcnt = lv_label_create(lv_scr_act());
  char str[10];
  sprintf(str, "%d", cpuLoad); 
  lv_label_set_text_fmt(labelCpuUsePrcnt, str);

  if (cpuLoad < 10) lv_obj_set_pos(labelCpuUsePrcnt, 233, 153);
  if ((cpuLoad >= 10) && (cpuLoad < 100)) lv_obj_set_pos(labelCpuUsePrcnt, 226, 153);
  if (cpuLoad == 100) lv_obj_set_pos(labelCpuUsePrcnt, 217, 153);

  
  lv_color_t colour;
  colour.ch.red   = 116;
  colour.ch.green = 172;
  colour.ch.blue  = 253;
  lv_style_set_text_color(&stCpuUseLabelStyle, colour);
  lv_obj_add_style(labelCpuUsePrcnt, &stCpuUseLabelStyle, LV_PART_MAIN);
}

void reshowCpuUse()
{
  char str[10];
  sprintf(str, "%d", cpuLoad); 
  lv_label_set_text_fmt(labelCpuUsePrcnt, str);
  if (cpuLoad < 10) lv_obj_set_pos(labelCpuUsePrcnt, 233, 153);
  if ((cpuLoad >= 10) && (cpuLoad < 100)) lv_obj_set_pos(labelCpuUsePrcnt, 226, 153);
  if (cpuLoad == 100) lv_obj_set_pos(labelCpuUsePrcnt, 217, 153);
}

void showCpuSpinner(bool reshow)
{
  int prcnt = cpuLoad;
  if (prcnt > 100) prcnt = 100;
  int angle = (prcnt * 360)/100;  
  if (angle == 360) angle -= 2; 
  spinnerCPU = lv_spinner_create(lv_scr_act(), 0, angle);
  lv_obj_set_size(spinnerCPU, 100, 100);
  lv_obj_set_pos(spinnerCPU, 190, 120);

   uint32_t desired_thickness = 10; 
   lv_obj_set_style_arc_width(spinnerCPU, desired_thickness, LV_PART_INDICATOR); 
   lv_obj_set_style_arc_width(spinnerCPU, desired_thickness, LV_PART_MAIN);
   if (!reshow) showCpuUse();
   else reshowCpuUse();
}

void reshowCpuSpinner()
{
  lv_obj_del(spinnerCPU);
  showCpuSpinner(true);
}
