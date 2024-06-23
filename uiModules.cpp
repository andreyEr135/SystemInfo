#include "uiModules.h"

// styles
lv_style_t style_def;
lv_style_t style_pr;


//Main Page
// WiFi Block
lv_obj_t *labelWiFi;
lv_obj_t *labelWiFiStatus;
lv_obj_t *labelWiFiUL;
lv_obj_t *labelWiFiDL;

// RAM Block
lv_obj_t *labelRAM;
lv_obj_t *spinnerRAM; 
lv_obj_t *labelRamUsePrcnt;

// RAM Used block
lv_obj_t *labelRamUsed;
lv_obj_t *labelRamAll;
lv_obj_t *labelRamUse;
lv_obj_t *barRamUse; 

// DataTime Block
lv_obj_t *labelDate;
lv_obj_t *labelTime;

// HDD block
lv_obj_t *labelHDD;
lv_obj_t *spinnerHDD; 
lv_obj_t *labelHdddUsePrcnt;

// HDD info block
lv_obj_t *labelHddInfo;
lv_obj_t *labelHddAll;
lv_obj_t *labelHddFree;

// Volume
lv_obj_t *labelVol;
lv_obj_t *barVol;
lv_obj_t *labelVolInfo;

// CPU Block
lv_obj_t *labelCpuTemp;
lv_obj_t *spinnerCPU; 
lv_obj_t *labelCpuUsePrcnt;

// Activity
lv_obj_t *ledAct;


// Timer
TaskHandle_t timerDispTask;
lv_timer_t *dispTimer;

 