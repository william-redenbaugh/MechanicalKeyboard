#include "event_management.h"
#include "STM32FreeRTOS.h"
#include "event_type_list.h"
#include "error.h"
#include "threads_list.h"

static volatile QueueHandle_t global_eventspace;
static volatile bool event_management_init = false;

static QueueHandle_t local_eventspaces[NUM_THREADS];
static event_type_t **subscribed_eventspaces;
static int num_subscribed_events[NUM_THREADS];

int num_eventspaces = 0;

static SemaphoreHandle_t event_management_mutx;

void event_management_thread(void *parameters){
    global_eventspace = xQueueCreate(32, sizeof(event_data_t));
    subscribed_eventspaces = (event_type_t**)malloc(sizeof(event_type_t*) * NUM_THREADS);
    memset(num_subscribed_events, 0, sizeof(num_subscribed_events));
    event_management_mutx = xSemaphoreCreateMutex();

    event_management_init = true;
    for(;;){
        event_data_t event;
        xQueueReceive(global_eventspace, &event, portMAX_DELAY);

        // Go through all the local event spaces, publish to whoever is subscribed to them
        xSemaphoreTake(event_management_mutx, portMAX_DELAY);
        for(int n = 0; n < num_eventspaces; n++){
            for(int i = 0; i < num_subscribed_events[n]; i++){
                if(subscribed_eventspaces[n][i] == event.event){
                    xQueueSend(local_eventspaces[n], (void*)&event, portMAX_DELAY);
                }
            }
        }
        xSemaphoreGive(event_management_mutx);
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

int subscribe_eventlist(event_type_t *event_list, int num_events, int event_length_max){
    if(!event_management_init){
        return MK_INT_ERR;
    }

    xSemaphoreTake(event_management_mutx, portMAX_DELAY);
    local_eventspaces[num_eventspaces] = xQueueCreate(sizeof(event_data_t), event_length_max);
    subscribed_eventspaces[num_eventspaces] = (event_type_t*)malloc(sizeof(event_type_t) * num_events);

    // Add to list of events
    for(int n = 0; n < num_events; n++){
        subscribed_eventspaces[num_eventspaces][n] = event_list[n];
    }
    num_subscribed_events[num_eventspaces] = num_events;
    int ret = num_eventspaces;
    num_eventspaces++;
    xSemaphoreGive(event_management_mutx);
    return ret;
}

bool available_events(int eventspace){
    if(!event_management_init){
        return false;
    }

    event_data_t event;
    int n = xQueuePeek(local_eventspaces[eventspace], &event, EVENT_PEEK_TIMEOUT);
    switch(n){
        case pdTRUE:
            return true;
        default:
            return false;
    }
}

event_data_t consume_event(int eventspace){
    event_data_t event;
    memset(&event, 0, sizeof(event_data_t));

    if(!event_management_init){
        return event;
    }
    xQueueReceive(local_eventspaces[eventspace], &event, portMAX_DELAY);

    return event;
}