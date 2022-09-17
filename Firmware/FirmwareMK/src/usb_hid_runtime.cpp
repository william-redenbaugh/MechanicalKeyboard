#include "usb_hid_runtime.h"
#include "STM32FreeRTOS.h"
#include "hid/usbd_hid_composite_if.h"
#include "Keyboard.h"

void usb_hid_thread(void *params){

    HID_Composite_Init(HID_KEYBOARD);
    for(;;){
        vTaskDelay((4000L * configTICK_RATE_HZ) / 1000L);

    }

    //HID_Composite_DeInit(HID_KEYBOARD);
}

