#include "watchdog.h"

float watchDogThreshhold = 25.0f;
bool simulateHang = false;

void handleWatchdog(IWDG_HandleTypeDef *hiwdg, float lastMeasuredTemp, bool adcHasRun) {
    if (adcHasRun) {
        simulateHang = (lastMeasuredTemp < watchDogThreshhold);
    } else {
        simulateHang = false; // Watchdog nach Reset füttern
    }

    if (!simulateHang) {
        HAL_IWDG_Refresh(hiwdg);
    }
}
