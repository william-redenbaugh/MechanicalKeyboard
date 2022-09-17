#include "display_management_runtime.h"
#include "STM32FreeRTOS.h"
#include "mk_helper.h"
void display_management_thread(void *params){
    (void)params;

    for(;;){
        MK_TASK_DELAY_MS(100);
    }
}