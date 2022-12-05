/*
 * Copyright (c) 2010, 2012-2016, GreenPeak Technologies
 * Copyright (c) 2017, Qorvo Inc
 *
 * hal_Sched.c
 *   Linux-specific implementation of event polling and event waiting.
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
 * $Header: //depot/release/Embedded/Components/Qorvo/HAL_PLATFORM/v2.10.3.1/comps/halLinux/user/src/hal_Sched.c#1 $
 * $Change: 197210 $
 * $DateTime: 2022/10/13 16:52:00 $
 *
 */

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/
//#define GP_LOCAL_LOG
#include "hal.h"
#include "hal_defs.h"
#include "gpAssert.h"
#ifdef GP_COMP_CHIPEMU
#include "gpChipEmu.h"
#ifdef GP_COMP_GPHAL
#include "gpHal.h"
#endif //GP_COMP_GPHAL
#endif //GP_COMP_CHIPEMU

#include <stdio.h>
#include <string.h>

#include "gpLog.h"
#include <sys/time.h>
#include <sys/types.h>

#include <unistd.h>
#include <errno.h>
#include <sys/eventfd.h>


/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/

#define GP_COMPONENT_ID GP_COMPONENT_ID_HALLINUX
#define HAL_NUM_OF_FD   40
#define HAL_INVALID_FD  -1
#define EVENTFD_INITIAL_VALUE_ZERO 0
/*****************************************************************************
 *                    Type Definitions
 *****************************************************************************/

typedef struct{
    Bool valid;
    int fd;
    hal_PollFunction_t pollFunction;
    hal_PollFunction_t pollFunction_write;
} hal_PollFunctionInfo_t;

/*****************************************************************************
 *                    Static Data Definitions
 *****************************************************************************/

static int hal_nfds = 0;
static hal_PollFunctionInfo_t hal_PollFunctionInfo[HAL_NUM_OF_FD];
static int hal_EventFd = -1;


#if defined(GP_COMP_CHIPEMU)
static hal_cbFastForwardSleep_t hal_cbFastForwardSleep;
#endif //defined(HAL_FASTFORWARD_FOR_UNIT_TEST) || defined(GP_COMP_CHIPEMU)

/*****************************************************************************
 *                    Static Function Declarations
 *****************************************************************************/

#if defined(GP_COMP_CHIPEMU)
void hal_FastForwardSleep(UInt32 requestedSleepTime, UInt64* clockCounter);
#endif //defined(HAL_FASTFORWARD_FOR_UNIT_TEST) || defined(GP_COMP_CHIPEMU)
static void hal_EventFdInit(void);
static void hal_EventFdDeInit(void);
static void hal_EventFdHandler(UInt8 x);

/*****************************************************************************
 *                    Static Function Definitions
 *****************************************************************************/


/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/

void halSched_Init(void)
{
    UIntLoop i;

    if (hal_nfds != 0)
    {
        // Allow re-init of hal without resetting registered file descriptors.
        return;
    }


    hal_nfds = 0;
    MEMSET(hal_PollFunctionInfo, 0, sizeof(hal_PollFunctionInfo_t) * HAL_NUM_OF_FD);
    for(i = 0; i < HAL_NUM_OF_FD; i++)
    {
        hal_PollFunctionInfo[i].valid = false;
        hal_PollFunctionInfo[i].fd = HAL_INVALID_FD;
    }
    #if defined(GP_COMP_CHIPEMU)
    hal_cbFastForwardSleep = hal_FastForwardSleep;
    #endif //defined(HAL_FASTFORWARD_FOR_UNIT_TEST) || defined(GP_COMP_CHIPEMU)

    hal_EventFdInit();

}

void halSched_DeInit(void)
{
    hal_EventFdDeInit();

    // Clear poll function table.
    hal_nfds = 0;
    memset(hal_PollFunctionInfo, 0, sizeof(hal_PollFunctionInfo_t) * HAL_NUM_OF_FD);
}

void hal_RegisterPollFunction(int fd, hal_PollFunction_t pollFunction)
{
    UIntLoop i;
    Bool added = false;

    //Check re-add first
    for(i=0; i < HAL_NUM_OF_FD; i++)
    {
        if(hal_PollFunctionInfo[i].fd == fd && hal_PollFunctionInfo[i].valid)
        {
            hal_PollFunctionInfo[i].pollFunction = pollFunction;
            added = true;
            break;
        }
    }

    if(!added)
    {
        for(i=0; i < HAL_NUM_OF_FD; i++)
        {
            if(!hal_PollFunctionInfo[i].valid)
            {
                hal_PollFunctionInfo[i].valid = true;
                hal_PollFunctionInfo[i].fd = fd;
                hal_PollFunctionInfo[i].pollFunction = pollFunction;
                if(fd >= hal_nfds)
                {
                    hal_nfds = fd +1;
                }
                added = true;
                break;
            }
        }
    }
    GP_ASSERT_SYSTEM(added);
}

void hal_UnRegisterPollFunction(int fd)
{
    UIntLoop i;
    int new_nfds = 0;

    for(i = 0; i < HAL_NUM_OF_FD; i++)
    {
        if(hal_PollFunctionInfo[i].valid)
        {
            if (hal_PollFunctionInfo[i].fd == fd)
            {
                //Invalidate all info for this fd
                hal_PollFunctionInfo[i].valid = false;
                hal_PollFunctionInfo[i].fd = HAL_INVALID_FD;
                hal_PollFunctionInfo[i].pollFunction = NULL;
                hal_PollFunctionInfo[i].pollFunction_write = NULL;
            }
            else
            {
                //Re-calculate nfds over remaining fds
                new_nfds = max(new_nfds, hal_PollFunctionInfo[i].fd);
            }
        }
    }
    hal_nfds = new_nfds+1;
}

Bool hal_Select(UInt32 time, Bool Execute)
{
    Bool ready = false;
    UInt32 time_us = time;

    fd_set readfds, writefds;
    UInt16 i;   /* the number of nfds can be larger than
                   255 in some linux based middleware applications */
    struct timeval tv;
    int retval;

    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    for(i=0;i<hal_nfds;i++)
    {
        UIntLoop j;
        for(j = 0; j < HAL_NUM_OF_FD; j++)
        {
            if(hal_PollFunctionInfo[j].valid && hal_PollFunctionInfo[j].fd == i)
            {
                FD_SET(i,&readfds);
                if (hal_PollFunctionInfo[j].pollFunction_write)
                {
                    FD_SET(i,&writefds);
                }
            }
        }
    }

    if(time != HAL_SLEEP_INDEFINITE_SLEEP_TIME)
    {
        tv.tv_sec = (time_us / 1000000);
        tv.tv_usec = (time_us % 1000000);

        retval = select(hal_nfds, &readfds, &writefds, NULL, &tv);
    }
    else
    {
        retval = select(hal_nfds, &readfds, &writefds, NULL, NULL);
    }

    if(retval == -1)
    {
        printf("Error on select(): %s\n", strerror(errno));
        if((errno != EINTR) && (errno !=EBADF))
        {
            perror("select()");
            GP_ASSERT_SYSTEM(false);
        }
    }
    else if (retval)
    {
        for(i=0;i<hal_nfds;i++)
        {
            if(FD_ISSET(i,&readfds))
            {
                UIntLoop j;
                for(j = 0; j < HAL_NUM_OF_FD; j++)
                {
                    if(hal_PollFunctionInfo[j].valid && hal_PollFunctionInfo[j].fd == i && hal_PollFunctionInfo[j].pollFunction)
                    {
                        ready |= true;
                        if (Execute)
                        {
                            hal_PollFunctionInfo[j].pollFunction(i);
                        }
                    }
                }

            }
            if(FD_ISSET(i,&writefds))
            {
                UIntLoop j;
                for(j = 0; j < HAL_NUM_OF_FD; j++)
                {
                    if(hal_PollFunctionInfo[j].valid && hal_PollFunctionInfo[j].fd == i && hal_PollFunctionInfo[j].pollFunction_write)
                    {
                        ready |= true;
                        if (Execute)
                        {
                            hal_PollFunctionInfo[j].pollFunction_write(i);
                        }
                    }
                }

            }
        }
    }
    return ready;
}

void hal_GoToSleep(UInt32 time)
{
#if defined(GP_COMP_CHIPEMU)
    hal_cbFastForwardSleep(time, &hal_ClockCounter);
#else
    (void) hal_Select(time, false);
#endif //defined(HAL_FASTFORWARD_FOR_UNIT_TEST) || defined(GP_COMP_CHIPEMU)
#ifdef GP_COMP_CHIPEMU
    gpChipEmu_UpdateChipClocks();
#endif //GP_COMP_CHIPEMU
}
Bool hal_HandleFds(Bool execute)
{
    return hal_Select(0, execute);
}

#if defined(GP_COMP_CHIPEMU)
void hal_FastForwardSleep(UInt32 requestedSleepTime, UInt64* clockCounter)
{
    *clockCounter += requestedSleepTime;
}
#endif //defined(HAL_FASTFORWARD_FOR_UNIT_TEST) || defined(GP_COMP_CHIPEMU)

#if defined(GP_COMP_CHIPEMU)
void hal_RegisterFastForwardSleepCallback(hal_cbFastForwardSleep_t cbFFSleep)
{
    hal_cbFastForwardSleep = cbFFSleep;
}
#endif //defined(HAL_FASTFORWARD_FOR_UNIT_TEST) || defined(GP_COMP_CHIPEMU)

void hal_WakeEventloop(void)
{
    ssize_t retval;
    uint64_t u = 1;

    GP_LOG_PRINTF("%s",0,__FUNCTION__);
    GP_ASSERT_SYSTEM(hal_EventFd != -1);
    errno = 0;
    retval = write(hal_EventFd, &u, sizeof(uint64_t));
    if (retval == -1 && errno != EAGAIN && errno != EINTR)
    {
        GP_LOG_SYSTEM_PRINTF("errno = %d, fd=%d",0,errno,hal_EventFd);
        GP_ASSERT_SYSTEM(false);
    }
}

void hal_ClearWakeUpEvent(void)
{
    GP_LOG_PRINTF("%s",0,__FUNCTION__);
    hal_EventFdHandler(0);
}

static void hal_EventFdHandler(UInt8 x)
{
    ssize_t retval;
    uint64_t u;

    NOT_USED(x);

    GP_ASSERT_SYSTEM(hal_EventFd != -1);
    errno = 0;
    retval = read(hal_EventFd, &u, sizeof(uint64_t));
    if (retval == -1 && errno != EAGAIN && errno != EINTR)
    {
        GP_LOG_SYSTEM_PRINTF("errno = %d, fd=%d",0,errno,hal_EventFd);
        GP_ASSERT_SYSTEM(false);
    }
}

static void hal_EventFdInit(void)
{
    /* Don't pass EFD_SEMAPHORE so upon read(), the counter is reset to zero.
     * This is important because the scheduler thread only needs to run once
     * after event(s) are scheduled from a different execution context */
    /* EFD_NONBLOCK: make the fd nonblocking so we can clear it to avoid
     * skipping the blocking select() call. */
    hal_EventFd = eventfd(EVENTFD_INITIAL_VALUE_ZERO, EFD_NONBLOCK);
    GP_ASSERT_SYSTEM(hal_EventFd  != -1);

    if (hal_EventFd != -1)
    {
        GP_LOG_PRINTF("register poll function",0);
        hal_RegisterPollFunction(hal_EventFd, hal_EventFdHandler);
    }
}
static void hal_EventFdDeInit(void)
{
    int result;

    GP_ASSERT_SYSTEM(hal_EventFd != -1);

    hal_UnRegisterPollFunction(hal_EventFd);

    errno = 0;
    result = close(hal_EventFd);
    if (result == -1 && errno != EINTR)
    {
        GP_LOG_SYSTEM_PRINTF("errno = %d, fd=%d",0,errno,hal_EventFd);
        GP_ASSERT_SYSTEM(false);
    }
    hal_EventFd = -1;
}

void hal_SetPollFunction_write(int fd, hal_PollFunction_t pollFunction)
{
    UIntLoop i;

    for(i = 0; i < HAL_NUM_OF_FD; i++)
    {
        if(hal_PollFunctionInfo[i].fd == fd && hal_PollFunctionInfo[i].valid)
        {
            hal_PollFunctionInfo[i].pollFunction_write = pollFunction;
            break;
        }
    }
}

void hal_MutexAcquire(pthread_mutex_t *pMutex)
{
    pthread_mutex_lock(pMutex);
}

void hal_MutexRelease(pthread_mutex_t *pMutex)
{
    pthread_mutex_unlock(pMutex);
}

void hal_MutexCreate(pthread_mutex_t **pMutex)
{
    pthread_mutex_t *pThreadMutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(pThreadMutex, NULL);
    *pMutex = pThreadMutex;
}

void hal_MutexDestroy(pthread_mutex_t **pMutex)
{
    pthread_mutex_destroy(*pMutex);
    free(*pMutex);
    *pMutex = NULL;
}

Bool hal_MutexIsValid(pthread_mutex_t *pMutex)
{
    return (pMutex != NULL);
}

Bool hal_MutexIsAcquired(pthread_mutex_t *pMutex)
{
    int __result = pthread_mutex_trylock(pMutex);
    if(0 == __result) { pthread_mutex_unlock(pMutex); };
    return (0 != __result);
}
