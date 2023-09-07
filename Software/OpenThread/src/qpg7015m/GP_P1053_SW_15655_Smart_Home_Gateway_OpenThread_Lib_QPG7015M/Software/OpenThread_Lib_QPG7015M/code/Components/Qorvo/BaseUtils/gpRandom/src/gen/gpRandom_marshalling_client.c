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
 * $Header$
 * $Change$
 * $DateTime$
 */

/** @file "gpRandom_marshalling_client.c"
 *
 *  Random generator component
 *
 *  Marshalling structures and functions
*/

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

// General includes
#include "gpRandom.h"
#include "gpRandom_marshalling.h"

#include "gpLog.h"
#include "gpAssert.h"

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/
#define GP_COMPONENT_ID GP_COMPONENT_ID_RANDOM

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

void gpRandom_GetNewSequence_Input_par2buf(UInt8Buffer* pDest , UInt8 nmbrRandomBytes , UInt16* pIndex)
{
    UInt8_api2buf_1(pDest, &(nmbrRandomBytes), pIndex);
}

void gpRandom_GetNewSequence_Output_buf2par(UInt8 nmbrRandomBytes , UInt8* pBuffer , UInt8Buffer* pSource , UInt16* pIndex)
{
    NOT_USED(nmbrRandomBytes);
    if (0x0 == pSource[(*pIndex)++]) // Check null byte
    {
        UInt8_buf2api(pBuffer, pSource, nmbrRandomBytes, pIndex);
    }
}





void gpRandom_GetFromDRBG_Input_par2buf(UInt8Buffer* pDest , UInt8 nmbrRandomBytes , UInt16* pIndex)
{
    UInt8_api2buf_1(pDest, &(nmbrRandomBytes), pIndex);
}

void gpRandom_GetFromDRBG_Output_buf2par(UInt8 nmbrRandomBytes , UInt8* pBuffer , UInt8Buffer* pSource , UInt16* pIndex)
{
    NOT_USED(nmbrRandomBytes);
    if (0x0 == pSource[(*pIndex)++]) // Check null byte
    {
        UInt8_buf2api(pBuffer, pSource, nmbrRandomBytes, pIndex);
    }
}

