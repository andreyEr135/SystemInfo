#include "uiActLed.h"

void showActLed()
{
  ledAct = lv_led_create(lv_scr_act());
  lv_obj_set_pos(ledAct, 182, 100); 
  lv_obj_set_size(ledAct, 20, 20);
  lv_led_set_color(ledAct, lv_palette_main(LV_PALETTE_GREEN));
  offActLed();
}

void onActLed()
{
  lv_led_set_brightness(ledAct, 150);
}
void offActLed()
{
  lv_led_set_brightness(ledAct, 10);
}