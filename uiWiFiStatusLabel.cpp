#include "uiWiFiStatusLabel.h"

void showWiFiStatusLabel()
{
  lv_style_init(&stWiFiStatusLabelStyle);
  lv_style_set_text_font(&stWiFiStatusLabelStyle, &ubuntu_20);
  labelWiFiStatus = lv_label_create(lv_scr_act());
  if (wifiConnect) lv_label_set_text_fmt(labelWiFiStatus, "Connected");
  else lv_label_set_text_fmt(labelWiFiStatus, "Disconnected");
  lv_obj_set_pos(labelWiFiStatus, 100, 21);
  
  lv_color_t colour;
  colour.ch.red   = 116;
  colour.ch.green = 172;
  colour.ch.blue  = 253;
  // if (wifiConnect)
  // {
  //   colour.ch.red   = 0;
  //   colour.ch.green = 255;
  //   colour.ch.blue  = 0;
  // } else
  // {
  //   colour.ch.red   = 255;
  //   colour.ch.green = 0;
  //   colour.ch.blue  = 0;
  // }
  lv_style_set_text_color(&stWiFiStatusLabelStyle, colour);
  lv_obj_add_style(labelWiFiStatus, &stWiFiStatusLabelStyle, LV_PART_MAIN);
}

void reshowWiFiStatusLabel()
{
  //lv_style_init(&stWiFiStatusLabelStyle);
  if (wifiConnect) lv_label_set_text_fmt(labelWiFiStatus, "Connected");
  else lv_label_set_text_fmt(labelWiFiStatus, "Disconnected");
  
  // lv_color_t colour;
  // if (wifiConnect)
  // {
  //   colour.ch.red   = 0;
  //   colour.ch.green = 255;
  //   colour.ch.blue  = 0;
  // } else
  // {
  //   colour.ch.red   = 255;
  //   colour.ch.green = 0;
  //   colour.ch.blue  = 0;
  // }
  // lv_style_set_text_color(&stWiFiStatusLabelStyle, colour);
  // lv_obj_add_style(labelWiFiStatus, &stWiFiStatusLabelStyle, LV_PART_MAIN);
  wifiConnectOld = wifiConnect;
}
