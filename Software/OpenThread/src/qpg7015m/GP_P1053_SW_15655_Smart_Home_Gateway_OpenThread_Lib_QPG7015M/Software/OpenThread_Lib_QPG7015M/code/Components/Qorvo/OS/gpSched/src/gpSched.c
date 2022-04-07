/*
 * Copyright (c) 2008-2016, GreenPeak Technologies
 * Copyright (c) 2017-2018, Qorvo Inc
 *
 * gpSched.c
 *   This file contains the implementation of the scheduler, which is the operating system.
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
 * Alternatively, this software may be distributed under the terms of the
 * modified BSD License or the 3-clause BSD License as published by the Free
 * Software Foundation @ https://directory.fsf.org/wiki/License:BSD-3-Clause
 *
 * $Header: //depot/release/Embedded/Components/Qorvo/OS/v2.10.2.2/comps/gpSched/src/gpSched.c#1 $
 * $Change: 190959 $
 * $DateTime: 2022/02/18 16:20:44 $
 *
 */

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

#define GP_COMPONENT_ID GP_COMPONENT_ID_SCHED

#include "gpSched.h"
#include "gpSched_defs.h"
#include "hal.h"
#include "gpUtils.h"
#include "gpLog.h"

UInt32 gpSched_GetTimeToNextEvent (void)
{
    gpSched_globals_t* sched_globals = GP_SCHED_GET_GLOBALS();
    UInt32 timeToNextEvent = 0;
    gpSched_Event_t* pevt;

    SCHED_ACQUIRE_EVENT_LIST();
    pevt = (gpSched_Event_t*)gpUtils_LLGetFirstElem(sched_globals->gpSched_EventList);
    if(pevt)
    {
        UInt32 time_now;
        HAL_TIMER_GET_CURRENT_TIME_1US(time_now);

        if(GP_SCHED_TIME_COMPARE_BIGGER_EQUAL(pevt->time, time_now))
        {
            timeToNextEvent = GP_SCHED_GET_TIME_DIFF(time_now, pevt->time);
        }
        else
        {
            timeToNextEvent = 0;
        }
    }
    SCHED_RELEASE_EVENT_LIST();

    return timeToNextEvent;
}

UInt32 gpSched_GetGoToSleepThreshold (void)
{
    UInt32 threshold;

#if defined(GP_SCHED_DIVERSITY_SLEEP)
    gpSched_globals_t* sched_globals = GP_SCHED_GET_GLOBALS();
    threshold = (sched_globals->gpSched_GoToSleepTreshold);
#else
    threshold = GP_SCHED_DEFAULT_GOTOSLEEP_THRES;
#endif
    return threshold;
}

/* return 1 if sleep is enabled and 0 otherwise */
Bool gpSched_IsSleepEnabled(void)
{
#ifdef GP_SCHED_DIVERSITY_SLEEP
    gpSched_globals_t* sched_globals = GP_SCHED_GET_GLOBALS();
    return (sched_globals->gpSched_GoToSleepDisableCounter == 0);
#else
    return 0;
#endif
}
