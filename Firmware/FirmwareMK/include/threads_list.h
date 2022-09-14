#ifndef THREADS_LIST_H
#define THREADS_LIST_H
#include "Arduino.h"
#include <STM32FreeRTOS.h>
#include "main_statemachine.h"
#include "lptaskthread.h"

#define THREAD_LIST {\
                        {app_main_statemachine_thread, "Main Statemachine", 256, 1, NULL, NULL},\
                        {lptaskthread, "Low Priority Task", 256, 1, NULL, NULL}\
                    }

#define NUM_THREADS 2

#endif