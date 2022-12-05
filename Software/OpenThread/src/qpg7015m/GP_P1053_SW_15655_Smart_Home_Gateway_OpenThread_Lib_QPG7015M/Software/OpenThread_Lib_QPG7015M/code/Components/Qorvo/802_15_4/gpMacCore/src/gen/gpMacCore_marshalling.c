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
 * $Header: //depot/release/Embedded/Components/Qorvo/802_15_4/v2.10.3.1/comps/gpMacCore/src/gen/gpMacCore_marshalling.c#1 $
 * $Change: 197210 $
 * $DateTime: 2022/10/13 16:52:00 $
 */

/** @file "gpMacCore_marshalling.c"
 *
 *  MACCore
 *
 *   Marshalling structures and functions.
*/

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

// General includes
#include "gpMacCore.h"
#include "gpMacCore_marshalling.h"

#ifdef GP_DIVERSITY_LOG
#include "gpLog.h"
#endif
/* <CodeGenerator Placeholder> AdditionalIncludes */
#include "gpEncryption_marshalling.h"
#include "gpMacCore_marshalling.h"
/* </CodeGenerator Placeholder> AdditionalIncludes */

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/
#define GP_COMPONENT_ID GP_COMPONENT_ID_MACCORE

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

gpMarshall_AckStatus_t gpMacCore_DeviceDescriptor_t_buf2api(gpMacCore_DeviceDescriptor_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex )
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        gpMacCore_PanId_t_buf2api_1(&(pDest->panId), pSource, pIndex);
        UInt16_buf2api_1(&(pDest->shortAddr), pSource, pIndex);
        MACAddress_t_buf2api_1(&(pDest->extAddress), pSource, pIndex);
        UInt32_buf2api_1(&(pDest->frameCounter), pSource, pIndex);
        Bool_buf2api_1(&(pDest->exempt), pSource, pIndex);
        pDest++;
    }
    return gpMarshall_AckStatusSuccess;
}

void gpMacCore_DeviceDescriptor_t_api2buf(UInt8Buffer* pDest , const gpMacCore_DeviceDescriptor_t* pSource , UInt16 length , UInt16* pIndex)
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        gpMacCore_PanId_t_api2buf_1(pDest , &(pSource->panId), pIndex);
        UInt16_api2buf_1(pDest , &(pSource->shortAddr), pIndex);
        MACAddress_t_api2buf_1(pDest , &(pSource->extAddress), pIndex);
        UInt32_api2buf_1(pDest , &(pSource->frameCounter), pIndex);
        Bool_api2buf_1(pDest , &(pSource->exempt), pIndex);
        pSource++;
    }
}

gpMarshall_AckStatus_t gpMacCore_KeyUsageDescriptor_t_buf2api(gpMacCore_KeyUsageDescriptor_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex )
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        gpMacCore_FrameType_t_buf2api_1(&(pDest->frameType), pSource, pIndex);
        gpMacCore_Command_t_buf2api_1(&(pDest->commandFrameIdentifier), pSource, pIndex);
        pDest++;
    }
    return gpMarshall_AckStatusSuccess;
}

void gpMacCore_KeyUsageDescriptor_t_api2buf(UInt8Buffer* pDest , const gpMacCore_KeyUsageDescriptor_t* pSource , UInt16 length , UInt16* pIndex)
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        gpMacCore_FrameType_t_api2buf_1(pDest , &(pSource->frameType), pIndex);
        gpMacCore_Command_t_api2buf_1(pDest , &(pSource->commandFrameIdentifier), pIndex);
        pSource++;
    }
}

gpMarshall_AckStatus_t gpMacCore_KeyDeviceDescriptor_t_buf2api(gpMacCore_KeyDeviceDescriptor_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex )
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        gpMacCore_DeviceDescriptor_t_buf2api(&(pDest->deviceDescriptor), pSource, 1, pIndex);
        Bool_buf2api_1(&(pDest->uniqueDevice), pSource, pIndex);
        Bool_buf2api_1(&(pDest->blackListed), pSource, pIndex);
        pDest++;
    }
    return gpMarshall_AckStatusSuccess;
}

void gpMacCore_KeyDeviceDescriptor_t_api2buf(UInt8Buffer* pDest , const gpMacCore_KeyDeviceDescriptor_t* pSource , UInt16 length , UInt16* pIndex)
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        gpMacCore_DeviceDescriptor_t_api2buf(pDest , &(pSource->deviceDescriptor), 1, pIndex);
        Bool_api2buf_1(pDest , &(pSource->uniqueDevice), pIndex);
        Bool_api2buf_1(pDest , &(pSource->blackListed), pIndex);
        pSource++;
    }
}

gpMarshall_AckStatus_t gpMacCore_Security_t_buf2api(gpMacCore_Security_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex )
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        gpEncryption_SecLevel_t_buf2api_1(&(pDest->securityLevel), pSource, pIndex);
        gpMacCore_KeyIdMode_t_buf2api_1(&(pDest->keyIdMode), pSource, pIndex);
        gpMacCore_KeySource_t_buf2api(gpMacCore_KeyIdModeExplicit8Octet , &(pDest->pKeySource), pSource, 1, pIndex);
        gpMacCore_KeyIndex_t_buf2api_1(&(pDest->keyIndex), pSource, pIndex);
        pDest++;
    }
    return gpMarshall_AckStatusSuccess;
}

void gpMacCore_Security_t_api2buf(UInt8Buffer* pDest , const gpMacCore_Security_t* pSource , UInt16 length , UInt16* pIndex)
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        gpEncryption_SecLevel_t_api2buf_1(pDest , &(pSource->securityLevel), pIndex);
        gpMacCore_KeyIdMode_t_api2buf_1(pDest , &(pSource->keyIdMode), pIndex);
        gpMacCore_KeySource_t_api2buf(gpMacCore_KeyIdModeExplicit8Octet , pDest , &(pSource->pKeySource), 1, pIndex);
        gpMacCore_KeyIndex_t_api2buf_1(pDest , &(pSource->keyIndex), pIndex);
        pSource++;
    }
}

gpMarshall_AckStatus_t gpMacCore_AddressInfo_t_buf2api(gpMacCore_AddressInfo_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex )
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        gpMacCore_Address_t_buf2api(gpMacCore_AddressModeExtendedAddress , &(pDest->address), pSource, 1, pIndex);
        gpMacCore_PanId_t_buf2api_1(&(pDest->panId), pSource, pIndex);
        gpMacCore_AddressMode_t_buf2api_1(&(pDest->addressMode), pSource, pIndex);
        pDest++;
    }
    return gpMarshall_AckStatusSuccess;
}

void gpMacCore_AddressInfo_t_api2buf(UInt8Buffer* pDest , const gpMacCore_AddressInfo_t* pSource , UInt16 length , UInt16* pIndex)
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        gpMacCore_Address_t_api2buf(gpMacCore_AddressModeExtendedAddress , pDest , &(pSource->address), 1, pIndex);
        gpMacCore_PanId_t_api2buf_1(pDest , &(pSource->panId), pIndex);
        gpMacCore_AddressMode_t_api2buf_1(pDest , &(pSource->addressMode), pIndex);
        pSource++;
    }
}

gpMarshall_AckStatus_t gpMacCore_PanDescriptor_t_buf2api(gpMacCore_PanDescriptor_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex )
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        UInt32_buf2api_1(&(pDest->timeStamp), pSource, pIndex);
        gpMacCore_SuperFrameSpec_t_buf2api_1(&(pDest->superFrame), pSource, pIndex);
        UInt8_buf2api_1(&(pDest->logicalChannel), pSource, pIndex);
        UInt8_buf2api_1(&(pDest->linkQuality), pSource, pIndex);
        gpMacCore_AddressInfo_t_buf2api(&(pDest->coordAddressInfo), pSource, 1, pIndex);
        pDest++;
    }
    return gpMarshall_AckStatusSuccess;
}

void gpMacCore_PanDescriptor_t_api2buf(UInt8Buffer* pDest , const gpMacCore_PanDescriptor_t* pSource , UInt16 length , UInt16* pIndex)
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        UInt32_api2buf_1(pDest , &(pSource->timeStamp), pIndex);
        gpMacCore_SuperFrameSpec_t_api2buf_1(pDest , &(pSource->superFrame), pIndex);
        UInt8_api2buf_1(pDest , &(pSource->logicalChannel), pIndex);
        UInt8_api2buf_1(pDest , &(pSource->linkQuality), pIndex);
        gpMacCore_AddressInfo_t_api2buf(pDest , &(pSource->coordAddressInfo), 1, pIndex);
        pSource++;
    }
}

gpMarshall_AckStatus_t gpMacCore_KeyIdLookupDescriptor_t_buf2api(gpMacCore_KeyIdLookupDescriptor_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex )
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        UInt8_buf2api((pDest->lookupData), pSource, 9, pIndex);
        UInt8_buf2api_1(&(pDest->lookupDataSize), pSource, pIndex);
        pDest++;
    }
    return gpMarshall_AckStatusSuccess;
}

void gpMacCore_KeyIdLookupDescriptor_t_api2buf(UInt8Buffer* pDest , const gpMacCore_KeyIdLookupDescriptor_t* pSource , UInt16 length , UInt16* pIndex)
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        UInt8_api2buf(pDest , (pSource->lookupData), 9, pIndex);
        UInt8_api2buf_1(pDest , &(pSource->lookupDataSize), pIndex);
        pSource++;
    }
}

gpMarshall_AckStatus_t gpMacCore_KeyDescriptor_t_buf2api(gpMacCore_KeyDescriptor_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex )
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        gpMacCore_KeyIdLookupDescriptor_t_buf2api((pDest->keyIdLookupDescriptors), pSource, GP_MACCORE_NUMBER_OF_KEY_ID_LOOKUP_DESCRIPTORS, pIndex);
        gpMacCore_KeyIdLookupListEntries_t_buf2api_1(&(pDest->keyIdLookupListEntries), pSource, pIndex);
        gpMacCore_KeyDeviceDescriptor_t_buf2api((pDest->keyDeviceDescriptorList), pSource, GP_MACCORE_NUMBER_OF_KEY_DEVICE_DESCRIPTORS, pIndex);
        gpMacCore_KeyDeviceListEntries_t_buf2api_1(&(pDest->keyDeviceListEntries), pSource, pIndex);
        gpMacCore_KeyUsageDescriptor_t_buf2api((pDest->keyUsageDescriptorList), pSource, GP_MACCORE_NUMBER_OF_KEY_USAGE_DESCRIPTORS, pIndex);
        gpMacCore_KeyUsageListEntries_t_buf2api_1(&(pDest->keyUsageListEntries), pSource, pIndex);
        UInt8_buf2api((pDest->key), pSource, 16, pIndex);
        pDest++;
    }
    return gpMarshall_AckStatusSuccess;
}

void gpMacCore_KeyDescriptor_t_api2buf(UInt8Buffer* pDest , const gpMacCore_KeyDescriptor_t* pSource , UInt16 length , UInt16* pIndex)
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        gpMacCore_KeyIdLookupDescriptor_t_api2buf(pDest , (pSource->keyIdLookupDescriptors), GP_MACCORE_NUMBER_OF_KEY_ID_LOOKUP_DESCRIPTORS, pIndex);
        gpMacCore_KeyIdLookupListEntries_t_api2buf_1(pDest , &(pSource->keyIdLookupListEntries), pIndex);
        gpMacCore_KeyDeviceDescriptor_t_api2buf(pDest , (pSource->keyDeviceDescriptorList), GP_MACCORE_NUMBER_OF_KEY_DEVICE_DESCRIPTORS, pIndex);
        gpMacCore_KeyDeviceListEntries_t_api2buf_1(pDest , &(pSource->keyDeviceListEntries), pIndex);
        gpMacCore_KeyUsageDescriptor_t_api2buf(pDest , (pSource->keyUsageDescriptorList), GP_MACCORE_NUMBER_OF_KEY_USAGE_DESCRIPTORS, pIndex);
        gpMacCore_KeyUsageListEntries_t_api2buf_1(pDest , &(pSource->keyUsageListEntries), pIndex);
        UInt8_api2buf(pDest , (pSource->key), 16, pIndex);
        pSource++;
    }
}

gpMarshall_AckStatus_t gpMacCore_SecurityLevelDescriptor_t_buf2api(gpMacCore_SecurityLevelDescriptor_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex )
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        gpMacCore_FrameType_t_buf2api_1(&(pDest->frameType), pSource, pIndex);
        gpMacCore_Command_t_buf2api_1(&(pDest->commandFrameIdentifier), pSource, pIndex);
        gpEncryption_SecLevel_t_buf2api_1(&(pDest->securityMinimum), pSource, pIndex);
        Bool_buf2api_1(&(pDest->deviceOverrideSecurityMinimum), pSource, pIndex);
        pDest++;
    }
    return gpMarshall_AckStatusSuccess;
}

void gpMacCore_SecurityLevelDescriptor_t_api2buf(UInt8Buffer* pDest , const gpMacCore_SecurityLevelDescriptor_t* pSource , UInt16 length , UInt16* pIndex)
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        gpMacCore_FrameType_t_api2buf_1(pDest , &(pSource->frameType), pIndex);
        gpMacCore_Command_t_api2buf_1(pDest , &(pSource->commandFrameIdentifier), pIndex);
        gpEncryption_SecLevel_t_api2buf_1(pDest , &(pSource->securityMinimum), pIndex);
        Bool_api2buf_1(pDest , &(pSource->deviceOverrideSecurityMinimum), pIndex);
        pSource++;
    }
}

gpMarshall_AckStatus_t gpMacCore_MultiChannelOptions_t_buf2api(gpMacCore_MultiChannelOptions_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex )
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        UInt8_buf2api((pDest->channel), pSource, 3, pIndex);
        pDest++;
    }
    return gpMarshall_AckStatusSuccess;
}

void gpMacCore_MultiChannelOptions_t_api2buf(UInt8Buffer* pDest , const gpMacCore_MultiChannelOptions_t* pSource , UInt16 length , UInt16* pIndex)
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        UInt8_api2buf(pDest , (pSource->channel), 3, pIndex);
        pSource++;
    }
}

gpMarshall_AckStatus_t gpMacCore_TxTimingOptions_t_buf2api(gpMacCore_TxTimingOptions_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex )
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        UInt32_buf2api_1(&(pDest->txTimestamp), pSource, pIndex);
        pDest++;
    }
    return gpMarshall_AckStatusSuccess;
}

void gpMacCore_TxTimingOptions_t_api2buf(UInt8Buffer* pDest , const gpMacCore_TxTimingOptions_t* pSource , UInt16 length , UInt16* pIndex)
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        UInt32_api2buf_1(pDest , &(pSource->txTimestamp), pIndex);
        pSource++;
    }
}

gpMarshall_AckStatus_t gpMacCore_DiagRxCntr_t_buf2api(gpMacCore_DiagRxCntr_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex )
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        UInt8_buf2api_1(&(pDest->lqi), pSource, pIndex);
        gpPd_Rssi_t_buf2api_1(&(pDest->rssi), pSource, pIndex);
        pDest++;
    }
    return gpMarshall_AckStatusSuccess;
}

void gpMacCore_DiagRxCntr_t_api2buf(UInt8Buffer* pDest , const gpMacCore_DiagRxCntr_t* pSource , UInt16 length , UInt16* pIndex)
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        UInt8_api2buf_1(pDest , &(pSource->lqi), pIndex);
        gpPd_Rssi_t_api2buf_1(pDest , &(pSource->rssi), pIndex);
        pSource++;
    }
}

gpMarshall_AckStatus_t gpMacCore_DiagTxCntr_t_buf2api(gpMacCore_DiagTxCntr_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex )
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        UInt32_buf2api_1(&(pDest->avgRetryCntr), pSource, pIndex);
        UInt32_buf2api_1(&(pDest->txCntr), pSource, pIndex);
        pDest++;
    }
    return gpMarshall_AckStatusSuccess;
}

void gpMacCore_DiagTxCntr_t_api2buf(UInt8Buffer* pDest , const gpMacCore_DiagTxCntr_t* pSource , UInt16 length , UInt16* pIndex)
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        UInt32_api2buf_1(pDest , &(pSource->avgRetryCntr), pIndex);
        UInt32_api2buf_1(pDest , &(pSource->txCntr), pIndex);
        pSource++;
    }
}

// Union copy functions
gpMarshall_AckStatus_t gpMacCore_Address_t_buf2api(UInt8 unionid , gpMacCore_Address_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex)
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        switch (unionid)
        {
            case gpMacCore_AddressModeShortAddress:
            {
                UInt16_buf2api(&(pDest->Short), pSource, 1, pIndex);
                break;
            }
            case gpMacCore_AddressModeExtendedAddress:
            {
                MACAddress_t_buf2api(&(pDest->Extended), pSource, 1, pIndex);
                break;
            }
            default:
            {
#ifdef GP_DIVERSITY_LOG
                GP_LOG_SYSTEM_PRINTF("  Extended (MACAddress_t): Unknown unionid %i",2,unionid);
#endif
                break;
            }
        }
        pDest++;
    }
    return gpMarshall_AckStatusSuccess;
}

void gpMacCore_Address_t_api2buf(UInt8 unionid , UInt8Buffer* pDest , const gpMacCore_Address_t* pSource , UInt16 length , UInt16* pIndex)
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        switch (unionid)
        {
            case gpMacCore_AddressModeShortAddress:
            {
                UInt16_api2buf_1(pDest , &(pSource->Short), pIndex);
                break;
            }
            case gpMacCore_AddressModeExtendedAddress:
            {
                MACAddress_t_api2buf_1(pDest , &(pSource->Extended), pIndex);
                break;
            }
            default:
            {
#ifdef GP_DIVERSITY_LOG
                GP_LOG_SYSTEM_PRINTF("  Extended (MACAddress_t): Unknown unionid %i",2,unionid);
#endif
                break;
            }
        }
        pSource++;
    }
}
gpMarshall_AckStatus_t gpMacCore_KeySource_t_buf2api(UInt8 unionid , gpMacCore_KeySource_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex)
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        switch (unionid)
        {
            case gpMacCore_KeyIdModeExplicit4Octet:
            {
                UInt8_buf2api((pDest->pKeySource4), pSource, 4, pIndex);
                break;
            }
            case gpMacCore_KeyIdModeExplicit8Octet:
            {
                UInt8_buf2api((pDest->pKeySource8), pSource, 8, pIndex);
                break;
            }
            default:
            {
#ifdef GP_DIVERSITY_LOG
                GP_LOG_SYSTEM_PRINTF("  pKeySource8 (UInt8): Unknown unionid %i",2,unionid);
#endif
                break;
            }
        }
        pDest++;
    }
    return gpMarshall_AckStatusSuccess;
}

void gpMacCore_KeySource_t_api2buf(UInt8 unionid , UInt8Buffer* pDest , const gpMacCore_KeySource_t* pSource , UInt16 length , UInt16* pIndex)
{
    UIntLoop i;
    for(i = 0; i < length; i++)
    {
        switch (unionid)
        {
            case gpMacCore_KeyIdModeExplicit4Octet:
            {
                UInt8_api2buf(pDest , (pSource->pKeySource4), 4, pIndex);
                break;
            }
            case gpMacCore_KeyIdModeExplicit8Octet:
            {
                UInt8_api2buf(pDest , (pSource->pKeySource8), 8, pIndex);
                break;
            }
            default:
            {
#ifdef GP_DIVERSITY_LOG
                GP_LOG_SYSTEM_PRINTF("  pKeySource8 (UInt8): Unknown unionid %i",2,unionid);
#endif
                break;
            }
        }
        pSource++;
    }
}


void gpMacCore_InitMarshalling(void)
{
}


