#ifndef THREADS_LIST_H
#define THREADS_LIST_H
#include "Arduino.h"
#include <STM32FreeRTOS.h>
#include "main_statemachine.h"

#define THREAD_LIST {\
                        {app_main_statemachine_thread, "Main Statemachine", 2048, 1, NULL, NULL}\
                    }

#define NUM_THREADS 1

#endif