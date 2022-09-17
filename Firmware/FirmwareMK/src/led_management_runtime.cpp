#include "led_management_runtime.h"
#include "mk_helper.h"

void led_management_thread(void *params){
    (void)params;

    for(;;){
        MK_TASK_DELAY_MS(100);
    }
}