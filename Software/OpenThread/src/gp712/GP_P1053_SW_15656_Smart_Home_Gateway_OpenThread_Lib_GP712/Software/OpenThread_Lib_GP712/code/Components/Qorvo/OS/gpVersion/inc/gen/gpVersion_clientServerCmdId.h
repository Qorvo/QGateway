/*
 * Copyright (c) 2015, GreenPeak Technologies
 * Copyright (c) 2017-2018, Qorvo Inc
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
 * $Header: //depot/main/Embedded/Components/Qorvo/OS/v2.10.3.1/comps/gpVersion/inc/gen/gpVersion_clientServerCmdId.h#1 $
 * $Change: 195340 $
 * $DateTime: 2022/06/17 14:57:48 $
 */

/** @file "gpVersion_clientServerCmdId.h"
 *
 *  GPVERSION
 *
 *  Client Server Link Command IDs
*/

#ifndef _GPVERSION_CLIENTSERVERCMDID_H_
#define _GPVERSION_CLIENTSERVERCMDID_H_

/*****************************************************************************
 *                    Common timeout
 *****************************************************************************/

#ifndef GPVERSION_GPCOMTIMEOUT_US
#define GPVERSION_GPCOMTIMEOUT_US 10000000UL //10s
#endif //GPVERSION_GPCOMTIMEOUT_US

/*****************************************************************************
 *                    Component Specific Command IDs
 *****************************************************************************/

#define Version_ExchangeGlobalVersion_CmdId                          0x02 /*02*/
#define Version_NegotiateModuleVersion_CmdId                         0x03 /*03*/

/*****************************************************************************
 *                    Fixed Command IDs
 *****************************************************************************/

#define gpVersion_Acknowledge_CmdId                                   0xfe /*254*/
#define gpVersion_GetServerCompatibilityNumber_CmdId                  0xfd /*253*/

#endif //_GPVERSION_CLIENTSERVERCMDID_H_

