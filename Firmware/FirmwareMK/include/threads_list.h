#ifndef THREADS_LIST_H
#define THREADS_LIST_H
#include "Arduino.h"
#include <STM32FreeRTOS.h>
#include "main_statemachine.h"
#include "lptaskthread.h"
#include "usb_hid_runtime.h"
#include "led_management_runtime.h"
#include "display_management_runtime.h"
#include "event_management.h"

#define THREAD_LIST {\
                        {display_management_thread, "LCD Display Task", 64, 1, NULL, NULL},\
                        {app_main_statemachine_thread, "Main Statemachine", 64, 1, NULL, NULL},\
                        {lptaskthread, "Low Priority Task", 64, 1, NULL, NULL},\
                        {event_management_thread, "Event Handler Thread", 192, 1, NULL, NULL},\
                        {usb_hid_thread, "USB HID Task", 256, 1, NULL, NULL},\
                        {led_management_thread, "LED Matrix Task", 256, 1, NULL, NULL}\
                    }

#define NUM_THREADS 6

#endif