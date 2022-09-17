#ifndef _MK_HELPER
#define _MK_HELPER
#include "STM32FreeRTOS.h"

#define MK_TASK_DELAY_MS(num) vTaskDelay((num * configTICK_RATE_HZ) / 1000L);

#endif