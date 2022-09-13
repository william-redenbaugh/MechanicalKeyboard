#ifndef _LPTASKTHREAD_H
#define _LPTASKTHREAD_H

/**
 * @brief Maxium Number of tasks that we can have
 *
 */
#define LPTASK_MAX_TASKS 64

/**
 * @brief Function prototype that we can use to pass in functions into our low priority thread handler
 */
typedef void(*lptaskfunc_t)(void);

/**
 * @brief Thread that handles all of our low priority task stuff
 *
 * @param params
 * @note Should only be invoked in our thread_init header
 */
void lptaskthread(void *params);

/**
 * @brief Add a task to our queue of low priority tasks
 *
 * @param task
 */
int lptask_add_task(lptaskfunc_t task);

#endif