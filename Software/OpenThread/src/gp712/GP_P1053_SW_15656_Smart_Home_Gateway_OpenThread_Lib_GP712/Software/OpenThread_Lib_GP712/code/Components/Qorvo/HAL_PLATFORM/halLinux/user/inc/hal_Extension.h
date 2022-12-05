/*
 * Copyright (c) 2010-2016, GreenPeak Technologies
 * Copyright (c) 2017, Qorvo Inc
 *
 * hal_Extension.h
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
 * $Header: //depot/release/Embedded/Components/Qorvo/HAL_PLATFORM/v2.10.3.1/comps/halLinux/user/inc/hal_Extension.h#1 $
 * $Change: 197210 $
 * $DateTime: 2022/10/13 16:52:00 $
 *
 */

#ifndef _HAL_EXTENSION_H_
#define _HAL_EXTENSION_H_

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/

#define HAVE_LOCALTIME

//Chip access macro's
#define HAL_ACCESS_CHIP(command, pValue)        ioctl(fdGP, command, pValue)

#define HAL_TIMER_RESTART()

/*****************************************************************************
 *                    Type Definitions
 *****************************************************************************/

typedef Int16 (* hal_cbUartGetTxData_t) (void);
#if defined(HAL_DIVERSITY_UART_RX_BUFFER_CALLBACK)
typedef void (* hal_cbUartRx_t)(UInt8 *buffer, UInt16 size);
#else
typedef void (* hal_cbUartRx_t) (Int16);
#endif
typedef void (* hal_cbUartTxReady_t) (void);
typedef Bool (* hal_cbUartTxPending_t) (void);

typedef void (*hal_PollFunction_t)(UInt8);
typedef void (*hal_RadioFunction_t)(void);

typedef void (*hal_cbSocketRx_t)(UInt16, const char*, UInt32 socketId);
typedef void (*hal_cbSocketClose_t)(UInt32 socketId);

/*****************************************************************************
 *                    Public Data Definitions
 *****************************************************************************/
extern Bool hal_UartRxEnabled;
extern Bool hal_UartTxEnabled;
extern int fdGP;
/*****************************************************************************
 *                    Internal Function Definitions
 *****************************************************************************/

void hal_InitSocket(hal_cbSocketRx_t RxISR, hal_cbSocketClose_t closeCb);
void hal_DeInitSocket(void);

int  hal_TxDataSocket(UInt16 length, UInt8 *pData, UInt32 socketId);

void hal_RegisterGPPollFunction(hal_RadioFunction_t pollFunction);


#ifdef GP_COMP_CHIPEMU
void hal_msiInit(UInt8 not_in_reset);
UInt8 hal_msiHandleTx(UInt8 byte);
UInt8 hal_msiHandleRx(UInt8 byte);

void hal_update_interrupt(void);
#endif //GP_COMP_CHIPEMU

UInt32 hal_getSecondsSinceEpoch(void);

/** @brief Return the current real time in microseconds since the Unix epoch.
 *
 *  This function returns the real time as reported by the operating system.
 *  The time is represented as the number of microseconds elapsed
 *  since 1970-01-01 00:00:00 UTC (excluding leap seconds).
 */
UInt64 hal_GetMicrosecondsSinceEpoch(void);

#define __DSB()
#endif //_HAL_EXTENSION_H_
