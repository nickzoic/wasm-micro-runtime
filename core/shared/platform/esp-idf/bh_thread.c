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

//static bool is_thread_sys_inited = false;

int _vm_thread_sys_init()
{
	return 0;
}

void vm_thread_sys_destroy(void)
{
}

/*static void *vm_thread_wrapper(void *arg)
{
}*/

int _vm_thread_create_with_prio(korp_tid *tid, thread_start_routine_t start,
                                void *arg, unsigned int stack_size, int prio)
{
	return 0;
}

int _vm_thread_create(korp_tid *tid, thread_start_routine_t start, void *arg,
                      unsigned int stack_size)
{
	return 0;
}

korp_tid _vm_self_thread()
{
	return 0;
}

void vm_thread_exit(void * code)
{
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
	return 0;
}

int _vm_recursive_mutex_init(korp_mutex *mutex)
{
	return 0;
}


int _vm_mutex_destroy(korp_mutex *mutex)
{
	return 0;
}

/* Returned error (EINVAL, EAGAIN and EDEADLK) from
 locking the mutex indicates some logic error present in
 the program somewhere.
 Don't try to recover error for an existing unknown error.*/
void vm_mutex_lock(korp_mutex *mutex)
{
}

int vm_mutex_trylock(korp_mutex *mutex)
{
    return 0;
}

/* Returned error (EINVAL, EAGAIN and EPERM) from
 unlocking the mutex indicates some logic error present
 in the program somewhere.
 Don't try to recover error for an existing unknown error.*/
void vm_mutex_unlock(korp_mutex *mutex)
{
}

int _vm_sem_init(korp_sem* sem, unsigned int c)
{
    return 0;
}

int _vm_sem_destroy(korp_sem *sem)
{
    return 0;
}

int _vm_sem_wait(korp_sem *sem)
{
    return 0;
}

int _vm_sem_reltimedwait(korp_sem *sem, int mills)
{
    return 0;
}

int _vm_sem_post(korp_sem *sem)
{
    return 0;
}

int _vm_cond_init(korp_cond *cond)
{
	return 0;
}

int _vm_cond_destroy(korp_cond *cond)
{
	return 0;
}

int _vm_cond_wait(korp_cond *cond, korp_mutex *mutex)
{
	return 0;
}

/*static void msec_nsec_to_abstime(struct timespec *ts, int64 msec, int32 nsec)
{
	return 0;
}*/

int _vm_cond_reltimedwait(korp_cond *cond, korp_mutex *mutex, int mills)
{
	return 0;
}

int _vm_cond_signal(korp_cond *cond)
{
	return 0;
}

int _vm_cond_broadcast(korp_cond *cond)
{
	return 0;
}

int _vm_thread_cancel(korp_tid thread)
{
	return 0;
}

int _vm_thread_join(korp_tid thread, void **value_ptr, int mills)
{
	return 0;
}

int _vm_thread_detach(korp_tid thread)
{
	return 0;
}

