/*
 * Copyright (c) 2017, Qorvo Inc
 *
 * uart_rpi_qorvo.c
 *   This file contains the implementation of the qorvo uart api for openthread.
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
 * $Header: //depot/release/Embedded/Applications/P959_OpenThread/v1.1.23.0/comps/qvOT/src/uart_rpi_qorvo.c#1 $
 * $Change: 187624 $
 * $DateTime: 2021/12/20 10:58:50 $
 *
 */

#define GP_COMPONENT_ID GP_COMPONENT_ID_QVOT

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

#include "platform_qorvo.h"
#include "uart_qorvo.h"
#include "gpLog.h"
#include "hal.h"

#include <common/code_utils.hpp>
#include <utils/uart.h>
#include <openthread/config.h>

#include <stdio.h>
#include <stdarg.h>

/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/

void qorvoUartLog(otLogLevel aLogLevel, otLogRegion aLogRegion, const char *aFormat, va_list args)
{
    NOT_USED(aLogLevel);
    NOT_USED(aLogRegion);

    char logString[512];

    vsnprintf(&logString[0], sizeof(logString), aFormat, args);

    GP_LOG_SYSTEM_PRINTF("%s", 0, logString);
    gpLog_Flush();
}

void myPlatLog(const char *aFormat, ...)
{
    va_list args;

    va_start(args, aFormat);
    qorvoUartLog(OT_LOG_LEVEL_CRIT, OT_LOG_REGION_PLATFORM, aFormat, args);
    va_end(args);
}
