/*
 * Copyright (c) 2015-2016, GreenPeak Technologies
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
 * $Header: //depot/release/Embedded/Components/Qorvo/OS/v2.10.3.1/comps/gpVersion/src/gen/gpVersion_marshalling_client.c#1 $
 * $Change: 197210 $
 * $DateTime: 2022/10/13 16:52:00 $
 */

/** @file "gpVersion_marshalling_client.c"
 *
 *  GPVERSION
 *
 *  Marshalling structures and functions
*/

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

// General includes
#include "gpVersion.h"
#include "gpVersion_marshalling.h"

#include "gpLog.h"
#include "gpAssert.h"

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/
#define GP_COMPONENT_ID GP_COMPONENT_ID_VERSION

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

void Version_ExchangeGlobalVersion_Input_par2buf(UInt8Buffer* pDest , gpVersion_ReleaseInfo_t clientInfo , UInt16* pIndex)
{
    gpVersion_ReleaseInfo_t_api2buf(pDest, &(clientInfo), 1, pIndex);
}

void Version_ExchangeGlobalVersion_Output_buf2par(gpVersion_VersionStatusResult_t* result , gpVersion_ReleaseInfo_t clientInfo , gpVersion_ReleaseInfo_t* serverInfo , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpVersion_VersionStatusResult_t_buf2api(result, pSource, 1, pIndex);
    NOT_USED(clientInfo);
    // no NULL byte check for output buffers if (0x0 == pSource[(*pIndex)++]) // Check null byte
    {
        gpMarshall_AckStatus_t marshall_result = gpVersion_ReleaseInfo_t_buf2api(serverInfo , pSource , 1 , pIndex);
        GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == marshall_result);
    }
}

void Version_NegotiateModuleVersion_Input_par2buf(UInt8Buffer* pDest , UInt8 moduleId , UInt8 nrOfClientVersions , gpVersion_ReleaseInfo_t* pClientVersions , UInt16* pIndex)
{
    UInt8_api2buf_1(pDest, &(moduleId), pIndex);
    UInt8_api2buf_1(pDest, &(nrOfClientVersions), pIndex);
    pDest[(*pIndex)++] = (NULL == pClientVersions);
    if (NULL != pClientVersions)
    {
        gpVersion_ReleaseInfo_t_api2buf(pDest, pClientVersions, nrOfClientVersions, pIndex);
    }
}

void Version_NegotiateModuleVersion_Output_buf2par(gpVersion_VersionStatusResult_t* result , UInt8 moduleId , UInt8 nrOfClientVersions , gpVersion_ReleaseInfo_t* pClientVersions , gpVersion_ReleaseInfo_t* serverInfo , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpVersion_VersionStatusResult_t_buf2api(result, pSource, 1, pIndex);
    NOT_USED(moduleId);
    NOT_USED(nrOfClientVersions);
    NOT_USED(pClientVersions);
    // no NULL byte check for output buffers if (0x0 == pSource[(*pIndex)++]) // Check null byte
    {
        gpMarshall_AckStatus_t marshall_result = gpVersion_ReleaseInfo_t_buf2api(serverInfo , pSource , 1 , pIndex);
        GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == marshall_result);
    }
}

