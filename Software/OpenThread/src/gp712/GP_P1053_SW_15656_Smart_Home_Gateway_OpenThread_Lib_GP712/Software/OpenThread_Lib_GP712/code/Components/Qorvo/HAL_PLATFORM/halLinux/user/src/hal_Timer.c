/*
 * Copyright (c) 2010, 2013-2016, GreenPeak Technologies
 * Copyright (c) 2017, Qorvo Inc
 *
 * hal_Timer.c
 *   Hardware Abstraction Layer for linux based devices.
 *
 *
 * This software is owned by Qorvo Inc
 * and protected under applicable copyright laws.
 * It is delivered under the terms of the license
 * and is intended and supplied for use solely and
 * exclusively with products manufactured by
 * Qorvo Inc.
 *
 *
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS"
 * CONDITION. NO WARRANTIES, WHETHER EXPRESS,
 * IMPLIED OR STATUTORY, INCLUDING, BUT NOT
 * LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * QORVO INC. SHALL NOT, IN ANY
 * CIRCUMSTANCES, BE LIABLE FOR SPECIAL,
 * INCIDENTAL OR CONSEQUENTIAL DAMAGES,
 * FOR ANY REASON WHATSOEVER.
 *
 * $Header$
 * $Change$
 * $DateTime$
 *
 */

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

#include "hal.h"
#include <sys/time.h>
#include <stdio.h>


/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/
#define GP_COMPONENT_ID GP_COMPONENT_ID_HALLINUX

//Legacy system time resolution = 32 us
#define HAL_TIME_RES_ORDER      5

/*****************************************************************************
 *                    Static Data Definitions
 *****************************************************************************/
#if defined(GP_COMP_CHIPEMU)
UInt64 hal_ClockCounter;
#endif //GP_COMP_UNIT_TEST

/**
 * Return 1us resolution time in 64-bit
*/
#if defined(GP_COMP_CHIPEMU)
UInt64 halTimer_GetCurrentTime_1us_64bit(void)
{
    return hal_ClockCounter;
}
#else
UInt64 halTimer_GetCurrentTime_1us_64bit(void)
{
    UInt64 timestampUs;
    struct timespec tp;

    // use monotonic clock to be robust against system time changes
    clock_gettime(CLOCK_MONOTONIC, &tp);

    timestampUs = (UInt64)tp.tv_nsec/1000 + ((UInt64)tp.tv_sec * 1000000);

    return timestampUs;
}
#endif //defined(GP_COMP_UNIT_TEST) && !defined(GP_HAL_DIVERSITY_USE_SELECT) && !defined(HAL_DIVERSITY_USE_LIBEV)&& !defined(GP_UNITTEST_DIVERSITY_NO_FASTFORWARD)

/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/

/*
 * Timers
 */

#if defined(GP_COMP_CHIPEMU)
void hal_StartTimer(void)
{
    hal_ClockCounter = 0;
}
#endif //GP_COMP_UNIT_TEST

/**
 * Return 32us resolution time in full 32-bit.
*/
UInt32 hal_GetCurrentTime(void)
{
    return (UInt32)(halTimer_GetCurrentTime_1us_64bit() >> HAL_TIME_RES_ORDER);
}

/**
 * Return 1us resolution time in full 32-bit
*/
UInt32 hal_GetCurrentTime_1us(void)
{
    return (UInt32)halTimer_GetCurrentTime_1us_64bit();
}

/**
 * Return the current real time in seconds since the Unix epoch.
*/
UInt32 hal_getSecondsSinceEpoch(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return tv.tv_sec;
}

/**
 * Return the current real time in microseconds since the Unix epoch.
*/
UInt64 hal_GetMicrosecondsSinceEpoch(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((UInt64)tv.tv_sec) * 1000000 + tv.tv_usec;
}
