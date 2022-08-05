/*
 * Copyright (c) 2010-2016, GreenPeak Technologies
 * Copyright (c) 2017, 2019, Qorvo Inc
 *
 * This file contains the implementation of the logging module (forward to printf version).
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
 * $Header: //depot/main/Embedded/BaseComps/vlatest/sw/comps/gpLog/src/gpLog.c#35 $
 * $Change: 12663 $
 * $DateTime: 2010/03/29 17:27:52 $
 *
 */

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

#define GP_COMPONENT_ID GP_COMPONENT_ID_LOG

#include "gpLog.h"
#include "hal.h" /*HAVE_LOCALTIME setting*/

#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>



/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/

#define LOG_MAX_LEN 200

/*****************************************************************************
 *                    Type Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Static Data Definitions
 *****************************************************************************/

#ifdef GP_LOG_BUFFERED_COMPID
static char Log_BufferCompId[LOG_MAX_LEN];
#endif //GP_LOG_BUFFERED_COMPID

static FILE* Log_pLogFile = NULL;
static Bool Log_Enabled = true;


/*****************************************************************************
 *                    Static Function Prototypes
 *****************************************************************************/

static void Log_Formatted(UInt8 componentID, char* buf);

/*****************************************************************************
 *                    Static Function Definitions
 *****************************************************************************/

#ifdef GP_LOG_BUFFERED_COMPID
Bool Log_Buffer(char* buf)
{
    UIntLoop i;
    Bool buffered;

    UInt8 newBufLength;
    UInt8 logBufLength;

    newBufLength = strlen(buf);
    logBufLength = strlen(Log_BufferCompId);

    //Max buffering exceeded - dump what is stored
    if((newBufLength + logBufLength) >= LOG_MAX_LEN)
    {
        Log_Formatted(GP_LOG_BUFFERED_COMPID, Log_BufferCompId);
        //Reset buffer
        MEMSET(Log_BufferCompId, 0, sizeof(Log_BufferCompId));
        logBufLength = 0;
    }

    //buffer to static buffer - limited to max length
    STRNCPY(&Log_BufferCompId[logBufLength], buf, LOG_MAX_LEN - logBufLength);
    buffered = true;

    // check for \n present:
    for(i = 0; i < newBufLength; i++)
    {
        if(buf[i] == '\n') //End of line found
        {
            //Add buffered logging to end-of-line logging and let it pass
            STRNCPY(buf, Log_BufferCompId, LOG_MAX_LEN);

            buf[strlen(buf) - 1] = 0x0; //remove /n

            //Reset buffer
            MEMSET(Log_BufferCompId, 0, sizeof(Log_BufferCompId));
            buffered = false;
            break;
        }
    }

    return buffered;
}
#endif //GP_LOG_BUFFERED_COMPID

static void Log_Formatted(UInt8 componentID, char* buf)
{
#if defined(HAVE_LOCALTIME) 
    char timeBuf[10];
    struct tm* local;
#endif
#if defined(GP_COMP_UNIT_TEST) || defined(GP_COMP_CHIPEMU)
    UInt16 ms, us;
#endif

#ifdef HAVE_LOCALTIME
#if defined(GP_COMP_UNIT_TEST) || defined(GP_COMP_CHIPEMU)
    time_t t;
    t = (time_t)hal_GetCurrentTime()*32;
    us = (UInt16)(t % 1000);
    t = t / 1000;
    ms = (UInt16)(t % 1000);
    t  = t / 1000;
    local = localtime(&t);
    strftime(timeBuf, 10, "%H:%M:%S", local);
    printf("%s.%03d.%03d: %02X %s\n", timeBuf, ms, us, componentID, buf);
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    local = localtime(&tv.tv_sec);
    strftime(timeBuf, 10, "%H:%M:%S", local);
    if(Log_Enabled)
    {
        printf("%s:%03u %02X %s\n", timeBuf, (UInt16)(tv.tv_usec / 1000), componentID, buf);
    }
    if(Log_pLogFile)
    {
        fprintf(Log_pLogFile, "%s:%03u %02X %s\n", timeBuf, (UInt16)(tv.tv_usec / 1000), componentID, buf);
        fflush(Log_pLogFile);
    }
#endif
#else
    printf("%02X %s\n", componentID, buf);
#endif
}

/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/

void gpLog_Init(void)
{
#ifdef GP_LOG_BUFFERED_COMPID
    MEMSET(Log_BufferCompId, 0, sizeof(Log_BufferCompId));
#endif //GP_LOG_BUFFERED_COMPID
}

void gpLog_Printf(UInt8 componentID, Bool progmem, FLASH_STRING format_str, UInt8 length, ...)
{
    NOT_USED(progmem);
    char buf[LOG_MAX_LEN];

    va_list ap;
    va_start(ap, length);
    vsnprintf(buf, LOG_MAX_LEN, format_str, ap);
    va_end(ap);

#ifdef GP_LOG_BUFFERED_COMPID
    if((componentID == GP_LOG_BUFFERED_COMPID) && Log_Buffer(buf))
    {
        return;
    }
#endif
    Log_Formatted(componentID, buf);
}

void gpLog_PrintBuffer(UInt16 length, UInt8* buf)
{
    int i;

    for(i = 0; i < length; i += 8)
    {
        gpLog_Printf(GP_COMPONENT_ID, true, "%u/%u: %04x %04x %04x %04x", 0,
                     i, length, ((buf[i] << 8) | buf[i + 1]),
                     ((buf[i + 2] << 8) | buf[i + 3]),
                     ((buf[i + 4] << 8) | buf[i + 5]),
                     ((buf[i + 6] << 8) | buf[i + 7]));
        gpLog_Flush();
    }
}

void gpLog_Flush(void)
{
    fflush(stdout);
}

void gpLog_EnableConsoleLog(Bool enable)
{
    Log_Enabled = enable;
}
Bool gpLog_GetConsoleLog(void)
{
    return Log_Enabled;
}
void gpLog_SetFilePointer(void* pFile)
{
    Log_pLogFile = (FILE*)pFile;
}


