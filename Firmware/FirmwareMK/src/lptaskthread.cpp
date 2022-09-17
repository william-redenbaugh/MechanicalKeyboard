#include "lptaskthread.h"
#include "STM32FreeRTOS.h"
#include "error.h"

//////////////////// Function prototypes ////////////////////
int lptask_run_task(void);
int is_full(void);
int is_empty(void);

//////////////////// Low Priority task circular queue variables ////////////////////
static volatile lptaskfunc_t task_list[LPTASK_MAX_TASKS];

static volatile uint16_t num_tasks = 0;
static volatile uint16_t front = 0;
static volatile uint16_t rear = 0;
static volatile bool lptaskthread_init = false;

//////////////////// Safety Primitives ////////////////////
static SemaphoreHandle_t lptask_muttx;


//////////////////// Function thread  ////////////////////
void lptaskthread(void *params){
    (void)params;

    lptask_muttx = xSemaphoreCreateMutex();

    lptaskthread_init = true;

    for(;;){
        vTaskDelay((40L * configTICK_RATE_HZ) / 1000L);
        // Iterate and go through items on list until it's empty
        while(num_tasks > 0){
            lptask_run_task();
            vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
        }
    }

    vTaskDelete(NULL);
}

//////////////////// Helper Functions ////////////////////

int lptask_run_task(void){
    xSemaphoreTake(lptask_muttx, portMAX_DELAY);
    if(num_tasks == 0){
        xSemaphoreGive(lptask_muttx);
        return MK_LIST_EMPTY;
    }
    num_tasks--;
    lptaskfunc_t func = task_list[rear];

    rear++;
    if(rear == LPTASK_MAX_TASKS){
        rear = 0;
    }

    xSemaphoreGive(lptask_muttx);
    func();
    return MK_OK;
}

//////////////////// External Interfaces ////////////////////
int lptask_add_task(lptaskfunc_t func){
    if(lptaskthread_init == false){
        return MK_NOT_INITED;
    }

    xSemaphoreTake(lptask_muttx, portMAX_DELAY);
    if(num_tasks >= (LPTASK_MAX_TASKS - 1)){
        xSemaphoreGive(lptask_muttx);
        return MK_LOW_MEM_ERR;
    }
    num_tasks++;
    task_list[front] = func;

    front++;
    if(front == LPTASK_MAX_TASKS){
        front = 0;
    }

    xSemaphoreGive(lptask_muttx);
    return MK_OK;
}