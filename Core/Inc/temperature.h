#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "stm32f4xx_hal.h"
#include <stdbool.h>

extern float lastMeasuredTemp;
extern float criticalTemp;
extern uint8_t ledOn;
extern bool adcHasRun;


void temperatureInit(ADC_HandleTypeDef* hadc);
float convertAnalogToCelsius(uint32_t adc_value);
void checkCriticalTemperature(float temp);
void temperatureCallback(ADC_HandleTypeDef *hadc);


#endif // TEMPERATURE_H
