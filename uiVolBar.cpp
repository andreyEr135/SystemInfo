#include "uiVolBar.h"


// static void event_cb(lv_event_t * e)
// {
//     lv_obj_t * obj = lv_event_get_target(e);

//     lv_draw_label_dsc_t label_dsc;
//     lv_draw_label_dsc_init(&label_dsc);
//     label_dsc.font = LV_FONT_DEFAULT;

//     char buf[8];
//     lv_snprintf(buf, sizeof(buf), "%d", (int)lv_bar_get_value(obj));

//     lv_point_t txt_size;
//     lv_text_get_size(&txt_size, buf, label_dsc.font, label_dsc.letter_space, label_dsc.line_space, LV_COORD_MAX,
//                      label_dsc.flag);

//     lv_area_t txt_area;
//     txt_area.x1 = 0;
//     txt_area.x2 = txt_size.x - 1;
//     txt_area.y1 = 0;
//     txt_area.y2 = txt_size.y - 1;

//     lv_bar_t * bar = (lv_bar_t *) obj;
//     const lv_area_t * indic_area = &bar->indic_area;

//     /*If the indicator is long enough put the text inside on the right*/
//     if(lv_area_get_width(indic_area) > txt_size.x + 20) {
//         lv_area_align(indic_area, &txt_area, LV_ALIGN_RIGHT_MID, -10, 0);
//         label_dsc.color = lv_color_white();
//     }
//     /*If the indicator is still short put the text out of it on the right*/
//     else {
//         lv_area_align(indic_area, &txt_area, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
//         label_dsc.color = lv_color_black();
//     }
//     label_dsc.text = buf;
//     label_dsc.text_local = true;
//     lv_layer_t * layer = lv_event_get_layer(e);
//     lv_draw_label(layer, &label_dsc, &txt_area);
// }



void showVolBar()
{
  barVol = lv_bar_create(lv_scr_act());
  lv_obj_set_size(barVol, 125, 15);
  lv_obj_set_pos(barVol, 295, 286);
  lv_bar_set_value(barVol, volume, LV_ANIM_OFF);

  //lv_obj_add_event_cb(barRamUse, event_cb, LV_EVENT_DRAW_MAIN_END, NULL);

  /*lv_anim_t a;
  lv_anim_init(&a);
  lv_anim_set_var(&a, bar);
  lv_anim_set_values(&a, 0, 100);
  lv_anim_set_exec_cb(&a, set_value);
  lv_anim_set_duration(&a, 4000);
  lv_anim_set_playback_duration(&a, 4000);
  lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
  lv_anim_start(&a);*/
}

void reshowVolBar()
{
  lv_bar_set_value(barVol, volume, LV_ANIM_OFF);
}
