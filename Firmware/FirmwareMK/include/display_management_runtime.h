#ifndef _DISPLAY_MANAGEMENT_RUNTIME_H
#define _DISPLAY_MANAGEMENT_RUNTIME_H

/**
 * @brief Display management thread
 *
 * @param params
 * @note only to be called by threads_init.h
 */
void display_management_thread(void *params);

#endif