#include "uiActLed.h"

void onActLed()
{
  //ledState = true;
  countLed = 0;
  lv_led_set_brightness(ledAct, 150);
}
void offActLed()
{
  //ledState = false;
  countLed = 0;
  lv_led_set_brightness(ledAct, 10);
}

void showActLed()
{
  ledAct = lv_led_create(lv_scr_act());
  lv_obj_set_pos(ledAct, 182, 100); 
  lv_obj_set_size(ledAct, 20, 20);
  lv_led_set_color(ledAct, lv_palette_main(LV_PALETTE_GREEN));
  offActLed();
}



void reshowActLed()
{
  if (ledState) onActLed();
  else offActLed();
  oldLedState = ledState;
}