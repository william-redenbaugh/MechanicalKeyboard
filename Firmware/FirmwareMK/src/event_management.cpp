#include "event_management.h"
#include "STM32FreeRTOS.h"
#include "event_type_list.h"
#include "error.h"
#include "threads_list.h"

typedef struct{
    void *ptr;
    event_type_t event; 
}event_data_t;

static volatile QueueHandle_t global_eventspace;
static volatile bool event_management_init = false;

static QueueHandle_t local_eventspaces[NUM_THREADS];
int num_eventspaces = 0; 

void event_management_thread(void *parameters){
    global_eventspace = xQueueCreate(32, sizeof(event_data_t));
    for(;;){

    }
}

int publish_event(event_type_t event, void *ptr){
    if(!event_management_init){
        return MK_INT_ERR;
    }
    event_data_t data;
    data.event = event; 
    data.ptr = ptr;
    int ret = xQueueSend(global_eventspace, (void*)&data, portMAX_DELAY);
    switch(ret){
        case errQUEUE_FULL:
            return MK_LOW_MEM_ERR;
        case pdTRUE: 
            return MK_OK;
        default: 
            return MK_INT_ERR;
    }
}

int subscribe_events(event_type_t event_list[], int event_length_max){
    local_eventspaces[num_eventspaces] = xQueueCreate(sizeof(event_data_t), event_length_max);

    
    int ret = num_eventspaces; 
}