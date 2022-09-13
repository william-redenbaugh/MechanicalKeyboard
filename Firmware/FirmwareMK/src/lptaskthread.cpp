#include "lptaskthread.h"
#include "STM32FreeRTOS.h"
#include "error.h"

static lptaskfunc_t task_list[LPTASK_MAX_TASKS];
static volatile bool lptaskthread_init = false;
static SemaphoreHandle_t lptask_muttx;
void lptaskthread(void *params){
    (void)params;

    lptask_muttx = xSemaphoreCreateBinary();

    lptaskthread_init = true;
    for(;;){
        vTaskDelay((10L * configTICK_RATE_HZ) / 1000L);
    }

    vTaskDelete(NULL);
}

int lptask_add_task(lptaskfunc_t task){
    if(lptaskthread_init == false){
        return MK_NOT_INITED;
    }

    xSemaphoreTake(lptask_muttx, portMAX_DELAY);

    xSemaphoreGive(lptask_muttx);
}
