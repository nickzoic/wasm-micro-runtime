/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#ifndef _BH_PLATFORM_H
#define _BH_PLATFORM_H

#include "bh_config.h"
#include "bh_types.h"
#include "bh_memory.h"
#include <inttypes.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <ctype.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#include "esp_task.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint64_t uint64;
typedef int64_t int64;

extern void DEBUGME(void);

#define DIE do{bh_debug("Die here\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); DEBUGME(void); while(1);}while(0)

#ifndef BH_PLATFORM_LINUX
#define BH_PLATFORM_LINUX
#endif

/* NEED qsort */

#define _STACK_SIZE_ADJUSTMENT (32 * 1024)

/* Stack size of applet threads's native part.  */
#define BH_APPLET_PRESERVED_STACK_SIZE      (8 * 1024 + _STACK_SIZE_ADJUSTMENT)

/* Default thread priority */
#define BH_THREAD_DEFAULT_PRIORITY 0

#define BH_ROUTINE_MODIFIER

#define BHT_TIMEDOUT ETIMEDOUT


typedef TaskHandle_t korp_tid;
typedef SemaphoreHandle_t korp_sem;
typedef SemaphoreHandle_t korp_mutex;
typedef int korp_cond;
typedef void korp_thread;
typedef void (*thread_start_routine_t)(void*);

#define INVALID_THREAD_ID ((korp_tid)0xFFffFFff)

#define wa_malloc bh_malloc
#define wa_free bh_free
#define wa_strdup bh_strdup

#define bh_printf printf

int snprintf(char *buffer, size_t count, const char *format, ...);
double fmod(double x, double y);
float fmodf(float x, float y);
double sqrt(double x);

#define BH_WAIT_FOREVER 0xFFFFFFFF

#ifndef NULL
#  define NULL ((void*) 0)
#endif

/**
 * Return the offset of the given field in the given type.
 *
 * @param Type the type containing the filed
 * @param field the field in the type
 *
 * @return the offset of field in Type
 */
#ifndef offsetof
#define offsetof(Type, field) ((size_t)(&((Type *)0)->field))
#endif

#define bh_assert assert

int b_memcpy_s(void * s1, unsigned int s1max, const void * s2,
               unsigned int n);
int b_strcat_s(char * s1, size_t s1max, const char * s2);
int b_strcpy_s(char * s1, size_t s1max, const char * s2);

int fopen_s(FILE ** pFile, const char *filename, const char *mode);

char *bh_read_file_to_buffer(const char *filename, uint32_t *ret_size);

char *bh_strdup(const char *s);

int bh_platform_init();

void *bh_mmap(void *hint, unsigned int size, int prot, int flags);
void bh_munmap(void *addr, uint32_t size);
int bh_mprotect(void *addr, uint32_t size, int prot);

enum {
    MMAP_PROT_NONE = 0,
    MMAP_PROT_READ = 1,
    MMAP_PROT_WRITE = 2,
    MMAP_PROT_EXEC = 4
};

enum {
    MMAP_MAP_NONE = 0,
};

#endif
