/*
 * Copyright (c) 2016, GreenPeak Technologies
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
 * $Header: //depot/main/Embedded/Components/Qorvo/802_15_4/v2.10.3.1/comps/gpMacDispatcher/src/gen/gpMacDispatcher_marshalling.c#1 $
 * $Change: 195340 $
 * $DateTime: 2022/06/17 14:57:48 $
 */

/** @file "gpMacDispatcher_marshalling.c"
 *
 *  MAC Dispatcher
 *
 *   Marshalling structures and functions.
*/

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

// General includes
#include "gpMacDispatcher.h"
#include "gpMacDispatcher_marshalling.h"

#ifdef GP_DIVERSITY_LOG
#include "gpLog.h"
#endif

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/
#define GP_COMPONENT_ID GP_COMPONENT_ID_MACDISPATCHER

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

gpMarshall_AckStatus_t gpMacDispatcher_StringIdentifier_t_buf2api(gpMacDispatcher_StringIdentifier_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex )
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        UInt8_buf2api((pDest->str), pSource, 5, pIndex);
        pDest++;
    }
    return gpMarshall_AckStatusSuccess;
}

void gpMacDispatcher_StringIdentifier_t_api2buf(UInt8Buffer* pDest , const gpMacDispatcher_StringIdentifier_t* pSource , UInt16 length , UInt16* pIndex)
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        UInt8_api2buf(pDest , (pSource->str), 5, pIndex);
        pSource++;
    }
}

gpMarshall_AckStatus_t gpMacDispatcher_Callbacks_t_buf2api(gpMacDispatcher_Callbacks_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex )
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        gpMacDispatcher_cbDataIndication_t_buf2api_1(&(pDest->dataIndicationCallback), pSource, pIndex);
        gpMacDispatcher_cbDataConfirm_t_buf2api_1(&(pDest->dataConfirmCallback), pSource, pIndex);
        gpMacDispatcher_cbPollIndication_t_buf2api_1(&(pDest->pollIndicationCallback), pSource, pIndex);
        gpMacDispatcher_cbPollConfirm_t_buf2api_1(&(pDest->pollConfirmCallback), pSource, pIndex);
        gpMacDispatcher_cbPurgeConfirm_t_buf2api_1(&(pDest->purgeConfirmCallback), pSource, pIndex);
        gpMacDispatcher_cbBeaconNotifyIndication_t_buf2api_1(&(pDest->beaconNotifyIndicationCallback), pSource, pIndex);
        gpMacDispatcher_cbScanConfirm_t_buf2api_1(&(pDest->scanConfirmCallback), pSource, pIndex);
        gpMacDispatcher_cbAssociateIndication_t_buf2api_1(&(pDest->assocIndicationCallback), pSource, pIndex);
        gpMacDispatcher_cbAssocConfirm_t_buf2api_1(&(pDest->assocConfirmCallback), pSource, pIndex);
        gpMacDispatcher_cbOrphanIndication_t_buf2api_1(&(pDest->orphanIndicationCallback), pSource, pIndex);
        gpMacDispatcher_cbSecurityFailureCommStatusIndication_t_buf2api_1(&(pDest->securityFailureCommStatusIndicationCallback), pSource, pIndex);
        gpMacDispatcher_cbAssociateCommStatusIndication_t_buf2api_1(&(pDest->associateCommStatusIndicationCallback), pSource, pIndex);
        gpMacDispatcher_cbOrphanCommStatusIndication_t_buf2api_1(&(pDest->orphanCommStatusIndicationCallback), pSource, pIndex);
        gpMacDispatcher_cbDriverResetIndication_t_buf2api_1(&(pDest->driverResetIndicationCallback), pSource, pIndex);
        gpMacDispatcher_cbPollNotify_t_buf2api_1(&(pDest->pollNotifyCallback), pSource, pIndex);
        pDest++;
    }
    return gpMarshall_AckStatusSuccess;
}

void gpMacDispatcher_Callbacks_t_api2buf(UInt8Buffer* pDest , const gpMacDispatcher_Callbacks_t* pSource , UInt16 length , UInt16* pIndex)
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        gpMacDispatcher_cbDataIndication_t_api2buf_1(pDest , &(pSource->dataIndicationCallback), pIndex);
        gpMacDispatcher_cbDataConfirm_t_api2buf_1(pDest , &(pSource->dataConfirmCallback), pIndex);
        gpMacDispatcher_cbPollIndication_t_api2buf_1(pDest , &(pSource->pollIndicationCallback), pIndex);
        gpMacDispatcher_cbPollConfirm_t_api2buf_1(pDest , &(pSource->pollConfirmCallback), pIndex);
        gpMacDispatcher_cbPurgeConfirm_t_api2buf_1(pDest , &(pSource->purgeConfirmCallback), pIndex);
        gpMacDispatcher_cbBeaconNotifyIndication_t_api2buf_1(pDest , &(pSource->beaconNotifyIndicationCallback), pIndex);
        gpMacDispatcher_cbScanConfirm_t_api2buf_1(pDest , &(pSource->scanConfirmCallback), pIndex);
        gpMacDispatcher_cbAssociateIndication_t_api2buf_1(pDest , &(pSource->assocIndicationCallback), pIndex);
        gpMacDispatcher_cbAssocConfirm_t_api2buf_1(pDest , &(pSource->assocConfirmCallback), pIndex);
        gpMacDispatcher_cbOrphanIndication_t_api2buf_1(pDest , &(pSource->orphanIndicationCallback), pIndex);
        gpMacDispatcher_cbSecurityFailureCommStatusIndication_t_api2buf_1(pDest , &(pSource->securityFailureCommStatusIndicationCallback), pIndex);
        gpMacDispatcher_cbAssociateCommStatusIndication_t_api2buf_1(pDest , &(pSource->associateCommStatusIndicationCallback), pIndex);
        gpMacDispatcher_cbOrphanCommStatusIndication_t_api2buf_1(pDest , &(pSource->orphanCommStatusIndicationCallback), pIndex);
        gpMacDispatcher_cbDriverResetIndication_t_api2buf_1(pDest , &(pSource->driverResetIndicationCallback), pIndex);
        gpMacDispatcher_cbPollNotify_t_api2buf_1(pDest , &(pSource->pollNotifyCallback), pIndex);
        pSource++;
    }
}


void gpMacDispatcher_InitMarshalling(void)
{
}



