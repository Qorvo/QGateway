/*
 * Copyright (c) 2015, GreenPeak Technologies
 * Copyright (c) 2017-2019, Qorvo Inc
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
 * $Header: //depot/main/Embedded/Components/Qorvo/802_15_4/v2.10.3.1/comps/gpRxArbiter/inc/gen/gpRxArbiter_clientServerCmdId.h#1 $
 * $Change: 195340 $
 * $DateTime: 2022/06/17 14:57:48 $
 */

/** @file "gpRxArbiter_clientServerCmdId.h"
 *
 *  RxArbiter
 *
 *  Client Server Link Command IDs
*/

#ifndef _GPRXARBITER_CLIENTSERVERCMDID_H_
#define _GPRXARBITER_CLIENTSERVERCMDID_H_

/*****************************************************************************
 *                    Common timeout
 *****************************************************************************/

#ifndef GPRXARBITER_GPCOMTIMEOUT_US
#define GPRXARBITER_GPCOMTIMEOUT_US 10000000UL //10s
#endif //GPRXARBITER_GPCOMTIMEOUT_US

/*****************************************************************************
 *                    Component Specific Command IDs
 *****************************************************************************/

#define gpRxArbiter_ResetStack_CmdId                                 0x02 /*02*/
#define gpRxArbiter_SetStackChannel_CmdId                            0x03 /*03*/
#define gpRxArbiter_GetStackChannel_CmdId                            0x04 /*04*/
#define gpRxArbiter_GetCurrentRxOnState_CmdId                        0x05 /*05*/
#define gpRxArbiter_GetCurrentRxChannel_CmdId                        0x06 /*06*/
#define gpRxArbiter_SetStackRxOn_CmdId                               0x07 /*07*/
#define gpRxArbiter_GetStackRxOn_CmdId                               0x08 /*08*/
#define gpRxArbiter_SetDutyCycleOnOffTimes_CmdId                     0x09 /*09*/
#define gpRxArbiter_EnableDutyCycling_CmdId                          0x0a /*10*/
#define gpRxArbiter_GetDutyCycleEnabled_CmdId                        0x0b /*11*/
#define gpRxArbiter_SetStackPriority_CmdId                           0x0c /*12*/
#define gpRxArbiter_IsAnActiveChannel_CmdId                          0x11 /*17*/
#define gpRxArbiter_EnableRxWindows_CmdId                            0x12 /*18*/
#define gpRxArbiter_DisableRxWindows_CmdId                           0x13 /*19*/
#define gpRxArbiter_cbSetFaModeNotification_CmdId                    0x0e /*14*/
#define gpRxArbiter_cbChannelUpdateNotification_CmdId                0x10 /*16*/

/*****************************************************************************
 *                    Fixed Command IDs
 *****************************************************************************/

#define gpRxArbiter_Acknowledge_CmdId                                   0xfe /*254*/
#define gpRxArbiter_GetServerCompatibilityNumber_CmdId                  0xfd /*253*/

#endif //_GPRXARBITER_CLIENTSERVERCMDID_H_

