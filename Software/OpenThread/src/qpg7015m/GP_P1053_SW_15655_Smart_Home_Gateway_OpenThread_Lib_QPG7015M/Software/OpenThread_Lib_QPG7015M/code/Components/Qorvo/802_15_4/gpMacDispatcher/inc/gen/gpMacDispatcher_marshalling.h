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
 * $Header: //depot/main/Embedded/Components/Qorvo/802_15_4/v2.10.3.1/comps/gpMacDispatcher/inc/gen/gpMacDispatcher_marshalling.h#4 $
 * $Change: 195905 $
 * $DateTime: 2022/07/08 07:46:42 $
 */

#ifndef _GPMACDISPATCHER_MARSHALLING_H_
#define _GPMACDISPATCHER_MARSHALLING_H_

//DOCUMENTATION MACDISPATCHER: no @file required as all documented items are refered to a group

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/
#include <global.h>
#include "gpMacDispatcher.h"
/* <CodeGenerator Placeholder> AdditionalIncludes */
#include "gpPd_marshalling.h"
#include "gpMacCore_marshalling.h"
/* </CodeGenerator Placeholder> AdditionalIncludes */

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Type Definitions
 *****************************************************************************/

typedef struct {
    gpMacDispatcher_StringIdentifier_t data[1];
} gpMacDispatcher_StringIdentifier_t_l1_pointer_marshall_t;


typedef struct {
    gpMacDispatcher_Callbacks_t data[1];
} gpMacDispatcher_Callbacks_t_l1_pointer_marshall_t;



typedef struct {
    gpMacDispatcher_StringIdentifier_t* stringIdentifier;
} gpMacDispatcher_RegisterNetworkStack_Input_struct_t;

typedef struct {
    gpMacDispatcher_RegisterNetworkStack_Input_struct_t data;
    gpMacDispatcher_StringIdentifier_t_l1_pointer_marshall_t stringIdentifier;
} gpMacDispatcher_RegisterNetworkStack_Input_marshall_struct_t;

typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_RegisterNetworkStack_Output_struct_t;

typedef struct {
    gpMacDispatcher_RegisterNetworkStack_Output_struct_t data;
} gpMacDispatcher_RegisterNetworkStack_Output_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_UnRegisterNetworkStack_Input_struct_t;

typedef struct {
    gpMacDispatcher_UnRegisterNetworkStack_Input_struct_t data;
} gpMacDispatcher_UnRegisterNetworkStack_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
} gpMacDispatcher_UnRegisterNetworkStack_Output_struct_t;

typedef struct {
    gpMacDispatcher_UnRegisterNetworkStack_Output_struct_t data;
} gpMacDispatcher_UnRegisterNetworkStack_Output_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
    gpMacDispatcher_Callbacks_t* callbacks;
} gpMacDispatcher_RegisterCallbacks_Input_struct_t;

typedef struct {
    gpMacDispatcher_RegisterCallbacks_Input_struct_t data;
    gpMacDispatcher_Callbacks_t_l1_pointer_marshall_t callbacks;
} gpMacDispatcher_RegisterCallbacks_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_LockClaim_Input_struct_t;

typedef struct {
    gpMacDispatcher_LockClaim_Input_struct_t data;
} gpMacDispatcher_LockClaim_Input_marshall_struct_t;

typedef struct {
    Bool result;
} gpMacDispatcher_LockClaim_Output_struct_t;

typedef struct {
    gpMacDispatcher_LockClaim_Output_struct_t data;
} gpMacDispatcher_LockClaim_Output_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_LockRelease_Input_struct_t;

typedef struct {
    gpMacDispatcher_LockRelease_Input_struct_t data;
} gpMacDispatcher_LockRelease_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_LockedByThisStack_Input_struct_t;

typedef struct {
    gpMacDispatcher_LockedByThisStack_Input_struct_t data;
} gpMacDispatcher_LockedByThisStack_Input_marshall_struct_t;

typedef struct {
    Bool locked;
} gpMacDispatcher_LockedByThisStack_Output_struct_t;

typedef struct {
    gpMacDispatcher_LockedByThisStack_Output_struct_t data;
} gpMacDispatcher_LockedByThisStack_Output_marshall_struct_t;


typedef struct {
    Bool locked;
} gpMacDispatcher_Locked_Output_struct_t;

typedef struct {
    gpMacDispatcher_Locked_Output_struct_t data;
} gpMacDispatcher_Locked_Output_marshall_struct_t;


typedef struct {
    Bool setDefaultPib;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_Reset_Input_struct_t;

typedef struct {
    gpMacDispatcher_Reset_Input_struct_t data;
} gpMacDispatcher_Reset_Input_marshall_struct_t;

typedef struct {
    gpMacDispatcher_Result_t result;
} gpMacDispatcher_Reset_Output_struct_t;

typedef struct {
    gpMacDispatcher_Reset_Output_struct_t data;
} gpMacDispatcher_Reset_Output_marshall_struct_t;


typedef struct {
    gpMacCore_AddressMode_t srcAddrMode;
    gpMacCore_AddressInfo_t* pDstAddressInfo;
    UInt8 txOptions;
    gpMacCore_Security_t* pSecOptions;
    gpMacCore_MultiChannelOptions_t multiChannelOptions;
    gpPd_Loh_t pdLoh;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_DataRequest_Input_struct_t;

typedef struct {
    gpMacDispatcher_DataRequest_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pDstAddressInfo;
    gpMacCore_Security_t_l1_pointer_marshall_t pSecOptions;
    gpMacCore_MultiChannelOptions_t_l1_pointer_marshall_t multiChannelOptions;
    gpPd_Loh_t_l1_pointer_marshall_t pdLoh;
} gpMacDispatcher_DataRequest_Input_marshall_struct_t;


typedef struct {
    gpMacCore_ScanType_t scanType;
    UInt32 scanChannels;
    UInt8 scanDuration;
    UInt8 resultListSize;
    UInt8* pResultList;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_ScanRequest_Input_struct_t;

typedef struct {
    gpMacDispatcher_ScanRequest_Input_struct_t data;
} gpMacDispatcher_ScanRequest_Input_marshall_struct_t;


typedef struct {
    UInt8 logicalChannel;
    gpMacCore_AddressInfo_t* coordAddrInfo;
    UInt8 capabilityInformation;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_AssociateRequest_Input_struct_t;

typedef struct {
    gpMacDispatcher_AssociateRequest_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t coordAddrInfo;
} gpMacDispatcher_AssociateRequest_Input_marshall_struct_t;


typedef struct {
    MACAddress_t* pDeviceAddress;
    UInt16 associateShortAddress;
    gpMacCore_Result_t status;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_AssociateResponse_Input_struct_t;

typedef struct {
    gpMacDispatcher_AssociateResponse_Input_struct_t data;
    MACAddress_t pDeviceAddress[1];
} gpMacDispatcher_AssociateResponse_Input_marshall_struct_t;


typedef struct {
    gpMacCore_AddressInfo_t* coordAddrInfo;
    gpMacCore_Security_t* pSecOptions;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_PollRequest_Input_struct_t;

typedef struct {
    gpMacDispatcher_PollRequest_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t coordAddrInfo;
    gpMacCore_Security_t_l1_pointer_marshall_t pSecOptions;
} gpMacDispatcher_PollRequest_Input_marshall_struct_t;


typedef struct {
    gpPd_Handle_t pdHandle;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_PurgeRequest_Input_struct_t;

typedef struct {
    gpMacDispatcher_PurgeRequest_Input_struct_t data;
} gpMacDispatcher_PurgeRequest_Input_marshall_struct_t;


typedef struct {
    gpMacCore_PanId_t panId;
    UInt8 logicalChannel;
    Bool panCoordinator;
    UInt8 stackId;
} gpMacDispatcher_Start_Input_struct_t;

typedef struct {
    gpMacDispatcher_Start_Input_struct_t data;
} gpMacDispatcher_Start_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t returnValue;
} gpMacDispatcher_Start_Output_struct_t;

typedef struct {
    gpMacDispatcher_Start_Output_struct_t data;
} gpMacDispatcher_Start_Output_marshall_struct_t;


typedef struct {
    MACAddress_t* pOrphanAddress;
    UInt16 shortAddress;
    Bool associatedMember;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_OrphanResponse_Input_struct_t;

typedef struct {
    gpMacDispatcher_OrphanResponse_Input_struct_t data;
    MACAddress_t pOrphanAddress[1];
} gpMacDispatcher_OrphanResponse_Input_marshall_struct_t;


typedef struct {
    UInt16 panId;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetPanId_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetPanId_Input_struct_t data;
} gpMacDispatcher_SetPanId_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetPanId_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetPanId_Input_struct_t data;
} gpMacDispatcher_GetPanId_Input_marshall_struct_t;

typedef struct {
    gpMacCore_PanId_t panId;
} gpMacDispatcher_GetPanId_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetPanId_Output_struct_t data;
} gpMacDispatcher_GetPanId_Output_marshall_struct_t;


typedef struct {
    UInt16 shortAddress;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetShortAddress_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetShortAddress_Input_struct_t data;
} gpMacDispatcher_SetShortAddress_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetShortAddress_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetShortAddress_Input_struct_t data;
} gpMacDispatcher_GetShortAddress_Input_marshall_struct_t;

typedef struct {
    UInt16 address;
} gpMacDispatcher_GetShortAddress_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetShortAddress_Output_struct_t data;
} gpMacDispatcher_GetShortAddress_Output_marshall_struct_t;


typedef struct {
    MACAddress_t* pExtendedAddress;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetExtendedAddress_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetExtendedAddress_Input_struct_t data;
    MACAddress_t pExtendedAddress[1];
} gpMacDispatcher_SetExtendedAddress_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetExtendedAddress_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetExtendedAddress_Input_struct_t data;
} gpMacDispatcher_GetExtendedAddress_Input_marshall_struct_t;

typedef struct {
    MACAddress_t* pExtendedAddress;
} gpMacDispatcher_GetExtendedAddress_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetExtendedAddress_Output_struct_t data;
    MACAddress_t pExtendedAddress[1];
} gpMacDispatcher_GetExtendedAddress_Output_marshall_struct_t;


typedef struct {
    UInt8 dsn;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetDsn_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetDsn_Input_struct_t data;
} gpMacDispatcher_SetDsn_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetDsn_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetDsn_Input_struct_t data;
} gpMacDispatcher_GetDsn_Input_marshall_struct_t;

typedef struct {
    UInt8 dsn;
} gpMacDispatcher_GetDsn_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetDsn_Output_struct_t data;
} gpMacDispatcher_GetDsn_Output_marshall_struct_t;


typedef struct {
    UInt8 channel;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetCurrentChannel_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetCurrentChannel_Input_struct_t data;
} gpMacDispatcher_SetCurrentChannel_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetCurrentChannel_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetCurrentChannel_Input_struct_t data;
} gpMacDispatcher_GetCurrentChannel_Input_marshall_struct_t;

typedef struct {
    UInt8 channel;
} gpMacDispatcher_GetCurrentChannel_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetCurrentChannel_Output_struct_t data;
} gpMacDispatcher_GetCurrentChannel_Output_marshall_struct_t;


typedef struct {
    UInt8* pBeaconPayload;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetBeaconPayload_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetBeaconPayload_Input_struct_t data;
    UInt8 pBeaconPayload[GP_MACCORE_MAX_BEACON_PAYLOAD_LENGTH];
} gpMacDispatcher_SetBeaconPayload_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetBeaconPayload_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetBeaconPayload_Input_struct_t data;
} gpMacDispatcher_GetBeaconPayload_Input_marshall_struct_t;

typedef struct {
    UInt8* pBeaconPayload;
} gpMacDispatcher_GetBeaconPayload_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetBeaconPayload_Output_struct_t data;
    UInt8 pBeaconPayload[GP_MACCORE_MAX_BEACON_PAYLOAD_LENGTH];
} gpMacDispatcher_GetBeaconPayload_Output_marshall_struct_t;


typedef struct {
    UInt8 beaconPayloadLength;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetBeaconPayloadLength_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetBeaconPayloadLength_Input_struct_t data;
} gpMacDispatcher_SetBeaconPayloadLength_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetBeaconPayloadLength_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetBeaconPayloadLength_Input_struct_t data;
} gpMacDispatcher_GetBeaconPayloadLength_Input_marshall_struct_t;

typedef struct {
    UInt8 beaconPayloadLength;
} gpMacDispatcher_GetBeaconPayloadLength_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetBeaconPayloadLength_Output_struct_t data;
} gpMacDispatcher_GetBeaconPayloadLength_Output_marshall_struct_t;




typedef struct {
    Bool rxOnWhenIdle;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetRxOnWhenIdle_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetRxOnWhenIdle_Input_struct_t data;
} gpMacDispatcher_SetRxOnWhenIdle_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetRxOnWhenIdle_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetRxOnWhenIdle_Input_struct_t data;
} gpMacDispatcher_GetRxOnWhenIdle_Input_marshall_struct_t;

typedef struct {
    Bool rxOnWhenIdle;
} gpMacDispatcher_GetRxOnWhenIdle_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetRxOnWhenIdle_Output_struct_t data;
} gpMacDispatcher_GetRxOnWhenIdle_Output_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetTransactionPersistenceTime_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetTransactionPersistenceTime_Input_struct_t data;
} gpMacDispatcher_GetTransactionPersistenceTime_Input_marshall_struct_t;

typedef struct {
    UInt16 time;
} gpMacDispatcher_GetTransactionPersistenceTime_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetTransactionPersistenceTime_Output_struct_t data;
} gpMacDispatcher_GetTransactionPersistenceTime_Output_marshall_struct_t;


typedef struct {
    UInt16 time;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetTransactionPersistenceTime_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetTransactionPersistenceTime_Input_struct_t data;
} gpMacDispatcher_SetTransactionPersistenceTime_Input_marshall_struct_t;


typedef struct {
    Bool beaconStarted;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetBeaconStarted_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetBeaconStarted_Input_struct_t data;
} gpMacDispatcher_SetBeaconStarted_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetBeaconStarted_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetBeaconStarted_Input_struct_t data;
} gpMacDispatcher_GetBeaconStarted_Input_marshall_struct_t;

typedef struct {
    Bool beaconStarted;
} gpMacDispatcher_GetBeaconStarted_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetBeaconStarted_Output_struct_t data;
} gpMacDispatcher_GetBeaconStarted_Output_marshall_struct_t;


typedef struct {
    UInt16 coordShortAddress;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetCoordShortAddress_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetCoordShortAddress_Input_struct_t data;
} gpMacDispatcher_SetCoordShortAddress_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetCoordShortAddress_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetCoordShortAddress_Input_struct_t data;
} gpMacDispatcher_GetCoordShortAddress_Input_marshall_struct_t;

typedef struct {
    UInt16 coordShortAddress;
} gpMacDispatcher_GetCoordShortAddress_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetCoordShortAddress_Output_struct_t data;
} gpMacDispatcher_GetCoordShortAddress_Output_marshall_struct_t;


typedef struct {
    MACAddress_t* pCoordExtendedAddress;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetCoordExtendedAddress_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetCoordExtendedAddress_Input_struct_t data;
    MACAddress_t pCoordExtendedAddress[1];
} gpMacDispatcher_SetCoordExtendedAddress_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetCoordExtendedAddress_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetCoordExtendedAddress_Input_struct_t data;
} gpMacDispatcher_GetCoordExtendedAddress_Input_marshall_struct_t;

typedef struct {
    MACAddress_t* pCoordExtendedAddress;
} gpMacDispatcher_GetCoordExtendedAddress_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetCoordExtendedAddress_Output_struct_t data;
    MACAddress_t pCoordExtendedAddress[1];
} gpMacDispatcher_GetCoordExtendedAddress_Output_marshall_struct_t;


typedef struct {
    UInt8 promiscuousMode;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetPromiscuousMode_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetPromiscuousMode_Input_struct_t data;
} gpMacDispatcher_SetPromiscuousMode_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetPromiscuousMode_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetPromiscuousMode_Input_struct_t data;
} gpMacDispatcher_GetPromiscuousMode_Input_marshall_struct_t;

typedef struct {
    Bool promiscuousMode;
} gpMacDispatcher_GetPromiscuousMode_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetPromiscuousMode_Output_struct_t data;
} gpMacDispatcher_GetPromiscuousMode_Output_marshall_struct_t;


typedef struct {
    Bool associationPermit;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetAssociationPermit_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetAssociationPermit_Input_struct_t data;
} gpMacDispatcher_SetAssociationPermit_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetAssociationPermit_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetAssociationPermit_Input_struct_t data;
} gpMacDispatcher_GetAssociationPermit_Input_marshall_struct_t;

typedef struct {
    Bool associationPermit;
} gpMacDispatcher_GetAssociationPermit_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetAssociationPermit_Output_struct_t data;
} gpMacDispatcher_GetAssociationPermit_Output_marshall_struct_t;


typedef struct {
    Bool securityEnabled;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetSecurityEnabled_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetSecurityEnabled_Input_struct_t data;
} gpMacDispatcher_SetSecurityEnabled_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetSecurityEnabled_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetSecurityEnabled_Input_struct_t data;
} gpMacDispatcher_GetSecurityEnabled_Input_marshall_struct_t;

typedef struct {
    Bool securityEnabled;
} gpMacDispatcher_GetSecurityEnabled_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetSecurityEnabled_Output_struct_t data;
} gpMacDispatcher_GetSecurityEnabled_Output_marshall_struct_t;


typedef struct {
    UInt8 numberOfRetries;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetNumberOfRetries_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetNumberOfRetries_Input_struct_t data;
} gpMacDispatcher_SetNumberOfRetries_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetNumberOfRetries_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetNumberOfRetries_Input_struct_t data;
} gpMacDispatcher_GetNumberOfRetries_Input_marshall_struct_t;

typedef struct {
    UInt8 numberOfRetries;
} gpMacDispatcher_GetNumberOfRetries_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetNumberOfRetries_Output_struct_t data;
} gpMacDispatcher_GetNumberOfRetries_Output_marshall_struct_t;


typedef struct {
    UInt8 maxCsmaBackoffs;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetMaxCsmaBackoffs_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetMaxCsmaBackoffs_Input_struct_t data;
} gpMacDispatcher_SetMaxCsmaBackoffs_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetMaxCsmaBackoffs_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetMaxCsmaBackoffs_Input_struct_t data;
} gpMacDispatcher_GetMaxCsmaBackoffs_Input_marshall_struct_t;

typedef struct {
    UInt8 maxCsmaBackoffs;
} gpMacDispatcher_GetMaxCsmaBackoffs_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetMaxCsmaBackoffs_Output_struct_t data;
} gpMacDispatcher_GetMaxCsmaBackoffs_Output_marshall_struct_t;


typedef struct {
    Int8* pDefaultTransmitPowerTable;
} gpMacDispatcher_SetDefaultTransmitPowers_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetDefaultTransmitPowers_Input_struct_t data;
    Int8 pDefaultTransmitPowerTable[16];
} gpMacDispatcher_SetDefaultTransmitPowers_Input_marshall_struct_t;


typedef struct {
    gpMacCore_TxPower_t transmitPower;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetTransmitPower_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetTransmitPower_Input_struct_t data;
} gpMacDispatcher_SetTransmitPower_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetTransmitPower_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetTransmitPower_Input_struct_t data;
} gpMacDispatcher_GetTransmitPower_Input_marshall_struct_t;

typedef struct {
    Int8 transmitPower;
} gpMacDispatcher_GetTransmitPower_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetTransmitPower_Output_struct_t data;
} gpMacDispatcher_GetTransmitPower_Output_marshall_struct_t;


typedef struct {
    UInt8 cCAMode;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetCCAMode_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetCCAMode_Input_struct_t data;
} gpMacDispatcher_SetCCAMode_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetCCAMode_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetCCAMode_Input_struct_t data;
} gpMacDispatcher_GetCCAMode_Input_marshall_struct_t;

typedef struct {
    UInt8 cCAMode;
} gpMacDispatcher_GetCCAMode_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetCCAMode_Output_struct_t data;
} gpMacDispatcher_GetCCAMode_Output_marshall_struct_t;


typedef struct {
    Bool panCoordinator;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetPanCoordinator_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetPanCoordinator_Input_struct_t data;
} gpMacDispatcher_SetPanCoordinator_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetPanCoordinator_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetPanCoordinator_Input_struct_t data;
} gpMacDispatcher_GetPanCoordinator_Input_marshall_struct_t;

typedef struct {
    Bool panCoordinator;
} gpMacDispatcher_GetPanCoordinator_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetPanCoordinator_Output_struct_t data;
} gpMacDispatcher_GetPanCoordinator_Output_marshall_struct_t;


typedef struct {
    UInt8 minBE;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetMinBE_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetMinBE_Input_struct_t data;
} gpMacDispatcher_SetMinBE_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetMinBE_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetMinBE_Input_struct_t data;
} gpMacDispatcher_GetMinBE_Input_marshall_struct_t;

typedef struct {
    UInt8 minBE;
} gpMacDispatcher_GetMinBE_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetMinBE_Output_struct_t data;
} gpMacDispatcher_GetMinBE_Output_marshall_struct_t;


typedef struct {
    Bool enable;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetIndicateBeaconNotifications_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetIndicateBeaconNotifications_Input_struct_t data;
} gpMacDispatcher_SetIndicateBeaconNotifications_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetIndicateBeaconNotifications_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetIndicateBeaconNotifications_Input_struct_t data;
} gpMacDispatcher_GetIndicateBeaconNotifications_Input_marshall_struct_t;

typedef struct {
    Bool enable;
} gpMacDispatcher_GetIndicateBeaconNotifications_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetIndicateBeaconNotifications_Output_struct_t data;
} gpMacDispatcher_GetIndicateBeaconNotifications_Output_marshall_struct_t;


typedef struct {
    gpMacCore_MacVersion_t macVersion;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetMacVersion_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetMacVersion_Input_struct_t data;
} gpMacDispatcher_SetMacVersion_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetMacVersion_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetMacVersion_Input_struct_t data;
} gpMacDispatcher_GetMacVersion_Input_marshall_struct_t;

typedef struct {
    gpMacCore_MacVersion_t macVersion;
} gpMacDispatcher_GetMacVersion_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetMacVersion_Output_struct_t data;
} gpMacDispatcher_GetMacVersion_Output_marshall_struct_t;


typedef struct {
    Bool enable;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetForwardPollIndications_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetForwardPollIndications_Input_struct_t data;
} gpMacDispatcher_SetForwardPollIndications_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetForwardPollIndications_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetForwardPollIndications_Input_struct_t data;
} gpMacDispatcher_GetForwardPollIndications_Input_marshall_struct_t;

typedef struct {
    Bool enable;
} gpMacDispatcher_GetForwardPollIndications_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetForwardPollIndications_Output_struct_t data;
} gpMacDispatcher_GetForwardPollIndications_Output_marshall_struct_t;


typedef struct {
    gpMacCore_AddressInfo_t* pAddrInfo;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_DataPending_QueueAdd_Input_struct_t;

typedef struct {
    gpMacDispatcher_DataPending_QueueAdd_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pAddrInfo;
} gpMacDispatcher_DataPending_QueueAdd_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
} gpMacDispatcher_DataPending_QueueAdd_Output_struct_t;

typedef struct {
    gpMacDispatcher_DataPending_QueueAdd_Output_struct_t data;
} gpMacDispatcher_DataPending_QueueAdd_Output_marshall_struct_t;


typedef struct {
    gpMacCore_AddressInfo_t* pAddrInfo;
    gpMacCore_StackId_t stackId;
} gpMacDispatcher_DataPending_QueueRemove_Input_struct_t;

typedef struct {
    gpMacDispatcher_DataPending_QueueRemove_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pAddrInfo;
} gpMacDispatcher_DataPending_QueueRemove_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
} gpMacDispatcher_DataPending_QueueRemove_Output_struct_t;

typedef struct {
    gpMacDispatcher_DataPending_QueueRemove_Output_struct_t data;
} gpMacDispatcher_DataPending_QueueRemove_Output_marshall_struct_t;


typedef struct {
    Int8* pInterferenceLevels;
} gpMacDispatcher_SetMinInterferenceLevels_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetMinInterferenceLevels_Input_struct_t data;
    Int8 pInterferenceLevels[1];
} gpMacDispatcher_SetMinInterferenceLevels_Input_marshall_struct_t;


typedef struct {
    UInt8 maxBE;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetMaxBE_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetMaxBE_Input_struct_t data;
} gpMacDispatcher_SetMaxBE_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetMaxBE_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetMaxBE_Input_struct_t data;
} gpMacDispatcher_GetMaxBE_Input_marshall_struct_t;

typedef struct {
    UInt8 maxBE;
} gpMacDispatcher_GetMaxBE_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetMaxBE_Output_struct_t data;
} gpMacDispatcher_GetMaxBE_Output_marshall_struct_t;


typedef struct {
    gpMacCore_DeviceDescriptor_t* pDeviceDescriptor;
    gpMacCore_Index_t index;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetDeviceDescriptor_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetDeviceDescriptor_Input_struct_t data;
    gpMacCore_DeviceDescriptor_t_l1_pointer_marshall_t pDeviceDescriptor;
} gpMacDispatcher_SetDeviceDescriptor_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
} gpMacDispatcher_SetDeviceDescriptor_Output_struct_t;

typedef struct {
    gpMacDispatcher_SetDeviceDescriptor_Output_struct_t data;
} gpMacDispatcher_SetDeviceDescriptor_Output_marshall_struct_t;


typedef struct {
    gpMacCore_Index_t index;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetDeviceDescriptor_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetDeviceDescriptor_Input_struct_t data;
} gpMacDispatcher_GetDeviceDescriptor_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
    gpMacCore_DeviceDescriptor_t* pDeviceDescriptor;
} gpMacDispatcher_GetDeviceDescriptor_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetDeviceDescriptor_Output_struct_t data;
    gpMacCore_DeviceDescriptor_t_l1_pointer_marshall_t pDeviceDescriptor;
} gpMacDispatcher_GetDeviceDescriptor_Output_marshall_struct_t;


typedef struct {
    gpMacCore_DeviceTablesEntries_t deviceTableEntries;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetDeviceTableEntries_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetDeviceTableEntries_Input_struct_t data;
} gpMacDispatcher_SetDeviceTableEntries_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetDeviceTableEntries_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetDeviceTableEntries_Input_struct_t data;
} gpMacDispatcher_GetDeviceTableEntries_Input_marshall_struct_t;

typedef struct {
    gpMacCore_DeviceTablesEntries_t deviceTableEntries;
} gpMacDispatcher_GetDeviceTableEntries_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetDeviceTableEntries_Output_struct_t data;
} gpMacDispatcher_GetDeviceTableEntries_Output_marshall_struct_t;


typedef struct {
    gpMacCore_KeyDescriptor_t* pKeyDescriptor;
    gpMacCore_Index_t index;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetKeyDescriptor_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetKeyDescriptor_Input_struct_t data;
    gpMacCore_KeyDescriptor_t_l1_pointer_marshall_t pKeyDescriptor;
} gpMacDispatcher_SetKeyDescriptor_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
} gpMacDispatcher_SetKeyDescriptor_Output_struct_t;

typedef struct {
    gpMacDispatcher_SetKeyDescriptor_Output_struct_t data;
} gpMacDispatcher_SetKeyDescriptor_Output_marshall_struct_t;


typedef struct {
    gpMacCore_Index_t index;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetKeyDescriptor_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetKeyDescriptor_Input_struct_t data;
} gpMacDispatcher_GetKeyDescriptor_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
    gpMacCore_KeyDescriptor_t* pKeyDescriptor;
} gpMacDispatcher_GetKeyDescriptor_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetKeyDescriptor_Output_struct_t data;
    gpMacCore_KeyDescriptor_t_l1_pointer_marshall_t pKeyDescriptor;
} gpMacDispatcher_GetKeyDescriptor_Output_marshall_struct_t;


typedef struct {
    gpMacCore_KeyTablesEntries_t keyTableEntries;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetKeyTableEntries_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetKeyTableEntries_Input_struct_t data;
} gpMacDispatcher_SetKeyTableEntries_Input_marshall_struct_t;


typedef struct {
    gpMacCore_SecurityLevelDescriptor_t* pSecurityLevelDescriptor;
    gpMacCore_Index_t index;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetSecurityLevelDescriptor_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetSecurityLevelDescriptor_Input_struct_t data;
    gpMacCore_SecurityLevelDescriptor_t_l1_pointer_marshall_t pSecurityLevelDescriptor;
} gpMacDispatcher_SetSecurityLevelDescriptor_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
} gpMacDispatcher_SetSecurityLevelDescriptor_Output_struct_t;

typedef struct {
    gpMacDispatcher_SetSecurityLevelDescriptor_Output_struct_t data;
} gpMacDispatcher_SetSecurityLevelDescriptor_Output_marshall_struct_t;


typedef struct {
    gpMacCore_Index_t index;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetSecurityLevelDescriptor_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetSecurityLevelDescriptor_Input_struct_t data;
} gpMacDispatcher_GetSecurityLevelDescriptor_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
    gpMacCore_SecurityLevelDescriptor_t* pSecurityLevelDescriptor;
} gpMacDispatcher_GetSecurityLevelDescriptor_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetSecurityLevelDescriptor_Output_struct_t data;
    gpMacCore_SecurityLevelDescriptor_t_l1_pointer_marshall_t pSecurityLevelDescriptor;
} gpMacDispatcher_GetSecurityLevelDescriptor_Output_marshall_struct_t;


typedef struct {
    gpMacCore_SecurityLevelTableEntries_t securityLevelTableEntries;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetSecurityLevelTableEntries_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetSecurityLevelTableEntries_Input_struct_t data;
} gpMacDispatcher_SetSecurityLevelTableEntries_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetSecurityLevelTableEntries_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetSecurityLevelTableEntries_Input_struct_t data;
} gpMacDispatcher_GetSecurityLevelTableEntries_Input_marshall_struct_t;

typedef struct {
    gpMacCore_SecurityLevelTableEntries_t securityLevelTableEntries;
} gpMacDispatcher_GetSecurityLevelTableEntries_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetSecurityLevelTableEntries_Output_struct_t data;
} gpMacDispatcher_GetSecurityLevelTableEntries_Output_marshall_struct_t;


typedef struct {
    UInt8* pDefaultKeySource;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetDefaultKeySource_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetDefaultKeySource_Input_struct_t data;
    UInt8 pDefaultKeySource[8];
} gpMacDispatcher_SetDefaultKeySource_Input_marshall_struct_t;


typedef struct {
    UInt32 frameCounter;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetFrameCounter_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetFrameCounter_Input_struct_t data;
} gpMacDispatcher_SetFrameCounter_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetFrameCounter_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetFrameCounter_Input_struct_t data;
} gpMacDispatcher_GetFrameCounter_Input_marshall_struct_t;

typedef struct {
    UInt32 frameCounter;
} gpMacDispatcher_GetFrameCounter_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetFrameCounter_Output_struct_t data;
} gpMacDispatcher_GetFrameCounter_Output_marshall_struct_t;


typedef struct {
    UInt16 panCoordShortAddress;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetPanCoordShortAddress_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetPanCoordShortAddress_Input_struct_t data;
} gpMacDispatcher_SetPanCoordShortAddress_Input_marshall_struct_t;


typedef struct {
    MACAddress_t* pPanCoordExtendedAddress;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetPanCoordExtendedAddress_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetPanCoordExtendedAddress_Input_struct_t data;
    MACAddress_t pPanCoordExtendedAddress[1];
} gpMacDispatcher_SetPanCoordExtendedAddress_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetPanCoordExtendedAddress_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetPanCoordExtendedAddress_Input_struct_t data;
} gpMacDispatcher_GetPanCoordExtendedAddress_Input_marshall_struct_t;

typedef struct {
    MACAddress_t* pPanCoordExtendedAddress;
} gpMacDispatcher_GetPanCoordExtendedAddress_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetPanCoordExtendedAddress_Output_struct_t data;
    MACAddress_t pPanCoordExtendedAddress[1];
} gpMacDispatcher_GetPanCoordExtendedAddress_Output_marshall_struct_t;


typedef struct {
    gpMacCore_AddressInfo_t* pAddrInfo;
    gpMacCore_StackId_t stackId;
} gpMacDispatcher_AddNeighbour_Input_struct_t;

typedef struct {
    gpMacDispatcher_AddNeighbour_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pAddrInfo;
} gpMacDispatcher_AddNeighbour_Input_marshall_struct_t;

typedef struct {
    Bool result;
} gpMacDispatcher_AddNeighbour_Output_struct_t;

typedef struct {
    gpMacDispatcher_AddNeighbour_Output_struct_t data;
} gpMacDispatcher_AddNeighbour_Output_marshall_struct_t;


typedef struct {
    gpMacCore_AddressInfo_t* pAddrInfo;
    gpMacCore_StackId_t stackId;
} gpMacDispatcher_RemoveNeighbour_Input_struct_t;

typedef struct {
    gpMacDispatcher_RemoveNeighbour_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pAddrInfo;
} gpMacDispatcher_RemoveNeighbour_Input_marshall_struct_t;

typedef struct {
    Bool result;
} gpMacDispatcher_RemoveNeighbour_Output_struct_t;

typedef struct {
    gpMacDispatcher_RemoveNeighbour_Output_struct_t data;
} gpMacDispatcher_RemoveNeighbour_Output_marshall_struct_t;


typedef struct {
    gpMacCore_DataPendingMode_t dataPendingMode;
    gpMacCore_StackId_t stackId;
} gpMacDispatcher_SetDataPendingMode_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetDataPendingMode_Input_struct_t data;
} gpMacDispatcher_SetDataPendingMode_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
} gpMacDispatcher_SetDataPendingMode_Output_struct_t;

typedef struct {
    gpMacDispatcher_SetDataPendingMode_Output_struct_t data;
} gpMacDispatcher_SetDataPendingMode_Output_marshall_struct_t;



typedef struct {
    UInt8 addressMode;
    gpMacCore_StackId_t stackId;
} gpMacDispatcher_SetAddressModeOverrideForBeacons_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetAddressModeOverrideForBeacons_Input_struct_t data;
} gpMacDispatcher_SetAddressModeOverrideForBeacons_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacDispatcher_ClearNeighbours_Input_struct_t;

typedef struct {
    gpMacDispatcher_ClearNeighbours_Input_struct_t data;
} gpMacDispatcher_ClearNeighbours_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetCallbacks_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetCallbacks_Input_struct_t data;
} gpMacDispatcher_GetCallbacks_Input_marshall_struct_t;

typedef struct {
    gpMacDispatcher_Callbacks_t* callbacks;
} gpMacDispatcher_GetCallbacks_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetCallbacks_Output_struct_t data;
    gpMacDispatcher_Callbacks_t_l1_pointer_marshall_t callbacks;
} gpMacDispatcher_GetCallbacks_Output_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_IsValidStack_Input_struct_t;

typedef struct {
    gpMacDispatcher_IsValidStack_Input_struct_t data;
} gpMacDispatcher_IsValidStack_Input_marshall_struct_t;

typedef struct {
    Bool valid;
} gpMacDispatcher_IsValidStack_Output_struct_t;

typedef struct {
    gpMacDispatcher_IsValidStack_Output_struct_t data;
} gpMacDispatcher_IsValidStack_Output_marshall_struct_t;


typedef struct {
    UInt8 csmaMode;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetCsmaMode_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetCsmaMode_Input_struct_t data;
} gpMacDispatcher_SetCsmaMode_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetCsmaMode_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetCsmaMode_Input_struct_t data;
} gpMacDispatcher_GetCsmaMode_Input_marshall_struct_t;

typedef struct {
    UInt8 csmaMode;
} gpMacDispatcher_GetCsmaMode_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetCsmaMode_Output_struct_t data;
} gpMacDispatcher_GetCsmaMode_Output_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacDispatcher_DataPending_QueueClear_Input_struct_t;

typedef struct {
    gpMacDispatcher_DataPending_QueueClear_Input_struct_t data;
} gpMacDispatcher_DataPending_QueueClear_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
} gpMacDispatcher_DataPending_QueueClear_Output_struct_t;

typedef struct {
    gpMacDispatcher_DataPending_QueueClear_Output_struct_t data;
} gpMacDispatcher_DataPending_QueueClear_Output_marshall_struct_t;


typedef struct {
    gpPd_Handle_t pdHandle;
    gpMacCore_TxTimingOptions_t timingOptions;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_ScheduleTimedTx_Input_struct_t;

typedef struct {
    gpMacDispatcher_ScheduleTimedTx_Input_struct_t data;
    gpMacCore_TxTimingOptions_t_l1_pointer_marshall_t timingOptions;
} gpMacDispatcher_ScheduleTimedTx_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
} gpMacDispatcher_ScheduleTimedTx_Output_struct_t;

typedef struct {
    gpMacDispatcher_ScheduleTimedTx_Output_struct_t data;
} gpMacDispatcher_ScheduleTimedTx_Output_marshall_struct_t;







typedef struct {
    Bool rawModeEnabled;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_SetStackInRawMode_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetStackInRawMode_Input_struct_t data;
} gpMacDispatcher_SetStackInRawMode_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_GetStackInRawMode_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetStackInRawMode_Input_struct_t data;
} gpMacDispatcher_GetStackInRawMode_Input_marshall_struct_t;

typedef struct {
    Bool rawModeEnabled;
} gpMacDispatcher_GetStackInRawMode_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetStackInRawMode_Output_struct_t data;
} gpMacDispatcher_GetStackInRawMode_Output_marshall_struct_t;




typedef struct {
    Bool enableEnhancedFramePending;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_EnableEnhancedFramePending_Input_struct_t;

typedef struct {
    gpMacDispatcher_EnableEnhancedFramePending_Input_struct_t data;
} gpMacDispatcher_EnableEnhancedFramePending_Input_marshall_struct_t;


typedef struct {
    UInt32 dutyCycleOnTime;
    UInt32 dutyCyclePeriod;
    UInt16 recurrenceAmount;
    UInt32 startTime;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_EnableRxWindows_Input_struct_t;

typedef struct {
    gpMacDispatcher_EnableRxWindows_Input_struct_t data;
} gpMacDispatcher_EnableRxWindows_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_DisableRxWindows_Input_struct_t;

typedef struct {
    gpMacDispatcher_DisableRxWindows_Input_struct_t data;
} gpMacDispatcher_DisableRxWindows_Input_marshall_struct_t;


typedef struct {
    UInt16 dutyCyclePeriod;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_EnableCsl_Input_struct_t;

typedef struct {
    gpMacDispatcher_EnableCsl_Input_struct_t data;
} gpMacDispatcher_EnableCsl_Input_marshall_struct_t;


typedef struct {
    UInt32 nextCslSampleTime;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_UpdateCslSampleTime_Input_struct_t;

typedef struct {
    gpMacDispatcher_UpdateCslSampleTime_Input_struct_t data;
} gpMacDispatcher_UpdateCslSampleTime_Input_marshall_struct_t;


typedef struct {
    UInt32 currentTime;
} gpMacDispatcher_GetCurrentTimeUs_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetCurrentTimeUs_Output_struct_t data;
} gpMacDispatcher_GetCurrentTimeUs_Output_marshall_struct_t;


typedef struct {
    UInt8 linkMetrics;
    MACAddress_t* pExtendedAddress;
    UInt16 shortAddress;
    gpMacDispatcher_StackId_t stackId;
} gpMacDispatcher_ConfigureEnhAckProbing_Input_struct_t;

typedef struct {
    gpMacDispatcher_ConfigureEnhAckProbing_Input_struct_t data;
    MACAddress_t pExtendedAddress[1];
} gpMacDispatcher_ConfigureEnhAckProbing_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
} gpMacDispatcher_ConfigureEnhAckProbing_Output_struct_t;

typedef struct {
    gpMacDispatcher_ConfigureEnhAckProbing_Output_struct_t data;
} gpMacDispatcher_ConfigureEnhAckProbing_Output_marshall_struct_t;


typedef struct {
    Bool enable;
    gpMacCore_StackId_t stackId;
} gpMacDispatcher_SetRetransmitOnCcaFail_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetRetransmitOnCcaFail_Input_struct_t data;
} gpMacDispatcher_SetRetransmitOnCcaFail_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacDispatcher_GetRetransmitOnCcaFail_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetRetransmitOnCcaFail_Input_struct_t data;
} gpMacDispatcher_GetRetransmitOnCcaFail_Input_marshall_struct_t;

typedef struct {
    Bool enable;
} gpMacDispatcher_GetRetransmitOnCcaFail_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetRetransmitOnCcaFail_Output_struct_t data;
} gpMacDispatcher_GetRetransmitOnCcaFail_Output_marshall_struct_t;


typedef struct {
    Bool enable;
    gpMacCore_StackId_t stackId;
} gpMacDispatcher_SetRetransmitRandomBackoff_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetRetransmitRandomBackoff_Input_struct_t data;
} gpMacDispatcher_SetRetransmitRandomBackoff_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacDispatcher_GetRetransmitRandomBackoff_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetRetransmitRandomBackoff_Input_struct_t data;
} gpMacDispatcher_GetRetransmitRandomBackoff_Input_marshall_struct_t;

typedef struct {
    Bool enable;
} gpMacDispatcher_GetRetransmitRandomBackoff_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetRetransmitRandomBackoff_Output_struct_t data;
} gpMacDispatcher_GetRetransmitRandomBackoff_Output_marshall_struct_t;


typedef struct {
    UInt8 minBERetransmit;
    gpMacCore_StackId_t stackId;
} gpMacDispatcher_SetMinBeRetransmit_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetMinBeRetransmit_Input_struct_t data;
} gpMacDispatcher_SetMinBeRetransmit_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacDispatcher_GetMinBeRetransmit_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetMinBeRetransmit_Input_struct_t data;
} gpMacDispatcher_GetMinBeRetransmit_Input_marshall_struct_t;

typedef struct {
    UInt8 minBERetransmit;
} gpMacDispatcher_GetMinBeRetransmit_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetMinBeRetransmit_Output_struct_t data;
} gpMacDispatcher_GetMinBeRetransmit_Output_marshall_struct_t;


typedef struct {
    UInt8 maxBERetransmit;
    gpMacCore_StackId_t stackId;
} gpMacDispatcher_SetMaxBeRetransmit_Input_struct_t;

typedef struct {
    gpMacDispatcher_SetMaxBeRetransmit_Input_struct_t data;
} gpMacDispatcher_SetMaxBeRetransmit_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacDispatcher_GetMaxBeRetransmit_Input_struct_t;

typedef struct {
    gpMacDispatcher_GetMaxBeRetransmit_Input_struct_t data;
} gpMacDispatcher_GetMaxBeRetransmit_Input_marshall_struct_t;

typedef struct {
    UInt8 maxBERetransmit;
} gpMacDispatcher_GetMaxBeRetransmit_Output_struct_t;

typedef struct {
    gpMacDispatcher_GetMaxBeRetransmit_Output_struct_t data;
} gpMacDispatcher_GetMaxBeRetransmit_Output_marshall_struct_t;


typedef struct {
    gpMacCore_Result_t status;
    gpPd_Handle_t pdHandle;
    gpMacDispatcher_StackId_t stackId;
} MacDispatcher_cbDataConfirm_Input_struct_t;

typedef struct {
    MacDispatcher_cbDataConfirm_Input_struct_t data;
} MacDispatcher_cbDataConfirm_Input_marshall_struct_t;


typedef struct {
    gpMacCore_AddressInfo_t* pSrcAddrInfo;
    gpMacCore_AddressInfo_t* pDstAddrInfo;
    UInt8 dsn;
    gpMacCore_Security_t* pSecOptions;
    gpPd_Loh_t pdLoh;
    gpMacDispatcher_StackId_t stackId;
} MacDispatcher_cbDataIndication_Input_struct_t;

typedef struct {
    MacDispatcher_cbDataIndication_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pSrcAddrInfo;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pDstAddrInfo;
    gpMacCore_Security_t_l1_pointer_marshall_t pSecOptions;
    gpPd_Loh_t_l1_pointer_marshall_t pdLoh;
} MacDispatcher_cbDataIndication_Input_marshall_struct_t;


typedef struct {
    gpMacCore_Result_t status;
    gpMacCore_ScanType_t scanType;
    UInt32 unscannedChannels;
    UInt8 resultListSize;
    UInt8* pEdScanResultList;
    gpMacDispatcher_StackId_t stackId;
} MacDispatcher_cbScanConfirm_Input_struct_t;

typedef struct {
    MacDispatcher_cbScanConfirm_Input_struct_t data;
} MacDispatcher_cbScanConfirm_Input_marshall_struct_t;


typedef struct {
    gpMacCore_Address_t* pDeviceAddress;
    UInt8 capabilityInformation;
    gpPd_TimeStamp_t rxTime;
    gpMacDispatcher_StackId_t stackId;
} MacDispatcher_cbAssociateIndication_Input_struct_t;

typedef struct {
    MacDispatcher_cbAssociateIndication_Input_struct_t data;
    gpMacCore_Address_t_l1_pointer_marshall_t pDeviceAddress;
} MacDispatcher_cbAssociateIndication_Input_marshall_struct_t;


typedef struct {
    UInt16 assocShortAddress;
    gpMacCore_Result_t status;
    gpPd_TimeStamp_t txTime;
    gpMacDispatcher_StackId_t stackId;
} MacDispatcher_cbAssociateConfirm_Input_struct_t;

typedef struct {
    MacDispatcher_cbAssociateConfirm_Input_struct_t data;
} MacDispatcher_cbAssociateConfirm_Input_marshall_struct_t;


typedef struct {
    gpMacCore_AddressInfo_t* pSrcAddrInfo;
    gpMacCore_AddressInfo_t* pDstAddrInfo;
    gpMacCore_Result_t status;
    gpPd_TimeStamp_t txTime;
    gpMacDispatcher_StackId_t stackId;
} MacDispatcher_cbAssociateCommStatusIndication_Input_struct_t;

typedef struct {
    MacDispatcher_cbAssociateCommStatusIndication_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pSrcAddrInfo;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pDstAddrInfo;
} MacDispatcher_cbAssociateCommStatusIndication_Input_marshall_struct_t;


typedef struct {
    gpMacCore_Result_t status;
    gpMacCore_AddressInfo_t* coordAddrInfo;
    gpPd_TimeStamp_t txTime;
    gpMacDispatcher_StackId_t stackId;
} MacDispatcher_cbPollConfirm_Input_struct_t;

typedef struct {
    MacDispatcher_cbPollConfirm_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t coordAddrInfo;
} MacDispatcher_cbPollConfirm_Input_marshall_struct_t;


typedef struct {
    gpMacCore_AddressInfo_t* addressInfo;
    gpPd_TimeStamp_t rxTime;
    gpMacDispatcher_StackId_t stackId;
} MacDispatcher_cbPollIndication_Input_struct_t;

typedef struct {
    MacDispatcher_cbPollIndication_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t addressInfo;
} MacDispatcher_cbPollIndication_Input_marshall_struct_t;


typedef struct {
    gpMacCore_Result_t status;
    gpPd_Handle_t pdHandle;
    gpMacDispatcher_StackId_t stackId;
} MacDispatcher_cbPurgeConfirm_Input_struct_t;

typedef struct {
    MacDispatcher_cbPurgeConfirm_Input_struct_t data;
} MacDispatcher_cbPurgeConfirm_Input_marshall_struct_t;


typedef struct {
    UInt8 bsn;
    gpMacCore_PanDescriptor_t* pPanDescriptor;
    UInt8 beaconPayloadLength;
    UInt8* pBeaconPayload;
    gpMacDispatcher_StackId_t stackId;
} MacDispatcher_cbBeaconNotifyIndication_Input_struct_t;

typedef struct {
    MacDispatcher_cbBeaconNotifyIndication_Input_struct_t data;
    gpMacCore_PanDescriptor_t_l1_pointer_marshall_t pPanDescriptor;
    UInt8 pBeaconPayload[GP_MACCORE_MAX_BEACON_PAYLOAD_LENGTH];
} MacDispatcher_cbBeaconNotifyIndication_Input_marshall_struct_t;


typedef struct {
    MACAddress_t* pOrphanAddress;
    gpPd_TimeStamp_t rxTime;
    gpMacDispatcher_StackId_t stackId;
} MacDispatcher_cbOrphanIndication_Input_struct_t;

typedef struct {
    MacDispatcher_cbOrphanIndication_Input_struct_t data;
    MACAddress_t pOrphanAddress[1];
} MacDispatcher_cbOrphanIndication_Input_marshall_struct_t;


typedef struct {
    gpMacCore_AddressInfo_t* pSrcAddrInfo;
    gpMacCore_AddressInfo_t* pDstAddrInfo;
    gpMacCore_Result_t status;
    gpPd_TimeStamp_t txTime;
    gpMacDispatcher_StackId_t stackId;
} MacDispatcher_cbOrphanCommStatusIndication_Input_struct_t;

typedef struct {
    MacDispatcher_cbOrphanCommStatusIndication_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pSrcAddrInfo;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pDstAddrInfo;
} MacDispatcher_cbOrphanCommStatusIndication_Input_marshall_struct_t;


typedef struct {
    gpMacCore_AddressInfo_t* pSrcAddrInfo;
    gpMacCore_AddressInfo_t* pDstAddrInfo;
    gpMacCore_Result_t status;
    gpPd_TimeStamp_t txTime;
    gpMacDispatcher_StackId_t stackId;
} MacDispatcher_cbSecurityFailureCommStatusIndication_Input_struct_t;

typedef struct {
    MacDispatcher_cbSecurityFailureCommStatusIndication_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pSrcAddrInfo;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pDstAddrInfo;
} MacDispatcher_cbSecurityFailureCommStatusIndication_Input_marshall_struct_t;


typedef struct {
    gpMacDispatcher_Result_t status;
    gpMacDispatcher_StackId_t stackId;
} MacDispatcher_cbDriverResetIndication_Input_struct_t;

typedef struct {
    MacDispatcher_cbDriverResetIndication_Input_struct_t data;
} MacDispatcher_cbDriverResetIndication_Input_marshall_struct_t;


typedef struct {
    gpMacCore_AddressInfo_t* addressInfo;
    gpPd_TimeStamp_t rxTime;
    gpPd_Handle_t pdHandle;
    Bool fromNeighbour;
    gpMacDispatcher_StackId_t stackId;
} MacDispatcher_cbPollNotify_Input_struct_t;

typedef struct {
    MacDispatcher_cbPollNotify_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t addressInfo;
} MacDispatcher_cbPollNotify_Input_marshall_struct_t;


typedef struct {
    UInt32 frameCounter;
    gpMacDispatcher_StackId_t stackId;
} MacDispatcher_cbSecurityFrameCounterIndication_Input_struct_t;

typedef struct {
    MacDispatcher_cbSecurityFrameCounterIndication_Input_struct_t data;
} MacDispatcher_cbSecurityFrameCounterIndication_Input_marshall_struct_t;


typedef union {
    gpMacDispatcher_RegisterNetworkStack_Input_marshall_struct_t gpMacDispatcher_RegisterNetworkStack;
    gpMacDispatcher_UnRegisterNetworkStack_Input_marshall_struct_t gpMacDispatcher_UnRegisterNetworkStack;
    gpMacDispatcher_RegisterCallbacks_Input_marshall_struct_t gpMacDispatcher_RegisterCallbacks;
    gpMacDispatcher_LockClaim_Input_marshall_struct_t gpMacDispatcher_LockClaim;
    gpMacDispatcher_LockRelease_Input_marshall_struct_t gpMacDispatcher_LockRelease;
    gpMacDispatcher_LockedByThisStack_Input_marshall_struct_t gpMacDispatcher_LockedByThisStack;
    gpMacDispatcher_Reset_Input_marshall_struct_t gpMacDispatcher_Reset;
    gpMacDispatcher_DataRequest_Input_marshall_struct_t gpMacDispatcher_DataRequest;
    gpMacDispatcher_ScanRequest_Input_marshall_struct_t gpMacDispatcher_ScanRequest;
    gpMacDispatcher_AssociateRequest_Input_marshall_struct_t gpMacDispatcher_AssociateRequest;
    gpMacDispatcher_AssociateResponse_Input_marshall_struct_t gpMacDispatcher_AssociateResponse;
    gpMacDispatcher_PollRequest_Input_marshall_struct_t gpMacDispatcher_PollRequest;
    gpMacDispatcher_PurgeRequest_Input_marshall_struct_t gpMacDispatcher_PurgeRequest;
    gpMacDispatcher_Start_Input_marshall_struct_t gpMacDispatcher_Start;
    gpMacDispatcher_OrphanResponse_Input_marshall_struct_t gpMacDispatcher_OrphanResponse;
    gpMacDispatcher_SetPanId_Input_marshall_struct_t gpMacDispatcher_SetPanId;
    gpMacDispatcher_GetPanId_Input_marshall_struct_t gpMacDispatcher_GetPanId;
    gpMacDispatcher_SetShortAddress_Input_marshall_struct_t gpMacDispatcher_SetShortAddress;
    gpMacDispatcher_GetShortAddress_Input_marshall_struct_t gpMacDispatcher_GetShortAddress;
    gpMacDispatcher_SetExtendedAddress_Input_marshall_struct_t gpMacDispatcher_SetExtendedAddress;
    gpMacDispatcher_GetExtendedAddress_Input_marshall_struct_t gpMacDispatcher_GetExtendedAddress;
    gpMacDispatcher_SetDsn_Input_marshall_struct_t gpMacDispatcher_SetDsn;
    gpMacDispatcher_GetDsn_Input_marshall_struct_t gpMacDispatcher_GetDsn;
    gpMacDispatcher_SetCurrentChannel_Input_marshall_struct_t gpMacDispatcher_SetCurrentChannel;
    gpMacDispatcher_GetCurrentChannel_Input_marshall_struct_t gpMacDispatcher_GetCurrentChannel;
    gpMacDispatcher_SetBeaconPayload_Input_marshall_struct_t gpMacDispatcher_SetBeaconPayload;
    gpMacDispatcher_GetBeaconPayload_Input_marshall_struct_t gpMacDispatcher_GetBeaconPayload;
    gpMacDispatcher_SetBeaconPayloadLength_Input_marshall_struct_t gpMacDispatcher_SetBeaconPayloadLength;
    gpMacDispatcher_GetBeaconPayloadLength_Input_marshall_struct_t gpMacDispatcher_GetBeaconPayloadLength;
    gpMacDispatcher_SetRxOnWhenIdle_Input_marshall_struct_t gpMacDispatcher_SetRxOnWhenIdle;
    gpMacDispatcher_GetRxOnWhenIdle_Input_marshall_struct_t gpMacDispatcher_GetRxOnWhenIdle;
    gpMacDispatcher_GetTransactionPersistenceTime_Input_marshall_struct_t gpMacDispatcher_GetTransactionPersistenceTime;
    gpMacDispatcher_SetTransactionPersistenceTime_Input_marshall_struct_t gpMacDispatcher_SetTransactionPersistenceTime;
    gpMacDispatcher_SetBeaconStarted_Input_marshall_struct_t gpMacDispatcher_SetBeaconStarted;
    gpMacDispatcher_GetBeaconStarted_Input_marshall_struct_t gpMacDispatcher_GetBeaconStarted;
    gpMacDispatcher_SetCoordShortAddress_Input_marshall_struct_t gpMacDispatcher_SetCoordShortAddress;
    gpMacDispatcher_GetCoordShortAddress_Input_marshall_struct_t gpMacDispatcher_GetCoordShortAddress;
    gpMacDispatcher_SetCoordExtendedAddress_Input_marshall_struct_t gpMacDispatcher_SetCoordExtendedAddress;
    gpMacDispatcher_GetCoordExtendedAddress_Input_marshall_struct_t gpMacDispatcher_GetCoordExtendedAddress;
    gpMacDispatcher_SetPromiscuousMode_Input_marshall_struct_t gpMacDispatcher_SetPromiscuousMode;
    gpMacDispatcher_GetPromiscuousMode_Input_marshall_struct_t gpMacDispatcher_GetPromiscuousMode;
    gpMacDispatcher_SetAssociationPermit_Input_marshall_struct_t gpMacDispatcher_SetAssociationPermit;
    gpMacDispatcher_GetAssociationPermit_Input_marshall_struct_t gpMacDispatcher_GetAssociationPermit;
    gpMacDispatcher_SetSecurityEnabled_Input_marshall_struct_t gpMacDispatcher_SetSecurityEnabled;
    gpMacDispatcher_GetSecurityEnabled_Input_marshall_struct_t gpMacDispatcher_GetSecurityEnabled;
    gpMacDispatcher_SetNumberOfRetries_Input_marshall_struct_t gpMacDispatcher_SetNumberOfRetries;
    gpMacDispatcher_GetNumberOfRetries_Input_marshall_struct_t gpMacDispatcher_GetNumberOfRetries;
    gpMacDispatcher_SetMaxCsmaBackoffs_Input_marshall_struct_t gpMacDispatcher_SetMaxCsmaBackoffs;
    gpMacDispatcher_GetMaxCsmaBackoffs_Input_marshall_struct_t gpMacDispatcher_GetMaxCsmaBackoffs;
    gpMacDispatcher_SetDefaultTransmitPowers_Input_marshall_struct_t gpMacDispatcher_SetDefaultTransmitPowers;
    gpMacDispatcher_SetTransmitPower_Input_marshall_struct_t gpMacDispatcher_SetTransmitPower;
    gpMacDispatcher_GetTransmitPower_Input_marshall_struct_t gpMacDispatcher_GetTransmitPower;
    gpMacDispatcher_SetCCAMode_Input_marshall_struct_t gpMacDispatcher_SetCCAMode;
    gpMacDispatcher_GetCCAMode_Input_marshall_struct_t gpMacDispatcher_GetCCAMode;
    gpMacDispatcher_SetPanCoordinator_Input_marshall_struct_t gpMacDispatcher_SetPanCoordinator;
    gpMacDispatcher_GetPanCoordinator_Input_marshall_struct_t gpMacDispatcher_GetPanCoordinator;
    gpMacDispatcher_SetMinBE_Input_marshall_struct_t gpMacDispatcher_SetMinBE;
    gpMacDispatcher_GetMinBE_Input_marshall_struct_t gpMacDispatcher_GetMinBE;
    gpMacDispatcher_SetIndicateBeaconNotifications_Input_marshall_struct_t gpMacDispatcher_SetIndicateBeaconNotifications;
    gpMacDispatcher_GetIndicateBeaconNotifications_Input_marshall_struct_t gpMacDispatcher_GetIndicateBeaconNotifications;
    gpMacDispatcher_SetMacVersion_Input_marshall_struct_t gpMacDispatcher_SetMacVersion;
    gpMacDispatcher_GetMacVersion_Input_marshall_struct_t gpMacDispatcher_GetMacVersion;
    gpMacDispatcher_SetForwardPollIndications_Input_marshall_struct_t gpMacDispatcher_SetForwardPollIndications;
    gpMacDispatcher_GetForwardPollIndications_Input_marshall_struct_t gpMacDispatcher_GetForwardPollIndications;
    gpMacDispatcher_DataPending_QueueAdd_Input_marshall_struct_t gpMacDispatcher_DataPending_QueueAdd;
    gpMacDispatcher_DataPending_QueueRemove_Input_marshall_struct_t gpMacDispatcher_DataPending_QueueRemove;
    gpMacDispatcher_SetMinInterferenceLevels_Input_marshall_struct_t gpMacDispatcher_SetMinInterferenceLevels;
    gpMacDispatcher_SetMaxBE_Input_marshall_struct_t gpMacDispatcher_SetMaxBE;
    gpMacDispatcher_GetMaxBE_Input_marshall_struct_t gpMacDispatcher_GetMaxBE;
    gpMacDispatcher_SetDeviceDescriptor_Input_marshall_struct_t gpMacDispatcher_SetDeviceDescriptor;
    gpMacDispatcher_GetDeviceDescriptor_Input_marshall_struct_t gpMacDispatcher_GetDeviceDescriptor;
    gpMacDispatcher_SetDeviceTableEntries_Input_marshall_struct_t gpMacDispatcher_SetDeviceTableEntries;
    gpMacDispatcher_GetDeviceTableEntries_Input_marshall_struct_t gpMacDispatcher_GetDeviceTableEntries;
    gpMacDispatcher_SetKeyDescriptor_Input_marshall_struct_t gpMacDispatcher_SetKeyDescriptor;
    gpMacDispatcher_GetKeyDescriptor_Input_marshall_struct_t gpMacDispatcher_GetKeyDescriptor;
    gpMacDispatcher_SetKeyTableEntries_Input_marshall_struct_t gpMacDispatcher_SetKeyTableEntries;
    gpMacDispatcher_SetSecurityLevelDescriptor_Input_marshall_struct_t gpMacDispatcher_SetSecurityLevelDescriptor;
    gpMacDispatcher_GetSecurityLevelDescriptor_Input_marshall_struct_t gpMacDispatcher_GetSecurityLevelDescriptor;
    gpMacDispatcher_SetSecurityLevelTableEntries_Input_marshall_struct_t gpMacDispatcher_SetSecurityLevelTableEntries;
    gpMacDispatcher_GetSecurityLevelTableEntries_Input_marshall_struct_t gpMacDispatcher_GetSecurityLevelTableEntries;
    gpMacDispatcher_SetDefaultKeySource_Input_marshall_struct_t gpMacDispatcher_SetDefaultKeySource;
    gpMacDispatcher_SetFrameCounter_Input_marshall_struct_t gpMacDispatcher_SetFrameCounter;
    gpMacDispatcher_GetFrameCounter_Input_marshall_struct_t gpMacDispatcher_GetFrameCounter;
    gpMacDispatcher_SetPanCoordShortAddress_Input_marshall_struct_t gpMacDispatcher_SetPanCoordShortAddress;
    gpMacDispatcher_SetPanCoordExtendedAddress_Input_marshall_struct_t gpMacDispatcher_SetPanCoordExtendedAddress;
    gpMacDispatcher_GetPanCoordExtendedAddress_Input_marshall_struct_t gpMacDispatcher_GetPanCoordExtendedAddress;
    gpMacDispatcher_AddNeighbour_Input_marshall_struct_t gpMacDispatcher_AddNeighbour;
    gpMacDispatcher_RemoveNeighbour_Input_marshall_struct_t gpMacDispatcher_RemoveNeighbour;
    gpMacDispatcher_SetDataPendingMode_Input_marshall_struct_t gpMacDispatcher_SetDataPendingMode;
    gpMacDispatcher_SetAddressModeOverrideForBeacons_Input_marshall_struct_t gpMacDispatcher_SetAddressModeOverrideForBeacons;
    gpMacDispatcher_ClearNeighbours_Input_marshall_struct_t gpMacDispatcher_ClearNeighbours;
    gpMacDispatcher_GetCallbacks_Input_marshall_struct_t gpMacDispatcher_GetCallbacks;
    gpMacDispatcher_IsValidStack_Input_marshall_struct_t gpMacDispatcher_IsValidStack;
    gpMacDispatcher_SetCsmaMode_Input_marshall_struct_t gpMacDispatcher_SetCsmaMode;
    gpMacDispatcher_GetCsmaMode_Input_marshall_struct_t gpMacDispatcher_GetCsmaMode;
    gpMacDispatcher_DataPending_QueueClear_Input_marshall_struct_t gpMacDispatcher_DataPending_QueueClear;
    gpMacDispatcher_ScheduleTimedTx_Input_marshall_struct_t gpMacDispatcher_ScheduleTimedTx;
    gpMacDispatcher_SetStackInRawMode_Input_marshall_struct_t gpMacDispatcher_SetStackInRawMode;
    gpMacDispatcher_GetStackInRawMode_Input_marshall_struct_t gpMacDispatcher_GetStackInRawMode;
    gpMacDispatcher_EnableEnhancedFramePending_Input_marshall_struct_t gpMacDispatcher_EnableEnhancedFramePending;
    gpMacDispatcher_EnableRxWindows_Input_marshall_struct_t gpMacDispatcher_EnableRxWindows;
    gpMacDispatcher_DisableRxWindows_Input_marshall_struct_t gpMacDispatcher_DisableRxWindows;
    gpMacDispatcher_EnableCsl_Input_marshall_struct_t gpMacDispatcher_EnableCsl;
    gpMacDispatcher_UpdateCslSampleTime_Input_marshall_struct_t gpMacDispatcher_UpdateCslSampleTime;
    gpMacDispatcher_ConfigureEnhAckProbing_Input_marshall_struct_t gpMacDispatcher_ConfigureEnhAckProbing;
    gpMacDispatcher_SetRetransmitOnCcaFail_Input_marshall_struct_t gpMacDispatcher_SetRetransmitOnCcaFail;
    gpMacDispatcher_GetRetransmitOnCcaFail_Input_marshall_struct_t gpMacDispatcher_GetRetransmitOnCcaFail;
    gpMacDispatcher_SetRetransmitRandomBackoff_Input_marshall_struct_t gpMacDispatcher_SetRetransmitRandomBackoff;
    gpMacDispatcher_GetRetransmitRandomBackoff_Input_marshall_struct_t gpMacDispatcher_GetRetransmitRandomBackoff;
    gpMacDispatcher_SetMinBeRetransmit_Input_marshall_struct_t gpMacDispatcher_SetMinBeRetransmit;
    gpMacDispatcher_GetMinBeRetransmit_Input_marshall_struct_t gpMacDispatcher_GetMinBeRetransmit;
    gpMacDispatcher_SetMaxBeRetransmit_Input_marshall_struct_t gpMacDispatcher_SetMaxBeRetransmit;
    gpMacDispatcher_GetMaxBeRetransmit_Input_marshall_struct_t gpMacDispatcher_GetMaxBeRetransmit;
    UInt8 dummy; //ensure none empty union definition
} gpMacDispatcher_Server_Input_union_t;

typedef union {
    gpMacDispatcher_RegisterNetworkStack_Output_marshall_struct_t gpMacDispatcher_RegisterNetworkStack;
    gpMacDispatcher_UnRegisterNetworkStack_Output_marshall_struct_t gpMacDispatcher_UnRegisterNetworkStack;
    gpMacDispatcher_LockClaim_Output_marshall_struct_t gpMacDispatcher_LockClaim;
    gpMacDispatcher_LockedByThisStack_Output_marshall_struct_t gpMacDispatcher_LockedByThisStack;
    gpMacDispatcher_Locked_Output_marshall_struct_t gpMacDispatcher_Locked;
    gpMacDispatcher_Reset_Output_marshall_struct_t gpMacDispatcher_Reset;
    gpMacDispatcher_Start_Output_marshall_struct_t gpMacDispatcher_Start;
    gpMacDispatcher_GetPanId_Output_marshall_struct_t gpMacDispatcher_GetPanId;
    gpMacDispatcher_GetShortAddress_Output_marshall_struct_t gpMacDispatcher_GetShortAddress;
    gpMacDispatcher_GetExtendedAddress_Output_marshall_struct_t gpMacDispatcher_GetExtendedAddress;
    gpMacDispatcher_GetDsn_Output_marshall_struct_t gpMacDispatcher_GetDsn;
    gpMacDispatcher_GetCurrentChannel_Output_marshall_struct_t gpMacDispatcher_GetCurrentChannel;
    gpMacDispatcher_GetBeaconPayload_Output_marshall_struct_t gpMacDispatcher_GetBeaconPayload;
    gpMacDispatcher_GetBeaconPayloadLength_Output_marshall_struct_t gpMacDispatcher_GetBeaconPayloadLength;
    gpMacDispatcher_GetRxOnWhenIdle_Output_marshall_struct_t gpMacDispatcher_GetRxOnWhenIdle;
    gpMacDispatcher_GetTransactionPersistenceTime_Output_marshall_struct_t gpMacDispatcher_GetTransactionPersistenceTime;
    gpMacDispatcher_GetBeaconStarted_Output_marshall_struct_t gpMacDispatcher_GetBeaconStarted;
    gpMacDispatcher_GetCoordShortAddress_Output_marshall_struct_t gpMacDispatcher_GetCoordShortAddress;
    gpMacDispatcher_GetCoordExtendedAddress_Output_marshall_struct_t gpMacDispatcher_GetCoordExtendedAddress;
    gpMacDispatcher_GetPromiscuousMode_Output_marshall_struct_t gpMacDispatcher_GetPromiscuousMode;
    gpMacDispatcher_GetAssociationPermit_Output_marshall_struct_t gpMacDispatcher_GetAssociationPermit;
    gpMacDispatcher_GetSecurityEnabled_Output_marshall_struct_t gpMacDispatcher_GetSecurityEnabled;
    gpMacDispatcher_GetNumberOfRetries_Output_marshall_struct_t gpMacDispatcher_GetNumberOfRetries;
    gpMacDispatcher_GetMaxCsmaBackoffs_Output_marshall_struct_t gpMacDispatcher_GetMaxCsmaBackoffs;
    gpMacDispatcher_GetTransmitPower_Output_marshall_struct_t gpMacDispatcher_GetTransmitPower;
    gpMacDispatcher_GetCCAMode_Output_marshall_struct_t gpMacDispatcher_GetCCAMode;
    gpMacDispatcher_GetPanCoordinator_Output_marshall_struct_t gpMacDispatcher_GetPanCoordinator;
    gpMacDispatcher_GetMinBE_Output_marshall_struct_t gpMacDispatcher_GetMinBE;
    gpMacDispatcher_GetIndicateBeaconNotifications_Output_marshall_struct_t gpMacDispatcher_GetIndicateBeaconNotifications;
    gpMacDispatcher_GetMacVersion_Output_marshall_struct_t gpMacDispatcher_GetMacVersion;
    gpMacDispatcher_GetForwardPollIndications_Output_marshall_struct_t gpMacDispatcher_GetForwardPollIndications;
    gpMacDispatcher_DataPending_QueueAdd_Output_marshall_struct_t gpMacDispatcher_DataPending_QueueAdd;
    gpMacDispatcher_DataPending_QueueRemove_Output_marshall_struct_t gpMacDispatcher_DataPending_QueueRemove;
    gpMacDispatcher_GetMaxBE_Output_marshall_struct_t gpMacDispatcher_GetMaxBE;
    gpMacDispatcher_SetDeviceDescriptor_Output_marshall_struct_t gpMacDispatcher_SetDeviceDescriptor;
    gpMacDispatcher_GetDeviceDescriptor_Output_marshall_struct_t gpMacDispatcher_GetDeviceDescriptor;
    gpMacDispatcher_GetDeviceTableEntries_Output_marshall_struct_t gpMacDispatcher_GetDeviceTableEntries;
    gpMacDispatcher_SetKeyDescriptor_Output_marshall_struct_t gpMacDispatcher_SetKeyDescriptor;
    gpMacDispatcher_GetKeyDescriptor_Output_marshall_struct_t gpMacDispatcher_GetKeyDescriptor;
    gpMacDispatcher_SetSecurityLevelDescriptor_Output_marshall_struct_t gpMacDispatcher_SetSecurityLevelDescriptor;
    gpMacDispatcher_GetSecurityLevelDescriptor_Output_marshall_struct_t gpMacDispatcher_GetSecurityLevelDescriptor;
    gpMacDispatcher_GetSecurityLevelTableEntries_Output_marshall_struct_t gpMacDispatcher_GetSecurityLevelTableEntries;
    gpMacDispatcher_GetFrameCounter_Output_marshall_struct_t gpMacDispatcher_GetFrameCounter;
    gpMacDispatcher_GetPanCoordExtendedAddress_Output_marshall_struct_t gpMacDispatcher_GetPanCoordExtendedAddress;
    gpMacDispatcher_AddNeighbour_Output_marshall_struct_t gpMacDispatcher_AddNeighbour;
    gpMacDispatcher_RemoveNeighbour_Output_marshall_struct_t gpMacDispatcher_RemoveNeighbour;
    gpMacDispatcher_SetDataPendingMode_Output_marshall_struct_t gpMacDispatcher_SetDataPendingMode;
    gpMacDispatcher_GetCallbacks_Output_marshall_struct_t gpMacDispatcher_GetCallbacks;
    gpMacDispatcher_IsValidStack_Output_marshall_struct_t gpMacDispatcher_IsValidStack;
    gpMacDispatcher_GetCsmaMode_Output_marshall_struct_t gpMacDispatcher_GetCsmaMode;
    gpMacDispatcher_DataPending_QueueClear_Output_marshall_struct_t gpMacDispatcher_DataPending_QueueClear;
    gpMacDispatcher_ScheduleTimedTx_Output_marshall_struct_t gpMacDispatcher_ScheduleTimedTx;
    gpMacDispatcher_GetStackInRawMode_Output_marshall_struct_t gpMacDispatcher_GetStackInRawMode;
    gpMacDispatcher_GetCurrentTimeUs_Output_marshall_struct_t gpMacDispatcher_GetCurrentTimeUs;
    gpMacDispatcher_ConfigureEnhAckProbing_Output_marshall_struct_t gpMacDispatcher_ConfigureEnhAckProbing;
    gpMacDispatcher_GetRetransmitOnCcaFail_Output_marshall_struct_t gpMacDispatcher_GetRetransmitOnCcaFail;
    gpMacDispatcher_GetRetransmitRandomBackoff_Output_marshall_struct_t gpMacDispatcher_GetRetransmitRandomBackoff;
    gpMacDispatcher_GetMinBeRetransmit_Output_marshall_struct_t gpMacDispatcher_GetMinBeRetransmit;
    gpMacDispatcher_GetMaxBeRetransmit_Output_marshall_struct_t gpMacDispatcher_GetMaxBeRetransmit;
    UInt8 dummy; //ensure none empty union definition
} gpMacDispatcher_Server_Output_union_t;

typedef union {
    MacDispatcher_cbDataConfirm_Input_marshall_struct_t MacDispatcher_cbDataConfirm;
    MacDispatcher_cbDataIndication_Input_marshall_struct_t MacDispatcher_cbDataIndication;
    MacDispatcher_cbScanConfirm_Input_marshall_struct_t MacDispatcher_cbScanConfirm;
    MacDispatcher_cbAssociateIndication_Input_marshall_struct_t MacDispatcher_cbAssociateIndication;
    MacDispatcher_cbAssociateConfirm_Input_marshall_struct_t MacDispatcher_cbAssociateConfirm;
    MacDispatcher_cbAssociateCommStatusIndication_Input_marshall_struct_t MacDispatcher_cbAssociateCommStatusIndication;
    MacDispatcher_cbPollConfirm_Input_marshall_struct_t MacDispatcher_cbPollConfirm;
    MacDispatcher_cbPollIndication_Input_marshall_struct_t MacDispatcher_cbPollIndication;
    MacDispatcher_cbPurgeConfirm_Input_marshall_struct_t MacDispatcher_cbPurgeConfirm;
    MacDispatcher_cbBeaconNotifyIndication_Input_marshall_struct_t MacDispatcher_cbBeaconNotifyIndication;
    MacDispatcher_cbOrphanIndication_Input_marshall_struct_t MacDispatcher_cbOrphanIndication;
    MacDispatcher_cbOrphanCommStatusIndication_Input_marshall_struct_t MacDispatcher_cbOrphanCommStatusIndication;
    MacDispatcher_cbSecurityFailureCommStatusIndication_Input_marshall_struct_t MacDispatcher_cbSecurityFailureCommStatusIndication;
    MacDispatcher_cbDriverResetIndication_Input_marshall_struct_t MacDispatcher_cbDriverResetIndication;
    MacDispatcher_cbPollNotify_Input_marshall_struct_t MacDispatcher_cbPollNotify;
    MacDispatcher_cbSecurityFrameCounterIndication_Input_marshall_struct_t MacDispatcher_cbSecurityFrameCounterIndication;
    UInt8 dummy; //ensure none empty union definition
} gpMacDispatcher_Client_Input_union_t;

/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

// Alias/enum copy macro's
#define gpMacDispatcher_StackId_t_buf2api(pDest, pSource, length, pIndex) UInt8_buf2api(pDest, pSource, length, pIndex)
#define gpMacDispatcher_StackId_t_api2buf(pDest, pSource, length, pIndex) UInt8_api2buf(pDest, pSource, length, pIndex)
#define gpMacDispatcher_StackId_t_buf2api_1(pDest, pSource, pIndex)       UInt8_buf2api_1(pDest, pSource, pIndex)
#define gpMacDispatcher_StackId_t_api2buf_1(pDest, pSource, pIndex)       UInt8_api2buf_1(pDest, pSource, pIndex)
#define gpMacDispatcher_Result_t_buf2api(pDest, pSource, length, pIndex) gpMacCore_Result_t_buf2api(pDest, pSource, length, pIndex)
#define gpMacDispatcher_Result_t_api2buf(pDest, pSource, length, pIndex) gpMacCore_Result_t_api2buf(pDest, pSource, length, pIndex)
#define gpMacDispatcher_Result_t_buf2api_1(pDest, pSource, pIndex)       gpMacCore_Result_t_buf2api_1(pDest, pSource, pIndex)
#define gpMacDispatcher_Result_t_api2buf_1(pDest, pSource, pIndex)       gpMacCore_Result_t_api2buf_1(pDest, pSource, pIndex)
#define gpMacDispatcher_cbDataIndication_t_buf2api(pDest, pSource, length, pIndex) generic_buf2api(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbDataIndication_t_api2buf(pDest, pSource, length, pIndex) generic_api2buf(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbDataIndication_t_buf2api_1(pDest, pSource, pIndex)       generic_buf2api_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbDataIndication_t_api2buf_1(pDest, pSource, pIndex)       generic_api2buf_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbDataConfirm_t_buf2api(pDest, pSource, length, pIndex) generic_buf2api(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbDataConfirm_t_api2buf(pDest, pSource, length, pIndex) generic_api2buf(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbDataConfirm_t_buf2api_1(pDest, pSource, pIndex)       generic_buf2api_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbDataConfirm_t_api2buf_1(pDest, pSource, pIndex)       generic_api2buf_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbPollIndication_t_buf2api(pDest, pSource, length, pIndex) generic_buf2api(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbPollIndication_t_api2buf(pDest, pSource, length, pIndex) generic_api2buf(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbPollIndication_t_buf2api_1(pDest, pSource, pIndex)       generic_buf2api_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbPollIndication_t_api2buf_1(pDest, pSource, pIndex)       generic_api2buf_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbPollConfirm_t_buf2api(pDest, pSource, length, pIndex) generic_buf2api(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbPollConfirm_t_api2buf(pDest, pSource, length, pIndex) generic_api2buf(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbPollConfirm_t_buf2api_1(pDest, pSource, pIndex)       generic_buf2api_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbPollConfirm_t_api2buf_1(pDest, pSource, pIndex)       generic_api2buf_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbPurgeConfirm_t_buf2api(pDest, pSource, length, pIndex) generic_buf2api(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbPurgeConfirm_t_api2buf(pDest, pSource, length, pIndex) generic_api2buf(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbPurgeConfirm_t_buf2api_1(pDest, pSource, pIndex)       generic_buf2api_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbPurgeConfirm_t_api2buf_1(pDest, pSource, pIndex)       generic_api2buf_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbBeaconNotifyIndication_t_buf2api(pDest, pSource, length, pIndex) generic_buf2api(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbBeaconNotifyIndication_t_api2buf(pDest, pSource, length, pIndex) generic_api2buf(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbBeaconNotifyIndication_t_buf2api_1(pDest, pSource, pIndex)       generic_buf2api_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbBeaconNotifyIndication_t_api2buf_1(pDest, pSource, pIndex)       generic_api2buf_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbScanConfirm_t_buf2api(pDest, pSource, length, pIndex) generic_buf2api(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbScanConfirm_t_api2buf(pDest, pSource, length, pIndex) generic_api2buf(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbScanConfirm_t_buf2api_1(pDest, pSource, pIndex)       generic_buf2api_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbScanConfirm_t_api2buf_1(pDest, pSource, pIndex)       generic_api2buf_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbAssociateIndication_t_buf2api(pDest, pSource, length, pIndex) generic_buf2api(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbAssociateIndication_t_api2buf(pDest, pSource, length, pIndex) generic_api2buf(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbAssociateIndication_t_buf2api_1(pDest, pSource, pIndex)       generic_buf2api_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbAssociateIndication_t_api2buf_1(pDest, pSource, pIndex)       generic_api2buf_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbAssocConfirm_t_buf2api(pDest, pSource, length, pIndex) generic_buf2api(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbAssocConfirm_t_api2buf(pDest, pSource, length, pIndex) generic_api2buf(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbAssocConfirm_t_buf2api_1(pDest, pSource, pIndex)       generic_buf2api_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbAssocConfirm_t_api2buf_1(pDest, pSource, pIndex)       generic_api2buf_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbOrphanIndication_t_buf2api(pDest, pSource, length, pIndex) generic_buf2api(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbOrphanIndication_t_api2buf(pDest, pSource, length, pIndex) generic_api2buf(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbOrphanIndication_t_buf2api_1(pDest, pSource, pIndex)       generic_buf2api_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbOrphanIndication_t_api2buf_1(pDest, pSource, pIndex)       generic_api2buf_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbSecurityFailureCommStatusIndication_t_buf2api(pDest, pSource, length, pIndex) generic_buf2api(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbSecurityFailureCommStatusIndication_t_api2buf(pDest, pSource, length, pIndex) generic_api2buf(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbSecurityFailureCommStatusIndication_t_buf2api_1(pDest, pSource, pIndex)       generic_buf2api_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbSecurityFailureCommStatusIndication_t_api2buf_1(pDest, pSource, pIndex)       generic_api2buf_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbAssociateCommStatusIndication_t_buf2api(pDest, pSource, length, pIndex) generic_buf2api(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbAssociateCommStatusIndication_t_api2buf(pDest, pSource, length, pIndex) generic_api2buf(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbAssociateCommStatusIndication_t_buf2api_1(pDest, pSource, pIndex)       generic_buf2api_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbAssociateCommStatusIndication_t_api2buf_1(pDest, pSource, pIndex)       generic_api2buf_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbOrphanCommStatusIndication_t_buf2api(pDest, pSource, length, pIndex) generic_buf2api(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbOrphanCommStatusIndication_t_api2buf(pDest, pSource, length, pIndex) generic_api2buf(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbOrphanCommStatusIndication_t_buf2api_1(pDest, pSource, pIndex)       generic_buf2api_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbOrphanCommStatusIndication_t_api2buf_1(pDest, pSource, pIndex)       generic_api2buf_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbDriverResetIndication_t_buf2api(pDest, pSource, length, pIndex) generic_buf2api(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbDriverResetIndication_t_api2buf(pDest, pSource, length, pIndex) generic_api2buf(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbDriverResetIndication_t_buf2api_1(pDest, pSource, pIndex)       generic_buf2api_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbDriverResetIndication_t_api2buf_1(pDest, pSource, pIndex)       generic_api2buf_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbPollNotify_t_buf2api(pDest, pSource, length, pIndex) generic_buf2api(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbPollNotify_t_api2buf(pDest, pSource, length, pIndex) generic_api2buf(pDest, pSource, length, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbPollNotify_t_buf2api_1(pDest, pSource, pIndex)       generic_buf2api_1(pDest, pSource, pIndex,sizeof(void (*)(void)))
#define gpMacDispatcher_cbPollNotify_t_api2buf_1(pDest, pSource, pIndex)       generic_api2buf_1(pDest, pSource, pIndex,sizeof(void (*)(void)))

// Structure copy functions
gpMarshall_AckStatus_t gpMacDispatcher_StringIdentifier_t_buf2api(gpMacDispatcher_StringIdentifier_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex );
void gpMacDispatcher_StringIdentifier_t_api2buf(UInt8Buffer* pDest , const gpMacDispatcher_StringIdentifier_t* pSource , UInt16 length , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_Callbacks_t_buf2api(gpMacDispatcher_Callbacks_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex );
void gpMacDispatcher_Callbacks_t_api2buf(UInt8Buffer* pDest , const gpMacDispatcher_Callbacks_t* pSource , UInt16 length , UInt16* pIndex);
// Server functions
gpMarshall_AckStatus_t gpMacDispatcher_RegisterNetworkStack_Input_buf2api(gpMacDispatcher_RegisterNetworkStack_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_RegisterNetworkStack_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_RegisterNetworkStack_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_RegisterNetworkStack_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_UnRegisterNetworkStack_Input_buf2api(gpMacDispatcher_UnRegisterNetworkStack_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_UnRegisterNetworkStack_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_UnRegisterNetworkStack_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_UnRegisterNetworkStack_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_RegisterCallbacks_Input_buf2api(gpMacDispatcher_RegisterCallbacks_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_LockClaim_Input_buf2api(gpMacDispatcher_LockClaim_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_LockClaim_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_LockClaim_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_LockClaim_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_LockRelease_Input_buf2api(gpMacDispatcher_LockRelease_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_LockedByThisStack_Input_buf2api(gpMacDispatcher_LockedByThisStack_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_LockedByThisStack_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_LockedByThisStack_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_LockedByThisStack_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
void gpMacDispatcher_Locked_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_Locked_Output_marshall_struct_t* pSourceoutput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_Reset_Input_buf2api(gpMacDispatcher_Reset_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_Reset_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_Reset_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_Reset_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_DataRequest_Input_buf2api(gpMacDispatcher_DataRequest_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_ScanRequest_Input_buf2api(gpMacDispatcher_ScanRequest_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_AssociateRequest_Input_buf2api(gpMacDispatcher_AssociateRequest_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_AssociateResponse_Input_buf2api(gpMacDispatcher_AssociateResponse_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_PollRequest_Input_buf2api(gpMacDispatcher_PollRequest_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_PurgeRequest_Input_buf2api(gpMacDispatcher_PurgeRequest_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_Start_Input_buf2api(gpMacDispatcher_Start_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_Start_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_Start_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_Start_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_OrphanResponse_Input_buf2api(gpMacDispatcher_OrphanResponse_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetPanId_Input_buf2api(gpMacDispatcher_SetPanId_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetPanId_Input_buf2api(gpMacDispatcher_GetPanId_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetPanId_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetPanId_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetPanId_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetShortAddress_Input_buf2api(gpMacDispatcher_SetShortAddress_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetShortAddress_Input_buf2api(gpMacDispatcher_GetShortAddress_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetShortAddress_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetShortAddress_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetShortAddress_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetExtendedAddress_Input_buf2api(gpMacDispatcher_SetExtendedAddress_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetExtendedAddress_Input_buf2api(gpMacDispatcher_GetExtendedAddress_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetExtendedAddress_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetExtendedAddress_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetExtendedAddress_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetDsn_Input_buf2api(gpMacDispatcher_SetDsn_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetDsn_Input_buf2api(gpMacDispatcher_GetDsn_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetDsn_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetDsn_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetDsn_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetCurrentChannel_Input_buf2api(gpMacDispatcher_SetCurrentChannel_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetCurrentChannel_Input_buf2api(gpMacDispatcher_GetCurrentChannel_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetCurrentChannel_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetCurrentChannel_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetCurrentChannel_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetBeaconPayload_Input_buf2api(gpMacDispatcher_SetBeaconPayload_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetBeaconPayload_Input_buf2api(gpMacDispatcher_GetBeaconPayload_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetBeaconPayload_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetBeaconPayload_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetBeaconPayload_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetBeaconPayloadLength_Input_buf2api(gpMacDispatcher_SetBeaconPayloadLength_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetBeaconPayloadLength_Input_buf2api(gpMacDispatcher_GetBeaconPayloadLength_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetBeaconPayloadLength_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetBeaconPayloadLength_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetBeaconPayloadLength_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetRxOnWhenIdle_Input_buf2api(gpMacDispatcher_SetRxOnWhenIdle_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetRxOnWhenIdle_Input_buf2api(gpMacDispatcher_GetRxOnWhenIdle_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetRxOnWhenIdle_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetRxOnWhenIdle_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetRxOnWhenIdle_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetTransactionPersistenceTime_Input_buf2api(gpMacDispatcher_GetTransactionPersistenceTime_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetTransactionPersistenceTime_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetTransactionPersistenceTime_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetTransactionPersistenceTime_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetTransactionPersistenceTime_Input_buf2api(gpMacDispatcher_SetTransactionPersistenceTime_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetBeaconStarted_Input_buf2api(gpMacDispatcher_SetBeaconStarted_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetBeaconStarted_Input_buf2api(gpMacDispatcher_GetBeaconStarted_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetBeaconStarted_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetBeaconStarted_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetBeaconStarted_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetCoordShortAddress_Input_buf2api(gpMacDispatcher_SetCoordShortAddress_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetCoordShortAddress_Input_buf2api(gpMacDispatcher_GetCoordShortAddress_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetCoordShortAddress_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetCoordShortAddress_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetCoordShortAddress_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetCoordExtendedAddress_Input_buf2api(gpMacDispatcher_SetCoordExtendedAddress_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetCoordExtendedAddress_Input_buf2api(gpMacDispatcher_GetCoordExtendedAddress_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetCoordExtendedAddress_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetCoordExtendedAddress_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetCoordExtendedAddress_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetPromiscuousMode_Input_buf2api(gpMacDispatcher_SetPromiscuousMode_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetPromiscuousMode_Input_buf2api(gpMacDispatcher_GetPromiscuousMode_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetPromiscuousMode_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetPromiscuousMode_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetPromiscuousMode_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetAssociationPermit_Input_buf2api(gpMacDispatcher_SetAssociationPermit_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetAssociationPermit_Input_buf2api(gpMacDispatcher_GetAssociationPermit_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetAssociationPermit_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetAssociationPermit_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetAssociationPermit_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetSecurityEnabled_Input_buf2api(gpMacDispatcher_SetSecurityEnabled_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetSecurityEnabled_Input_buf2api(gpMacDispatcher_GetSecurityEnabled_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetSecurityEnabled_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetSecurityEnabled_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetSecurityEnabled_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetNumberOfRetries_Input_buf2api(gpMacDispatcher_SetNumberOfRetries_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetNumberOfRetries_Input_buf2api(gpMacDispatcher_GetNumberOfRetries_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetNumberOfRetries_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetNumberOfRetries_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetNumberOfRetries_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetMaxCsmaBackoffs_Input_buf2api(gpMacDispatcher_SetMaxCsmaBackoffs_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetMaxCsmaBackoffs_Input_buf2api(gpMacDispatcher_GetMaxCsmaBackoffs_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetMaxCsmaBackoffs_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetMaxCsmaBackoffs_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetMaxCsmaBackoffs_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetDefaultTransmitPowers_Input_buf2api(gpMacDispatcher_SetDefaultTransmitPowers_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetTransmitPower_Input_buf2api(gpMacDispatcher_SetTransmitPower_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetTransmitPower_Input_buf2api(gpMacDispatcher_GetTransmitPower_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetTransmitPower_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetTransmitPower_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetTransmitPower_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetCCAMode_Input_buf2api(gpMacDispatcher_SetCCAMode_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetCCAMode_Input_buf2api(gpMacDispatcher_GetCCAMode_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetCCAMode_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetCCAMode_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetCCAMode_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetPanCoordinator_Input_buf2api(gpMacDispatcher_SetPanCoordinator_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetPanCoordinator_Input_buf2api(gpMacDispatcher_GetPanCoordinator_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetPanCoordinator_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetPanCoordinator_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetPanCoordinator_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetMinBE_Input_buf2api(gpMacDispatcher_SetMinBE_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetMinBE_Input_buf2api(gpMacDispatcher_GetMinBE_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetMinBE_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetMinBE_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetMinBE_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetIndicateBeaconNotifications_Input_buf2api(gpMacDispatcher_SetIndicateBeaconNotifications_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetIndicateBeaconNotifications_Input_buf2api(gpMacDispatcher_GetIndicateBeaconNotifications_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetIndicateBeaconNotifications_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetIndicateBeaconNotifications_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetIndicateBeaconNotifications_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetMacVersion_Input_buf2api(gpMacDispatcher_SetMacVersion_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetMacVersion_Input_buf2api(gpMacDispatcher_GetMacVersion_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetMacVersion_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetMacVersion_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetMacVersion_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetForwardPollIndications_Input_buf2api(gpMacDispatcher_SetForwardPollIndications_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetForwardPollIndications_Input_buf2api(gpMacDispatcher_GetForwardPollIndications_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetForwardPollIndications_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetForwardPollIndications_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetForwardPollIndications_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_DataPending_QueueAdd_Input_buf2api(gpMacDispatcher_DataPending_QueueAdd_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_DataPending_QueueAdd_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_DataPending_QueueAdd_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_DataPending_QueueAdd_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_DataPending_QueueRemove_Input_buf2api(gpMacDispatcher_DataPending_QueueRemove_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_DataPending_QueueRemove_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_DataPending_QueueRemove_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_DataPending_QueueRemove_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetMinInterferenceLevels_Input_buf2api(gpMacDispatcher_SetMinInterferenceLevels_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetMaxBE_Input_buf2api(gpMacDispatcher_SetMaxBE_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetMaxBE_Input_buf2api(gpMacDispatcher_GetMaxBE_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetMaxBE_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetMaxBE_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetMaxBE_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetDeviceDescriptor_Input_buf2api(gpMacDispatcher_SetDeviceDescriptor_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetDeviceDescriptor_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_SetDeviceDescriptor_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_SetDeviceDescriptor_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetDeviceDescriptor_Input_buf2api(gpMacDispatcher_GetDeviceDescriptor_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetDeviceDescriptor_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetDeviceDescriptor_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetDeviceDescriptor_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetDeviceTableEntries_Input_buf2api(gpMacDispatcher_SetDeviceTableEntries_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetDeviceTableEntries_Input_buf2api(gpMacDispatcher_GetDeviceTableEntries_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetDeviceTableEntries_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetDeviceTableEntries_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetDeviceTableEntries_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetKeyDescriptor_Input_buf2api(gpMacDispatcher_SetKeyDescriptor_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetKeyDescriptor_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_SetKeyDescriptor_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_SetKeyDescriptor_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetKeyDescriptor_Input_buf2api(gpMacDispatcher_GetKeyDescriptor_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetKeyDescriptor_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetKeyDescriptor_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetKeyDescriptor_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetKeyTableEntries_Input_buf2api(gpMacDispatcher_SetKeyTableEntries_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetSecurityLevelDescriptor_Input_buf2api(gpMacDispatcher_SetSecurityLevelDescriptor_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetSecurityLevelDescriptor_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_SetSecurityLevelDescriptor_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_SetSecurityLevelDescriptor_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetSecurityLevelDescriptor_Input_buf2api(gpMacDispatcher_GetSecurityLevelDescriptor_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetSecurityLevelDescriptor_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetSecurityLevelDescriptor_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetSecurityLevelDescriptor_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetSecurityLevelTableEntries_Input_buf2api(gpMacDispatcher_SetSecurityLevelTableEntries_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetSecurityLevelTableEntries_Input_buf2api(gpMacDispatcher_GetSecurityLevelTableEntries_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetSecurityLevelTableEntries_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetSecurityLevelTableEntries_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetSecurityLevelTableEntries_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetDefaultKeySource_Input_buf2api(gpMacDispatcher_SetDefaultKeySource_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetFrameCounter_Input_buf2api(gpMacDispatcher_SetFrameCounter_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetFrameCounter_Input_buf2api(gpMacDispatcher_GetFrameCounter_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetFrameCounter_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetFrameCounter_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetFrameCounter_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetPanCoordShortAddress_Input_buf2api(gpMacDispatcher_SetPanCoordShortAddress_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetPanCoordExtendedAddress_Input_buf2api(gpMacDispatcher_SetPanCoordExtendedAddress_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetPanCoordExtendedAddress_Input_buf2api(gpMacDispatcher_GetPanCoordExtendedAddress_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetPanCoordExtendedAddress_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetPanCoordExtendedAddress_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetPanCoordExtendedAddress_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_AddNeighbour_Input_buf2api(gpMacDispatcher_AddNeighbour_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_AddNeighbour_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_AddNeighbour_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_AddNeighbour_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_RemoveNeighbour_Input_buf2api(gpMacDispatcher_RemoveNeighbour_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_RemoveNeighbour_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_RemoveNeighbour_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_RemoveNeighbour_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetDataPendingMode_Input_buf2api(gpMacDispatcher_SetDataPendingMode_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetDataPendingMode_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_SetDataPendingMode_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_SetDataPendingMode_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetAddressModeOverrideForBeacons_Input_buf2api(gpMacDispatcher_SetAddressModeOverrideForBeacons_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_ClearNeighbours_Input_buf2api(gpMacDispatcher_ClearNeighbours_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetCallbacks_Input_buf2api(gpMacDispatcher_GetCallbacks_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetCallbacks_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetCallbacks_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetCallbacks_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_IsValidStack_Input_buf2api(gpMacDispatcher_IsValidStack_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_IsValidStack_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_IsValidStack_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_IsValidStack_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetCsmaMode_Input_buf2api(gpMacDispatcher_SetCsmaMode_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetCsmaMode_Input_buf2api(gpMacDispatcher_GetCsmaMode_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetCsmaMode_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetCsmaMode_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetCsmaMode_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_DataPending_QueueClear_Input_buf2api(gpMacDispatcher_DataPending_QueueClear_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_DataPending_QueueClear_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_DataPending_QueueClear_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_DataPending_QueueClear_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_ScheduleTimedTx_Input_buf2api(gpMacDispatcher_ScheduleTimedTx_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_ScheduleTimedTx_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_ScheduleTimedTx_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_ScheduleTimedTx_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetStackInRawMode_Input_buf2api(gpMacDispatcher_SetStackInRawMode_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetStackInRawMode_Input_buf2api(gpMacDispatcher_GetStackInRawMode_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetStackInRawMode_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetStackInRawMode_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetStackInRawMode_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_EnableEnhancedFramePending_Input_buf2api(gpMacDispatcher_EnableEnhancedFramePending_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_EnableRxWindows_Input_buf2api(gpMacDispatcher_EnableRxWindows_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_DisableRxWindows_Input_buf2api(gpMacDispatcher_DisableRxWindows_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_EnableCsl_Input_buf2api(gpMacDispatcher_EnableCsl_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_UpdateCslSampleTime_Input_buf2api(gpMacDispatcher_UpdateCslSampleTime_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetCurrentTimeUs_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetCurrentTimeUs_Output_marshall_struct_t* pSourceoutput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_ConfigureEnhAckProbing_Input_buf2api(gpMacDispatcher_ConfigureEnhAckProbing_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_ConfigureEnhAckProbing_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_ConfigureEnhAckProbing_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_ConfigureEnhAckProbing_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetRetransmitOnCcaFail_Input_buf2api(gpMacDispatcher_SetRetransmitOnCcaFail_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetRetransmitOnCcaFail_Input_buf2api(gpMacDispatcher_GetRetransmitOnCcaFail_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetRetransmitOnCcaFail_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetRetransmitOnCcaFail_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetRetransmitOnCcaFail_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetRetransmitRandomBackoff_Input_buf2api(gpMacDispatcher_SetRetransmitRandomBackoff_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetRetransmitRandomBackoff_Input_buf2api(gpMacDispatcher_GetRetransmitRandomBackoff_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetRetransmitRandomBackoff_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetRetransmitRandomBackoff_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetRetransmitRandomBackoff_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetMinBeRetransmit_Input_buf2api(gpMacDispatcher_SetMinBeRetransmit_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetMinBeRetransmit_Input_buf2api(gpMacDispatcher_GetMinBeRetransmit_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetMinBeRetransmit_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetMinBeRetransmit_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetMinBeRetransmit_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_SetMaxBeRetransmit_Input_buf2api(gpMacDispatcher_SetMaxBeRetransmit_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacDispatcher_GetMaxBeRetransmit_Input_buf2api(gpMacDispatcher_GetMaxBeRetransmit_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetMaxBeRetransmit_Output_api2buf(UInt8Buffer* pDest , gpMacDispatcher_GetMaxBeRetransmit_Output_marshall_struct_t* pSourceoutput , gpMacDispatcher_GetMaxBeRetransmit_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
void MacDispatcher_cbDataConfirm_Input_par2api(UInt8Buffer* pDest , gpMacCore_Result_t status , gpPd_Handle_t pdHandle , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void MacDispatcher_cbDataIndication_Input_par2api(UInt8Buffer* pDest , const gpMacCore_AddressInfo_t* pSrcAddrInfo , const gpMacCore_AddressInfo_t* pDstAddrInfo , UInt8 dsn , gpMacCore_Security_t* pSecOptions , gpPd_Loh_t pdLoh , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void MacDispatcher_cbScanConfirm_Input_par2api(UInt8Buffer* pDest , gpMacCore_Result_t status , gpMacCore_ScanType_t scanType , UInt32 unscannedChannels , UInt8 resultListSize , UInt8* pEdScanResultList , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void MacDispatcher_cbAssociateIndication_Input_par2api(UInt8Buffer* pDest , gpMacCore_Address_t* pDeviceAddress , UInt8 capabilityInformation , gpPd_TimeStamp_t rxTime , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void MacDispatcher_cbAssociateConfirm_Input_par2api(UInt8Buffer* pDest , UInt16 assocShortAddress , gpMacCore_Result_t status , gpPd_TimeStamp_t txTime , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void MacDispatcher_cbAssociateCommStatusIndication_Input_par2api(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* pSrcAddrInfo , gpMacCore_AddressInfo_t* pDstAddrInfo , gpMacCore_Result_t status , gpPd_TimeStamp_t txTime , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void MacDispatcher_cbPollConfirm_Input_par2api(UInt8Buffer* pDest , gpMacCore_Result_t status , gpMacCore_AddressInfo_t* coordAddrInfo , gpPd_TimeStamp_t txTime , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void MacDispatcher_cbPollIndication_Input_par2api(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* addressInfo , gpPd_TimeStamp_t rxTime , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void MacDispatcher_cbPurgeConfirm_Input_par2api(UInt8Buffer* pDest , gpMacCore_Result_t status , gpPd_Handle_t pdHandle , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void MacDispatcher_cbBeaconNotifyIndication_Input_par2api(UInt8Buffer* pDest , UInt8 bsn , gpMacCore_PanDescriptor_t* pPanDescriptor , UInt8 beaconPayloadLength , UInt8* pBeaconPayload , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void MacDispatcher_cbOrphanIndication_Input_par2api(UInt8Buffer* pDest , MACAddress_t* pOrphanAddress , gpPd_TimeStamp_t rxTime , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void MacDispatcher_cbOrphanCommStatusIndication_Input_par2api(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* pSrcAddrInfo , gpMacCore_AddressInfo_t* pDstAddrInfo , gpMacCore_Result_t status , gpPd_TimeStamp_t txTime , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void MacDispatcher_cbSecurityFailureCommStatusIndication_Input_par2api(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* pSrcAddrInfo , gpMacCore_AddressInfo_t* pDstAddrInfo , gpMacCore_Result_t status , gpPd_TimeStamp_t txTime , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void MacDispatcher_cbDriverResetIndication_Input_par2api(UInt8Buffer* pDest , gpMacDispatcher_Result_t status , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void MacDispatcher_cbPollNotify_Input_par2api(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* addressInfo , gpPd_TimeStamp_t rxTime , gpPd_Handle_t pdHandle , Bool fromNeighbour , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void MacDispatcher_cbSecurityFrameCounterIndication_Input_par2api(UInt8Buffer* pDest , UInt32 frameCounter , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);

// Client functions
void gpMacDispatcher_RegisterNetworkStack_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StringIdentifier_t* stringIdentifier , UInt16* pIndex);
void gpMacDispatcher_RegisterNetworkStack_Output_buf2par(gpMacDispatcher_StackId_t* stackId , gpMacDispatcher_StringIdentifier_t* stringIdentifier , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_UnRegisterNetworkStack_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_UnRegisterNetworkStack_Output_buf2par(gpMacCore_Result_t* result , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_RegisterCallbacks_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , gpMacDispatcher_Callbacks_t* callbacks , UInt16* pIndex);
void gpMacDispatcher_LockClaim_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_LockClaim_Output_buf2par(Bool* result , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_LockRelease_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_LockedByThisStack_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_LockedByThisStack_Output_buf2par(Bool* locked , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_Locked_Output_buf2par(Bool* locked , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_Reset_Input_par2buf(UInt8Buffer* pDest , Bool setDefaultPib , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_Reset_Output_buf2par(gpMacDispatcher_Result_t* result , Bool setDefaultPib , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_DataRequest_Input_par2buf(UInt8Buffer* pDest , gpMacCore_AddressMode_t srcAddrMode , gpMacCore_AddressInfo_t* pDstAddressInfo , UInt8 txOptions , gpMacCore_Security_t* pSecOptions , gpMacCore_MultiChannelOptions_t multiChannelOptions , gpPd_Loh_t pdLoh , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_ScanRequest_Input_par2buf(UInt8Buffer* pDest , gpMacCore_ScanType_t scanType , UInt32 scanChannels , UInt8 scanDuration , UInt8 resultListSize , UInt8* pResultList , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_AssociateRequest_Input_par2buf(UInt8Buffer* pDest , UInt8 logicalChannel , gpMacCore_AddressInfo_t* coordAddrInfo , UInt8 capabilityInformation , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_AssociateResponse_Input_par2buf(UInt8Buffer* pDest , MACAddress_t* pDeviceAddress , UInt16 associateShortAddress , gpMacCore_Result_t status , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_PollRequest_Input_par2buf(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* coordAddrInfo , gpMacCore_Security_t* pSecOptions , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_PurgeRequest_Input_par2buf(UInt8Buffer* pDest , gpPd_Handle_t pdHandle , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_Start_Input_par2buf(UInt8Buffer* pDest , gpMacCore_PanId_t panId , UInt8 logicalChannel , Bool panCoordinator , UInt8 stackId , UInt16* pIndex);
void gpMacDispatcher_Start_Output_buf2par(gpMacCore_Result_t* returnValue , gpMacCore_PanId_t panId , UInt8 logicalChannel , Bool panCoordinator , UInt8 stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_OrphanResponse_Input_par2buf(UInt8Buffer* pDest , MACAddress_t* pOrphanAddress , UInt16 shortAddress , Bool associatedMember , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_SetPanId_Input_par2buf(UInt8Buffer* pDest , UInt16 panId , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetPanId_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetPanId_Output_buf2par(gpMacCore_PanId_t* panId , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetShortAddress_Input_par2buf(UInt8Buffer* pDest , UInt16 shortAddress , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetShortAddress_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetShortAddress_Output_buf2par(UInt16* address , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetExtendedAddress_Input_par2buf(UInt8Buffer* pDest , MACAddress_t* pExtendedAddress , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetExtendedAddress_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetExtendedAddress_Output_buf2par(MACAddress_t* pExtendedAddress , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetDsn_Input_par2buf(UInt8Buffer* pDest , UInt8 dsn , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetDsn_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetDsn_Output_buf2par(UInt8* dsn , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetCurrentChannel_Input_par2buf(UInt8Buffer* pDest , UInt8 channel , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetCurrentChannel_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetCurrentChannel_Output_buf2par(UInt8* channel , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetBeaconPayload_Input_par2buf(UInt8Buffer* pDest , UInt8* pBeaconPayload , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetBeaconPayload_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetBeaconPayload_Output_buf2par(UInt8* pBeaconPayload , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetBeaconPayloadLength_Input_par2buf(UInt8Buffer* pDest , UInt8 beaconPayloadLength , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetBeaconPayloadLength_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetBeaconPayloadLength_Output_buf2par(UInt8* beaconPayloadLength , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetRxOnWhenIdle_Input_par2buf(UInt8Buffer* pDest , Bool rxOnWhenIdle , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetRxOnWhenIdle_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetRxOnWhenIdle_Output_buf2par(Bool* rxOnWhenIdle , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetTransactionPersistenceTime_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetTransactionPersistenceTime_Output_buf2par(UInt16* time , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetTransactionPersistenceTime_Input_par2buf(UInt8Buffer* pDest , UInt16 time , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_SetBeaconStarted_Input_par2buf(UInt8Buffer* pDest , Bool beaconStarted , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetBeaconStarted_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetBeaconStarted_Output_buf2par(Bool* beaconStarted , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetCoordShortAddress_Input_par2buf(UInt8Buffer* pDest , UInt16 coordShortAddress , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetCoordShortAddress_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetCoordShortAddress_Output_buf2par(UInt16* coordShortAddress , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetCoordExtendedAddress_Input_par2buf(UInt8Buffer* pDest , MACAddress_t* pCoordExtendedAddress , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetCoordExtendedAddress_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetCoordExtendedAddress_Output_buf2par(MACAddress_t* pCoordExtendedAddress , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetPromiscuousMode_Input_par2buf(UInt8Buffer* pDest , UInt8 promiscuousMode , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetPromiscuousMode_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetPromiscuousMode_Output_buf2par(Bool* promiscuousMode , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetAssociationPermit_Input_par2buf(UInt8Buffer* pDest , Bool associationPermit , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetAssociationPermit_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetAssociationPermit_Output_buf2par(Bool* associationPermit , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetSecurityEnabled_Input_par2buf(UInt8Buffer* pDest , Bool securityEnabled , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetSecurityEnabled_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetSecurityEnabled_Output_buf2par(Bool* securityEnabled , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetNumberOfRetries_Input_par2buf(UInt8Buffer* pDest , UInt8 numberOfRetries , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetNumberOfRetries_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetNumberOfRetries_Output_buf2par(UInt8* numberOfRetries , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetMaxCsmaBackoffs_Input_par2buf(UInt8Buffer* pDest , UInt8 maxCsmaBackoffs , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetMaxCsmaBackoffs_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetMaxCsmaBackoffs_Output_buf2par(UInt8* maxCsmaBackoffs , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetDefaultTransmitPowers_Input_par2buf(UInt8Buffer* pDest , Int8* pDefaultTransmitPowerTable , UInt16* pIndex);
void gpMacDispatcher_SetTransmitPower_Input_par2buf(UInt8Buffer* pDest , gpMacCore_TxPower_t transmitPower , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetTransmitPower_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetTransmitPower_Output_buf2par(Int8* transmitPower , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetCCAMode_Input_par2buf(UInt8Buffer* pDest , UInt8 cCAMode , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetCCAMode_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetCCAMode_Output_buf2par(UInt8* cCAMode , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetPanCoordinator_Input_par2buf(UInt8Buffer* pDest , Bool panCoordinator , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetPanCoordinator_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetPanCoordinator_Output_buf2par(Bool* panCoordinator , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetMinBE_Input_par2buf(UInt8Buffer* pDest , UInt8 minBE , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetMinBE_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetMinBE_Output_buf2par(UInt8* minBE , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetIndicateBeaconNotifications_Input_par2buf(UInt8Buffer* pDest , Bool enable , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetIndicateBeaconNotifications_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetIndicateBeaconNotifications_Output_buf2par(Bool* enable , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetMacVersion_Input_par2buf(UInt8Buffer* pDest , gpMacCore_MacVersion_t macVersion , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetMacVersion_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetMacVersion_Output_buf2par(gpMacCore_MacVersion_t* macVersion , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetForwardPollIndications_Input_par2buf(UInt8Buffer* pDest , Bool enable , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetForwardPollIndications_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetForwardPollIndications_Output_buf2par(Bool* enable , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_DataPending_QueueAdd_Input_par2buf(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* pAddrInfo , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_DataPending_QueueAdd_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_AddressInfo_t* pAddrInfo , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_DataPending_QueueRemove_Input_par2buf(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* pAddrInfo , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_DataPending_QueueRemove_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_AddressInfo_t* pAddrInfo , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetMinInterferenceLevels_Input_par2buf(UInt8Buffer* pDest , Int8* pInterferenceLevels , UInt16* pIndex);
void gpMacDispatcher_SetMaxBE_Input_par2buf(UInt8Buffer* pDest , UInt8 maxBE , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetMaxBE_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetMaxBE_Output_buf2par(UInt8* maxBE , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetDeviceDescriptor_Input_par2buf(UInt8Buffer* pDest , gpMacCore_DeviceDescriptor_t* pDeviceDescriptor , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_SetDeviceDescriptor_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_DeviceDescriptor_t* pDeviceDescriptor , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetDeviceDescriptor_Input_par2buf(UInt8Buffer* pDest , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetDeviceDescriptor_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_DeviceDescriptor_t* pDeviceDescriptor , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetDeviceTableEntries_Input_par2buf(UInt8Buffer* pDest , gpMacCore_DeviceTablesEntries_t deviceTableEntries , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetDeviceTableEntries_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetDeviceTableEntries_Output_buf2par(gpMacCore_DeviceTablesEntries_t* deviceTableEntries , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetKeyDescriptor_Input_par2buf(UInt8Buffer* pDest , gpMacCore_KeyDescriptor_t* pKeyDescriptor , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_SetKeyDescriptor_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_KeyDescriptor_t* pKeyDescriptor , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetKeyDescriptor_Input_par2buf(UInt8Buffer* pDest , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetKeyDescriptor_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_KeyDescriptor_t* pKeyDescriptor , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetKeyTableEntries_Input_par2buf(UInt8Buffer* pDest , gpMacCore_KeyTablesEntries_t keyTableEntries , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_SetSecurityLevelDescriptor_Input_par2buf(UInt8Buffer* pDest , gpMacCore_SecurityLevelDescriptor_t* pSecurityLevelDescriptor , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_SetSecurityLevelDescriptor_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_SecurityLevelDescriptor_t* pSecurityLevelDescriptor , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_GetSecurityLevelDescriptor_Input_par2buf(UInt8Buffer* pDest , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetSecurityLevelDescriptor_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_SecurityLevelDescriptor_t* pSecurityLevelDescriptor , gpMacCore_Index_t index , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetSecurityLevelTableEntries_Input_par2buf(UInt8Buffer* pDest , gpMacCore_SecurityLevelTableEntries_t securityLevelTableEntries , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetSecurityLevelTableEntries_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetSecurityLevelTableEntries_Output_buf2par(gpMacCore_SecurityLevelTableEntries_t* securityLevelTableEntries , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetDefaultKeySource_Input_par2buf(UInt8Buffer* pDest , UInt8* pDefaultKeySource , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_SetFrameCounter_Input_par2buf(UInt8Buffer* pDest , UInt32 frameCounter , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetFrameCounter_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetFrameCounter_Output_buf2par(UInt32* frameCounter , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetPanCoordShortAddress_Input_par2buf(UInt8Buffer* pDest , UInt16 panCoordShortAddress , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_SetPanCoordExtendedAddress_Input_par2buf(UInt8Buffer* pDest , MACAddress_t* pPanCoordExtendedAddress , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetPanCoordExtendedAddress_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetPanCoordExtendedAddress_Output_buf2par(MACAddress_t* pPanCoordExtendedAddress , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_AddNeighbour_Input_par2buf(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* pAddrInfo , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_AddNeighbour_Output_buf2par(Bool* result , gpMacCore_AddressInfo_t* pAddrInfo , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_RemoveNeighbour_Input_par2buf(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* pAddrInfo , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_RemoveNeighbour_Output_buf2par(Bool* result , gpMacCore_AddressInfo_t* pAddrInfo , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetDataPendingMode_Input_par2buf(UInt8Buffer* pDest , gpMacCore_DataPendingMode_t dataPendingMode , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_SetDataPendingMode_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_DataPendingMode_t dataPendingMode , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetAddressModeOverrideForBeacons_Input_par2buf(UInt8Buffer* pDest , UInt8 addressMode , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_ClearNeighbours_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetCallbacks_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetCallbacks_Output_buf2par(gpMacDispatcher_StackId_t stackId , gpMacDispatcher_Callbacks_t* callbacks , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_IsValidStack_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_IsValidStack_Output_buf2par(Bool* valid , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetCsmaMode_Input_par2buf(UInt8Buffer* pDest , UInt8 csmaMode , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetCsmaMode_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetCsmaMode_Output_buf2par(UInt8* csmaMode , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_DataPending_QueueClear_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_DataPending_QueueClear_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_ScheduleTimedTx_Input_par2buf(UInt8Buffer* pDest , gpPd_Handle_t pdHandle , gpMacCore_TxTimingOptions_t timingOptions , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_ScheduleTimedTx_Output_buf2par(gpMacCore_Result_t* result , gpPd_Handle_t pdHandle , gpMacCore_TxTimingOptions_t timingOptions , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetStackInRawMode_Input_par2buf(UInt8Buffer* pDest , Bool rawModeEnabled , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetStackInRawMode_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetStackInRawMode_Output_buf2par(Bool* rawModeEnabled , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_EnableEnhancedFramePending_Input_par2buf(UInt8Buffer* pDest , Bool enableEnhancedFramePending , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_EnableRxWindows_Input_par2buf(UInt8Buffer* pDest , UInt32 dutyCycleOnTime , UInt32 dutyCyclePeriod , UInt16 recurrenceAmount , UInt32 startTime , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_DisableRxWindows_Input_par2buf(UInt8Buffer* pDest , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_EnableCsl_Input_par2buf(UInt8Buffer* pDest , UInt16 dutyCyclePeriod , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_UpdateCslSampleTime_Input_par2buf(UInt8Buffer* pDest , UInt32 nextCslSampleTime , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetCurrentTimeUs_Output_buf2par(UInt32* currentTime , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_ConfigureEnhAckProbing_Input_par2buf(UInt8Buffer* pDest , UInt8 linkMetrics , MACAddress_t* pExtendedAddress , UInt16 shortAddress , gpMacDispatcher_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_ConfigureEnhAckProbing_Output_buf2par(gpMacCore_Result_t* result , UInt8 linkMetrics , MACAddress_t* pExtendedAddress , UInt16 shortAddress , gpMacDispatcher_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetRetransmitOnCcaFail_Input_par2buf(UInt8Buffer* pDest , Bool enable , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetRetransmitOnCcaFail_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetRetransmitOnCcaFail_Output_buf2par(Bool* enable , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetRetransmitRandomBackoff_Input_par2buf(UInt8Buffer* pDest , Bool enable , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetRetransmitRandomBackoff_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetRetransmitRandomBackoff_Output_buf2par(Bool* enable , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetMinBeRetransmit_Input_par2buf(UInt8Buffer* pDest , UInt8 minBERetransmit , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetMinBeRetransmit_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetMinBeRetransmit_Output_buf2par(UInt8* minBERetransmit , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacDispatcher_SetMaxBeRetransmit_Input_par2buf(UInt8Buffer* pDest , UInt8 maxBERetransmit , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetMaxBeRetransmit_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacDispatcher_GetMaxBeRetransmit_Output_buf2par(UInt8* maxBERetransmit , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t MacDispatcher_cbDataConfirm_Input_buf2api(MacDispatcher_cbDataConfirm_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t MacDispatcher_cbDataIndication_Input_buf2api(MacDispatcher_cbDataIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t MacDispatcher_cbScanConfirm_Input_buf2api(MacDispatcher_cbScanConfirm_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t MacDispatcher_cbAssociateIndication_Input_buf2api(MacDispatcher_cbAssociateIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t MacDispatcher_cbAssociateConfirm_Input_buf2api(MacDispatcher_cbAssociateConfirm_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t MacDispatcher_cbAssociateCommStatusIndication_Input_buf2api(MacDispatcher_cbAssociateCommStatusIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t MacDispatcher_cbPollConfirm_Input_buf2api(MacDispatcher_cbPollConfirm_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t MacDispatcher_cbPollIndication_Input_buf2api(MacDispatcher_cbPollIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t MacDispatcher_cbPurgeConfirm_Input_buf2api(MacDispatcher_cbPurgeConfirm_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t MacDispatcher_cbBeaconNotifyIndication_Input_buf2api(MacDispatcher_cbBeaconNotifyIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t MacDispatcher_cbOrphanIndication_Input_buf2api(MacDispatcher_cbOrphanIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t MacDispatcher_cbOrphanCommStatusIndication_Input_buf2api(MacDispatcher_cbOrphanCommStatusIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t MacDispatcher_cbSecurityFailureCommStatusIndication_Input_buf2api(MacDispatcher_cbSecurityFailureCommStatusIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t MacDispatcher_cbDriverResetIndication_Input_buf2api(MacDispatcher_cbDriverResetIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t MacDispatcher_cbPollNotify_Input_buf2api(MacDispatcher_cbPollNotify_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t MacDispatcher_cbSecurityFrameCounterIndication_Input_buf2api(MacDispatcher_cbSecurityFrameCounterIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);

void gpMacDispatcher_InitMarshalling(void);

#define gpMacDispatcher_SetDummyDataInsertion(enable)
#define gpMacDispatcher_GetDummyDataInsertion()      false

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // _GPMACDISPATCHER_MARSHALLING_H_


