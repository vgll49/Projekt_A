#include "temperature.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>

// Globale Variablen
float lastMeasuredTemp = 0;
float criticalTemp = 30.0f;
uint8_t ledOn = 0;
bool adcHasRun = false;

float convertAnalogToCelsius(uint32_t adc_value) {
    const float VREF = 3.0f;
    const float V25 = 0.76f;
    const float AVG_SLOPE = 0.0025f;

    float v_sense = (adc_value * VREF) / 4095.0f;
    return ((v_sense - V25) / AVG_SLOPE) + 25.0f;
}

void checkCriticalTemperature(float temp) {
    if (temp > criticalTemp) {
        if (!ledOn) {
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
            ledOn = 1;
        }
    } else {
        if (ledOn) {
            HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
            ledOn = 0;
        }
    }
}

// ADC Callback
void temperatureCallback(ADC_HandleTypeDef *hadc) {
    uint32_t analogValue = HAL_ADC_GetValue(hadc);
    float temp = convertAnalogToCelsius(analogValue);
    lastMeasuredTemp = temp;
	
    checkCriticalTemperature(temp);
	
		// Flag für Watchdog
    adcHasRun = true;

    printf("ADC: %d -> %.2f °C\n", analogValue, temp);
}
