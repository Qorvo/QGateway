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
 * $Header$
 * $Change$
 * $DateTime$
 */

/** @file "gpRandom_clientServerCmdId.h"
 *
 *  Random generator component
 *
 *  Client Server Link Command IDs
*/

#ifndef _GPRANDOM_CLIENTSERVERCMDID_H_
#define _GPRANDOM_CLIENTSERVERCMDID_H_

/*****************************************************************************
 *                    Common timeout
 *****************************************************************************/

#ifndef GPRANDOM_GPCOMTIMEOUT_US
#define GPRANDOM_GPCOMTIMEOUT_US 10000000UL //10s
#endif //GPRANDOM_GPCOMTIMEOUT_US

/*****************************************************************************
 *                    Component Specific Command IDs
 *****************************************************************************/

#define gpRandom_GetNewSequence_CmdId                                0x02 /*02*/
#define gpRandom_CTR_DRBG_Init_CmdId                                 0x04 /*04*/
#define gpRandom_CTR_DRBG_Reseed_CmdId                               0x05 /*05*/
#define gpRandom_CTR_DRBG_Generate_CmdId                             0x06 /*06*/
#define gpRandom_GetFromDRBG_CmdId                                   0x08 /*08*/

/*****************************************************************************
 *                    Fixed Command IDs
 *****************************************************************************/

#define gpRandom_Acknowledge_CmdId                                   0xfe /*254*/
#define gpRandom_GetServerCompatibilityNumber_CmdId                  0xfd /*253*/

#endif //_GPRANDOM_CLIENTSERVERCMDID_H_

