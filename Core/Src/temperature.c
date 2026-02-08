#include "temperature.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "stm32f429i_discovery_lcd.h"
#define TEMP_X       0      // X-Position des Textes
#define TEMP_Y       140    // Y-Position
#define TEMP_WIDTH   240    // Breite des Rechtecks zum Löschen
#define TEMP_HEIGHT  20     // Höhe des Rechtecks zum Löschen (Textgröße anpassen)


// Globale Variablen
float lastMeasuredTemp = 0;
float criticalTemp = 30.0f;
uint8_t ledOn = 0;
bool adcHasRun = false;

void displayTemperature(float temp)
{
    char buf[20];
    snprintf(buf, sizeof(buf), "%.2f C", temp);

    // Alten Textbereich löschen (mit Hintergrundfarbe)
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_FillRect(TEMP_X, TEMP_Y, TEMP_WIDTH, TEMP_HEIGHT);

    // Textfarbe wieder weiß setzen
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);

    // neuen Text zeichnen
    BSP_LCD_DisplayStringAt(TEMP_X, TEMP_Y, (uint8_t*)buf, CENTER_MODE);
}

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

// für ADC Callback
void temperatureCallback(ADC_HandleTypeDef *hadc) {
    uint32_t analogValue = HAL_ADC_GetValue(hadc);
    float temp = convertAnalogToCelsius(analogValue);
    lastMeasuredTemp = temp;
	
    checkCriticalTemperature(temp);
	
		// flag für Watchdog
    adcHasRun = true;

	
    displayTemperature(temp);
    printf("ADC: %d -> %.2f °C\n", analogValue, temp);
}
