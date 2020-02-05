/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#include "bh_time.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>

#include "freertos/FreeRTOS.h"
//#include "freertos/task.h"

#include "esp_timer.h"

/*
 * This function returns milliseconds per tick.
 * @return milliseconds per tick.
 */
uint64 _bh_time_get_tick_millisecond()
{
    return portTICK_PERIOD_MS;
}

/*
 * This function returns milliseconds after boot.
 * @return milliseconds after boot.
 */
uint64 _bh_time_get_boot_millisecond()
{
    return esp_timer_get_time() / 1000;
}

uint32 bh_get_tick_sec()
{
    return esp_timer_get_time() / 1000000L;
}

/*
 * This function returns GMT time milliseconds since from 1970.1.1, AKA UNIX time.
 * @return milliseconds since from 1970.1.1.
 */
uint64 _bh_time_get_millisecond_from_1970()
{
    return 0;
}

size_t _bh_time_strftime(char *s, size_t max, const char *format, int64 time)
{
    return 0;
}

