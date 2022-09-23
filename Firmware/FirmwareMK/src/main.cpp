/*
 * Example to demonstrate thread definition, semaphores, and thread sleep.
 */
#include <STM32FreeRTOS.h>
#include "Arduino.h"
#include "threads_init.h"
#include "threads_list.h"
//------------------------------------------------------------------------------
void setup() {
  // Initialize all of our threads.
  HAL_Init();
  SystemClock_Config();
  
  threads_list_init();
  vTaskStartScheduler();
  Serial.println("Insufficient RAM");
  while(1);
}

//------------------------------------------------------------------------------
// WARNING idle loop has a very small stack (configMINIMAL_STACK_SIZE)
// loop must never block
void loop() {
  // Not used.
}