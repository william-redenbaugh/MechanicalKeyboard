#include <STM32FreeRTOS.h>
#include <Arduino.h>
#include "lptaskthread.h"
#include "event_management.h"

void app_main_statemachine_thread(void *params){
    for(;;){
        // On 200 ms
        vTaskDelay((200L * configTICK_RATE_HZ) / 1000L);
        publish_event(EVENT_STATUS_LED_OFF, NULL);
        //turn_off_light();

        vTaskDelay((200L * configTICK_RATE_HZ) / 1000L);
        publish_event(EVENT_STATUS_LED_ON, NULL);
        //turn_on_light();
    }

    vTaskDelete(NULL);
}
