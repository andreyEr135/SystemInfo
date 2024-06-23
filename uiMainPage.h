#ifndef UIMAINPAGE_H
#define UIMAINPAGE_H

#include <iostream>
#include <string>

#include <Arduino.h>

#include "globals.h"

#include "uiWiFiLabel.h"
#include "uiWiFiStatusLabel.h"
#include "uiWiFiUlLabel.h"
#include "uiWiFiDlLabel.h"

#include "uiRamLabel.h"
#include "uiRamSpinner.h"

#include "uiRamUsedLabel.h"
#include "uiRamAllLabel.h"
#include "uiRamUseLabel.h"
#include "uiRamUseBar.h"


#include "uiDateLabel.h"
#include "uiTimeLabel.h"

#include "uiHddLabel.h"
#include "uiHddSpinner.h"


#include "uiHddInfoLabel.h"
#include "uiHddAllLabel.h"
#include "uiHddFreeLabel.h"
#include "uiVolLabel.h"
#include "uiVolBar.h"
#include "uiVolInfoLabel.h"

#include "uiCpuTempLabel.h"
#include "uiCpuSpinner.h"

#include "uiActLed.h"






//#include "uiModules.h"

extern void showMainPage();
extern void reshowMainPage();


#endif 