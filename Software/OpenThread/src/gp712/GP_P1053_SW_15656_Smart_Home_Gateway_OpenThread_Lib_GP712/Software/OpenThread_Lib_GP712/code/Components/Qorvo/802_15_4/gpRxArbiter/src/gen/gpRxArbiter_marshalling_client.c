/*
 * Copyright (c) 2015-2016, GreenPeak Technologies
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
 * $Header: //depot/main/Embedded/Components/Qorvo/802_15_4/v2.10.3.1/comps/gpRxArbiter/src/gen/gpRxArbiter_marshalling_client.c#1 $
 * $Change: 195340 $
 * $DateTime: 2022/06/17 14:57:48 $
 */

/** @file "gpRxArbiter_marshalling_client.c"
 *
 *  RxArbiter
 *
 *  Marshalling structures and functions
*/

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

// General includes
#include "gpRxArbiter.h"
#include "gpRxArbiter_marshalling.h"

#include "gpLog.h"
#include "gpAssert.h"

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/
#define GP_COMPONENT_ID GP_COMPONENT_ID_RXARBITER

/*****************************************************************************
 *                    Static Function Prototypes
 *****************************************************************************/

 /*****************************************************************************
 *                    Static Data Definitions
 *****************************************************************************/

 /*****************************************************************************
 *                    Static Function Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/

void gpRxArbiter_ResetStack_Input_par2buf(UInt8Buffer* pDest , gpRxArbiter_StackId_t stackId , UInt16* pIndex)
{
    gpRxArbiter_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpRxArbiter_ResetStack_Output_buf2par(gpRxArbiter_Result_t* result , gpRxArbiter_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpRxArbiter_Result_t_buf2api(result, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpRxArbiter_SetStackChannel_Input_par2buf(UInt8Buffer* pDest , UInt8 channel , gpRxArbiter_StackId_t stackId , UInt16* pIndex)
{
    UInt8_api2buf_1(pDest, &(channel), pIndex);
    gpRxArbiter_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpRxArbiter_SetStackChannel_Output_buf2par(gpRxArbiter_Result_t* result , UInt8 channel , gpRxArbiter_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpRxArbiter_Result_t_buf2api(result, pSource, 1, pIndex);
    NOT_USED(channel);
    NOT_USED(stackId);
}

void gpRxArbiter_GetStackChannel_Input_par2buf(UInt8Buffer* pDest , gpRxArbiter_StackId_t stackId , UInt16* pIndex)
{
    gpRxArbiter_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpRxArbiter_GetStackChannel_Output_buf2par(UInt8* channel , gpRxArbiter_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    UInt8_buf2api(channel, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpRxArbiter_GetCurrentRxOnState_Output_buf2par(Bool* rxon , UInt8Buffer* pSource , UInt16* pIndex)
{
    Bool_buf2api(rxon, pSource, 1, pIndex);
}

void gpRxArbiter_GetCurrentRxChannel_Output_buf2par(UInt8* currentChannel , UInt8Buffer* pSource , UInt16* pIndex)
{
    UInt8_buf2api(currentChannel, pSource, 1, pIndex);
}

void gpRxArbiter_SetStackRxOn_Input_par2buf(UInt8Buffer* pDest , Bool enable , gpRxArbiter_StackId_t stackId , UInt16* pIndex)
{
    Bool_api2buf_1(pDest, &(enable), pIndex);
    gpRxArbiter_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpRxArbiter_SetStackRxOn_Output_buf2par(gpRxArbiter_Result_t* result , Bool enable , gpRxArbiter_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpRxArbiter_Result_t_buf2api(result, pSource, 1, pIndex);
    NOT_USED(enable);
    NOT_USED(stackId);
}

void gpRxArbiter_GetStackRxOn_Input_par2buf(UInt8Buffer* pDest , gpRxArbiter_StackId_t stackId , UInt16* pIndex)
{
    gpRxArbiter_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpRxArbiter_GetStackRxOn_Output_buf2par(Bool* enable , gpRxArbiter_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    Bool_buf2api(enable, pSource, 1, pIndex);
    NOT_USED(stackId);
}





void gpRxArbiter_GetDutyCycleEnabled_Input_par2buf(UInt8Buffer* pDest , gpRxArbiter_StackId_t stackId , UInt16* pIndex)
{
    gpRxArbiter_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpRxArbiter_GetDutyCycleEnabled_Output_buf2par(Bool* result , gpRxArbiter_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    Bool_buf2api(result, pSource, 1, pIndex);
    NOT_USED(stackId);
}

#if (GP_RX_ARBITER_NUMBER_OF_STACKS > 1)
void gpRxArbiter_SetStackPriority_Input_par2buf(UInt8Buffer* pDest , UInt8 priority , gpRxArbiter_StackId_t stackId , UInt16* pIndex)
{
    UInt8_api2buf_1(pDest, &(priority), pIndex);
    gpRxArbiter_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}
#endif /* (GP_RX_ARBITER_NUMBER_OF_STACKS > 1) */

#if (GP_RX_ARBITER_NUMBER_OF_STACKS > 1)
void gpRxArbiter_SetStackPriority_Output_buf2par(gpRxArbiter_Result_t* result , UInt8 priority , gpRxArbiter_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpRxArbiter_Result_t_buf2api(result, pSource, 1, pIndex);
    NOT_USED(priority);
    NOT_USED(stackId);
}
#endif /* (GP_RX_ARBITER_NUMBER_OF_STACKS > 1) */

void gpRxArbiter_IsAnActiveChannel_Input_par2buf(UInt8Buffer* pDest , gpRxArbiter_StackId_t stackId , UInt8 channel , UInt16* pIndex)
{
    gpRxArbiter_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
    UInt8_api2buf_1(pDest, &(channel), pIndex);
}

void gpRxArbiter_IsAnActiveChannel_Output_buf2par(Bool* result , gpRxArbiter_StackId_t stackId , UInt8 channel , UInt8Buffer* pSource , UInt16* pIndex)
{
    Bool_buf2api(result, pSource, 1, pIndex);
    NOT_USED(stackId);
    NOT_USED(channel);
}





gpMarshall_AckStatus_t gpRxArbiter_cbSetFaModeNotification_Input_buf2api(gpRxArbiter_cbSetFaModeNotification_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpRxArbiter_StackId_t_buf2api(&(pDest->data.stackId), pSource, 1, pIndex);
    gpRxArbiter_FaMode_t_buf2api(&(pDest->data.mode), pSource, 1, pIndex);
    return gpMarshall_AckStatusSuccess;
}

gpMarshall_AckStatus_t gpRxArbiter_cbChannelUpdateNotification_Input_buf2api(gpRxArbiter_cbChannelUpdateNotification_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpRxArbiter_StackId_t_buf2api(&(pDest->data.stackId), pSource, 1, pIndex);
    UInt8_buf2api(&(pDest->data.channel), pSource, 1, pIndex);
    return gpMarshall_AckStatusSuccess;
}

