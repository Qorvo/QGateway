/*
 * Copyright (c) 2017-2019, Qorvo Inc
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
 * $Header: //depot/release/Embedded/Components/Qorvo/OS/v2.10.2.0/comps/gpSched/src/gpSched_rom.c#1 $
 * $Change: 187624 $
 * $DateTime: 2021/12/20 10:58:50 $
 *
 */

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

#define GP_COMPONENT_ID GP_COMPONENT_ID_SCHED
#ifdef GP_DIVERSITY_JUMPTABLES
#define GP_DIVERSITY_ROM_CODE
#endif //def GP_DIVERSITY_JUMPTABLES

#include "gpSched.h"
#include "gpSched_defs.h"
#include "hal.h"
#include "gpUtils.h"
#include "gpLog.h"
#ifdef GP_COMP_COM
#include "gpCom.h"
#endif
#include "gpAssert.h"

#ifdef GP_COMP_WMRK
#include "gpWmrk.h"
#endif //GP_COMP_WMRK

#ifdef GP_COMP_CHIPEMU
#include "gpChipEmu.h"
#endif

#ifdef GP_DIVERSITY_JUMPTABLES
#include "gpJumpTables_DataTable.h"
#endif //def GP_DIVERSITY_JUMPTABLES

/*****************************************************************************
 *                    Precompiler checks
 *****************************************************************************/

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/


/*****************************************************************************
 *                    Functional Macro Definitions
 *****************************************************************************/

/* Macros defining hook for SCHED_MAIN_BODY patch */
#define SCHED_MAIN_BODY(pS)

/*****************************************************************************
 *                    Type Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Static Data Definitions
 *****************************************************************************/




/*****************************************************************************
 *                    External Function Prototypes
 *****************************************************************************/


/*****************************************************************************
 *                    Static Function Prototypes
 *****************************************************************************/
#if defined(GP_DIVERSITY_JUMPTABLES) && defined(GP_DIVERSITY_ROM_CODE)
#include "gpSched_CodeJumpTableFlash_Defs_rom_c.h"
#include "gpSched_CodeJumpTableRom_Defs_rom_c.h"
#include "gpSched_CodeJumpTableRom_Defs.h"
#endif // defined(GP_DIVERSITY_JUMPTABLES) && defined(GP_DIVERSITY_ROM_CODE)

/*
 * @brief Internal helper function to schedule an event with argument
 *
 * @param  time                relative time in us, or, in case scheduleAbsTime==true, absolute time in us
 * @param  scheduleAbsTime     Set to true when specifying an absolute time
 * @param  RemainderInSeconds  An additional value in seconds to be added to the time argument
 */
/* JUMPTABLE_FLASH_FUNCTION_DEFINITIONS_START */
/* JUMPTABLE_ROM_FUNCTION_DEFINITIONS_START */
STATIC_FUNC void Sched_ScheduleEvent( UInt32 time, gpSched_EventCallback_t callback, void* arg,UInt32 RemainderInSeconds ,Bool scheduleAbsTime);
STATIC_FUNC void Sched_ScheduleEventInSeconds(UInt32 delayInSec, UInt32 delayInUs, Bool reScheduling, UInt32 delayerror, gpSched_EventCallback_t callback, void* arg);

STATIC_FUNC gpSched_Event_t* Sched_GetEvent( void );
STATIC_FUNC gpSched_Event_t* Sched_FindEventArg(gpUtils_LinkList_t* plst, gpSched_EventCallback_t callback, void* arg, Bool unscheduleWhenFound );
STATIC_FUNC void Sched_RescheduleEvent (UInt32 rel_time, gpSched_Event_t * pevt);
STATIC_FUNC void Sched_RescheduleEventAbs (UInt32 time, gpSched_Event_t * pevt);
STATIC_FUNC void Sched_ReleaseEventBody(gpSched_Event_t* pevt );


#ifdef GP_SCHED_DIVERSITY_SLEEP
STATIC_FUNC UInt32 Sched_GetEventIdlePeriod(void);
#endif //GP_SCHED_DIVERSITY_SLEEP


STATIC_FUNC UInt32 Sched_GetRemainingTime(gpSched_Event_t* pevt, UInt32* sec);

STATIC_FUNC void Sched_ExecEvent(gpSched_Event_t * pevt);
STATIC_FUNC void Sched_ReleaseEvent(gpSched_Event_t * pevt);

/* JUMPTABLE_FLASH_FUNCTION_DEFINITIONS_END */
/* JUMPTABLE_ROM_FUNCTION_DEFINITIONS_END */

/*****************************************************************************
 *                    Static Function Definitions
 *****************************************************************************/

void Sched_ExecEvent(gpSched_Event_t * pevt)
{
    if (pevt->arg) pevt->func.callbackarg(pevt->arg);
    else           pevt->func.callback();
}

void Sched_ReleaseEvent(gpSched_Event_t * pevt)
{
    HAL_DISABLE_GLOBAL_INT();
    Sched_ReleaseEventBody(pevt);
    HAL_ENABLE_GLOBAL_INT();
}

void Sched_RescheduleEvent (UInt32 rel_time, gpSched_Event_t * pevt)
{
    gpSched_globals_t* sched_globals = GP_SCHED_GET_GLOBALS();
    gpUtils_LinkList_t* pList = sched_globals->gpSched_EventList;
    gpSched_Event_t* pevt_nxt = NULL;
    UInt32 now;

    GP_ASSERT_DEV_INT(pevt); //pevt pointer should be != NULL

    HAL_TIMER_GET_CURRENT_TIME_1US(now);
    if (rel_time == GP_SCHED_EVENT_TIME_NOW)
    {
        UInt32 first_time;

        if (pList->plnk_first)
        {
            pevt_nxt = (gpSched_Event_t*)GP_UTILS_LL_GET_ELEM(pList->plnk_first);
            first_time = pevt_nxt->time;
        }
        else
        {
            first_time = now;
        }
        pevt->time = GP_SCHED_TIME_COMPARE_LOWER_EQUAL (first_time, now)?
                first_time - 1L
            :
                now - 1L;
    }
    else
    {
        pevt->time = now + rel_time;
    }

    // You can't schedule negative times.
    // This is aLready checked: GP_ASSERT_SYSTEM((rel_time <= GP_SCHED_EVENT_TIME_MAX) || (rel_time == GP_SCHED_EVENT_TIME_NOW));
    // But you also can't schedule further then GP_SCHED_EVENT_TIME_MAX from the first event in the list (else the order in the list will be wrong)
    // This is especially true if the first event in the list is in the past (before 'now').

    if(pList->plnk_first)
    {
        pevt_nxt = (gpSched_Event_t*)GP_UTILS_LL_GET_ELEM(pList->plnk_first);
        GP_ASSERT_SYSTEM(rel_time < (pevt_nxt->time - now + GP_SCHED_EVENT_TIME_MAX));
    }

    Sched_RescheduleEventAbs (pevt->time, pevt);
}

STATIC_FUNC void Sched_RescheduleEventAbs (UInt32 time, gpSched_Event_t * pevt)
{
    gpSched_globals_t* sched_globals = GP_SCHED_GET_GLOBALS();
    gpUtils_LinkList_t* pList = sched_globals->gpSched_EventList;
    gpSched_Event_t* pevt_nxt = NULL;
    gpUtils_Link_t* plnk = NULL;

    pevt->time  = time;

    // Scroll pointer
    // Insert event
    // Duration : 8us per loop
    {
        // Search for first item, that should be executed later as the current one
        // or that will be executed as last
        for (plnk = pList->plnk_first;
             plnk;
             plnk = plnk->plnk_nxt)
        {
            pevt_nxt = (gpSched_Event_t*)GP_UTILS_LL_GET_ELEM(plnk);
            if (GP_SCHED_TIME_COMPARE_BIGGER( pevt_nxt->time, pevt->time ))
            {
                break;
            }
        }
    }

    if (plnk)
    {
        gpUtils_LLInsertBefore( pevt, pevt_nxt, pList);
    }
    else
    {
        gpUtils_LLAdd( pevt, pList );
    }
}

void Sched_ScheduleEvent( UInt32 time, gpSched_EventCallback_t callback, void* arg,UInt32 RemainderInSeconds ,Bool scheduleAbsTime)
{
    gpSched_Event_t* pevt;
    gpSched_globals_t* sched_globals = GP_SCHED_GET_GLOBALS();

    GP_UTILS_LL_FREE_ACQUIRE_LOCK(sched_globals->gpSched_EventFree);
    pevt = (gpSched_Event_t*)gpUtils_LLNew(sched_globals->gpSched_EventFree);
    GP_UTILS_LL_FREE_RELEASE_LOCK(sched_globals->gpSched_EventFree);

    if (!pevt)
    {

        /* Maximum number of events scheduled has been reached (maximum number of scheduled events can be changed with GP_SCHED_EVENT_LIST_SIZE) */
        GP_ASSERT_SYSTEM(false);
    }
    else
    {
        {
            pevt->arg = arg;
        }
        pevt->func.callbackarg = callback;
        pevt->RemainderInSeconds = RemainderInSeconds;
        if (scheduleAbsTime)
        {
            Sched_RescheduleEventAbs(time, pevt);
        }
        else
        {
            Sched_RescheduleEvent( time,  pevt);
        }

    }
}

void Sched_ReleaseEventBody(gpSched_Event_t* pevt )
{
    gpSched_globals_t* sched_globals = GP_SCHED_GET_GLOBALS();
    // Free event (Unlink has been done by GetEvent)
    GP_UTILS_LL_FREE_ACQUIRE_LOCK(sched_globals->gpSched_EventFree);
    gpUtils_LLFree(pevt, sched_globals->gpSched_EventFree);
    GP_UTILS_LL_FREE_RELEASE_LOCK(sched_globals->gpSched_EventFree);
}


#ifdef GP_SCHED_DIVERSITY_SLEEP

/*
* @brief Returns time untill next event (in microseconds) compared with the gpSched_GoToSleepTreshold.
*/
UInt32 Sched_GetEventIdlePeriod (void)
{
    gpSched_globals_t* sched_globals = GP_SCHED_GET_GLOBALS();
    UInt32 idleTime = HAL_SLEEP_INDEFINITE_SLEEP_TIME;

    gpSched_Event_t* pevt;

    SCHED_ACQUIRE_EVENT_LIST();
    pevt = (gpSched_Event_t*)gpUtils_LLGetFirstElem(sched_globals->gpSched_EventList);
    if (pevt)
    {
        if(sched_globals->gpSched_GoToSleepTreshold == GP_SCHED_NO_EVENTS_GOTOSLEEP_THRES) //Only sleep if no events are pending
        {
            idleTime = 0;
        }
        else
        {
            UInt32 time_now;
            HAL_TIMER_GET_CURRENT_TIME_1US(time_now);

            if(GP_SCHED_TIME_COMPARE_BIGGER(pevt->time,(time_now + sched_globals->gpSched_GoToSleepTreshold)))
            {
                idleTime = GP_SCHED_GET_TIME_DIFF(time_now, pevt->time);
            }
            else
            {
                idleTime = 0;
            }
        }
    }
    SCHED_RELEASE_EVENT_LIST();

    return (idleTime);
}

#endif // GP_SCHED_DIVERSITY_SLEEP

STATIC_FUNC gpSched_Event_t* Sched_GetEvent(void)
{
    gpSched_Event_t* pevt = NULL;
    gpSched_globals_t* sched_globals = GP_SCHED_GET_GLOBALS();

    SCHED_ACQUIRE_EVENT_LIST();
    pevt = (gpSched_Event_t*)gpUtils_LLGetFirstElem(sched_globals->gpSched_EventList);
    if(pevt)
    {
        UInt32 time_now;
        //Check the eventList for overdue events
        HAL_TIMER_GET_CURRENT_TIME_1US(time_now);

        if (GP_SCHED_TIME_COMPARE_BIGGER_EQUAL (time_now, pevt->time))
        {
            gpUtils_LLUnlink(pevt, sched_globals->gpSched_EventList);
        }
        else
        {
            pevt = NULL;
        }
    }
    SCHED_RELEASE_EVENT_LIST();
    return pevt;
}

/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/

void gpSched_Init(void)
{
    gpSched_globals_t* sched_globals = GP_SCHED_GET_GLOBALS();

    // Inititialize event lists
    gpSched_InitExtramData(); //Initialize free list and event data buffer
    gpUtils_LLClear(sched_globals->gpSched_EventList);

#ifdef GP_SCHED_DIVERSITY_SLEEP
    sched_globals->gpSched_GoToSleepTreshold = GP_SCHED_DEFAULT_GOTOSLEEP_THRES;

#endif //GP_SCHED_DIVERSITY_SLEEP

#ifdef GP_SCHED_DIVERSITY_SLEEP
    sched_globals->gpSched_GoToSleepDisableCounter = 0; // Enable GotoSleep by default
    sched_globals->gpSched_cbGotoSleepCheck = NULL;
#endif //GP_SCHED_DIVERSITY_SLEEP
    Sched_Integration_Init();
} //gpSched_init

void gpSched_DeInit(void)
{
    gpSched_globals_t* sched_globals = GP_SCHED_GET_GLOBALS();
    gpUtils_LLDeInit(sched_globals->gpSched_EventList);
    gpUtils_LLDeInitFree(sched_globals->gpSched_EventFree);

    Sched_Integration_DeInit();
}

void gpSched_StartTimeBase( void )
{
    //Startup sync timer

    HAL_DISABLE_GLOBAL_INT();

    //init the timer1
    HAL_TIMER_START( 0 );
    HAL_ENABLE_GLOBAL_INT();
}

UInt32 gpSched_GetCurrentTime( void )
{
    // This function should not be called from an interrupt service routine,
    // since it uses atomic_on/off, and this can cause unwanted nested interrupt
    // service routines; instead, HAL_TIMER_GET_CURRENT_TIME_1US() should be used in such cases
    UInt32 time;

    HAL_TIMER_GET_CURRENT_TIME_1US( time );

    return time;
}

Bool gpSched_TimeCompareLower (UInt32 n_time1, UInt32 n_time2)
{
    return GP_SCHED_TIME_COMPARE_LOWER(n_time1,n_time2);
}

void gpSched_Clear( void )
{
    gpSched_globals_t* sched_globals = GP_SCHED_GET_GLOBALS();
    SCHED_ACQUIRE_EVENT_LIST();

    while(sched_globals->gpSched_EventList->plnk_last)
    {
        gpSched_Event_t* pevt;

        pevt = (gpSched_Event_t*)GP_UTILS_LL_GET_ELEM(sched_globals->gpSched_EventList->plnk_last);
        GP_LOG_SYSTEM_PRINTF("event %p",2, pevt->func.callback);
        gpUtils_LLUnlink(pevt, sched_globals->gpSched_EventList);
        Sched_ReleaseEventBody(pevt);
    }


#ifdef GP_SCHED_DIVERSITY_SLEEP
    sched_globals->gpSched_GoToSleepDisableCounter = 0; // Enable GotoSleep by default
#endif //GP_SCHED_DIVERSITY_SLEEP
    SCHED_RELEASE_EVENT_LIST();
}

Bool gpSched_EventQueueEmpty( void )
{
    gpSched_globals_t* sched_globals = GP_SCHED_GET_GLOBALS();
    Bool Empty;
    SCHED_ACQUIRE_EVENT_LIST();
    Empty = (!sched_globals->gpSched_EventList->plnk_first);
    SCHED_RELEASE_EVENT_LIST();
    return Empty;
}

void gpSched_ScheduleEventArg(UInt32 rel_time, gpSched_EventCallback_t callback, void* arg)
{
    GP_ASSERT_SYSTEM((rel_time <= GP_SCHED_EVENT_TIME_MAX) || (rel_time == GP_SCHED_EVENT_TIME_NOW));

    SCHED_ACQUIRE_EVENT_LIST();

    Sched_ScheduleEvent(rel_time , callback , arg, 0, false);
    SCHED_RELEASE_EVENT_LIST();
    gpSched_NotifySchedTask();
}

void gpSched_ScheduleEvent(UInt32 rel_time, void_func callback )
{
    gpSched_ScheduleEventArg(rel_time,(gpSched_EventCallback_t)callback, NULL);
}

Bool gpSched_UnscheduleEventArg(gpSched_EventCallback_t callback, void* arg)
{
    gpSched_globals_t* sched_globals = GP_SCHED_GET_GLOBALS();
    gpSched_Event_t* pevt;

    SCHED_ACQUIRE_EVENT_LIST();
    pevt = Sched_FindEventArg(sched_globals->gpSched_EventList, callback, arg, true);
    SCHED_RELEASE_EVENT_LIST();
    return pevt?true:false;
}

Bool gpSched_ExistsEventArg(gpSched_EventCallback_t callback, void* arg)
{
    gpSched_globals_t* sched_globals = GP_SCHED_GET_GLOBALS();
    gpSched_Event_t* pevt;
    SCHED_ACQUIRE_EVENT_LIST();
    pevt = Sched_FindEventArg(sched_globals->gpSched_EventList,callback, arg, false);
    SCHED_RELEASE_EVENT_LIST();
    return pevt?true:false;
}

STATIC_FUNC UInt32 Sched_GetRemainingTime(gpSched_Event_t* pevt, UInt32* sec)
{
    UInt32 RemainderInSec = 0xffffffff;
    UInt32 RemainderInUs  = 0xffffffff;

    if(pevt)
    {
        UInt32 time_now;
        HAL_TIMER_GET_CURRENT_TIME_1US(time_now);

        if(GP_SCHED_TIME_COMPARE_BIGGER_EQUAL(pevt->time, time_now))
        {
            RemainderInUs = GP_SCHED_GET_TIME_DIFF(time_now, pevt->time);
        }
        else
        {
            RemainderInUs = 0;
        }
        RemainderInSec = pevt->RemainderInSeconds;
    }
    if(sec)
    {
        *sec =  RemainderInSec;
        *sec += (RemainderInUs / 1000000);
        RemainderInUs = RemainderInUs % 1000000;
    }

    GP_LOG_PRINTF("delta %u evt %u cb 0x%lx",10, RemainderInUs, pevt->time,(UIntPtr) pevt->func.callback);

    return RemainderInUs;
}

UInt32 gpSched_GetRemainingTimeArg(gpSched_EventCallback_t callback, void* arg)
{
    return gpSched_GetRemainingTimeArgInSecAndUs(callback, arg, NULL);
}

UInt32 gpSched_GetRemainingTimeArgInSecAndUs(gpSched_EventCallback_t callback, void* arg, UInt32* sec)
{
    gpSched_Event_t*        pevt=NULL;
    UInt32                  remainingTime = 0xffffffff;
    gpSched_globals_t* sched_globals = GP_SCHED_GET_GLOBALS();

    SCHED_ACQUIRE_EVENT_LIST();
    pevt = Sched_FindEventArg(sched_globals->gpSched_EventList, callback, arg, false);
    SCHED_RELEASE_EVENT_LIST();

    remainingTime = Sched_GetRemainingTime(pevt, sec);

    return remainingTime;
}

gpSched_Event_t* Sched_FindEventArg(gpUtils_LinkList_t* plst , gpSched_EventCallback_t callback, void* arg, Bool unscheduleWhenFound)
{
    gpUtils_Link_t* plnk;
    for (plnk = plst->plnk_first;plnk;plnk = plnk->plnk_nxt)
    {
        gpSched_Event_t* pevt;
        pevt = (gpSched_Event_t*)GP_UTILS_LL_GET_ELEM(plnk);
        //using (arg == NULL) as wildcard

        if ((pevt->func.callbackarg == callback) && ((pevt->arg == arg) || (arg == NULL)))
        {
            if (unscheduleWhenFound)
            {
                gpUtils_LLUnlink (pevt, plst);
                Sched_ReleaseEventBody(pevt);
            }
            return pevt;
        }
    }

    return NULL;
}

Bool gpSched_UnscheduleEvent(void_func callback)
{
    return gpSched_UnscheduleEventArg((gpSched_EventCallback_t)callback, NULL);
}

Bool gpSched_ExistsEvent(void_func callback)
{
    return gpSched_ExistsEventArg((gpSched_EventCallback_t)callback, NULL);
}

UInt32 gpSched_GetRemainingTime(void_func callback)
{
    return gpSched_GetRemainingTimeArg((gpSched_EventCallback_t)callback,NULL);
}

void gpSched_ScheduleEventInSeconds (UInt32 delayInSec, gpSched_EventCallback_t callback, void* arg)
{
    Sched_ScheduleEventInSeconds(delayInSec, 0, false, 0, callback, arg);
}
void gpSched_ScheduleEventInSecAndUs(UInt32 delayInSec, UInt32 delayInUs, gpSched_EventCallback_t callback, void* arg)
{
    Sched_ScheduleEventInSeconds(delayInSec, delayInUs, false, 0, callback, arg);
}

STATIC_FUNC void Sched_ScheduleEventInSeconds(UInt32 delayInSec, UInt32 delayInUs, Bool reScheduling, UInt32 prevDeadline, gpSched_EventCallback_t callback, void* arg)
{
    UInt32 RemainderInUs  = delayInUs % 1000000;
    UInt32 RemainderInSec = delayInSec + (delayInUs / 1000000);
    UInt32 NextIntervalInSec;
    const Bool scheduleAbsTime = reScheduling;

    if(RemainderInSec > GP_SCHED_DISTANTEVENTS_INTERVAL)
    {
        NextIntervalInSec = GP_SCHED_DISTANTEVENTS_INTERVAL;
        RemainderInSec   -= GP_SCHED_DISTANTEVENTS_INTERVAL;
    }
    else
    {
        NextIntervalInSec = RemainderInSec;
        RemainderInSec    = 0;
    }

    RemainderInUs += NextIntervalInSec * 1000000;

    if (reScheduling) {
        RemainderInUs += prevDeadline;
    }

    SCHED_ACQUIRE_EVENT_LIST();
    Sched_ScheduleEvent(
        RemainderInUs,
        callback,
        arg,
        RemainderInSec,
        scheduleAbsTime
    );
    SCHED_RELEASE_EVENT_LIST();
}




#ifdef GP_SCHED_DIVERSITY_SLEEP
/*
* @brief Returns time to sleep (in microseconds).
* Will return 0 if no sleep is permitted at this point (pending actions, idle time below threshold)
*/
UInt32 Sched_CanGoToSleep(void)
{
    UInt32 result = 0;
    gpSched_globals_t* sched_globals = GP_SCHED_GET_GLOBALS();

    HAL_DISABLE_GLOBAL_INT();
    result = Sched_GetEventIdlePeriod();

    if (sched_globals->gpSched_GoToSleepDisableCounter ||
        (sched_globals->gpSched_cbGotoSleepCheck && !sched_globals->gpSched_cbGotoSleepCheck()))
    {
#ifdef GP_SCHED_FREE_CPU_TIME
/* Even when sleep is disabled, sleep for GP_SCHED_FREE_CPU_TIME */
        if(result > GP_SCHED_FREE_CPU_TIME)
        {
            result = GP_SCHED_FREE_CPU_TIME;
        }
#else
        result = 0;
#endif //GP_SCHED_FREE_CPU_TIME
    }

#if defined(GP_COMP_COM) && !defined(TBC_GPCOM) 
    if (SCHED_APP_DIVERSITY_COM() && !SCHED_APP_DIVERSITY_COM_NO_RX())
    {
        //overrule if pending RX data on COM
        if(gpCom_IsReceivedPacketPending())
        {
            result = 0;
        }
    }
#endif //defined(GP_COMP_COM) && !defined(GP_COM_DIVERSITY_NO_RX)

#if defined(GP_COMP_COM) && !defined(TBC_GPCOM)
    if (SCHED_APP_DIVERSITY_COM())
    {
        //overrule if pending TX data on COM
        if(gpCom_TXDataPending())
        {
            result = 0;
        }
    }
#endif //defined(GP_COMP_COM) && !defined(GP_COM_DIVERSITY_NO_RX)

    /* the radio is on a FD, so it is also checked in hal_HandleFds, except for halLinux/hal_noradio.c */
    if (hal_HandleFds(false))
    {
        result = 0;
    }
#if !defined(HAL_LINUX_DIVERSITY_INTERRUPT_WAKES_IOTHREAD)
    //Don't go to sleep when Radio interrupt is pending
    if(HAL_RADIO_INT_CHECK_IF_OCCURED())
    {
        result = 0;
    }
#endif


#ifdef GP_COMP_CHIPEMU
// FIXME: should implement this callback also for other chipemu variants.
#endif

    HAL_ENABLE_GLOBAL_INT();


    return result;
}
#endif // GP_SCHED_DIVERSITY_SLEEP

/*
* @brief Goes to sleep if able. Flushes com, stops timers, ...
*/
void gpSched_GoToSleep( void )
{
#ifdef GP_SCHED_DIVERSITY_SLEEP
    if (SCHED_APP_DIVERSITY_SLEEP())
    {
        UInt32 timeTosleep;

        timeTosleep = Sched_CanGoToSleep();
        if (timeTosleep)
        {


            HAL_DISABLE_GLOBAL_INT();
            // Disable unneeded interrupts
            HAL_TIMER_STOP();   // Re-enabled by TIMER_RESTART()

            HAL_ENABLE_SLEEP_UC();
            HAL_ENABLE_GLOBAL_INT();

            while (true)
            {
                timeTosleep = Sched_CanGoToSleep();
                if(timeTosleep == 0)
                {
                    break;
                }
                HAL_SLEEP_UC_1US(timeTosleep);
                HAL_ENABLE_SLEEP_UC();
            }

            // Restart timer of uC without initialization
            // Note: if we have a HAL that supports going to sleep while an event is pending,
            // we have to forward the time of the scheduler when a new event is scheduled from an ISR or
            // when we wake-up to execute the pending event.
            HAL_TIMER_RESTART();
        }
    }
#endif // GP_SCHED_DIVERSITY_SLEEP
}

void gpSched_SetGotoSleepEnable( Bool enable )
{
#ifdef GP_SCHED_DIVERSITY_SLEEP
    if (SCHED_APP_DIVERSITY_SLEEP())
    {
        gpSched_globals_t* sched_globals = GP_SCHED_GET_GLOBALS();
        //gpSched_GoToSleepEnable = enable;
        HAL_DISABLE_GLOBAL_INT();
        if (enable)
        {
            GP_ASSERT_DEV_EXT(sched_globals->gpSched_GoToSleepDisableCounter);
            sched_globals->gpSched_GoToSleepDisableCounter--;
        }
        else
        {
            sched_globals->gpSched_GoToSleepDisableCounter++;
        }
        HAL_ENABLE_GLOBAL_INT();
    }
#else // GP_SCHED_DIVERSITY_SLEEP
    NOT_USED(enable);
#endif // GP_SCHED_DIVERSITY_SLEEP
}


/*****************************************************************************
 *                    Main function
 *****************************************************************************/

void gpSched_Main_Body(void)
{
    gpSched_Event_t* pevt;

    // Check stack before event (after coming from sleep)
    GP_UTILS_CHECK_STACK_PATTERN();
    GP_UTILS_CHECK_STACK_POINTER();

    GP_ASSERT_DEV_EXT(HAL_GLOBAL_INT_ENABLED());

    HAL_WDT_RESET();

        /* service radio before hal_HandleFds */
        // Handle radio interrupts
#if !defined(HAL_LINUX_DIVERSITY_INTERRUPT_WAKES_IOTHREAD)
        HAL_RADIO_INT_EXEC_IF_OCCURED();
#endif
        GP_UTILS_CPUMON_PROCDONE(RADIO_INT);
        /* the radio will be serviced again if possible, since it is in the list of FD's! */
        (void)hal_HandleFds(true);

#if defined(GP_COMP_COM) && !defined(TBC_GPCOM)
        if (SCHED_APP_DIVERSITY_COM())
        {
            // Handle non-interrupt driven actions from gpCom
            gpCom_HandleTx();
            if (!SCHED_APP_DIVERSITY_COM_NO_RX())
            {
                gpCom_HandleRx();
            }
            GP_UTILS_CPUMON_PROCDONE(GPCOMTXRX);
        }
#endif //GP_COMP_COM


    // Handle events
    pevt = Sched_GetEvent();
    SCHED_MAIN_BODY( pevt );
    if (pevt)             // get event
    {
        GP_ASSERT_DEV_EXT(HAL_GLOBAL_INT_ENABLED());
            //GP_LOG_SYSTEM_PRINTF("sched: %08lx",0, pevt->func.callback);
            if (pevt->RemainderInSeconds) {
                Sched_ScheduleEventInSeconds(pevt->RemainderInSeconds, 0, true, pevt->time, pevt->func.callbackarg, pevt->arg);
            } else
            {
                Sched_ExecEvent(pevt);
            }

        // check stack after event
        GP_UTILS_CHECK_STACK_PATTERN();
        GP_UTILS_CHECK_STACK_POINTER();

        if (!HAL_GLOBAL_INT_ENABLED())
        {
            GP_LOG_PRINTF("AtomF %p",2,pevt->func.callback);
            GP_ASSERT_DEV_EXT(HAL_GLOBAL_INT_ENABLED());
        }
        Sched_ReleaseEvent(pevt);                // release event
        // check stack after event release
        GP_UTILS_CHECK_STACK_PATTERN();
        GP_UTILS_CHECK_STACK_POINTER();
        GP_UTILS_CHECK_STACK_USAGE();
    }
    GP_UTILS_CPUMON_PROCDONE(SCHEDEVENT);

#ifdef GP_COMP_CHIPEMU
    gpChipEmu_RunEmu();
#endif // GP_COMP_CHIPEMU

    GP_ASSERT_DEV_EXT(HAL_GLOBAL_INT_ENABLED());
}

