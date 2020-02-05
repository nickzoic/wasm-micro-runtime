/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#include "bh_thread.h"
#include "bh_assert.h"
#include "bh_log.h"
#include "bh_memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <esp_task.h>

int _vm_thread_sys_init()
{
    return BHT_OK;
}

void vm_thread_sys_destroy(void)
{
}

int _vm_thread_create_with_prio(korp_tid *tid, thread_start_routine_t start,
                                void *arg, unsigned int stack_size, int prio)
{
    TaskHandle_t task_handle;
    if (xTaskCreate(start, "", 600, arg, 2, &task_handle) == pdPASS) {
        *tid = task_handle;
	bh_printf("CREATED THREAD %p", task_handle);
        return BHT_OK;
    } else {
        return BHT_ERROR;
    }
}

int _vm_thread_create(korp_tid *tid, thread_start_routine_t start, void *arg,
                      unsigned int stack_size)
{
    return _vm_thread_create_with_prio(tid, start, arg, stack_size, 2);
}

korp_tid _vm_self_thread()
{
    return xTaskGetCurrentTaskHandle();
}

void vm_thread_exit(void *code)
{
    (void)code;
    vTaskDelete(xTaskGetCurrentTaskHandle());
}

void *_vm_tls_get(unsigned idx)
{
    return 0;
}

int _vm_tls_put(unsigned idx, void * tls)
{
    return 0;
}

int _vm_mutex_init(korp_mutex *mutex)
{
    *mutex = xSemaphoreCreateMutex();
    return BHT_OK;
}

int _vm_recursive_mutex_init(korp_mutex *mutex)
{
    // XXX there's separate TakeRecursive and GiveRecursive functions which should be called below
    // instead of just Take and Give ... 
    *mutex = xSemaphoreCreateRecursiveMutex();
    return BHT_OK;
}

int _vm_mutex_destroy(korp_mutex *mutex)
{
    vSemaphoreDelete(*mutex);
    return BHT_OK;
}

void vm_mutex_lock(korp_mutex *mutex)
{
    // XXX should chuck an exception if this fails
    xSemaphoreTake(*mutex, portMAX_DELAY);
}

int vm_mutex_trylock(korp_mutex *mutex)
{
    return (xSemaphoreTake(*mutex, 0) == pdTRUE) ? BHT_OK : BHT_ERROR;
}

void vm_mutex_unlock(korp_mutex *mutex)
{
    // XXX should chuck an exception if this fails
    xSemaphoreGive(*mutex);
}

int _vm_sem_init(korp_sem* sem, unsigned int c)
{
    // XXX what is c anyway?
    *sem = xSemaphoreCreateCounting(0, c);
    return *sem ? BHT_OK : BHT_ERROR;
}

int _vm_sem_destroy(korp_sem *sem)
{
    vSemaphoreDelete(*sem);
    return BHT_OK;
}

int _vm_sem_wait(korp_sem *sem)
{
    return (xSemaphoreTake(*sem, portMAX_DELAY) == pdTRUE) ? BHT_OK : BHT_ERROR;
}

int _vm_sem_reltimedwait(korp_sem *sem, int mills)
{
    return (xSemaphoreTake(*sem, mills / portTICK_PERIOD_MS) == pdTRUE) ? BHT_OK : BHT_ERROR;
}

int _vm_sem_post(korp_sem *sem)
{
    xSemaphoreGive(*sem);
    return BHT_OK;
}

int _vm_cond_init(korp_cond *cond)
{
	bh_printf("cond init\n");
	return 0;
}

int _vm_cond_destroy(korp_cond *cond)
{
	bh_printf("cond destroy\n");
	return 0;
}

int _vm_cond_wait(korp_cond *cond, korp_mutex *mutex)
{
	bh_printf("cond wait\n");
	return 0;
}

int _vm_cond_reltimedwait(korp_cond *cond, korp_mutex *mutex, int mills)
{
	return 0;
}

int _vm_cond_signal(korp_cond *cond)
{
	bh_printf("cond sig\n");
	return 0;
}

int _vm_cond_broadcast(korp_cond *cond)
{
	bh_printf("cond bcast\n");
	return 0;
}

int _vm_thread_cancel(korp_tid thread)
{
	bh_printf("thread cancel\n");
	return 0;
}

int _vm_thread_join(korp_tid thread, void **value_ptr, int mills)
{
	// XXX no idea
	bh_printf("thread join\n");
	return 0;
}

int _vm_thread_detach(korp_tid thread)
{
	// XXX this isn't defined in some other platforms either
	(void) thread;
	return BHT_OK;
}

