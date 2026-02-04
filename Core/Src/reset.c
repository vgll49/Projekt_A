#include "reset.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>

void getResetReason(void) {
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST)) {
        printf("WATCHDOG RESET: HÄNGER BEI WENIG LAST!\r\n");
    }
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST)) {
        printf("RESET durch externen Reset-Pin (NRST)!\r\n");
    }
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST)) {
        printf("Power-On-Reset!\r\n");
    }
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST)) {
        printf("Software-Reset!\r\n");
    }
    __HAL_RCC_CLEAR_RESET_FLAGS();
}
