#ifndef UIMODULES_H
#define UIMODULES_H

#include <iostream>
#include <string>

#include <Arduino.h>

#include "lvgl.h"

// Create an instance of the prepared class
#include <lvgl.h>

// styles
extern lv_style_t style_def;
extern lv_style_t style_pr;



//Main Page
// WiFi Block
extern lv_obj_t *labelWiFi;
extern lv_obj_t *labelWiFiStatus;
extern lv_obj_t *labelWiFiUL;
extern lv_obj_t *labelWiFiDL;

// RAM Block
extern lv_obj_t *labelRAM;
extern lv_obj_t *spinnerRAM; 
extern lv_obj_t *labelRamUsePrcnt;

// RAM Used block
extern lv_obj_t *labelRamUsed;
extern lv_obj_t *labelRamAll;
extern lv_obj_t *labelRamUse;
extern lv_obj_t *barRamUse; 

// DataTime Block
extern lv_obj_t *labelDate;
extern lv_obj_t *labelTime;

// HDD block
extern lv_obj_t *labelHDD;
extern lv_obj_t *spinnerHDD; 
extern lv_obj_t *labelHdddUsePrcnt;

// HDD info block
extern lv_obj_t *labelHddInfo;
extern lv_obj_t *labelHddAll;
extern lv_obj_t *labelHddFree;

// Volume
extern lv_obj_t *labelVol;
extern lv_obj_t *barVol;
extern lv_obj_t *labelVolInfo;

// CPU Block
extern lv_obj_t *labelCpuTemp;
extern lv_obj_t *spinnerCPU; 
extern lv_obj_t *labelCpuUsePrcnt;

// Activity
extern lv_obj_t *ledAct; 


// Timer
extern TaskHandle_t timerDispTask;
extern lv_timer_t *dispTimer;

#endif 