#include <STM32FreeRTOS.h>
#include <Arduino.h>
#include "lptaskthread.h"

// Define the LED pin is attached
const uint8_t LED_PIN = PC13;

void turn_on_light(void){
    // Turn LED on.
    digitalWrite(LED_PIN, HIGH);
}

void turn_off_light(void){
    // Signal thread 1 to turn LED off.
    digitalWrite(LED_PIN, LOW);

}

void app_main_statemachine_thread(void *params){
    pinMode(LED_PIN, OUTPUT);

    for(;;){
        // On 200 ms
        lptask_add_task((lptaskfunc_t)turn_on_light);
        vTaskDelay((200L * configTICK_RATE_HZ) / 1000L);

        // Off 200ms
        lptask_add_task((lptaskfunc_t)turn_off_light);
        vTaskDelay((200L * configTICK_RATE_HZ) / 1000L);
    }

    vTaskDelete(NULL);
}
