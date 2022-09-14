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

    lptask_muttx = xSemaphoreCreateBinary();

    lptaskthread_init = true;
    for(;;){
        vTaskDelay((40L * configTICK_RATE_HZ) / 1000L);

        // Iterate and go through items on list until it's empty
        while(is_empty() == false){
            lptask_run_task();
            vTaskDelay(1L * configTICK_RATE_HZ / 1000L);
        }
    }

    vTaskDelete(NULL);
}

//////////////////// Helper Functions ////////////////////

int is_full() {
  if ((front == rear + 1) || (front == 0 && rear == LPTASK_MAX_TASKS - 1)) return 1;
  return 0;
}

// Check if the queue is empty
int is_empty() {
  if (front == -1) return 1;
  return 0;
}

int lptask_run_task(void){
    if (is_empty()){
        return MK_LIST_EMPTY;
    }

    // Run task here
    task_list[front]();
    num_tasks--;

    if(front == rear){
        front = -1;
        rear = -1;
    }
    else{
        front = (front + 1) % LPTASK_MAX_TASKS;
    }

    return MK_OK;
}

//////////////////// External Interfaces ////////////////////
int lptask_add_task(lptaskfunc_t task){
    if(lptaskthread_init == false){
        return MK_NOT_INITED;
    }

    xSemaphoreTake(lptask_muttx, portMAX_DELAY);

    if(is_full()){
        return MK_LOW_MEM_ERR;
    }

    if(front == -1){
        front = 0;
    }
    rear = (rear + 1) & LPTASK_MAX_TASKS;
    task_list[rear] = task;

    // Now have one more task on queue
    num_tasks++;
    xSemaphoreGive(lptask_muttx);
}