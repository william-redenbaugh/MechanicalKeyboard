#include "display_management_runtime.h"
#include "STM32FreeRTOS.h"
#include "mk_helper.h"
#include "i2c_lcd.h"

void display_management_thread(void *params){
    (void)params;

    init_lcd(20, 4);
    for(;;){
        MK_TASK_DELAY_MS(100);
    }
}