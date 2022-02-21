/*
 * Copyright (c) 2017, Qorvo Inc
 *
 *   This file contains the implementation of the ComIoctlInterface API protocol.
 *
 *
 *   Marshalling structures and functions
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
 * $Header: //depot/release/Embedded/Components/Qorvo/BaseUtils/v2.10.2.0/comps/gpCom/src/gen/ComIoctlInterface_marshalling_server.c#1 $
 * $Change: 187624 $
 * $DateTime: 2021/12/20 10:58:50 $
 *
 */


/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

// General includes
#include "ComIoctlInterface.h"
#include "ComIoctlInterface_marshalling.h"

#include "gpLog.h"

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/
#define GP_COMPONENT_ID GP_COMPONENT_ID_COMIOCTLINTERFACE

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

gpMarshall_AckStatus_t writeMsg_Input_buf2api( writeMsg_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex )
{
    UInt8_buf2api(&(pDest->data.moduleID), pSource, 1, pIndex);
    UInt32_buf2api(&(pDest->data.commId), pSource, 1, pIndex);
    UInt16_buf2api(&(pDest->data.length), pSource, 1, pIndex);
    if (pSource[(*pIndex)++] == 0x0)  // Check IsNull byte
    {
        pDest->data.pIoctlPayload = pDest->pIoctlPayload;
        UInt8_buf2api( pDest->data.pIoctlPayload, pSource, pDest->data.length, pIndex );
    }
    else
    {
        pDest->data.pIoctlPayload = NULL;
    }
    return gpMarshall_AckStatusSuccess;
}


gpMarshall_AckStatus_t readMsg_Input_buf2api( readMsg_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex )
{
    UInt16_buf2api(&(pDest->data.maxLength), pSource, 1, pIndex);
    return gpMarshall_AckStatusSuccess;
}

void readMsg_Output_api2buf( UInt8Buffer* pDest , readMsg_Output_marshall_struct_t* pSourceoutput , readMsg_Input_marshall_struct_t* pSourceinput , UInt16* pIndex )
{
    pDest[(*pIndex)++] = (pSourceoutput->data.moduleID == NULL); // Add IsNull byte for output pointer
    if (pSourceoutput->data.moduleID != NULL)
    {
        UInt8_api2buf(pDest, pSourceoutput->data.moduleID,1,  pIndex);
    }
    pDest[(*pIndex)++] = (pSourceoutput->data.commId == NULL); // Add IsNull byte for output pointer
    if (pSourceoutput->data.commId != NULL)
    {
        UInt32_api2buf(pDest, pSourceoutput->data.commId,1,  pIndex);
    }
    pDest[(*pIndex)++] = (pSourceoutput->data.length == NULL); // Add IsNull byte for output pointer
    if (pSourceoutput->data.length != NULL)
    {
        UInt16_api2buf(pDest, pSourceoutput->data.length,1,  pIndex);
    }
    pDest[(*pIndex)++] = (pSourceoutput->data.pIoctlPayload == NULL); // Add IsNull byte for output pointer
    if (pSourceoutput->data.pIoctlPayload != NULL)
    {
        UInt8_api2buf(pDest, pSourceoutput->data.pIoctlPayload,(*pSourceoutput->data.length),  pIndex);
    }
}



