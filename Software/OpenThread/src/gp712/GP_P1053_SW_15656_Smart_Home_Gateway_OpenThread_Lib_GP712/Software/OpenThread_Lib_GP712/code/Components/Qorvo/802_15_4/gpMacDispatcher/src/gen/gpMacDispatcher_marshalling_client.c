/*
 * Copyright (c) 2016, GreenPeak Technologies
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
 * $Header: //depot/release/Embedded/Components/Qorvo/802_15_4/v2.10.2.0/comps/gpMacDispatcher/src/gen/gpMacDispatcher_marshalling_client.c#1 $
 * $Change: 187624 $
 * $DateTime: 2021/12/20 10:58:50 $
 */

/** @file "gpMacDispatcher_marshalling_client.c"
 *
 *  MAC Dispatcher
 *
 *  Marshalling structures and functions
*/

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

// General includes
#include "gpMacDispatcher.h"
#include "gpMacDispatcher_marshalling.h"

#include "gpLog.h"
#include "gpAssert.h"
#include "gpPd.h"

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

void gpMacDispatcher_RegisterNetworkStack_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StringIdentifier_t* stringIdentifier , UInt16* pIndex)
{
    pDest[(*pIndex)++] = (NULL == stringIdentifier);
    if (NULL != stringIdentifier)
    {
        gpMacDispatcher_StringIdentifier_t_api2buf(pDest, stringIdentifier, 1, pIndex);
    }
    else
    {
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            MEMSET(&(pDest[(*pIndex)]) , 0x00 , (5));
            (*pIndex) += (5);
        }
    }
}

void gpMacDispatcher_RegisterNetworkStack_Output_buf2par(gpMacDispatcher_StackId_t* stackId , gpMacDispatcher_StringIdentifier_t* stringIdentifier , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_buf2api(stackId, pSource, 1, pIndex);
    NOT_USED(stringIdentifier);
}

void gpMacDispatcher_UnRegisterNetworkStack_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_UnRegisterNetworkStack_Output_buf2par(gpMacCore_Result_t* result , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacCore_Result_t_buf2api(result, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_LockClaim_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_LockClaim_Output_buf2par(Bool* result , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    Bool_buf2api(result, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_LockRelease_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_LockedByThisStack_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_LockedByThisStack_Output_buf2par(Bool* locked , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    Bool_buf2api(locked, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_Locked_Output_buf2par(Bool* locked , UInt8Buffer* pSource , UInt16* pIndex)
{
    Bool_buf2api(locked, pSource, 1, pIndex);
}

void gpMacDispatcher_Reset_Input_par2buf(UInt8Buffer* pDest , Bool setDefaultPib , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    Bool_api2buf_1(pDest, &(setDefaultPib), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_Reset_Output_buf2par(gpMacDispatcher_Result_t* result , Bool setDefaultPib , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacDispatcher_Result_t_buf2api(result, pSource, 1, pIndex);
    NOT_USED(setDefaultPib);
    NOT_USED(stackId);
}

void gpMacDispatcher_DataRequest_Input_par2buf(UInt8Buffer* pDest , gpMacCore_AddressMode_t srcAddrMode , gpMacCore_AddressInfo_t* pDstAddressInfo , UInt8 txOptions , gpMacCore_Security_t* pSecOptions , gpMacCore_MultiChannelOptions_t multiChannelOptions , gpPd_Loh_t pdLoh , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacCore_AddressMode_t_api2buf_1(pDest, &(srcAddrMode), pIndex);
    pDest[(*pIndex)++] = (NULL == pDstAddressInfo);
    if (NULL != pDstAddressInfo)
    {
        gpMacCore_AddressInfo_t_api2buf(pDest, pDstAddressInfo, 1, pIndex);
    }
    else
    {
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            MEMSET(&(pDest[(*pIndex)]) , 0x00 , (max(2*1,8*1) + 2*1 + 1));
            (*pIndex) += (max(2*1,8*1) + 2*1 + 1);
        }
    }
    UInt8_api2buf_1(pDest, &(txOptions), pIndex);
    pDest[(*pIndex)++] = (NULL == pSecOptions);
    if (NULL != pSecOptions)
    {
        gpMacCore_Security_t_api2buf(pDest, pSecOptions, 1, pIndex);
    }
    else
    {
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            MEMSET(&(pDest[(*pIndex)]) , 0x00 , (1 + 1 + max(4,8) + 1));
            (*pIndex) += (1 + 1 + max(4,8) + 1);
        }
    }
    gpMacCore_MultiChannelOptions_t_api2buf(pDest, &(multiChannelOptions), 1, pIndex);
    gpPd_Loh_t_api2buf(pDest, &(pdLoh), 1, pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_ScanRequest_Input_par2buf(UInt8Buffer* pDest , gpMacCore_ScanType_t scanType , UInt32 scanChannels , UInt8 scanDuration , UInt8 resultListSize , UInt8* pResultList , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacCore_ScanType_t_api2buf_1(pDest, &(scanType), pIndex);
    UInt32_api2buf_1(pDest, &(scanChannels), pIndex);
    UInt8_api2buf_1(pDest, &(scanDuration), pIndex);
    UInt8_api2buf_1(pDest, &(resultListSize), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_AssociateRequest_Input_par2buf(UInt8Buffer* pDest , UInt8 logicalChannel , gpMacCore_AddressInfo_t* coordAddrInfo , UInt8 capabilityInformation , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    UInt8_api2buf_1(pDest, &(logicalChannel), pIndex);
    pDest[(*pIndex)++] = (NULL == coordAddrInfo);
    if (NULL != coordAddrInfo)
    {
        gpMacCore_AddressInfo_t_api2buf(pDest, coordAddrInfo, 1, pIndex);
    }
    else
    {
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            MEMSET(&(pDest[(*pIndex)]) , 0x00 , (max(2*1,8*1) + 2*1 + 1));
            (*pIndex) += (max(2*1,8*1) + 2*1 + 1);
        }
    }
    UInt8_api2buf_1(pDest, &(capabilityInformation), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_AssociateResponse_Input_par2buf(UInt8Buffer* pDest , MACAddress_t* pDeviceAddress , UInt16 associateShortAddress , gpMacCore_Result_t status , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    pDest[(*pIndex)++] = (NULL == pDeviceAddress);
    if (NULL != pDeviceAddress)
    {
        MACAddress_t_api2buf_1(pDest, pDeviceAddress, pIndex);
    }
    else
    {
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            MEMSET(&(pDest[(*pIndex)]) , 0x00 , 8*1);
            (*pIndex) += 8*1;
        }
    }
    UInt16_api2buf_1(pDest, &(associateShortAddress), pIndex);
    gpMacCore_Result_t_api2buf_1(pDest, &(status), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_PollRequest_Input_par2buf(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* coordAddrInfo , gpMacCore_Security_t* pSecOptions , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    pDest[(*pIndex)++] = (NULL == coordAddrInfo);
    if (NULL != coordAddrInfo)
    {
        gpMacCore_AddressInfo_t_api2buf(pDest, coordAddrInfo, 1, pIndex);
    }
    else
    {
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            MEMSET(&(pDest[(*pIndex)]) , 0x00 , (max(2*1,8*1) + 2*1 + 1));
            (*pIndex) += (max(2*1,8*1) + 2*1 + 1);
        }
    }
/* <CodeGenerator Placeholder> SpecialInputpar2bufParameterHandling_gpMacDispatcher_PollRequest_pSecOptions */
    pDest[(*pIndex)++] = (NULL == pSecOptions);

    if (NULL != pSecOptions)
    {
        gpMacCore_Security_t_api2buf(pDest, pSecOptions, 1, pIndex);
    }
    else
    {
        gpMacCore_Security_t dummy = {0};
        gpMacCore_Security_t_api2buf(pDest, &dummy, 1, pIndex);
    }
/* </CodeGenerator Placeholder> SpecialInputpar2bufParameterHandling_gpMacDispatcher_PollRequest_pSecOptions */
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_PurgeRequest_Input_par2buf(UInt8Buffer* pDest , gpPd_Handle_t pdHandle , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    pDest[(*pIndex)++] = gpPd_GetUtPd(pdHandle);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_Start_Input_par2buf(UInt8Buffer* pDest , gpMacCore_PanId_t panId , UInt8 logicalChannel , Bool panCoordinator , UInt8 stackId , UInt16* pIndex)
{
    gpMacCore_PanId_t_api2buf_1(pDest, &(panId), pIndex);
    UInt8_api2buf_1(pDest, &(logicalChannel), pIndex);
    Bool_api2buf_1(pDest, &(panCoordinator), pIndex);
    UInt8_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_Start_Output_buf2par(gpMacCore_Result_t* returnValue , gpMacCore_PanId_t panId , UInt8 logicalChannel , Bool panCoordinator , UInt8 stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacCore_Result_t_buf2api(returnValue, pSource, 1, pIndex);
    NOT_USED(panId);
    NOT_USED(logicalChannel);
    NOT_USED(panCoordinator);
    NOT_USED(stackId);
}

void gpMacDispatcher_OrphanResponse_Input_par2buf(UInt8Buffer* pDest , MACAddress_t* pOrphanAddress , UInt16 shortAddress , Bool associatedMember , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    pDest[(*pIndex)++] = (NULL == pOrphanAddress);
    if (NULL != pOrphanAddress)
    {
        MACAddress_t_api2buf_1(pDest, pOrphanAddress, pIndex);
    }
    else
    {
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            MEMSET(&(pDest[(*pIndex)]) , 0x00 , 8*1);
            (*pIndex) += 8*1;
        }
    }
    UInt16_api2buf_1(pDest, &(shortAddress), pIndex);
    Bool_api2buf_1(pDest, &(associatedMember), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_SetPanId_Input_par2buf(UInt8Buffer* pDest , UInt16 panId , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    UInt16_api2buf_1(pDest, &(panId), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetPanId_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetPanId_Output_buf2par(gpMacCore_PanId_t* panId , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacCore_PanId_t_buf2api(panId, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetShortAddress_Input_par2buf(UInt8Buffer* pDest , UInt16 shortAddress , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    UInt16_api2buf_1(pDest, &(shortAddress), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetShortAddress_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetShortAddress_Output_buf2par(UInt16* address , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    UInt16_buf2api(address, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetExtendedAddress_Input_par2buf(UInt8Buffer* pDest , MACAddress_t* pExtendedAddress , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    pDest[(*pIndex)++] = (NULL == pExtendedAddress);
    if (NULL != pExtendedAddress)
    {
        MACAddress_t_api2buf_1(pDest, pExtendedAddress, pIndex);
    }
    else
    {
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            MEMSET(&(pDest[(*pIndex)]) , 0x00 , 8*1);
            (*pIndex) += 8*1;
        }
    }
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetExtendedAddress_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetExtendedAddress_Output_buf2par(MACAddress_t* pExtendedAddress , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    if (0x0 == pSource[(*pIndex)++]) // Check null byte
    {
        MACAddress_t_buf2api(pExtendedAddress, pSource, 1, pIndex);
    }
    NOT_USED(stackId);
}

void gpMacDispatcher_SetDsn_Input_par2buf(UInt8Buffer* pDest , UInt8 dsn , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    UInt8_api2buf_1(pDest, &(dsn), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetDsn_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetDsn_Output_buf2par(UInt8* dsn , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    UInt8_buf2api(dsn, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetCurrentChannel_Input_par2buf(UInt8Buffer* pDest , UInt8 channel , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    UInt8_api2buf_1(pDest, &(channel), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetCurrentChannel_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetCurrentChannel_Output_buf2par(UInt8* channel , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    UInt8_buf2api(channel, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetBeaconPayload_Input_par2buf(UInt8Buffer* pDest , UInt8* pBeaconPayload , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    pDest[(*pIndex)++] = (NULL == pBeaconPayload);
    if (NULL != pBeaconPayload)
    {
        UInt8_api2buf(pDest, pBeaconPayload, GP_MACCORE_MAX_BEACON_PAYLOAD_LENGTH, pIndex);
    }
    else
    {
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            MEMSET(&(pDest[(*pIndex)]) , 0x00 , GP_MACCORE_MAX_BEACON_PAYLOAD_LENGTH);
            (*pIndex) += GP_MACCORE_MAX_BEACON_PAYLOAD_LENGTH;
        }
    }
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetBeaconPayload_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetBeaconPayload_Output_buf2par(UInt8* pBeaconPayload , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
/* <CodeGenerator Placeholder> SpecialOutputbuf2parParameterHandling_gpMacDispatcher_GetBeaconPayload_pBeaconPayload */
    if (0x0 == pSource[(*pIndex)++]) // Check null byte
    {
        // Needs a variable because otherwise gpMacDispatcher_GetBeaconPayloadLength() gets called twice (see definition of UInt8_buf2api())
        UInt8 length = gpMacDispatcher_GetBeaconPayloadLength(stackId);
        UInt8_buf2api( pBeaconPayload, pSource, length, pIndex);
    }
/* </CodeGenerator Placeholder> SpecialOutputbuf2parParameterHandling_gpMacDispatcher_GetBeaconPayload_pBeaconPayload */
    NOT_USED(stackId);
}

void gpMacDispatcher_SetBeaconPayloadLength_Input_par2buf(UInt8Buffer* pDest , UInt8 beaconPayloadLength , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    UInt8_api2buf_1(pDest, &(beaconPayloadLength), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetBeaconPayloadLength_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetBeaconPayloadLength_Output_buf2par(UInt8* beaconPayloadLength , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    UInt8_buf2api(beaconPayloadLength, pSource, 1, pIndex);
    NOT_USED(stackId);
}




void gpMacDispatcher_SetRxOnWhenIdle_Input_par2buf(UInt8Buffer* pDest , Bool rxOnWhenIdle , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    Bool_api2buf_1(pDest, &(rxOnWhenIdle), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetRxOnWhenIdle_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetRxOnWhenIdle_Output_buf2par(Bool* rxOnWhenIdle , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    Bool_buf2api(rxOnWhenIdle, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_GetTransactionPersistenceTime_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetTransactionPersistenceTime_Output_buf2par(UInt16* time , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    UInt16_buf2api(time, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetTransactionPersistenceTime_Input_par2buf(UInt8Buffer* pDest , UInt16 time , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    UInt16_api2buf_1(pDest, &(time), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_SetBeaconStarted_Input_par2buf(UInt8Buffer* pDest , Bool beaconStarted , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    Bool_api2buf_1(pDest, &(beaconStarted), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetBeaconStarted_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetBeaconStarted_Output_buf2par(Bool* beaconStarted , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    Bool_buf2api(beaconStarted, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetCoordShortAddress_Input_par2buf(UInt8Buffer* pDest , UInt16 coordShortAddress , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    UInt16_api2buf_1(pDest, &(coordShortAddress), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetCoordShortAddress_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetCoordShortAddress_Output_buf2par(UInt16* coordShortAddress , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    UInt16_buf2api(coordShortAddress, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetCoordExtendedAddress_Input_par2buf(UInt8Buffer* pDest , MACAddress_t* pCoordExtendedAddress , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    pDest[(*pIndex)++] = (NULL == pCoordExtendedAddress);
    if (NULL != pCoordExtendedAddress)
    {
        MACAddress_t_api2buf_1(pDest, pCoordExtendedAddress, pIndex);
    }
    else
    {
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            MEMSET(&(pDest[(*pIndex)]) , 0x00 , 8*1);
            (*pIndex) += 8*1;
        }
    }
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetCoordExtendedAddress_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetCoordExtendedAddress_Output_buf2par(MACAddress_t* pCoordExtendedAddress , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    if (0x0 == pSource[(*pIndex)++]) // Check null byte
    {
        MACAddress_t_buf2api(pCoordExtendedAddress, pSource, 1, pIndex);
    }
    NOT_USED(stackId);
}

void gpMacDispatcher_SetPromiscuousMode_Input_par2buf(UInt8Buffer* pDest , UInt8 promiscuousMode , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    UInt8_api2buf_1(pDest, &(promiscuousMode), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetPromiscuousMode_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetPromiscuousMode_Output_buf2par(Bool* promiscuousMode , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    Bool_buf2api(promiscuousMode, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetAssociationPermit_Input_par2buf(UInt8Buffer* pDest , Bool associationPermit , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    Bool_api2buf_1(pDest, &(associationPermit), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetAssociationPermit_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetAssociationPermit_Output_buf2par(Bool* associationPermit , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    Bool_buf2api(associationPermit, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetSecurityEnabled_Input_par2buf(UInt8Buffer* pDest , Bool securityEnabled , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    Bool_api2buf_1(pDest, &(securityEnabled), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetSecurityEnabled_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetSecurityEnabled_Output_buf2par(Bool* securityEnabled , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    Bool_buf2api(securityEnabled, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetNumberOfRetries_Input_par2buf(UInt8Buffer* pDest , UInt8 numberOfRetries , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    UInt8_api2buf_1(pDest, &(numberOfRetries), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetNumberOfRetries_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetNumberOfRetries_Output_buf2par(UInt8* numberOfRetries , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    UInt8_buf2api(numberOfRetries, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetMaxCsmaBackoffs_Input_par2buf(UInt8Buffer* pDest , UInt8 maxCsmaBackoffs , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    UInt8_api2buf_1(pDest, &(maxCsmaBackoffs), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetMaxCsmaBackoffs_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetMaxCsmaBackoffs_Output_buf2par(UInt8* maxCsmaBackoffs , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    UInt8_buf2api(maxCsmaBackoffs, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetDefaultTransmitPowers_Input_par2buf(UInt8Buffer* pDest , Int8* pDefaultTransmitPowerTable , UInt16* pIndex)
{
    pDest[(*pIndex)++] = (NULL == pDefaultTransmitPowerTable);
    if (NULL != pDefaultTransmitPowerTable)
    {
        Int8_api2buf(pDest, pDefaultTransmitPowerTable, 16, pIndex);
    }
    else
    {
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            MEMSET(&(pDest[(*pIndex)]) , 0x00 , 16);
            (*pIndex) += 16;
        }
    }
}

void gpMacDispatcher_SetTransmitPower_Input_par2buf(UInt8Buffer* pDest , gpMacCore_TxPower_t transmitPower , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacCore_TxPower_t_api2buf_1(pDest, &(transmitPower), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetTransmitPower_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetTransmitPower_Output_buf2par(Int8* transmitPower , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    Int8_buf2api(transmitPower, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetCCAMode_Input_par2buf(UInt8Buffer* pDest , UInt8 cCAMode , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    UInt8_api2buf_1(pDest, &(cCAMode), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetCCAMode_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetCCAMode_Output_buf2par(UInt8* cCAMode , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    UInt8_buf2api(cCAMode, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetPanCoordinator_Input_par2buf(UInt8Buffer* pDest , Bool panCoordinator , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    Bool_api2buf_1(pDest, &(panCoordinator), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetPanCoordinator_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetPanCoordinator_Output_buf2par(Bool* panCoordinator , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    Bool_buf2api(panCoordinator, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetMinBE_Input_par2buf(UInt8Buffer* pDest , UInt8 minBE , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    UInt8_api2buf_1(pDest, &(minBE), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetMinBE_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetMinBE_Output_buf2par(UInt8* minBE , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    UInt8_buf2api(minBE, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetIndicateBeaconNotifications_Input_par2buf(UInt8Buffer* pDest , Bool enable , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    Bool_api2buf_1(pDest, &(enable), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetIndicateBeaconNotifications_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetIndicateBeaconNotifications_Output_buf2par(Bool* enable , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    Bool_buf2api(enable, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetMacVersion_Input_par2buf(UInt8Buffer* pDest , gpMacCore_MacVersion_t macVersion , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacCore_MacVersion_t_api2buf_1(pDest, &(macVersion), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetMacVersion_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetMacVersion_Output_buf2par(gpMacCore_MacVersion_t* macVersion , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacCore_MacVersion_t_buf2api(macVersion, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetForwardPollIndications_Input_par2buf(UInt8Buffer* pDest , Bool enable , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    Bool_api2buf_1(pDest, &(enable), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetForwardPollIndications_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetForwardPollIndications_Output_buf2par(Bool* enable , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    Bool_buf2api(enable, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_DataPending_QueueAdd_Input_par2buf(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* pAddrInfo , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    pDest[(*pIndex)++] = (NULL == pAddrInfo);
    if (NULL != pAddrInfo)
    {
        gpMacCore_AddressInfo_t_api2buf(pDest, pAddrInfo, 1, pIndex);
    }
    else
    {
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            MEMSET(&(pDest[(*pIndex)]) , 0x00 , (max(2*1,8*1) + 2*1 + 1));
            (*pIndex) += (max(2*1,8*1) + 2*1 + 1);
        }
    }
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_DataPending_QueueAdd_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_AddressInfo_t* pAddrInfo , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacCore_Result_t_buf2api(result, pSource, 1, pIndex);
    NOT_USED(pAddrInfo);
    NOT_USED(stackId);
}

void gpMacDispatcher_DataPending_QueueRemove_Input_par2buf(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* pAddrInfo , gpMacCore_StackId_t stackId , UInt16* pIndex)
{
    pDest[(*pIndex)++] = (NULL == pAddrInfo);
    if (NULL != pAddrInfo)
    {
        gpMacCore_AddressInfo_t_api2buf(pDest, pAddrInfo, 1, pIndex);
    }
    else
    {
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            MEMSET(&(pDest[(*pIndex)]) , 0x00 , (max(2*1,8*1) + 2*1 + 1));
            (*pIndex) += (max(2*1,8*1) + 2*1 + 1);
        }
    }
    gpMacCore_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_DataPending_QueueRemove_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_AddressInfo_t* pAddrInfo , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacCore_Result_t_buf2api(result, pSource, 1, pIndex);
    NOT_USED(pAddrInfo);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetMinInterferenceLevels_Input_par2buf(UInt8Buffer* pDest , Int8* pInterferenceLevels , UInt16* pIndex)
{
    pDest[(*pIndex)++] = (NULL == pInterferenceLevels);
    if (NULL != pInterferenceLevels)
    {
        Int8_api2buf_1(pDest, pInterferenceLevels, pIndex);
    }
    else
    {
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            MEMSET(&(pDest[(*pIndex)]) , 0x00 , 1);
            (*pIndex) += 1;
        }
    }
}

void gpMacDispatcher_SetMaxBE_Input_par2buf(UInt8Buffer* pDest , UInt8 maxBE , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    UInt8_api2buf_1(pDest, &(maxBE), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetMaxBE_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetMaxBE_Output_buf2par(UInt8* maxBE , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    UInt8_buf2api(maxBE, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetDeviceDescriptor_Input_par2buf(UInt8Buffer* pDest , gpMacCore_DeviceDescriptor_t* pDeviceDescriptor , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    pDest[(*pIndex)++] = (NULL == pDeviceDescriptor);
    if (NULL != pDeviceDescriptor)
    {
        gpMacCore_DeviceDescriptor_t_api2buf(pDest, pDeviceDescriptor, 1, pIndex);
    }
    else
    {
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            MEMSET(&(pDest[(*pIndex)]) , 0x00 , (2*1 + 2*1 + 8*1 + 4*1 + 1));
            (*pIndex) += (2*1 + 2*1 + 8*1 + 4*1 + 1);
        }
    }
    gpMacCore_Index_t_api2buf_1(pDest, &(index), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_SetDeviceDescriptor_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_DeviceDescriptor_t* pDeviceDescriptor , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacCore_Result_t_buf2api(result, pSource, 1, pIndex);
    NOT_USED(pDeviceDescriptor);
    NOT_USED(index);
    NOT_USED(stackId);
}

void gpMacDispatcher_GetDeviceDescriptor_Input_par2buf(UInt8Buffer* pDest , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacCore_Index_t_api2buf_1(pDest, &(index), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetDeviceDescriptor_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_DeviceDescriptor_t* pDeviceDescriptor , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacCore_Result_t_buf2api(result, pSource, 1, pIndex);
    // no NULL byte check for output buffers if (0x0 == pSource[(*pIndex)++]) // Check null byte
    {
        gpMarshall_AckStatus_t marshall_result = gpMacCore_DeviceDescriptor_t_buf2api(pDeviceDescriptor , pSource , 1 , pIndex);
        GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == marshall_result);
    }
    NOT_USED(index);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetDeviceTableEntries_Input_par2buf(UInt8Buffer* pDest , gpMacCore_DeviceTablesEntries_t deviceTableEntries , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacCore_DeviceTablesEntries_t_api2buf_1(pDest, &(deviceTableEntries), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetDeviceTableEntries_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetDeviceTableEntries_Output_buf2par(gpMacCore_DeviceTablesEntries_t* deviceTableEntries , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacCore_DeviceTablesEntries_t_buf2api(deviceTableEntries, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetKeyDescriptor_Input_par2buf(UInt8Buffer* pDest , gpMacCore_KeyDescriptor_t* pKeyDescriptor , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    pDest[(*pIndex)++] = (NULL == pKeyDescriptor);
    if (NULL != pKeyDescriptor)
    {
        gpMacCore_KeyDescriptor_t_api2buf(pDest, pKeyDescriptor, 1, pIndex);
    }
    else
    {
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            MEMSET(&(pDest[(*pIndex)]) , 0x00 , (GP_MACCORE_NUMBER_OF_KEY_ID_LOOKUP_DESCRIPTORS*(9 + 1) + 1 + GP_MACCORE_NUMBER_OF_KEY_DEVICE_DESCRIPTORS*((2*1 + 2*1 + 8*1 + 4*1 + 1) + 1 + 1) + 1 + GP_MACCORE_NUMBER_OF_KEY_USAGE_DESCRIPTORS*(1 + 1) + 1 + 16));
            (*pIndex) += (GP_MACCORE_NUMBER_OF_KEY_ID_LOOKUP_DESCRIPTORS*(9 + 1) + 1 + GP_MACCORE_NUMBER_OF_KEY_DEVICE_DESCRIPTORS*((2*1 + 2*1 + 8*1 + 4*1 + 1) + 1 + 1) + 1 + GP_MACCORE_NUMBER_OF_KEY_USAGE_DESCRIPTORS*(1 + 1) + 1 + 16);
        }
    }
    gpMacCore_Index_t_api2buf_1(pDest, &(index), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_SetKeyDescriptor_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_KeyDescriptor_t* pKeyDescriptor , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacCore_Result_t_buf2api(result, pSource, 1, pIndex);
    NOT_USED(pKeyDescriptor);
    NOT_USED(index);
    NOT_USED(stackId);
}

void gpMacDispatcher_GetKeyDescriptor_Input_par2buf(UInt8Buffer* pDest , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacCore_Index_t_api2buf_1(pDest, &(index), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetKeyDescriptor_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_KeyDescriptor_t* pKeyDescriptor , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacCore_Result_t_buf2api(result, pSource, 1, pIndex);
    // no NULL byte check for output buffers if (0x0 == pSource[(*pIndex)++]) // Check null byte
    {
        gpMarshall_AckStatus_t marshall_result = gpMacCore_KeyDescriptor_t_buf2api(pKeyDescriptor , pSource , 1 , pIndex);
        GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == marshall_result);
    }
    NOT_USED(index);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetKeyTableEntries_Input_par2buf(UInt8Buffer* pDest , gpMacCore_KeyTablesEntries_t keyTableEntries , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacCore_KeyTablesEntries_t_api2buf_1(pDest, &(keyTableEntries), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_SetSecurityLevelDescriptor_Input_par2buf(UInt8Buffer* pDest , gpMacCore_SecurityLevelDescriptor_t* pSecurityLevelDescriptor , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    pDest[(*pIndex)++] = (NULL == pSecurityLevelDescriptor);
    if (NULL != pSecurityLevelDescriptor)
    {
        gpMacCore_SecurityLevelDescriptor_t_api2buf(pDest, pSecurityLevelDescriptor, 1, pIndex);
    }
    else
    {
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            MEMSET(&(pDest[(*pIndex)]) , 0x00 , (1 + 1 + 1 + 1));
            (*pIndex) += (1 + 1 + 1 + 1);
        }
    }
    gpMacCore_Index_t_api2buf_1(pDest, &(index), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_SetSecurityLevelDescriptor_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_SecurityLevelDescriptor_t* pSecurityLevelDescriptor , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacCore_Result_t_buf2api(result, pSource, 1, pIndex);
    NOT_USED(pSecurityLevelDescriptor);
    NOT_USED(index);
    NOT_USED(stackId);
}

void gpMacDispatcher_GetSecurityLevelDescriptor_Input_par2buf(UInt8Buffer* pDest , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacCore_Index_t_api2buf_1(pDest, &(index), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetSecurityLevelDescriptor_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_SecurityLevelDescriptor_t* pSecurityLevelDescriptor , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacCore_Result_t_buf2api(result, pSource, 1, pIndex);
    // no NULL byte check for output buffers if (0x0 == pSource[(*pIndex)++]) // Check null byte
    {
        gpMarshall_AckStatus_t marshall_result = gpMacCore_SecurityLevelDescriptor_t_buf2api(pSecurityLevelDescriptor , pSource , 1 , pIndex);
        GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == marshall_result);
    }
    NOT_USED(index);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetSecurityLevelTableEntries_Input_par2buf(UInt8Buffer* pDest , gpMacCore_SecurityLevelTableEntries_t securityLevelTableEntries , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacCore_SecurityLevelTableEntries_t_api2buf_1(pDest, &(securityLevelTableEntries), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetSecurityLevelTableEntries_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetSecurityLevelTableEntries_Output_buf2par(gpMacCore_SecurityLevelTableEntries_t* securityLevelTableEntries , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacCore_SecurityLevelTableEntries_t_buf2api(securityLevelTableEntries, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetDefaultKeySource_Input_par2buf(UInt8Buffer* pDest , UInt8* pDefaultKeySource , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    pDest[(*pIndex)++] = (NULL == pDefaultKeySource);
    if (NULL != pDefaultKeySource)
    {
        UInt8_api2buf(pDest, pDefaultKeySource, 8, pIndex);
    }
    else
    {
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            MEMSET(&(pDest[(*pIndex)]) , 0x00 , 8);
            (*pIndex) += 8;
        }
    }
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_SetFrameCounter_Input_par2buf(UInt8Buffer* pDest , UInt32 frameCounter , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    UInt32_api2buf_1(pDest, &(frameCounter), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetFrameCounter_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetFrameCounter_Output_buf2par(UInt32* frameCounter , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    UInt32_buf2api(frameCounter, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetPanCoordShortAddress_Input_par2buf(UInt8Buffer* pDest , UInt16 panCoordShortAddress , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    UInt16_api2buf_1(pDest, &(panCoordShortAddress), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_SetPanCoordExtendedAddress_Input_par2buf(UInt8Buffer* pDest , MACAddress_t* pPanCoordExtendedAddress , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    pDest[(*pIndex)++] = (NULL == pPanCoordExtendedAddress);
    if (NULL != pPanCoordExtendedAddress)
    {
        MACAddress_t_api2buf_1(pDest, pPanCoordExtendedAddress, pIndex);
    }
    else
    {
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            MEMSET(&(pDest[(*pIndex)]) , 0x00 , 8*1);
            (*pIndex) += 8*1;
        }
    }
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetPanCoordExtendedAddress_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetPanCoordExtendedAddress_Output_buf2par(MACAddress_t* pPanCoordExtendedAddress , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    // no NULL byte check for output buffers if (0x0 == pSource[(*pIndex)++]) // Check null byte
    {
        MACAddress_t_buf2api(pPanCoordExtendedAddress, pSource, 1, pIndex);
    }
    NOT_USED(stackId);
}

void gpMacDispatcher_AddNeighbour_Input_par2buf(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* pAddrInfo , gpMacCore_StackId_t stackId , UInt16* pIndex)
{
    pDest[(*pIndex)++] = (NULL == pAddrInfo);
    if (NULL != pAddrInfo)
    {
        gpMacCore_AddressInfo_t_api2buf(pDest, pAddrInfo, 1, pIndex);
    }
    else
    {
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            MEMSET(&(pDest[(*pIndex)]) , 0x00 , (max(2*1,8*1) + 2*1 + 1));
            (*pIndex) += (max(2*1,8*1) + 2*1 + 1);
        }
    }
    gpMacCore_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_AddNeighbour_Output_buf2par(Bool* result , gpMacCore_AddressInfo_t* pAddrInfo , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    Bool_buf2api(result, pSource, 1, pIndex);
    NOT_USED(pAddrInfo);
    NOT_USED(stackId);
}

void gpMacDispatcher_RemoveNeighbour_Input_par2buf(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* pAddrInfo , gpMacCore_StackId_t stackId , UInt16* pIndex)
{
    pDest[(*pIndex)++] = (NULL == pAddrInfo);
    if (NULL != pAddrInfo)
    {
        gpMacCore_AddressInfo_t_api2buf(pDest, pAddrInfo, 1, pIndex);
    }
    else
    {
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            MEMSET(&(pDest[(*pIndex)]) , 0x00 , (max(2*1,8*1) + 2*1 + 1));
            (*pIndex) += (max(2*1,8*1) + 2*1 + 1);
        }
    }
    gpMacCore_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_RemoveNeighbour_Output_buf2par(Bool* result , gpMacCore_AddressInfo_t* pAddrInfo , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    Bool_buf2api(result, pSource, 1, pIndex);
    NOT_USED(pAddrInfo);
    NOT_USED(stackId);
}

void gpMacDispatcher_SetDataPendingMode_Input_par2buf(UInt8Buffer* pDest , gpMacCore_DataPendingMode_t dataPendingMode , gpMacCore_StackId_t stackId , UInt16* pIndex)
{
    gpMacCore_DataPendingMode_t_api2buf_1(pDest, &(dataPendingMode), pIndex);
    gpMacCore_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_SetDataPendingMode_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_DataPendingMode_t dataPendingMode , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacCore_Result_t_buf2api(result, pSource, 1, pIndex);
    NOT_USED(dataPendingMode);
    NOT_USED(stackId);
}


void gpMacDispatcher_SetAddressModeOverrideForBeacons_Input_par2buf(UInt8Buffer* pDest , UInt8 addressMode , gpMacCore_StackId_t stackId , UInt16* pIndex)
{
    UInt8_api2buf_1(pDest, &(addressMode), pIndex);
    gpMacCore_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_ClearNeighbours_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex)
{
    gpMacCore_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_SetCsmaMode_Input_par2buf(UInt8Buffer* pDest , UInt8 csmaMode , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    UInt8_api2buf_1(pDest, &(csmaMode), pIndex);
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetCsmaMode_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex)
{
    gpMacDispatcher_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_GetCsmaMode_Output_buf2par(UInt8* csmaMode , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    UInt8_buf2api(csmaMode, pSource, 1, pIndex);
    NOT_USED(stackId);
}

void gpMacDispatcher_DataPending_QueueClear_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex)
{
    gpMacCore_StackId_t_api2buf_1(pDest, &(stackId), pIndex);
}

void gpMacDispatcher_DataPending_QueueClear_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacCore_Result_t_buf2api(result, pSource, 1, pIndex);
    NOT_USED(stackId);
}










gpMarshall_AckStatus_t MacDispatcher_cbDataConfirm_Input_buf2api(MacDispatcher_cbDataConfirm_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacCore_Result_t_buf2api(&(pDest->data.status), pSource, 1, pIndex);

    pDest->data.pdHandle = gpPd_GetRealPd(pSource[(*pIndex)++]); /* server had pdHandle stored */
    {
        gpPd_TimeStamp_t pdtimestamp;
        gpPd_TimeStamp_t_buf2api(&pdtimestamp , pSource, 1, pIndex );
        gpPd_SetTxTimestamp(pDest->data.pdHandle , pdtimestamp);
    }
    {
        UInt8 txr;
        UInt8_buf2api(&txr , pSource, 1, pIndex );
        gpPd_SetTxRetryCntr(pDest->data.pdHandle , txr);
    }
    {
        UInt8 framepending;
        UInt8_buf2api(&framepending , pSource, 1, pIndex );
        gpPd_SetFramePendingAfterTx(pDest->data.pdHandle , framepending);
    }
    gpMacDispatcher_StackId_t_buf2api(&(pDest->data.stackId), pSource, 1, pIndex);
    return gpMarshall_AckStatusSuccess;
}

gpMarshall_AckStatus_t MacDispatcher_cbDataIndication_Input_buf2api(MacDispatcher_cbDataIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex)
{
    if (pSource[(*pIndex)++] == 0x0)  // Check IsNull byte
    {
        pDest->data.pSrcAddrInfo = pDest->pSrcAddrInfo.data;
        {
            gpMarshall_AckStatus_t marshall_result = gpMacCore_AddressInfo_t_buf2api(pDest->data.pSrcAddrInfo , pSource , 1 , pIndex );
            if (gpMarshall_AckStatusSuccess != marshall_result) { return marshall_result; }
        }
    }
    else
    {
        pDest->data.pSrcAddrInfo = NULL;
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            (*pIndex) += (max(2*1,8*1) + 2*1 + 1);
        }
    }
    if (pSource[(*pIndex)++] == 0x0)  // Check IsNull byte
    {
        pDest->data.pDstAddrInfo = pDest->pDstAddrInfo.data;
        {
            gpMarshall_AckStatus_t marshall_result = gpMacCore_AddressInfo_t_buf2api(pDest->data.pDstAddrInfo , pSource , 1 , pIndex );
            if (gpMarshall_AckStatusSuccess != marshall_result) { return marshall_result; }
        }
    }
    else
    {
        pDest->data.pDstAddrInfo = NULL;
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            (*pIndex) += (max(2*1,8*1) + 2*1 + 1);
        }
    }
    UInt8_buf2api(&(pDest->data.dsn), pSource, 1, pIndex);
    if (pSource[(*pIndex)++] == 0x0)  // Check IsNull byte
    {
        pDest->data.pSecOptions = pDest->pSecOptions.data;
        {
            gpMarshall_AckStatus_t marshall_result = gpMacCore_Security_t_buf2api(pDest->data.pSecOptions , pSource , 1 , pIndex );
            if (gpMarshall_AckStatusSuccess != marshall_result) { return marshall_result; }
        }
    }
    else
    {
        pDest->data.pSecOptions = NULL;
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            (*pIndex) += (1 + 1 + max(4,8) + 1);
        }
    }
    {
        gpMarshall_AckStatus_t marshall_result = gpPd_Loh_t_buf2api(&(pDest->data.pdLoh), pSource, 1, pIndex , false );
        if (gpMarshall_AckStatusSuccess != marshall_result) { return marshall_result; }
    }
    gpPd_SetLqi(pDest->data.pdLoh.handle , pSource[(*pIndex)++]);
    gpPd_SetRssi(pDest->data.pdLoh.handle , pSource[(*pIndex)++]);
    {
        gpPd_TimeStamp_t pdtimestamp;
        gpPd_TimeStamp_t_buf2api(&pdtimestamp , pSource, 1, pIndex );
        gpPd_SetRxTimestamp(pDest->data.pdLoh.handle , pdtimestamp);
    }
    {
        UInt8 rxchannel;
        UInt8_buf2api(&rxchannel , pSource, 1, pIndex );
        gpPd_SetRxChannel(pDest->data.pdLoh.handle , rxchannel);
    }
    gpMacDispatcher_StackId_t_buf2api(&(pDest->data.stackId), pSource, 1, pIndex);
    return gpMarshall_AckStatusSuccess;
}

gpMarshall_AckStatus_t MacDispatcher_cbScanConfirm_Input_buf2api(MacDispatcher_cbScanConfirm_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacCore_Result_t_buf2api(&(pDest->data.status), pSource, 1, pIndex);
    gpMacCore_ScanType_t_buf2api(&(pDest->data.scanType), pSource, 1, pIndex);
    UInt32_buf2api(&(pDest->data.unscannedChannels), pSource, 1, pIndex);
    UInt8_buf2api(&(pDest->data.resultListSize), pSource, 1, pIndex);
    if (pSource[(*pIndex)++] == 0x0)  // Check IsNull byte
    {
        // the pointer for the static parameter pEdScanResultList is already initialized
        UInt8_buf2api(pDest->data.pEdScanResultList, pSource, pDest->data.resultListSize , pIndex );
    }
    else
    {
        pDest->data.pEdScanResultList = NULL;
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            (*pIndex) += 27;
        }
    }
    gpMacDispatcher_StackId_t_buf2api(&(pDest->data.stackId), pSource, 1, pIndex);
    return gpMarshall_AckStatusSuccess;
}

gpMarshall_AckStatus_t MacDispatcher_cbAssociateIndication_Input_buf2api(MacDispatcher_cbAssociateIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex)
{
    if (pSource[(*pIndex)++] == 0x0)  // Check IsNull byte
    {
        pDest->data.pDeviceAddress = pDest->pDeviceAddress.data;
        {
            gpMarshall_AckStatus_t marshall_result = gpMacCore_Address_t_buf2api(gpMacCore_AddressModeExtendedAddress , pDest->data.pDeviceAddress , pSource , 1 , pIndex );
            if (gpMarshall_AckStatusSuccess != marshall_result) { return marshall_result; }
        }
    }
    else
    {
        pDest->data.pDeviceAddress = NULL;
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            (*pIndex) += max(2*1,8*1);
        }
    }
    UInt8_buf2api(&(pDest->data.capabilityInformation), pSource, 1, pIndex);
    gpPd_TimeStamp_t_buf2api(&(pDest->data.rxTime), pSource, 1, pIndex);
    gpMacDispatcher_StackId_t_buf2api(&(pDest->data.stackId), pSource, 1, pIndex);
    return gpMarshall_AckStatusSuccess;
}

gpMarshall_AckStatus_t MacDispatcher_cbAssociateConfirm_Input_buf2api(MacDispatcher_cbAssociateConfirm_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex)
{
    UInt16_buf2api(&(pDest->data.assocShortAddress), pSource, 1, pIndex);
    gpMacCore_Result_t_buf2api(&(pDest->data.status), pSource, 1, pIndex);
    gpPd_TimeStamp_t_buf2api(&(pDest->data.txTime), pSource, 1, pIndex);
    gpMacDispatcher_StackId_t_buf2api(&(pDest->data.stackId), pSource, 1, pIndex);
    return gpMarshall_AckStatusSuccess;
}

gpMarshall_AckStatus_t MacDispatcher_cbAssociateCommStatusIndication_Input_buf2api(MacDispatcher_cbAssociateCommStatusIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex)
{
    if (pSource[(*pIndex)++] == 0x0)  // Check IsNull byte
    {
        pDest->data.pSrcAddrInfo = pDest->pSrcAddrInfo.data;
        {
            gpMarshall_AckStatus_t marshall_result = gpMacCore_AddressInfo_t_buf2api(pDest->data.pSrcAddrInfo , pSource , 1 , pIndex );
            if (gpMarshall_AckStatusSuccess != marshall_result) { return marshall_result; }
        }
    }
    else
    {
        pDest->data.pSrcAddrInfo = NULL;
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            (*pIndex) += (max(2*1,8*1) + 2*1 + 1);
        }
    }
    if (pSource[(*pIndex)++] == 0x0)  // Check IsNull byte
    {
        pDest->data.pDstAddrInfo = pDest->pDstAddrInfo.data;
        {
            gpMarshall_AckStatus_t marshall_result = gpMacCore_AddressInfo_t_buf2api(pDest->data.pDstAddrInfo , pSource , 1 , pIndex );
            if (gpMarshall_AckStatusSuccess != marshall_result) { return marshall_result; }
        }
    }
    else
    {
        pDest->data.pDstAddrInfo = NULL;
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            (*pIndex) += (max(2*1,8*1) + 2*1 + 1);
        }
    }
    gpMacCore_Result_t_buf2api(&(pDest->data.status), pSource, 1, pIndex);
    gpPd_TimeStamp_t_buf2api(&(pDest->data.txTime), pSource, 1, pIndex);
    gpMacDispatcher_StackId_t_buf2api(&(pDest->data.stackId), pSource, 1, pIndex);
    return gpMarshall_AckStatusSuccess;
}

gpMarshall_AckStatus_t MacDispatcher_cbPollConfirm_Input_buf2api(MacDispatcher_cbPollConfirm_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacCore_Result_t_buf2api(&(pDest->data.status), pSource, 1, pIndex);
    if (pSource[(*pIndex)++] == 0x0)  // Check IsNull byte
    {
        pDest->data.coordAddrInfo = pDest->coordAddrInfo.data;
        {
            gpMarshall_AckStatus_t marshall_result = gpMacCore_AddressInfo_t_buf2api(pDest->data.coordAddrInfo , pSource , 1 , pIndex );
            if (gpMarshall_AckStatusSuccess != marshall_result) { return marshall_result; }
        }
    }
    else
    {
        pDest->data.coordAddrInfo = NULL;
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            (*pIndex) += (max(2*1,8*1) + 2*1 + 1);
        }
    }
    gpPd_TimeStamp_t_buf2api(&(pDest->data.txTime), pSource, 1, pIndex);
    gpMacDispatcher_StackId_t_buf2api(&(pDest->data.stackId), pSource, 1, pIndex);
    return gpMarshall_AckStatusSuccess;
}

gpMarshall_AckStatus_t MacDispatcher_cbPollIndication_Input_buf2api(MacDispatcher_cbPollIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex)
{
    if (pSource[(*pIndex)++] == 0x0)  // Check IsNull byte
    {
        pDest->data.addressInfo = pDest->addressInfo.data;
        {
            gpMarshall_AckStatus_t marshall_result = gpMacCore_AddressInfo_t_buf2api(pDest->data.addressInfo , pSource , 1 , pIndex );
            if (gpMarshall_AckStatusSuccess != marshall_result) { return marshall_result; }
        }
    }
    else
    {
        pDest->data.addressInfo = NULL;
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            (*pIndex) += (max(2*1,8*1) + 2*1 + 1);
        }
    }
    gpPd_TimeStamp_t_buf2api(&(pDest->data.rxTime), pSource, 1, pIndex);
    gpMacDispatcher_StackId_t_buf2api(&(pDest->data.stackId), pSource, 1, pIndex);
    return gpMarshall_AckStatusSuccess;
}

gpMarshall_AckStatus_t MacDispatcher_cbPurgeConfirm_Input_buf2api(MacDispatcher_cbPurgeConfirm_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacCore_Result_t_buf2api(&(pDest->data.status), pSource, 1, pIndex);

    pDest->data.pdHandle = gpPd_GetRealPd(pSource[(*pIndex)++]); /* server had pdHandle stored */
    gpMacDispatcher_StackId_t_buf2api(&(pDest->data.stackId), pSource, 1, pIndex);
    return gpMarshall_AckStatusSuccess;
}

gpMarshall_AckStatus_t MacDispatcher_cbBeaconNotifyIndication_Input_buf2api(MacDispatcher_cbBeaconNotifyIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex)
{
    UInt8_buf2api(&(pDest->data.bsn), pSource, 1, pIndex);
    if (pSource[(*pIndex)++] == 0x0)  // Check IsNull byte
    {
        pDest->data.pPanDescriptor = pDest->pPanDescriptor.data;
        {
            gpMarshall_AckStatus_t marshall_result = gpMacCore_PanDescriptor_t_buf2api(pDest->data.pPanDescriptor , pSource , 1 , pIndex );
            if (gpMarshall_AckStatusSuccess != marshall_result) { return marshall_result; }
        }
    }
    else
    {
        pDest->data.pPanDescriptor = NULL;
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            (*pIndex) += (4*1 + 2*1 + 1 + 1 + (max(2*1,8*1) + 2*1 + 1));
        }
    }
    UInt8_buf2api(&(pDest->data.beaconPayloadLength), pSource, 1, pIndex);
    if (pSource[(*pIndex)++] == 0x0)  // Check IsNull byte
    {
        pDest->data.pBeaconPayload = pDest->pBeaconPayload;
        UInt8_buf2api(pDest->data.pBeaconPayload, pSource, pDest->data.beaconPayloadLength , pIndex );
    }
    else
    {
        pDest->data.pBeaconPayload = NULL;
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            (*pIndex) += GP_MACCORE_MAX_BEACON_PAYLOAD_LENGTH;
        }
    }
    gpMacDispatcher_StackId_t_buf2api(&(pDest->data.stackId), pSource, 1, pIndex);
    return gpMarshall_AckStatusSuccess;
}

gpMarshall_AckStatus_t MacDispatcher_cbOrphanIndication_Input_buf2api(MacDispatcher_cbOrphanIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex)
{
    if (pSource[(*pIndex)++] == 0x0)  // Check IsNull byte
    {
        pDest->data.pOrphanAddress = pDest->pOrphanAddress;
        MACAddress_t_buf2api(pDest->data.pOrphanAddress, pSource, 1 , pIndex );
    }
    else
    {
        pDest->data.pOrphanAddress = NULL;
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            (*pIndex) += 8*1;
        }
    }
    gpPd_TimeStamp_t_buf2api(&(pDest->data.rxTime), pSource, 1, pIndex);
    gpMacDispatcher_StackId_t_buf2api(&(pDest->data.stackId), pSource, 1, pIndex);
    return gpMarshall_AckStatusSuccess;
}

gpMarshall_AckStatus_t MacDispatcher_cbOrphanCommStatusIndication_Input_buf2api(MacDispatcher_cbOrphanCommStatusIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex)
{
    if (pSource[(*pIndex)++] == 0x0)  // Check IsNull byte
    {
        pDest->data.pSrcAddrInfo = pDest->pSrcAddrInfo.data;
        {
            gpMarshall_AckStatus_t marshall_result = gpMacCore_AddressInfo_t_buf2api(pDest->data.pSrcAddrInfo , pSource , 1 , pIndex );
            if (gpMarshall_AckStatusSuccess != marshall_result) { return marshall_result; }
        }
    }
    else
    {
        pDest->data.pSrcAddrInfo = NULL;
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            (*pIndex) += (max(2*1,8*1) + 2*1 + 1);
        }
    }
    if (pSource[(*pIndex)++] == 0x0)  // Check IsNull byte
    {
        pDest->data.pDstAddrInfo = pDest->pDstAddrInfo.data;
        {
            gpMarshall_AckStatus_t marshall_result = gpMacCore_AddressInfo_t_buf2api(pDest->data.pDstAddrInfo , pSource , 1 , pIndex );
            if (gpMarshall_AckStatusSuccess != marshall_result) { return marshall_result; }
        }
    }
    else
    {
        pDest->data.pDstAddrInfo = NULL;
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            (*pIndex) += (max(2*1,8*1) + 2*1 + 1);
        }
    }
    gpMacCore_Result_t_buf2api(&(pDest->data.status), pSource, 1, pIndex);
    gpPd_TimeStamp_t_buf2api(&(pDest->data.txTime), pSource, 1, pIndex);
    gpMacDispatcher_StackId_t_buf2api(&(pDest->data.stackId), pSource, 1, pIndex);
    return gpMarshall_AckStatusSuccess;
}

gpMarshall_AckStatus_t MacDispatcher_cbSecurityFailureCommStatusIndication_Input_buf2api(MacDispatcher_cbSecurityFailureCommStatusIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex)
{
    if (pSource[(*pIndex)++] == 0x0)  // Check IsNull byte
    {
        pDest->data.pSrcAddrInfo = pDest->pSrcAddrInfo.data;
        {
            gpMarshall_AckStatus_t marshall_result = gpMacCore_AddressInfo_t_buf2api(pDest->data.pSrcAddrInfo , pSource , 1 , pIndex );
            if (gpMarshall_AckStatusSuccess != marshall_result) { return marshall_result; }
        }
    }
    else
    {
        pDest->data.pSrcAddrInfo = NULL;
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            (*pIndex) += (max(2*1,8*1) + 2*1 + 1);
        }
    }
    if (pSource[(*pIndex)++] == 0x0)  // Check IsNull byte
    {
        pDest->data.pDstAddrInfo = pDest->pDstAddrInfo.data;
        {
            gpMarshall_AckStatus_t marshall_result = gpMacCore_AddressInfo_t_buf2api(pDest->data.pDstAddrInfo , pSource , 1 , pIndex );
            if (gpMarshall_AckStatusSuccess != marshall_result) { return marshall_result; }
        }
    }
    else
    {
        pDest->data.pDstAddrInfo = NULL;
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            (*pIndex) += (max(2*1,8*1) + 2*1 + 1);
        }
    }
    gpMacCore_Result_t_buf2api(&(pDest->data.status), pSource, 1, pIndex);
    gpPd_TimeStamp_t_buf2api(&(pDest->data.txTime), pSource, 1, pIndex);
    gpMacDispatcher_StackId_t_buf2api(&(pDest->data.stackId), pSource, 1, pIndex);
    return gpMarshall_AckStatusSuccess;
}

gpMarshall_AckStatus_t MacDispatcher_cbDriverResetIndication_Input_buf2api(MacDispatcher_cbDriverResetIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex)
{
    gpMacDispatcher_Result_t_buf2api(&(pDest->data.status), pSource, 1, pIndex);
    gpMacDispatcher_StackId_t_buf2api(&(pDest->data.stackId), pSource, 1, pIndex);
    return gpMarshall_AckStatusSuccess;
}

gpMarshall_AckStatus_t MacDispatcher_cbPollNotify_Input_buf2api(MacDispatcher_cbPollNotify_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex)
{
    if (pSource[(*pIndex)++] == 0x0)  // Check IsNull byte
    {
        pDest->data.addressInfo = pDest->addressInfo.data;
        {
            gpMarshall_AckStatus_t marshall_result = gpMacCore_AddressInfo_t_buf2api(pDest->data.addressInfo , pSource , 1 , pIndex );
            if (gpMarshall_AckStatusSuccess != marshall_result) { return marshall_result; }
        }
    }
    else
    {
        pDest->data.addressInfo = NULL;
        if (true == gpMacDispatcher_GetDummyDataInsertion())
        {
            (*pIndex) += (max(2*1,8*1) + 2*1 + 1);
        }
    }
    gpPd_TimeStamp_t_buf2api(&(pDest->data.rxTime), pSource, 1, pIndex);

    pDest->data.pdHandle = gpPd_GetRealPd(pSource[(*pIndex)++]); /* server had pdHandle stored */
    Bool_buf2api(&(pDest->data.fromNeighbour), pSource, 1, pIndex);
    gpMacDispatcher_StackId_t_buf2api(&(pDest->data.stackId), pSource, 1, pIndex);
    return gpMarshall_AckStatusSuccess;
}

gpMarshall_AckStatus_t MacDispatcher_cbSecurityFrameCounterIndication_Input_buf2api(MacDispatcher_cbSecurityFrameCounterIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex)
{
    UInt32_buf2api(&(pDest->data.frameCounter), pSource, 1, pIndex);
    gpMacDispatcher_StackId_t_buf2api(&(pDest->data.stackId), pSource, 1, pIndex);
    return gpMarshall_AckStatusSuccess;
}




