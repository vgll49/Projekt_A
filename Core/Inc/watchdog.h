#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "stm32f4xx_hal.h"
#include <stdbool.h>

extern float watchDogThreshhold;
extern bool simulateHang;

void watchdogInit(IWDG_HandleTypeDef *hiwdg);
void handleWatchdog(IWDG_HandleTypeDef *hiwdg, float lastMeasuredTemp, bool adcHasRun);

#endif // WATCHDOG_H
