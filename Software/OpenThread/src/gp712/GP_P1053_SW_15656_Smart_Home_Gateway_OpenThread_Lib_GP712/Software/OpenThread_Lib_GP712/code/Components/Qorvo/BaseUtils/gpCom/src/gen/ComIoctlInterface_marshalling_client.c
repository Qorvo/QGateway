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
 * $Header$
 * $Change$
 * $DateTime$
 *
 */


/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

// General includes
#include "ComIoctlInterface.h"
#include "ComIoctlInterface_marshalling.h"

#include "gpLog.h"
#include "gpAssert.h"

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

void writeMsg_Input_par2buf( UInt8Buffer* pDest , UInt8 moduleID , UInt32 commId , UInt16 length , UInt8* pIoctlPayload , UInt16* pIndex )
{
    UInt8_api2buf(pDest, &(moduleID), 1, pIndex);
    UInt32_api2buf(pDest, &(commId), 1, pIndex);
    UInt16_api2buf(pDest, &(length), 1, pIndex);
    pDest[(*pIndex)++] = (NULL == pIoctlPayload);
    if (NULL != pIoctlPayload)
    {
        UInt8_api2buf(pDest, pIoctlPayload, length, pIndex);
    }
}

void readMsg_Input_par2buf( UInt8Buffer* pDest , UInt16 maxLength , UInt16* pIndex )
{
    UInt16_api2buf(pDest, &(maxLength), 1, pIndex);
}

void readMsg_Output_buf2par( UInt16 maxLength , UInt8* moduleID , UInt32* commId , UInt16* length , UInt8* pIoctlPayload , UInt8Buffer* pSource , UInt16* pIndex )
{
    NOT_USED(maxLength);
    if (0x0 == pSource[(*pIndex)++]) // Check null byte
    {
        UInt8_buf2api( moduleID, pSource, 1, pIndex);
    }
    if (0x0 == pSource[(*pIndex)++]) // Check null byte
    {
        UInt32_buf2api( commId, pSource, 1, pIndex);
    }
    if (0x0 == pSource[(*pIndex)++]) // Check null byte
    {
        UInt16_buf2api( length, pSource, 1, pIndex);
    }
    if (0x0 == pSource[(*pIndex)++]) // Check null byte
    {
        UInt8_buf2api( pIoctlPayload, pSource, (*length), pIndex);
    }
}




