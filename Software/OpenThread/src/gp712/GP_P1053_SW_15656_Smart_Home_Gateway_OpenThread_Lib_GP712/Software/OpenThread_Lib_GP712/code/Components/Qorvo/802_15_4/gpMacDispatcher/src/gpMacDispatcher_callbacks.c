/*
 * Copyright (c) 2013-2014, 2016, GreenPeak Technologies
 * Copyright (c) 2017-2019, Qorvo Inc
 *
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
 * Alternatively, this software may be distributed under the terms of the
 * modified BSD License or the 3-clause BSD License as published by the Free
 * Software Foundation @ https://directory.fsf.org/wiki/License:BSD-3-Clause
 *
 * $Header: //depot/main/Embedded/Components/Qorvo/802_15_4/v2.10.3.1/comps/gpMacDispatcher/src/gpMacDispatcher_callbacks.c#1 $
 * $Change: 195340 $
 * $DateTime: 2022/06/17 14:57:48 $
 *
 */

/*****************************************************************************
 *                    Static Function Definitions
 *****************************************************************************/

//
// Functions for invocation of MacDispatcher callbacks
//
// This file is included in gpMacDispatcher.c               (normal stack or server side)
//                   and in gpMacDispatcher_clientWrapper.c (client side)
//                   and in utTbc_gpMacDispatcher.c         (unit test)
//
// These functions forward the callback event via the public callback registration API.
//

static void MacDispatcher_cbDataIndication(const gpMacCore_AddressInfo_t* pSrcAddrInfo, const gpMacCore_AddressInfo_t* pDstAddrInfo, UInt8 dsn,
                                           gpMacCore_Security_t *pSecOptions, gpPd_Loh_t pdLoh, gpMacDispatcher_StackId_t stackId)
{
    gpMacDispatcher_Callbacks_t* pCallbacks;

    GP_LOG_PRINTF("%s called stack %u", 0, __FUNCTION__, stackId);

    pCallbacks = MacDispatcher_GetCallbacks(stackId);
    if(pCallbacks != NULL && pCallbacks->dataIndicationCallback)
    {
        pCallbacks->dataIndicationCallback(pSrcAddrInfo, pDstAddrInfo, dsn, pSecOptions, pdLoh, stackId);
    }
    else
    {
        // Callback is responsible for freeing pdHandle.
        GP_LOG_PRINTF("WARNING: MacDispatcher_cbDataIndication has no handler registered", 0);
        gpPd_FreePd(pdLoh.handle);
    }
}

static void MacDispatcher_cbDataConfirm(gpMacCore_Result_t status, UInt8 pdHandle, gpMacDispatcher_StackId_t stackId)
{
    gpMacDispatcher_Callbacks_t* pCallbacks;

    GP_LOG_PRINTF("%s called stack %u", 0, __FUNCTION__, stackId);

    // get data related callback.
    pCallbacks = MacDispatcher_GetCallbacks(stackId);
    if(pCallbacks != NULL && pCallbacks->dataConfirmCallback)
    {
        pCallbacks->dataConfirmCallback(status, pdHandle, stackId);
    }
    else
    {
        // Callback is responsible for freeing pdHandle.
        if (pdHandle != GP_PD_INVALID_HANDLE)
        {
            gpPd_FreePd(pdHandle);
        }
    }
}
static void MacDispatcher_cbPollIndication(gpMacCore_AddressInfo_t* pAddrInfo, gpPd_TimeStamp_t rxTime, gpMacDispatcher_StackId_t stackId)
{
    gpMacDispatcher_Callbacks_t* pCallbacks;

    GP_LOG_PRINTF("%s called stack %u", 0, __FUNCTION__, stackId);

    pCallbacks = MacDispatcher_GetCallbacks(stackId);
    if(pCallbacks != NULL && pCallbacks->pollIndicationCallback)
    {
        pCallbacks->pollIndicationCallback(pAddrInfo, rxTime, stackId);
    }
}

static void MacDispatcher_cbPollNotify(gpMacCore_AddressInfo_t* pAddrInfo, gpPd_TimeStamp_t rxTime, gpPd_Handle_t pdHandle, Bool fromNeighbour, gpMacDispatcher_StackId_t stackId)
{
    gpMacDispatcher_Callbacks_t* pCallbacks;

    GP_LOG_PRINTF("%s called stack %u", 0, __FUNCTION__, stackId);

    pCallbacks = MacDispatcher_GetCallbacks(stackId);
    if(pCallbacks != NULL && pCallbacks->pollNotifyCallback)
    {
        pCallbacks->pollNotifyCallback(pAddrInfo, rxTime, pdHandle, fromNeighbour, stackId);
    }
}
static void MacDispatcher_cbPollConfirm(gpMacCore_Result_t status, gpMacCore_AddressInfo_t* pCoordAddrInfo, gpPd_TimeStamp_t txTime, gpMacDispatcher_StackId_t stackId)
{
    gpMacDispatcher_Callbacks_t* pCallbacks;

    GP_LOG_PRINTF("%s called stack %u", 0, __FUNCTION__, stackId);

    pCallbacks = MacDispatcher_GetCallbacks(stackId);
    if(pCallbacks != NULL && pCallbacks->pollConfirmCallback)
    {
        pCallbacks->pollConfirmCallback(status, pCoordAddrInfo, txTime, stackId);
    }
}
static void MacDispatcher_cbPurgeConfirm(gpMacCore_Result_t status, gpPd_Handle_t pdHandle, gpMacDispatcher_StackId_t stackId)
{
    gpMacDispatcher_Callbacks_t* pCallbacks;

    GP_LOG_PRINTF("%s called stack %u", 0, __FUNCTION__, stackId);

    pCallbacks = MacDispatcher_GetCallbacks(stackId);
    if(pCallbacks != NULL && pCallbacks->purgeConfirmCallback)
    {
        pCallbacks->purgeConfirmCallback(status, pdHandle, stackId);
    }
    else
    {
        if (status == gpMacCore_ResultSuccess)
        {
            // Callback is responsible for freeing pdHandle after succesful purge.
            GP_ASSERT_DEV_INT(false);
            if (pdHandle != GP_PD_INVALID_HANDLE)
            {
                gpPd_FreePd(pdHandle);
            }
        }
    }
}
static void MacDispatcher_cbBeaconNotifyIndication(UInt8 bsn, gpMacCore_PanDescriptor_t* pPanDescriptor, UInt8 beaconPayloadLength , UInt8 *pBeaconPayload, gpMacDispatcher_StackId_t stackId)
{
    gpMacDispatcher_Callbacks_t* pCallbacks;

    GP_LOG_PRINTF("%s called stack %u", 0, __FUNCTION__, stackId);

    pCallbacks = MacDispatcher_GetCallbacks(stackId);
    if(pCallbacks != NULL && pCallbacks->beaconNotifyIndicationCallback)
    {
        pCallbacks->beaconNotifyIndicationCallback(bsn, pPanDescriptor, beaconPayloadLength , pBeaconPayload, stackId);
    }
}
static void MacDispatcher_cbAssociateIndication(gpMacCore_Address_t* pDeviceAddress, UInt8 capabilityInformation, gpPd_TimeStamp_t rxTime, gpMacDispatcher_StackId_t stackId)
{
    gpMacDispatcher_Callbacks_t* pCallbacks;

    GP_LOG_PRINTF("%s called stack %u", 0, __FUNCTION__, stackId);

    pCallbacks = MacDispatcher_GetCallbacks(stackId);
    if(pCallbacks != NULL && pCallbacks->assocIndicationCallback)
    {
        pCallbacks->assocIndicationCallback(pDeviceAddress, capabilityInformation, rxTime, stackId);
    }
}
static void MacDispatcher_cbAssociateConfirm(UInt16 assocShortAddress, gpMacCore_Result_t status, gpPd_TimeStamp_t txTime, gpMacDispatcher_StackId_t stackId)
{
    gpMacDispatcher_Callbacks_t* pCallbacks;

    GP_LOG_PRINTF("%s called stack %u", 0, __FUNCTION__, stackId);

    pCallbacks = MacDispatcher_GetCallbacks(stackId);
    if(pCallbacks != NULL && pCallbacks->assocConfirmCallback)
    {
        pCallbacks->assocConfirmCallback(assocShortAddress, status, txTime, stackId);
    }
}

static void MacDispatcher_cbScanConfirm(gpMacCore_Result_t status, gpMacCore_ScanType_t scanType, UInt32 unscannedChannels, UInt8 resultListSize, UInt8* pEdScanResultList, gpMacDispatcher_StackId_t stackId)
{
    gpMacDispatcher_Callbacks_t* pCallbacks;

    GP_LOG_PRINTF("%s called stack %u", 0, __FUNCTION__, stackId);

    pCallbacks = MacDispatcher_GetCallbacks(stackId);
    if(pCallbacks != NULL && pCallbacks->scanConfirmCallback)
    {
        pCallbacks->scanConfirmCallback(status, scanType, unscannedChannels, resultListSize, pEdScanResultList, stackId);
    }
}

static void MacDispatcher_cbOrphanIndication(MACAddress_t* pOrphanAddress, gpPd_TimeStamp_t rxTime, gpMacDispatcher_StackId_t stackId)
{
    gpMacDispatcher_Callbacks_t* pCallbacks;

    GP_LOG_PRINTF("%s called stack %u", 0, __FUNCTION__, stackId);

    pCallbacks = MacDispatcher_GetCallbacks(stackId);
    if(pCallbacks != NULL && pCallbacks->orphanIndicationCallback)
    {
        pCallbacks->orphanIndicationCallback(pOrphanAddress, rxTime, stackId);
    }
}

static void MacDispatcher_cbSecurityFailureCommStatusIndication(gpMacCore_AddressInfo_t* pSrcAddrInfo, gpMacCore_AddressInfo_t* pDstAddrInfo, gpMacCore_Result_t status, gpPd_TimeStamp_t txTime, gpMacDispatcher_StackId_t stackId)
{
    gpMacDispatcher_Callbacks_t* pCallbacks;

    GP_LOG_PRINTF("%s called stack %u", 0, __FUNCTION__, stackId);

    pCallbacks = MacDispatcher_GetCallbacks(stackId);
    if(pCallbacks != NULL && pCallbacks->securityFailureCommStatusIndicationCallback)
    {
        pCallbacks->securityFailureCommStatusIndicationCallback(pSrcAddrInfo, pDstAddrInfo, status, txTime, stackId);
    }
}

static void MacDispatcher_cbSecurityFrameCounterIndication(UInt32 frameCounter, gpMacDispatcher_StackId_t stackId)
{
    gpMacDispatcher_Callbacks_t* pCallbacks;

    GP_LOG_PRINTF("%s called stack %u", 0, __FUNCTION__, stackId);

    pCallbacks = MacDispatcher_GetCallbacks(stackId);
    if(pCallbacks != NULL && pCallbacks->securityFrameCounterIndicationCallback)
    {
        pCallbacks->securityFrameCounterIndicationCallback(frameCounter, stackId);
    }
}
static void MacDispatcher_cbAssociateCommStatusIndication(gpMacCore_AddressInfo_t* pSrcAddrInfo, gpMacCore_AddressInfo_t* pDstAddrInfo, gpMacCore_Result_t status, gpPd_TimeStamp_t txTime, gpMacDispatcher_StackId_t stackId)
{
    gpMacDispatcher_Callbacks_t* pCallbacks;

    GP_LOG_PRINTF("%s called stack %u", 0, __FUNCTION__, stackId);

    pCallbacks = MacDispatcher_GetCallbacks(stackId);
    if(pCallbacks != NULL && pCallbacks->associateCommStatusIndicationCallback)
    {
        pCallbacks->associateCommStatusIndicationCallback(pSrcAddrInfo, pDstAddrInfo, status, txTime, stackId);
    }
}
static void MacDispatcher_cbOrphanCommStatusIndication(gpMacCore_AddressInfo_t* pSrcAddrInfo, gpMacCore_AddressInfo_t* pDstAddrInfo, gpMacCore_Result_t status, gpPd_TimeStamp_t txTime, gpMacDispatcher_StackId_t stackId)
{
    gpMacDispatcher_Callbacks_t* pCallbacks;

    GP_LOG_PRINTF("%s called stack %u", 0, __FUNCTION__, stackId);

    pCallbacks = MacDispatcher_GetCallbacks(stackId);
    if(pCallbacks != NULL && pCallbacks->orphanCommStatusIndicationCallback)
    {
        pCallbacks->orphanCommStatusIndicationCallback(pSrcAddrInfo, pDstAddrInfo, status, txTime, stackId);
    }
}
void MacDispatcher_cbDriverResetIndication(gpMacDispatcher_Result_t status, gpMacDispatcher_StackId_t stackId)
{
    gpMacDispatcher_Callbacks_t* pCallbacks;

    GP_LOG_PRINTF("%s called stack %u", 0, __FUNCTION__, stackId);

    pCallbacks = MacDispatcher_GetCallbacks(stackId);
    if(pCallbacks != NULL && pCallbacks->driverResetIndicationCallback)
    {
        if(status == gpMacDispatcher_ResultSecondStackRegistered)
        {
            GP_LOG_SYSTEM_PRINTF("ERROR: Second stack with same ID was registered",0);
        }
        else
        {
            GP_LOG_SYSTEM_PRINTF("Driver reset Ind %u %x",0, stackId, status);
        }
        pCallbacks->driverResetIndicationCallback(status, stackId);
    }
}
