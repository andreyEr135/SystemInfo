#define LGFX_USE_V1

#include <LovyanGFX.hpp>
#include "Arduino.h"
#include "globals.h"

#include "lvgl.h"

// Create an instance of the prepared class
#include <lvgl.h>

#include <TimeLib.h>

#include "uiMainPage.h"
//#include "uiModules.h"

#include "serialCore.h"
#include "uiActLed.h"


serialCore *serialData;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];

bool dateTimeSync = false;


int bl;
void offBacklight()
{
  if (bl == 255)
  {
    for (bl = 255; bl>=0; bl--)
    {
      tft.setBrightness(bl);
      delay(2);
    }
  }
}

void onBacklight()
{
  if (bl != 255)
  {
    for (bl = 0; bl<=255; bl++)
    {
      tft.setBrightness(bl);
      //delay(2);
    }
  }
}

//every 100 ms
void tickTimer(lv_timer_t * timer)
{
  if (countNoAct > 30*10) backlight = false;
  if (countLed == 5) ledState = false;
  if (backlight) 
  {
    bl = 255;
    tft.setBrightness(bl);
    //onBacklight();
  }
  else 
  {
    offBacklight();
  }

  reshowMainPage();
  if (ledState) countLed++;
  countNoAct++;
  
}


void showBackground()
{
  LV_IMG_DECLARE(bg);
  lv_obj_t *backgroundImg = lv_img_create(lv_scr_act());
  lv_img_set_src(backgroundImg, &bg);
  lv_obj_set_pos(backgroundImg, 0, 0);  
}

// Create a slider and write its value on a label.
void CreateControls(void)
{
  /*Create a transition animation on width transformation and recolor.*/
  static lv_style_prop_t tr_prop[] = {LV_STYLE_TRANSFORM_WIDTH, LV_STYLE_IMG_RECOLOR_OPA};
  static lv_style_transition_dsc_t tr;
  lv_style_transition_dsc_init(&tr, tr_prop, lv_anim_path_linear, 0, 0, NULL);

  lv_style_init(&style_def);
  lv_style_set_text_color(&style_def, lv_color_white());
  lv_style_set_transition(&style_def, &tr);

  /*Darken the button when pressed and make it wider*/
  lv_style_init(&style_pr);
  lv_style_set_img_recolor_opa(&style_pr, LV_OPA_30);
  lv_style_set_img_recolor(&style_pr, lv_color_black());
  //lv_style_set_transform_width(&style_pr, 20);

  showBackground();

  showMainPage(); 
}


void displaySetup()
{
  tft.begin();
  tft.setRotation(3);
  bl = 255;
  tft.setBrightness(bl);

  lv_init();
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10);
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  //indev_drv.read_cb = my_touch_read;
  lv_indev_drv_register(&indev_drv);  
}

/*bool wifiSetup()
{
  wifiConnect = false;
  audio_showstation("Waiting connection to WiFi");
  audio_showstreamtitle(ssid.c_str());
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  int t_sec = 0;
  while (WiFi.status() != WL_CONNECTED) 
  {
    t_sec++;
    if (t_sec > TIMEOUT_WIFI_CONNECT)
    {
      if (WiFi.status() != WL_CONNECTED)
      {
        audio_showstation("Connect to WiFi error");
        audio_showstreamtitle(ssid.c_str());
        return false;
      }
    }
    delay(1000);
  }  
  audio_showstation("Connected to WiFi");
  return true;
}*/

void Task_Audio(void *pvParameters) // This is a task.
{
  while (true)
  {
    serialData->getSerialData();
    delay(100);
  }
}

void setup() {
  displaySetup();

  

  CreateControls();
  serialData = new serialCore();

  delay(1000); 
  dispTimer = lv_timer_create(tickTimer, 100,  NULL);

  xTaskCreatePinnedToCore(Task_Audio, "Task_Audio", 10240, NULL, 3, NULL, 0);
  
  
}




void loop() {
  lv_timer_handler();  
}
