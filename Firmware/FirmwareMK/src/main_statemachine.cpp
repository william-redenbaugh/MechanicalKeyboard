#include <STM32FreeRTOS.h>
#include <Arduino.h>

// Define the LED pin is attached
const uint8_t LED_PIN = PC13;

void app_main_statemachine_thread(void *params){
    pinMode(LED_PIN, OUTPUT);

    for(;;){
        // Turn LED on.
        digitalWrite(LED_PIN, HIGH);

        // Sleep for 200 milliseconds.
        vTaskDelay((200L * configTICK_RATE_HZ) / 1000L);

        // Signal thread 1 to turn LED off.
        digitalWrite(LED_PIN, LOW);

        // Sleep for 200 milliseconds.
        vTaskDelay((200L * configTICK_RATE_HZ) / 1000L);
    }
}