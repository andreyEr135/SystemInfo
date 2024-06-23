#include "uiMainPage.h"


void showMainPage()
{
  showWiFiLabel();
  showWiFiStatusLabel();
  showWiFiUlLabel();
  showWiFiDlLabel();
  
  showRamLabel();
  showRamSpinner();

  showRamUsedLabel();
  showRamAllLabel();
  showRamUseLabel();
  showRamUseBar();
  
  showDateLabel();
  showTimeLabel();

  showHddLabel();
  showHddSpinner();

  showHddInfoLabel();
  showHddAllLabel();
  showHddFreeLabel();
  showVolLabel();
  showVolBar();
  showVolInfoLabel();

  showCpuTempLabel();
  showCpuSpinner();

  showActLed();
}

void reshowMainPage()
{
  if (wifiConnect != wifiConnectOld) reshowWiFiStatusLabel();
  reshowWiFiUlLabel();
  reshowWiFiDlLabel();

  reshowRamSpinner();

  reshowRamAllLabel();
  reshowRamUseLabel();
  reshowRamUseBar();
  
  reshowDateLabel();
  reshowTimeLabel();

  reshowHddSpinner();

  reshowHddAllLabel();
  reshowHddFreeLabel();

  reshowVolBar();
  reshowVolInfoLabel();

  reshowCpuTempLabel();
  reshowCpuSpinner();


}
