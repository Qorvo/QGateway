/*
 * Copyright (c) 2013-2016, GreenPeak Technologies
 * Copyright (c) 2017, Qorvo Inc
 *
 * hal.c
 *   Hardware Abstraction Layer for linux based devices, in combination with gp kernel driver
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
 * $Header: //depot/release/Embedded/Components/Qorvo/HAL_PLATFORM/v2.10.2.0/comps/halLinux/user/src/hal_backtrace.c#1 $
 * $Change: 187624 $
 * $DateTime: 2021/12/20 10:58:50 $
 *
 */

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/
#include "hal.h"
#include "hal_defs.h"
#include "gpBsp.h"
#include "gpAssert.h"
#include "gpLog.h"

#include <execinfo.h> // for getting the stack trace after assert
#include <signal.h>   // signal handlers defs.
#include <unistd.h>

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/
#define GP_COMPONENT_ID GP_COMPONENT_ID_HALLINUX

/*****************************************************************************
 *                    Type Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Static Data Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Public Data Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/

void hal_dump_backtrace(UInt8 maxlevel)
{
    //
    // use compiler options:
    // OPT = -rdynamic -funwind-tables
    //
    #define MAX_STACK_TRACE 16
    void* stacktrace[MAX_STACK_TRACE];
    UInt8 stacksize;
    char** stacknames;
    NOT_USED(maxlevel);

    stacksize = backtrace(stacktrace, MAX_STACK_TRACE);
    GP_LOG_SYSTEM_PRINTF("stacktrace size=%d",0,stacksize);
    stacknames = backtrace_symbols(stacktrace, stacksize);
    if(stacksize>1)
    {
        UInt8 stackindex;
        for(stackindex=1; stackindex<stacksize; stackindex++)
        {
                GP_LOG_SYSTEM_PRINTF("stack %d %s",0,stackindex, stacknames[stackindex]);
                gpLog_Flush();
        }
    }
}

void handler(int sig, siginfo_t *info, void* secret)
{
    NOT_USED(secret);
    GP_LOG_SYSTEM_PRINTF("Got signal %d at address %p",0, sig, info->si_addr);
    GP_ASSERT_DEV_INT(false);
}

void hal_install_exception_handlers(void)
{
    struct sigaction sa;
    sa.sa_sigaction = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_SIGINFO;

    sigaction(SIGSEGV, &sa, NULL);
    sigaction(SIGFPE , &sa, NULL);
    sigaction(SIGBUS , &sa, NULL);
    sigaction(SIGILL , &sa, NULL);
    sigaction(SIGABRT, &sa, NULL);
}

