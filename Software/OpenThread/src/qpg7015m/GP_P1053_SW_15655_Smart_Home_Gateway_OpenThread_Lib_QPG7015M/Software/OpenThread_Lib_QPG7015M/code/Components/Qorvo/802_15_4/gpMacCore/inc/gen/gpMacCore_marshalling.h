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
 * $Header$
 * $Change$
 * $DateTime$
 */

#ifndef _GPMACCORE_MARSHALLING_H_
#define _GPMACCORE_MARSHALLING_H_

//DOCUMENTATION MACCORE: no @file required as all documented items are refered to a group

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/
#include <global.h>
#include "gpMacCore.h"
/* <CodeGenerator Placeholder> AdditionalIncludes */
#include "gpPd_marshalling.h"
/* </CodeGenerator Placeholder> AdditionalIncludes */

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Type Definitions
 *****************************************************************************/

typedef struct {
    gpMacCore_DeviceDescriptor_t data[1];
} gpMacCore_DeviceDescriptor_t_l1_pointer_marshall_t;


typedef struct {
    gpMacCore_KeyUsageDescriptor_t data[1];
} gpMacCore_KeyUsageDescriptor_t_l1_pointer_marshall_t;


typedef struct {
    gpMacCore_KeyDeviceDescriptor_t data[1];
} gpMacCore_KeyDeviceDescriptor_t_l1_pointer_marshall_t;


typedef struct {
    gpMacCore_Security_t data[1];
} gpMacCore_Security_t_l1_pointer_marshall_t;


typedef struct {
    gpMacCore_AddressInfo_t data[1];
} gpMacCore_AddressInfo_t_l1_pointer_marshall_t;


typedef struct {
    gpMacCore_PanDescriptor_t data[1];
} gpMacCore_PanDescriptor_t_l1_pointer_marshall_t;


typedef struct {
    gpMacCore_KeyIdLookupDescriptor_t data[1];
} gpMacCore_KeyIdLookupDescriptor_t_l1_pointer_marshall_t;


typedef struct {
    gpMacCore_KeyDescriptor_t data[1];
} gpMacCore_KeyDescriptor_t_l1_pointer_marshall_t;


typedef struct {
    gpMacCore_SecurityLevelDescriptor_t data[1];
} gpMacCore_SecurityLevelDescriptor_t_l1_pointer_marshall_t;


typedef struct {
    gpMacCore_MultiChannelOptions_t data[1];
} gpMacCore_MultiChannelOptions_t_l1_pointer_marshall_t;


typedef struct {
    gpMacCore_TxTimingOptions_t data[1];
} gpMacCore_TxTimingOptions_t_l1_pointer_marshall_t;


typedef struct {
    gpMacCore_DiagRxCntr_t data[1];
} gpMacCore_DiagRxCntr_t_l1_pointer_marshall_t;


typedef struct {
    gpMacCore_DiagTxCntr_t data[1];
} gpMacCore_DiagTxCntr_t_l1_pointer_marshall_t;


typedef struct {
    gpMacCore_Address_t data[1];
} gpMacCore_Address_t_l1_pointer_marshall_t;


typedef struct {
    gpMacCore_KeySource_t data[1];
} gpMacCore_KeySource_t_l1_pointer_marshall_t;


typedef union {
    UInt16 Short;
    MACAddress_t Extended;
} gpMacCore_Address_t_marshall_t;

typedef union {
    UInt8 pKeySource4;
    UInt8 pKeySource8;
} gpMacCore_KeySource_t_marshall_t;

typedef struct {
    Bool setDefaultPib;
    gpMacCore_StackId_t stackId;
} gpMacCore_Reset_Input_struct_t;

typedef struct {
    gpMacCore_Reset_Input_struct_t data;
} gpMacCore_Reset_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
} gpMacCore_Reset_Output_struct_t;

typedef struct {
    gpMacCore_Reset_Output_struct_t data;
} gpMacCore_Reset_Output_marshall_struct_t;


typedef struct {
    gpMacCore_AddressMode_t srcAddrMode;
    gpMacCore_AddressInfo_t* pDstAddressInfo;
    UInt8 txOptions;
    gpMacCore_Security_t* pSecOptions;
    gpMacCore_MultiChannelOptions_t multiChannelOptions;
    gpPd_Loh_t pdLoh;
    gpMacCore_StackId_t stackId;
} gpMacCore_DataRequest_Input_struct_t;

typedef struct {
    gpMacCore_DataRequest_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pDstAddressInfo;
    gpMacCore_Security_t_l1_pointer_marshall_t pSecOptions;
    gpMacCore_MultiChannelOptions_t_l1_pointer_marshall_t multiChannelOptions;
    gpPd_Loh_t_l1_pointer_marshall_t pdLoh;
} gpMacCore_DataRequest_Input_marshall_struct_t;


typedef struct {
    gpMacCore_ScanType_t scanType;
    UInt32 scanChannels;
    UInt8 scanDuration;
    UInt8 resultListSize;
    UInt8* pEdScanResultList;
    gpMacCore_StackId_t stackId;
} gpMacCore_ScanRequest_Input_struct_t;

typedef struct {
    gpMacCore_ScanRequest_Input_struct_t data;
} gpMacCore_ScanRequest_Input_marshall_struct_t;


typedef struct {
    UInt8 logicalChannel;
    gpMacCore_AddressInfo_t* coordAddrInfo;
    UInt8 capabilityInformation;
    gpMacCore_StackId_t stackId;
} gpMacCore_AssociateRequest_Input_struct_t;

typedef struct {
    gpMacCore_AssociateRequest_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t coordAddrInfo;
} gpMacCore_AssociateRequest_Input_marshall_struct_t;


typedef struct {
    MACAddress_t* pDeviceAddress;
    UInt16 associateShortAddress;
    gpMacCore_Result_t status;
    gpMacCore_StackId_t stackId;
} gpMacCore_AssociateResponse_Input_struct_t;

typedef struct {
    gpMacCore_AssociateResponse_Input_struct_t data;
    MACAddress_t pDeviceAddress[1];
} gpMacCore_AssociateResponse_Input_marshall_struct_t;


typedef struct {
    gpMacCore_AddressInfo_t* coordAddrInfo;
    gpMacCore_Security_t* pSecOptions;
    gpMacCore_StackId_t stackId;
} gpMacCore_PollRequest_Input_struct_t;

typedef struct {
    gpMacCore_PollRequest_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t coordAddrInfo;
    gpMacCore_Security_t_l1_pointer_marshall_t pSecOptions;
} gpMacCore_PollRequest_Input_marshall_struct_t;


typedef struct {
    gpMacCore_PanId_t panId;
    UInt8 logicalChannel;
    Bool panCoordinator;
    gpMacCore_StackId_t stackId;
} gpMacCore_Start_Input_struct_t;

typedef struct {
    gpMacCore_Start_Input_struct_t data;
} gpMacCore_Start_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
} gpMacCore_Start_Output_struct_t;

typedef struct {
    gpMacCore_Start_Output_struct_t data;
} gpMacCore_Start_Output_marshall_struct_t;


typedef struct {
    Bool securityEnabled;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetSecurityEnabled_Input_struct_t;

typedef struct {
    gpMacCore_SetSecurityEnabled_Input_struct_t data;
} gpMacCore_SetSecurityEnabled_Input_marshall_struct_t;


typedef struct {
    gpMacCore_DeviceDescriptor_t* pDeviceDescriptor;
    gpMacCore_Index_t index;
} gpMacCore_SetDeviceDescriptor_Input_struct_t;

typedef struct {
    gpMacCore_SetDeviceDescriptor_Input_struct_t data;
    gpMacCore_DeviceDescriptor_t_l1_pointer_marshall_t pDeviceDescriptor;
} gpMacCore_SetDeviceDescriptor_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
} gpMacCore_SetDeviceDescriptor_Output_struct_t;

typedef struct {
    gpMacCore_SetDeviceDescriptor_Output_struct_t data;
} gpMacCore_SetDeviceDescriptor_Output_marshall_struct_t;


typedef struct {
    gpMacCore_Index_t index;
} gpMacCore_GetDeviceDescriptor_Input_struct_t;

typedef struct {
    gpMacCore_GetDeviceDescriptor_Input_struct_t data;
} gpMacCore_GetDeviceDescriptor_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
    gpMacCore_DeviceDescriptor_t* pDeviceDescriptor;
} gpMacCore_GetDeviceDescriptor_Output_struct_t;

typedef struct {
    gpMacCore_GetDeviceDescriptor_Output_struct_t data;
    gpMacCore_DeviceDescriptor_t_l1_pointer_marshall_t pDeviceDescriptor;
} gpMacCore_GetDeviceDescriptor_Output_marshall_struct_t;


typedef struct {
    gpMacCore_DeviceTablesEntries_t deviceTableEntries;
} gpMacCore_SetDeviceTableEntries_Input_struct_t;

typedef struct {
    gpMacCore_SetDeviceTableEntries_Input_struct_t data;
} gpMacCore_SetDeviceTableEntries_Input_marshall_struct_t;


typedef struct {
    gpMacCore_DeviceTablesEntries_t deviceTableEntries;
} gpMacCore_GetDeviceTableEntries_Output_struct_t;

typedef struct {
    gpMacCore_GetDeviceTableEntries_Output_struct_t data;
} gpMacCore_GetDeviceTableEntries_Output_marshall_struct_t;


typedef struct {
    gpMacCore_KeyDescriptor_t* pKeyDescriptor;
    gpMacCore_Index_t index;
} gpMacCore_SetKeyDescriptor_Input_struct_t;

typedef struct {
    gpMacCore_SetKeyDescriptor_Input_struct_t data;
    gpMacCore_KeyDescriptor_t_l1_pointer_marshall_t pKeyDescriptor;
} gpMacCore_SetKeyDescriptor_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
} gpMacCore_SetKeyDescriptor_Output_struct_t;

typedef struct {
    gpMacCore_SetKeyDescriptor_Output_struct_t data;
} gpMacCore_SetKeyDescriptor_Output_marshall_struct_t;


typedef struct {
    gpMacCore_Index_t index;
} gpMacCore_GetKeyDescriptor_Input_struct_t;

typedef struct {
    gpMacCore_GetKeyDescriptor_Input_struct_t data;
} gpMacCore_GetKeyDescriptor_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
    gpMacCore_KeyDescriptor_t* pKeyDescriptor;
} gpMacCore_GetKeyDescriptor_Output_struct_t;

typedef struct {
    gpMacCore_GetKeyDescriptor_Output_struct_t data;
    gpMacCore_KeyDescriptor_t_l1_pointer_marshall_t pKeyDescriptor;
} gpMacCore_GetKeyDescriptor_Output_marshall_struct_t;


typedef struct {
    gpMacCore_KeyTablesEntries_t keyTableEntries;
} gpMacCore_SetKeyTableEntries_Input_struct_t;

typedef struct {
    gpMacCore_SetKeyTableEntries_Input_struct_t data;
} gpMacCore_SetKeyTableEntries_Input_marshall_struct_t;


typedef struct {
    gpMacCore_SecurityLevelDescriptor_t* pSecurityLevelDescriptor;
    gpMacCore_Index_t index;
} gpMacCore_SetSecurityLevelDescriptor_Input_struct_t;

typedef struct {
    gpMacCore_SetSecurityLevelDescriptor_Input_struct_t data;
    gpMacCore_SecurityLevelDescriptor_t_l1_pointer_marshall_t pSecurityLevelDescriptor;
} gpMacCore_SetSecurityLevelDescriptor_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
} gpMacCore_SetSecurityLevelDescriptor_Output_struct_t;

typedef struct {
    gpMacCore_SetSecurityLevelDescriptor_Output_struct_t data;
} gpMacCore_SetSecurityLevelDescriptor_Output_marshall_struct_t;


typedef struct {
    gpMacCore_Index_t index;
} gpMacCore_GetSecurityLevelDescriptor_Input_struct_t;

typedef struct {
    gpMacCore_GetSecurityLevelDescriptor_Input_struct_t data;
} gpMacCore_GetSecurityLevelDescriptor_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
    gpMacCore_SecurityLevelDescriptor_t* pSecurityLevelDescriptor;
} gpMacCore_GetSecurityLevelDescriptor_Output_struct_t;

typedef struct {
    gpMacCore_GetSecurityLevelDescriptor_Output_struct_t data;
    gpMacCore_SecurityLevelDescriptor_t_l1_pointer_marshall_t pSecurityLevelDescriptor;
} gpMacCore_GetSecurityLevelDescriptor_Output_marshall_struct_t;


typedef struct {
    gpMacCore_SecurityLevelTableEntries_t securityLevelTableEntries;
} gpMacCore_SetSecurityLevelTableEntries_Input_struct_t;

typedef struct {
    gpMacCore_SetSecurityLevelTableEntries_Input_struct_t data;
} gpMacCore_SetSecurityLevelTableEntries_Input_marshall_struct_t;


typedef struct {
    gpMacCore_SecurityLevelTableEntries_t securityLevelTableEntries;
} gpMacCore_GetSecurityLevelTableEntries_Output_struct_t;

typedef struct {
    gpMacCore_GetSecurityLevelTableEntries_Output_struct_t data;
} gpMacCore_GetSecurityLevelTableEntries_Output_marshall_struct_t;


typedef struct {
    UInt8* pDefaultKeySource;
} gpMacCore_SetDefaultKeySource_Input_struct_t;

typedef struct {
    gpMacCore_SetDefaultKeySource_Input_struct_t data;
    UInt8 pDefaultKeySource[8];
} gpMacCore_SetDefaultKeySource_Input_marshall_struct_t;


typedef struct {
    UInt16 shortAddress;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetShortAddress_Input_struct_t;

typedef struct {
    gpMacCore_SetShortAddress_Input_struct_t data;
} gpMacCore_SetShortAddress_Input_marshall_struct_t;


typedef struct {
    MACAddress_t* pExtendedAddress;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetExtendedAddress_Input_struct_t;

typedef struct {
    gpMacCore_SetExtendedAddress_Input_struct_t data;
    MACAddress_t pExtendedAddress[1];
} gpMacCore_SetExtendedAddress_Input_marshall_struct_t;


typedef struct {
    UInt16 panId;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetPanId_Input_struct_t;

typedef struct {
    gpMacCore_SetPanId_Input_struct_t data;
} gpMacCore_SetPanId_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetPanId_Input_struct_t;

typedef struct {
    gpMacCore_GetPanId_Input_struct_t data;
} gpMacCore_GetPanId_Input_marshall_struct_t;

typedef struct {
    gpMacCore_PanId_t panId;
} gpMacCore_GetPanId_Output_struct_t;

typedef struct {
    gpMacCore_GetPanId_Output_struct_t data;
} gpMacCore_GetPanId_Output_marshall_struct_t;


typedef struct {
    UInt32 frameCounter;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetFrameCounter_Input_struct_t;

typedef struct {
    gpMacCore_SetFrameCounter_Input_struct_t data;
} gpMacCore_SetFrameCounter_Input_marshall_struct_t;


typedef struct {
    UInt8 dsn;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetDsn_Input_struct_t;

typedef struct {
    gpMacCore_SetDsn_Input_struct_t data;
} gpMacCore_SetDsn_Input_marshall_struct_t;


typedef struct {
    UInt8 channel;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetCurrentChannel_Input_struct_t;

typedef struct {
    gpMacCore_SetCurrentChannel_Input_struct_t data;
} gpMacCore_SetCurrentChannel_Input_marshall_struct_t;


typedef struct {
    UInt8* pBeaconPayload;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetBeaconPayload_Input_struct_t;

typedef struct {
    gpMacCore_SetBeaconPayload_Input_struct_t data;
    UInt8 pBeaconPayload[GP_MACCORE_MAX_BEACON_PAYLOAD_LENGTH];
} gpMacCore_SetBeaconPayload_Input_marshall_struct_t;


typedef struct {
    UInt8 beaconPayloadLength;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetBeaconPayloadLength_Input_struct_t;

typedef struct {
    gpMacCore_SetBeaconPayloadLength_Input_struct_t data;
} gpMacCore_SetBeaconPayloadLength_Input_marshall_struct_t;


typedef struct {
    Bool rxOnWhenIdle;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetRxOnWhenIdle_Input_struct_t;

typedef struct {
    gpMacCore_SetRxOnWhenIdle_Input_struct_t data;
} gpMacCore_SetRxOnWhenIdle_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetExtendedAddress_Input_struct_t;

typedef struct {
    gpMacCore_GetExtendedAddress_Input_struct_t data;
} gpMacCore_GetExtendedAddress_Input_marshall_struct_t;

typedef struct {
    MACAddress_t* pExtendedAddress;
} gpMacCore_GetExtendedAddress_Output_struct_t;

typedef struct {
    gpMacCore_GetExtendedAddress_Output_struct_t data;
    MACAddress_t pExtendedAddress[1];
} gpMacCore_GetExtendedAddress_Output_marshall_struct_t;


typedef struct {
    UInt8 maxCsmaBackoffs;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetMaxCsmaBackoffs_Input_struct_t;

typedef struct {
    gpMacCore_SetMaxCsmaBackoffs_Input_struct_t data;
} gpMacCore_SetMaxCsmaBackoffs_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetMaxCsmaBackoffs_Input_struct_t;

typedef struct {
    gpMacCore_GetMaxCsmaBackoffs_Input_struct_t data;
} gpMacCore_GetMaxCsmaBackoffs_Input_marshall_struct_t;

typedef struct {
    UInt8 maxCsmaBackoffs;
} gpMacCore_GetMaxCsmaBackoffs_Output_struct_t;

typedef struct {
    gpMacCore_GetMaxCsmaBackoffs_Output_struct_t data;
} gpMacCore_GetMaxCsmaBackoffs_Output_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetDsn_Input_struct_t;

typedef struct {
    gpMacCore_GetDsn_Input_struct_t data;
} gpMacCore_GetDsn_Input_marshall_struct_t;

typedef struct {
    UInt8 dsn;
} gpMacCore_GetDsn_Output_struct_t;

typedef struct {
    gpMacCore_GetDsn_Output_struct_t data;
} gpMacCore_GetDsn_Output_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetCurrentChannel_Input_struct_t;

typedef struct {
    gpMacCore_GetCurrentChannel_Input_struct_t data;
} gpMacCore_GetCurrentChannel_Input_marshall_struct_t;

typedef struct {
    UInt8 channel;
} gpMacCore_GetCurrentChannel_Output_struct_t;

typedef struct {
    gpMacCore_GetCurrentChannel_Output_struct_t data;
} gpMacCore_GetCurrentChannel_Output_marshall_struct_t;


typedef struct {
    UInt8 numberOfRetries;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetNumberOfRetries_Input_struct_t;

typedef struct {
    gpMacCore_SetNumberOfRetries_Input_struct_t data;
} gpMacCore_SetNumberOfRetries_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetNumberOfRetries_Input_struct_t;

typedef struct {
    gpMacCore_GetNumberOfRetries_Input_struct_t data;
} gpMacCore_GetNumberOfRetries_Input_marshall_struct_t;

typedef struct {
    UInt8 numberOfRetries;
} gpMacCore_GetNumberOfRetries_Output_struct_t;

typedef struct {
    gpMacCore_GetNumberOfRetries_Output_struct_t data;
} gpMacCore_GetNumberOfRetries_Output_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetFrameCounter_Input_struct_t;

typedef struct {
    gpMacCore_GetFrameCounter_Input_struct_t data;
} gpMacCore_GetFrameCounter_Input_marshall_struct_t;

typedef struct {
    UInt32 frameCounter;
} gpMacCore_GetFrameCounter_Output_struct_t;

typedef struct {
    gpMacCore_GetFrameCounter_Output_struct_t data;
} gpMacCore_GetFrameCounter_Output_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetRxOnWhenIdle_Input_struct_t;

typedef struct {
    gpMacCore_GetRxOnWhenIdle_Input_struct_t data;
} gpMacCore_GetRxOnWhenIdle_Input_marshall_struct_t;

typedef struct {
    Bool rxOnWhenIdle;
} gpMacCore_GetRxOnWhenIdle_Output_struct_t;

typedef struct {
    gpMacCore_GetRxOnWhenIdle_Output_struct_t data;
} gpMacCore_GetRxOnWhenIdle_Output_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetShortAddress_Input_struct_t;

typedef struct {
    gpMacCore_GetShortAddress_Input_struct_t data;
} gpMacCore_GetShortAddress_Input_marshall_struct_t;

typedef struct {
    UInt16 address;
} gpMacCore_GetShortAddress_Output_struct_t;

typedef struct {
    gpMacCore_GetShortAddress_Output_struct_t data;
} gpMacCore_GetShortAddress_Output_marshall_struct_t;


typedef struct {
    UInt16 panCoordShortAddress;
} gpMacCore_SetPanCoordShortAddress_Input_struct_t;

typedef struct {
    gpMacCore_SetPanCoordShortAddress_Input_struct_t data;
} gpMacCore_SetPanCoordShortAddress_Input_marshall_struct_t;


typedef struct {
    MACAddress_t* pPanCoordExtendedAddress;
} gpMacCore_SetPanCoordExtendedAddress_Input_struct_t;

typedef struct {
    gpMacCore_SetPanCoordExtendedAddress_Input_struct_t data;
    MACAddress_t pPanCoordExtendedAddress[1];
} gpMacCore_SetPanCoordExtendedAddress_Input_marshall_struct_t;


typedef struct {
    Bool associationPermit;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetAssociationPermit_Input_struct_t;

typedef struct {
    gpMacCore_SetAssociationPermit_Input_struct_t data;
} gpMacCore_SetAssociationPermit_Input_marshall_struct_t;


typedef struct {
    Int8* pDefaultTransmitPowerTable;
} gpMacCore_SetDefaultTransmitPowers_Input_struct_t;

typedef struct {
    gpMacCore_SetDefaultTransmitPowers_Input_struct_t data;
    Int8 pDefaultTransmitPowerTable[16];
} gpMacCore_SetDefaultTransmitPowers_Input_marshall_struct_t;


typedef struct {
    gpMacCore_TxPower_t transmitPower;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetTransmitPower_Input_struct_t;

typedef struct {
    gpMacCore_SetTransmitPower_Input_struct_t data;
} gpMacCore_SetTransmitPower_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetTransmitPower_Input_struct_t;

typedef struct {
    gpMacCore_GetTransmitPower_Input_struct_t data;
} gpMacCore_GetTransmitPower_Input_marshall_struct_t;

typedef struct {
    Int8 transmitPower;
} gpMacCore_GetTransmitPower_Output_struct_t;

typedef struct {
    gpMacCore_GetTransmitPower_Output_struct_t data;
} gpMacCore_GetTransmitPower_Output_marshall_struct_t;



typedef struct {
    Bool panCoordinator;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetPanCoordinator_Input_struct_t;

typedef struct {
    gpMacCore_SetPanCoordinator_Input_struct_t data;
} gpMacCore_SetPanCoordinator_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetPanCoordinator_Input_struct_t;

typedef struct {
    gpMacCore_GetPanCoordinator_Input_struct_t data;
} gpMacCore_GetPanCoordinator_Input_marshall_struct_t;

typedef struct {
    Bool panCoordinator;
} gpMacCore_GetPanCoordinator_Output_struct_t;

typedef struct {
    gpMacCore_GetPanCoordinator_Output_struct_t data;
} gpMacCore_GetPanCoordinator_Output_marshall_struct_t;


typedef struct {
    MACAddress_t* pOrphanAddress;
    UInt16 shortAddress;
    Bool associatedMember;
    gpMacCore_StackId_t stackId;
} gpMacCore_OrphanResponse_Input_struct_t;

typedef struct {
    gpMacCore_OrphanResponse_Input_struct_t data;
    MACAddress_t pOrphanAddress[1];
} gpMacCore_OrphanResponse_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetSecurityEnabled_Input_struct_t;

typedef struct {
    gpMacCore_GetSecurityEnabled_Input_struct_t data;
} gpMacCore_GetSecurityEnabled_Input_marshall_struct_t;

typedef struct {
    Bool securityEnabled;
} gpMacCore_GetSecurityEnabled_Output_struct_t;

typedef struct {
    gpMacCore_GetSecurityEnabled_Output_struct_t data;
} gpMacCore_GetSecurityEnabled_Output_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetTransactionPersistenceTime_Input_struct_t;

typedef struct {
    gpMacCore_GetTransactionPersistenceTime_Input_struct_t data;
} gpMacCore_GetTransactionPersistenceTime_Input_marshall_struct_t;

typedef struct {
    UInt16 time;
} gpMacCore_GetTransactionPersistenceTime_Output_struct_t;

typedef struct {
    gpMacCore_GetTransactionPersistenceTime_Output_struct_t data;
} gpMacCore_GetTransactionPersistenceTime_Output_marshall_struct_t;


typedef struct {
    UInt16 time;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetTransactionPersistenceTime_Input_struct_t;

typedef struct {
    gpMacCore_SetTransactionPersistenceTime_Input_struct_t data;
} gpMacCore_SetTransactionPersistenceTime_Input_marshall_struct_t;




typedef struct {
    Bool BeaconStarted;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetBeaconStarted_Input_struct_t;

typedef struct {
    gpMacCore_SetBeaconStarted_Input_struct_t data;
} gpMacCore_SetBeaconStarted_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetBeaconStarted_Input_struct_t;

typedef struct {
    gpMacCore_GetBeaconStarted_Input_struct_t data;
} gpMacCore_GetBeaconStarted_Input_marshall_struct_t;

typedef struct {
    Bool BeaconStarted;
} gpMacCore_GetBeaconStarted_Output_struct_t;

typedef struct {
    gpMacCore_GetBeaconStarted_Output_struct_t data;
} gpMacCore_GetBeaconStarted_Output_marshall_struct_t;


typedef struct {
    MACAddress_t* pPanCoordExtendedAddress;
} gpMacCore_GetPanCoordExtendedAddress_Output_struct_t;

typedef struct {
    gpMacCore_GetPanCoordExtendedAddress_Output_struct_t data;
    MACAddress_t pPanCoordExtendedAddress[1];
} gpMacCore_GetPanCoordExtendedAddress_Output_marshall_struct_t;


typedef struct {
    MACAddress_t* pPanCoordExtendedAddress;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetCoordExtendedAddress_Input_struct_t;

typedef struct {
    gpMacCore_SetCoordExtendedAddress_Input_struct_t data;
    MACAddress_t pPanCoordExtendedAddress[1];
} gpMacCore_SetCoordExtendedAddress_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetCoordExtendedAddress_Input_struct_t;

typedef struct {
    gpMacCore_GetCoordExtendedAddress_Input_struct_t data;
} gpMacCore_GetCoordExtendedAddress_Input_marshall_struct_t;

typedef struct {
    MACAddress_t* pPanCoordExtendedAddress;
} gpMacCore_GetCoordExtendedAddress_Output_struct_t;

typedef struct {
    gpMacCore_GetCoordExtendedAddress_Output_struct_t data;
    MACAddress_t pPanCoordExtendedAddress[1];
} gpMacCore_GetCoordExtendedAddress_Output_marshall_struct_t;


typedef struct {
    UInt16 panCoordShortAddress;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetCoordShortAddress_Input_struct_t;

typedef struct {
    gpMacCore_SetCoordShortAddress_Input_struct_t data;
} gpMacCore_SetCoordShortAddress_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetCoordShortAddress_Input_struct_t;

typedef struct {
    gpMacCore_GetCoordShortAddress_Input_struct_t data;
} gpMacCore_GetCoordShortAddress_Input_marshall_struct_t;

typedef struct {
    UInt16 panCoordShortAddress;
} gpMacCore_GetCoordShortAddress_Output_struct_t;

typedef struct {
    gpMacCore_GetCoordShortAddress_Output_struct_t data;
} gpMacCore_GetCoordShortAddress_Output_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetAssociationPermit_Input_struct_t;

typedef struct {
    gpMacCore_GetAssociationPermit_Input_struct_t data;
} gpMacCore_GetAssociationPermit_Input_marshall_struct_t;

typedef struct {
    Bool associationPermit;
} gpMacCore_GetAssociationPermit_Output_struct_t;

typedef struct {
    gpMacCore_GetAssociationPermit_Output_struct_t data;
} gpMacCore_GetAssociationPermit_Output_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetBeaconPayload_Input_struct_t;

typedef struct {
    gpMacCore_GetBeaconPayload_Input_struct_t data;
} gpMacCore_GetBeaconPayload_Input_marshall_struct_t;

typedef struct {
    UInt8* pBeaconPayload;
} gpMacCore_GetBeaconPayload_Output_struct_t;

typedef struct {
    gpMacCore_GetBeaconPayload_Output_struct_t data;
    UInt8 pBeaconPayload[GP_MACCORE_MAX_BEACON_PAYLOAD_LENGTH];
} gpMacCore_GetBeaconPayload_Output_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetBeaconPayloadLength_Input_struct_t;

typedef struct {
    gpMacCore_GetBeaconPayloadLength_Input_struct_t data;
} gpMacCore_GetBeaconPayloadLength_Input_marshall_struct_t;

typedef struct {
    UInt8 beaconPayloadLength;
} gpMacCore_GetBeaconPayloadLength_Output_struct_t;

typedef struct {
    gpMacCore_GetBeaconPayloadLength_Output_struct_t data;
} gpMacCore_GetBeaconPayloadLength_Output_marshall_struct_t;


typedef struct {
    Bool enable;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetIndicateBeaconNotifications_Input_struct_t;

typedef struct {
    gpMacCore_SetIndicateBeaconNotifications_Input_struct_t data;
} gpMacCore_SetIndicateBeaconNotifications_Input_marshall_struct_t;


typedef struct {
    UInt8 promiscuousMode;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetPromiscuousMode_Input_struct_t;

typedef struct {
    gpMacCore_SetPromiscuousMode_Input_struct_t data;
} gpMacCore_SetPromiscuousMode_Input_marshall_struct_t;


typedef struct {
    gpMacCore_MacVersion_t macVersion;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetMacVersion_Input_struct_t;

typedef struct {
    gpMacCore_SetMacVersion_Input_struct_t data;
} gpMacCore_SetMacVersion_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetMacVersion_Input_struct_t;

typedef struct {
    gpMacCore_GetMacVersion_Input_struct_t data;
} gpMacCore_GetMacVersion_Input_marshall_struct_t;

typedef struct {
    gpMacCore_MacVersion_t macVersion;
} gpMacCore_GetMacVersion_Output_struct_t;

typedef struct {
    gpMacCore_GetMacVersion_Output_struct_t data;
} gpMacCore_GetMacVersion_Output_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_StackAdded_Input_struct_t;

typedef struct {
    gpMacCore_StackAdded_Input_struct_t data;
} gpMacCore_StackAdded_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_StackRemoved_Input_struct_t;

typedef struct {
    gpMacCore_StackRemoved_Input_struct_t data;
} gpMacCore_StackRemoved_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetIndicateBeaconNotifications_Input_struct_t;

typedef struct {
    gpMacCore_GetIndicateBeaconNotifications_Input_struct_t data;
} gpMacCore_GetIndicateBeaconNotifications_Input_marshall_struct_t;

typedef struct {
    Bool enabled;
} gpMacCore_GetIndicateBeaconNotifications_Output_struct_t;

typedef struct {
    gpMacCore_GetIndicateBeaconNotifications_Output_struct_t data;
} gpMacCore_GetIndicateBeaconNotifications_Output_marshall_struct_t;


typedef struct {
    UInt8 cCAMode;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetCCAMode_Input_struct_t;

typedef struct {
    gpMacCore_SetCCAMode_Input_struct_t data;
} gpMacCore_SetCCAMode_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetCCAMode_Input_struct_t;

typedef struct {
    gpMacCore_GetCCAMode_Input_struct_t data;
} gpMacCore_GetCCAMode_Input_marshall_struct_t;

typedef struct {
    UInt8 cCAMode;
} gpMacCore_GetCCAMode_Output_struct_t;

typedef struct {
    gpMacCore_GetCCAMode_Output_struct_t data;
} gpMacCore_GetCCAMode_Output_marshall_struct_t;


typedef struct {
    UInt8 minBE;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetMinBE_Input_struct_t;

typedef struct {
    gpMacCore_SetMinBE_Input_struct_t data;
} gpMacCore_SetMinBE_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetMinBE_Input_struct_t;

typedef struct {
    gpMacCore_GetMinBE_Input_struct_t data;
} gpMacCore_GetMinBE_Input_marshall_struct_t;

typedef struct {
    UInt8 minBE;
} gpMacCore_GetMinBE_Output_struct_t;

typedef struct {
    gpMacCore_GetMinBE_Output_struct_t data;
} gpMacCore_GetMinBE_Output_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetPromiscuousMode_Input_struct_t;

typedef struct {
    gpMacCore_GetPromiscuousMode_Input_struct_t data;
} gpMacCore_GetPromiscuousMode_Input_marshall_struct_t;

typedef struct {
    Bool promiscuousMode;
} gpMacCore_GetPromiscuousMode_Output_struct_t;

typedef struct {
    gpMacCore_GetPromiscuousMode_Output_struct_t data;
} gpMacCore_GetPromiscuousMode_Output_marshall_struct_t;


typedef struct {
    gpPd_Handle_t pdHandle;
    gpMacCore_StackId_t stackId;
} gpMacCore_PurgeRequest_Input_struct_t;

typedef struct {
    gpMacCore_PurgeRequest_Input_struct_t data;
} gpMacCore_PurgeRequest_Input_marshall_struct_t;


typedef struct {
    Bool enable;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetForwardPollIndications_Input_struct_t;

typedef struct {
    gpMacCore_SetForwardPollIndications_Input_struct_t data;
} gpMacCore_SetForwardPollIndications_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetForwardPollIndications_Input_struct_t;

typedef struct {
    gpMacCore_GetForwardPollIndications_Input_struct_t data;
} gpMacCore_GetForwardPollIndications_Input_marshall_struct_t;

typedef struct {
    Bool enable;
} gpMacCore_GetForwardPollIndications_Output_struct_t;

typedef struct {
    gpMacCore_GetForwardPollIndications_Output_struct_t data;
} gpMacCore_GetForwardPollIndications_Output_marshall_struct_t;


typedef struct {
    UInt8 maxBE;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetMaxBE_Input_struct_t;

typedef struct {
    gpMacCore_SetMaxBE_Input_struct_t data;
} gpMacCore_SetMaxBE_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetMaxBE_Input_struct_t;

typedef struct {
    gpMacCore_GetMaxBE_Input_struct_t data;
} gpMacCore_GetMaxBE_Input_marshall_struct_t;

typedef struct {
    UInt8 maxBE;
} gpMacCore_GetMaxBE_Output_struct_t;

typedef struct {
    gpMacCore_GetMaxBE_Output_struct_t data;
} gpMacCore_GetMaxBE_Output_marshall_struct_t;


typedef struct {
    gpMacCore_AddressInfo_t* pAddrInfo;
    gpMacCore_StackId_t stackId;
} gpMacCore_AddNeighbour_Input_struct_t;

typedef struct {
    gpMacCore_AddNeighbour_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pAddrInfo;
} gpMacCore_AddNeighbour_Input_marshall_struct_t;

typedef struct {
    Bool result;
} gpMacCore_AddNeighbour_Output_struct_t;

typedef struct {
    gpMacCore_AddNeighbour_Output_struct_t data;
} gpMacCore_AddNeighbour_Output_marshall_struct_t;


typedef struct {
    gpMacCore_AddressInfo_t* pAddrInfo;
    gpMacCore_StackId_t stackId;
} gpMacCore_RemoveNeighbour_Input_struct_t;

typedef struct {
    gpMacCore_RemoveNeighbour_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pAddrInfo;
} gpMacCore_RemoveNeighbour_Input_marshall_struct_t;

typedef struct {
    Bool result;
} gpMacCore_RemoveNeighbour_Output_struct_t;

typedef struct {
    gpMacCore_RemoveNeighbour_Output_struct_t data;
} gpMacCore_RemoveNeighbour_Output_marshall_struct_t;


typedef struct {
    gpMacCore_DataPendingMode_t dataPendingMode;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetDataPendingMode_Input_struct_t;

typedef struct {
    gpMacCore_SetDataPendingMode_Input_struct_t data;
} gpMacCore_SetDataPendingMode_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
} gpMacCore_SetDataPendingMode_Output_struct_t;

typedef struct {
    gpMacCore_SetDataPendingMode_Output_struct_t data;
} gpMacCore_SetDataPendingMode_Output_marshall_struct_t;



typedef struct {
    UInt8 addressMode;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetAddressModeOverrideForBeacons_Input_struct_t;

typedef struct {
    gpMacCore_SetAddressModeOverrideForBeacons_Input_struct_t data;
} gpMacCore_SetAddressModeOverrideForBeacons_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_ClearNeighbours_Input_struct_t;

typedef struct {
    gpMacCore_ClearNeighbours_Input_struct_t data;
} gpMacCore_ClearNeighbours_Input_marshall_struct_t;


typedef struct {
    UInt8 csmaMode;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetCsmaMode_Input_struct_t;

typedef struct {
    gpMacCore_SetCsmaMode_Input_struct_t data;
} gpMacCore_SetCsmaMode_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetCsmaMode_Input_struct_t;

typedef struct {
    gpMacCore_GetCsmaMode_Input_struct_t data;
} gpMacCore_GetCsmaMode_Input_marshall_struct_t;

typedef struct {
    UInt8 csmaMode;
} gpMacCore_GetCsmaMode_Output_struct_t;

typedef struct {
    gpMacCore_GetCsmaMode_Output_struct_t data;
} gpMacCore_GetCsmaMode_Output_marshall_struct_t;


typedef struct {
    gpPd_Handle_t pdHandle;
    gpMacCore_TxTimingOptions_t timingOptions;
    gpMacCore_StackId_t stackId;
} gpMacCore_ScheduleTimedTx_Input_struct_t;

typedef struct {
    gpMacCore_ScheduleTimedTx_Input_struct_t data;
    gpMacCore_TxTimingOptions_t_l1_pointer_marshall_t timingOptions;
} gpMacCore_ScheduleTimedTx_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
} gpMacCore_ScheduleTimedTx_Output_struct_t;

typedef struct {
    gpMacCore_ScheduleTimedTx_Output_struct_t data;
} gpMacCore_ScheduleTimedTx_Output_marshall_struct_t;



typedef struct {
    gpMacCore_AddressInfo_t* pAddrInfo;
    gpMacCore_StackId_t stackId;
} gpMacCore_DataPending_QueueAdd_Input_struct_t;

typedef struct {
    gpMacCore_DataPending_QueueAdd_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pAddrInfo;
} gpMacCore_DataPending_QueueAdd_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
} gpMacCore_DataPending_QueueAdd_Output_struct_t;

typedef struct {
    gpMacCore_DataPending_QueueAdd_Output_struct_t data;
} gpMacCore_DataPending_QueueAdd_Output_marshall_struct_t;


typedef struct {
    gpMacCore_AddressInfo_t* pAddrInfo;
    gpMacCore_StackId_t stackId;
} gpMacCore_DataPending_QueueRemove_Input_struct_t;

typedef struct {
    gpMacCore_DataPending_QueueRemove_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pAddrInfo;
} gpMacCore_DataPending_QueueRemove_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
} gpMacCore_DataPending_QueueRemove_Output_struct_t;

typedef struct {
    gpMacCore_DataPending_QueueRemove_Output_struct_t data;
} gpMacCore_DataPending_QueueRemove_Output_marshall_struct_t;





typedef struct {
    Int8* pInterferenceLevels;
} gpMacCore_SetMinInterferenceLevels_Input_struct_t;

typedef struct {
    gpMacCore_SetMinInterferenceLevels_Input_struct_t data;
    Int8 pInterferenceLevels[16];
} gpMacCore_SetMinInterferenceLevels_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
} gpMacCore_SetMinInterferenceLevels_Output_struct_t;

typedef struct {
    gpMacCore_SetMinInterferenceLevels_Output_struct_t data;
} gpMacCore_SetMinInterferenceLevels_Output_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_DataPending_QueueClear_Input_struct_t;

typedef struct {
    gpMacCore_DataPending_QueueClear_Input_struct_t data;
} gpMacCore_DataPending_QueueClear_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
} gpMacCore_DataPending_QueueClear_Output_struct_t;

typedef struct {
    gpMacCore_DataPending_QueueClear_Output_struct_t data;
} gpMacCore_DataPending_QueueClear_Output_marshall_struct_t;


typedef struct {
    Bool pending;
} gpMacCore_DataPendingGetAckDataPending_Output_struct_t;

typedef struct {
    gpMacCore_DataPendingGetAckDataPending_Output_struct_t data;
} gpMacCore_DataPendingGetAckDataPending_Output_marshall_struct_t;


typedef struct {
    Bool rawModeEnabled;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetStackInRawMode_Input_struct_t;

typedef struct {
    gpMacCore_SetStackInRawMode_Input_struct_t data;
} gpMacCore_SetStackInRawMode_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetStackInRawMode_Input_struct_t;

typedef struct {
    gpMacCore_GetStackInRawMode_Input_struct_t data;
} gpMacCore_GetStackInRawMode_Input_marshall_struct_t;

typedef struct {
    Bool rawModeEnabled;
} gpMacCore_GetStackInRawMode_Output_struct_t;

typedef struct {
    gpMacCore_GetStackInRawMode_Output_struct_t data;
} gpMacCore_GetStackInRawMode_Output_marshall_struct_t;


typedef struct {
    Bool enableEnhancedFramePending;
    gpMacCore_StackId_t stackId;
} gpMacCore_EnableEnhancedFramePending_Input_struct_t;

typedef struct {
    gpMacCore_EnableEnhancedFramePending_Input_struct_t data;
} gpMacCore_EnableEnhancedFramePending_Input_marshall_struct_t;


typedef struct {
    UInt32 dutyCycleOnTime;
    UInt32 dutyCyclePeriod;
    UInt16 recurrenceAmount;
    UInt32 startTime;
    gpMacCore_StackId_t stackId;
} gpMacCore_EnableRxWindows_Input_struct_t;

typedef struct {
    gpMacCore_EnableRxWindows_Input_struct_t data;
} gpMacCore_EnableRxWindows_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_DisableRxWindows_Input_struct_t;

typedef struct {
    gpMacCore_DisableRxWindows_Input_struct_t data;
} gpMacCore_DisableRxWindows_Input_marshall_struct_t;


typedef struct {
    UInt16 dutyCyclePeriod;
    gpMacCore_StackId_t stackId;
} gpMacCore_EnableCsl_Input_struct_t;

typedef struct {
    gpMacCore_EnableCsl_Input_struct_t data;
} gpMacCore_EnableCsl_Input_marshall_struct_t;


typedef struct {
    UInt32 nextCslSampleTime;
    gpMacCore_StackId_t stackId;
} gpMacCore_UpdateCslSampleTime_Input_struct_t;

typedef struct {
    gpMacCore_UpdateCslSampleTime_Input_struct_t data;
} gpMacCore_UpdateCslSampleTime_Input_marshall_struct_t;


typedef struct {
    UInt32 currentTime;
} gpMacCore_GetCurrentTimeUs_Output_struct_t;

typedef struct {
    gpMacCore_GetCurrentTimeUs_Output_struct_t data;
} gpMacCore_GetCurrentTimeUs_Output_marshall_struct_t;


typedef struct {
    UInt8 linkMetrics;
    MACAddress_t* pExtendedAddress;
    UInt16 shortAddress;
    gpMacCore_StackId_t stackId;
} gpMacCore_ConfigureEnhAckProbing_Input_struct_t;

typedef struct {
    gpMacCore_ConfigureEnhAckProbing_Input_struct_t data;
    MACAddress_t pExtendedAddress[1];
} gpMacCore_ConfigureEnhAckProbing_Input_marshall_struct_t;

typedef struct {
    gpMacCore_Result_t result;
} gpMacCore_ConfigureEnhAckProbing_Output_struct_t;

typedef struct {
    gpMacCore_ConfigureEnhAckProbing_Output_struct_t data;
} gpMacCore_ConfigureEnhAckProbing_Output_marshall_struct_t;


typedef struct {
    Bool enable;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetRetransmitOnCcaFail_Input_struct_t;

typedef struct {
    gpMacCore_SetRetransmitOnCcaFail_Input_struct_t data;
} gpMacCore_SetRetransmitOnCcaFail_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetRetransmitOnCcaFail_Input_struct_t;

typedef struct {
    gpMacCore_GetRetransmitOnCcaFail_Input_struct_t data;
} gpMacCore_GetRetransmitOnCcaFail_Input_marshall_struct_t;

typedef struct {
    Bool enable;
} gpMacCore_GetRetransmitOnCcaFail_Output_struct_t;

typedef struct {
    gpMacCore_GetRetransmitOnCcaFail_Output_struct_t data;
} gpMacCore_GetRetransmitOnCcaFail_Output_marshall_struct_t;


typedef struct {
    Bool enable;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetRetransmitRandomBackoff_Input_struct_t;

typedef struct {
    gpMacCore_SetRetransmitRandomBackoff_Input_struct_t data;
} gpMacCore_SetRetransmitRandomBackoff_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetRetransmitRandomBackoff_Input_struct_t;

typedef struct {
    gpMacCore_GetRetransmitRandomBackoff_Input_struct_t data;
} gpMacCore_GetRetransmitRandomBackoff_Input_marshall_struct_t;

typedef struct {
    Bool enable;
} gpMacCore_GetRetransmitRandomBackoff_Output_struct_t;

typedef struct {
    gpMacCore_GetRetransmitRandomBackoff_Output_struct_t data;
} gpMacCore_GetRetransmitRandomBackoff_Output_marshall_struct_t;


typedef struct {
    UInt8 minBERetransmit;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetMinBeRetransmit_Input_struct_t;

typedef struct {
    gpMacCore_SetMinBeRetransmit_Input_struct_t data;
} gpMacCore_SetMinBeRetransmit_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetMinBeRetransmit_Input_struct_t;

typedef struct {
    gpMacCore_GetMinBeRetransmit_Input_struct_t data;
} gpMacCore_GetMinBeRetransmit_Input_marshall_struct_t;

typedef struct {
    UInt8 minBERetransmit;
} gpMacCore_GetMinBeRetransmit_Output_struct_t;

typedef struct {
    gpMacCore_GetMinBeRetransmit_Output_struct_t data;
} gpMacCore_GetMinBeRetransmit_Output_marshall_struct_t;


typedef struct {
    UInt8 maxBERetransmit;
    gpMacCore_StackId_t stackId;
} gpMacCore_SetMaxBeRetransmit_Input_struct_t;

typedef struct {
    gpMacCore_SetMaxBeRetransmit_Input_struct_t data;
} gpMacCore_SetMaxBeRetransmit_Input_marshall_struct_t;


typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_GetMaxBeRetransmit_Input_struct_t;

typedef struct {
    gpMacCore_GetMaxBeRetransmit_Input_struct_t data;
} gpMacCore_GetMaxBeRetransmit_Input_marshall_struct_t;

typedef struct {
    UInt8 maxBERetransmit;
} gpMacCore_GetMaxBeRetransmit_Output_struct_t;

typedef struct {
    gpMacCore_GetMaxBeRetransmit_Output_struct_t data;
} gpMacCore_GetMaxBeRetransmit_Output_marshall_struct_t;


#if !defined(GP_COMP_MACDISPATCHER)
typedef struct {
    gpMacCore_Result_t status;
    gpPd_Handle_t pdHandle;
} gpMacCore_cbDataConfirm_Input_struct_t;

typedef struct {
    gpMacCore_cbDataConfirm_Input_struct_t data;
} gpMacCore_cbDataConfirm_Input_marshall_struct_t;

#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */

#if !defined(GP_COMP_MACDISPATCHER)
typedef struct {
    gpMacCore_AddressInfo_t* pSrcAddrInfo;
    gpMacCore_AddressInfo_t* pDstAddrInfo;
    UInt8 dsn;
    gpMacCore_Security_t* pSecOptions;
    gpPd_Loh_t pdLoh;
    gpMacCore_StackId_t stackId;
} gpMacCore_cbDataIndication_Input_struct_t;

typedef struct {
    gpMacCore_cbDataIndication_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pSrcAddrInfo;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pDstAddrInfo;
    gpMacCore_Security_t_l1_pointer_marshall_t pSecOptions;
    gpPd_Loh_t_l1_pointer_marshall_t pdLoh;
} gpMacCore_cbDataIndication_Input_marshall_struct_t;

#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */

#if !defined(GP_COMP_MACDISPATCHER)
typedef struct {
    gpMacCore_Result_t status;
    gpMacCore_ScanType_t scanType;
    UInt32 unscannedChannels;
    UInt8 resultListSize;
    UInt8* pEdScanResultList;
} gpMacCore_cbScanConfirm_Input_struct_t;

typedef struct {
    gpMacCore_cbScanConfirm_Input_struct_t data;
    UInt8 pEdScanResultList[27];
} gpMacCore_cbScanConfirm_Input_marshall_struct_t;

#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */

#if !defined(GP_COMP_MACDISPATCHER)
typedef struct {
    UInt8 bsn;
    gpMacCore_PanDescriptor_t* pPanDescriptor;
    gpMacCore_StackId_t stackId;
    UInt8 beaconPayloadLength;
    UInt8* pBeaconPayload;
} gpMacCore_cbBeaconNotifyIndication_Input_struct_t;

typedef struct {
    gpMacCore_cbBeaconNotifyIndication_Input_struct_t data;
    gpMacCore_PanDescriptor_t_l1_pointer_marshall_t pPanDescriptor;
    UInt8 pBeaconPayload[52];
} gpMacCore_cbBeaconNotifyIndication_Input_marshall_struct_t;

#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */

#if !defined(GP_COMP_MACDISPATCHER)
typedef struct {
    MACAddress_t* pOrphanAddress;
    gpMacCore_StackId_t stackId;
    gpPd_TimeStamp_t rxTime;
} gpMacCore_cbOrphanIndication_Input_struct_t;

typedef struct {
    gpMacCore_cbOrphanIndication_Input_struct_t data;
    MACAddress_t pOrphanAddress[1];
} gpMacCore_cbOrphanIndication_Input_marshall_struct_t;

#endif /* defined(GP_MACCORE_DIVERSITY_ASSOCIATION_ORIGINATOR) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */

#if !defined(GP_COMP_MACDISPATCHER)
typedef struct {
    gpMacCore_AddressInfo_t* pSrcAddressInfo;
    gpMacCore_AddressInfo_t* pDstAddressInfo;
    gpMacCore_Result_t status;
    gpMacCore_StackId_t stackId;
    gpPd_TimeStamp_t txTime;
} gpMacCore_cbSecurityFailureCommStatusIndication_Input_struct_t;

typedef struct {
    gpMacCore_cbSecurityFailureCommStatusIndication_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pSrcAddressInfo;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pDstAddressInfo;
} gpMacCore_cbSecurityFailureCommStatusIndication_Input_marshall_struct_t;

#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */

#if !defined(GP_COMP_MACDISPATCHER)
typedef struct {
    gpMacCore_Result_t status;
    gpMacCore_AddressInfo_t* coordAddrInfo;
    gpPd_TimeStamp_t txTime;
} gpMacCore_cbPollConfirm_Input_struct_t;

typedef struct {
    gpMacCore_cbPollConfirm_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t coordAddrInfo;
} gpMacCore_cbPollConfirm_Input_marshall_struct_t;

#endif /* defined(GP_MACCORE_DIVERSITY_POLL_ORIGINATOR) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */

#if !defined(GP_COMP_MACDISPATCHER)
typedef struct {
    gpMacCore_AddressInfo_t* addressInfo;
    gpMacCore_StackId_t stackId;
    gpPd_TimeStamp_t rxTime;
} gpMacCore_cbPollIndication_Input_struct_t;

typedef struct {
    gpMacCore_cbPollIndication_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t addressInfo;
} gpMacCore_cbPollIndication_Input_marshall_struct_t;

#endif /* defined(GP_MACCORE_DIVERSITY_POLL_RECIPIENT) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */

#if !defined(GP_COMP_MACDISPATCHER)
typedef struct {
    UInt16 assocShortAddress;
    gpMacCore_Result_t status;
    gpPd_TimeStamp_t txTime;
} gpMacCore_cbAssociateConfirm_Input_struct_t;

typedef struct {
    gpMacCore_cbAssociateConfirm_Input_struct_t data;
} gpMacCore_cbAssociateConfirm_Input_marshall_struct_t;

#endif /* defined(GP_MACCORE_DIVERSITY_ASSOCIATION_ORIGINATOR) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */

#if !defined(GP_COMP_MACDISPATCHER)
typedef struct {
    gpMacCore_Address_t* pDeviceAddress;
    UInt8 capabilityInformation;
    gpMacCore_StackId_t stackId;
    gpPd_TimeStamp_t rxTime;
} gpMacCore_cbAssociateIndication_Input_struct_t;

typedef struct {
    gpMacCore_cbAssociateIndication_Input_struct_t data;
    gpMacCore_Address_t_l1_pointer_marshall_t pDeviceAddress;
} gpMacCore_cbAssociateIndication_Input_marshall_struct_t;

#endif /* defined(GP_MACCORE_DIVERSITY_ASSOCIATION_RECIPIENT) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */

#if !defined(GP_COMP_MACDISPATCHER)
typedef struct {
    gpMacCore_AddressInfo_t* pSrcAddressInfo;
    gpMacCore_AddressInfo_t* pDstAddressInfo;
    gpMacCore_Result_t status;
    gpMacCore_StackId_t stackId;
    gpPd_TimeStamp_t txTime;
} gpMacCore_cbAssociateCommStatusIndication_Input_struct_t;

typedef struct {
    gpMacCore_cbAssociateCommStatusIndication_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pSrcAddressInfo;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pDstAddressInfo;
} gpMacCore_cbAssociateCommStatusIndication_Input_marshall_struct_t;

#endif /* defined(GP_MACCORE_DIVERSITY_ASSOCIATION_RECIPIENT) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */

#if !defined(GP_COMP_MACDISPATCHER)
typedef struct {
    gpMacCore_AddressInfo_t* pSrcAddressInfo;
    gpMacCore_AddressInfo_t* pDstAddressInfo;
    gpMacCore_Result_t status;
    gpMacCore_StackId_t stackId;
    gpPd_TimeStamp_t txTime;
} gpMacCore_cbOrphanCommStatusIndication_Input_struct_t;

typedef struct {
    gpMacCore_cbOrphanCommStatusIndication_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pSrcAddressInfo;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t pDstAddressInfo;
} gpMacCore_cbOrphanCommStatusIndication_Input_marshall_struct_t;

#endif /* defined(GP_MACCORE_DIVERSITY_SCAN_ORPHAN_RECIPIENT) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */

#if !defined(GP_COMP_MACDISPATCHER)
typedef struct {
    gpMacCore_StackId_t stackId;
} gpMacCore_cbValidStack_Input_struct_t;

typedef struct {
    gpMacCore_cbValidStack_Input_struct_t data;
} gpMacCore_cbValidStack_Input_marshall_struct_t;

typedef struct {
    Bool valid;
} gpMacCore_cbValidStack_Output_struct_t;

typedef struct {
    gpMacCore_cbValidStack_Output_struct_t data;
} gpMacCore_cbValidStack_Output_marshall_struct_t;

#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */

#if !defined(GP_COMP_MACDISPATCHER)
typedef struct {
    gpMacCore_Result_t status;
    gpPd_Handle_t pdHandle;
} gpMacCore_cbPurgeConfirm_Input_struct_t;

typedef struct {
    gpMacCore_cbPurgeConfirm_Input_struct_t data;
} gpMacCore_cbPurgeConfirm_Input_marshall_struct_t;

#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */

#if !defined(GP_COMP_MACDISPATCHER)
typedef struct {
    gpMacCore_AddressInfo_t* addressInfo;
    gpMacCore_StackId_t stackId;
    gpPd_TimeStamp_t rxTime;
    gpPd_Handle_t pdHandle;
    Bool fromNeighbour;
} gpMacCore_cbPollNotify_Input_struct_t;

typedef struct {
    gpMacCore_cbPollNotify_Input_struct_t data;
    gpMacCore_AddressInfo_t_l1_pointer_marshall_t addressInfo;
} gpMacCore_cbPollNotify_Input_marshall_struct_t;

#endif /* defined(GP_MACCORE_DIVERSITY_POLL_RECIPIENT) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */

#if !(defined(GP_COMP_MACDISPATCHER))
typedef struct {
    UInt32 frameCounter;
    gpMacCore_StackId_t stackId;
} gpMacCore_cbSecurityFrameCounterIndication_Input_struct_t;

typedef struct {
    gpMacCore_cbSecurityFrameCounterIndication_Input_struct_t data;
} gpMacCore_cbSecurityFrameCounterIndication_Input_marshall_struct_t;

#endif /* !(defined(GP_COMP_MACDISPATCHER)) */

typedef union {
    gpMacCore_Reset_Input_marshall_struct_t gpMacCore_Reset;
    gpMacCore_DataRequest_Input_marshall_struct_t gpMacCore_DataRequest;
    gpMacCore_ScanRequest_Input_marshall_struct_t gpMacCore_ScanRequest;
    gpMacCore_AssociateRequest_Input_marshall_struct_t gpMacCore_AssociateRequest;
    gpMacCore_AssociateResponse_Input_marshall_struct_t gpMacCore_AssociateResponse;
    gpMacCore_PollRequest_Input_marshall_struct_t gpMacCore_PollRequest;
    gpMacCore_Start_Input_marshall_struct_t gpMacCore_Start;
    gpMacCore_SetSecurityEnabled_Input_marshall_struct_t gpMacCore_SetSecurityEnabled;
    gpMacCore_SetDeviceDescriptor_Input_marshall_struct_t gpMacCore_SetDeviceDescriptor;
    gpMacCore_GetDeviceDescriptor_Input_marshall_struct_t gpMacCore_GetDeviceDescriptor;
    gpMacCore_SetDeviceTableEntries_Input_marshall_struct_t gpMacCore_SetDeviceTableEntries;
    gpMacCore_SetKeyDescriptor_Input_marshall_struct_t gpMacCore_SetKeyDescriptor;
    gpMacCore_GetKeyDescriptor_Input_marshall_struct_t gpMacCore_GetKeyDescriptor;
    gpMacCore_SetKeyTableEntries_Input_marshall_struct_t gpMacCore_SetKeyTableEntries;
    gpMacCore_SetSecurityLevelDescriptor_Input_marshall_struct_t gpMacCore_SetSecurityLevelDescriptor;
    gpMacCore_GetSecurityLevelDescriptor_Input_marshall_struct_t gpMacCore_GetSecurityLevelDescriptor;
    gpMacCore_SetSecurityLevelTableEntries_Input_marshall_struct_t gpMacCore_SetSecurityLevelTableEntries;
    gpMacCore_SetDefaultKeySource_Input_marshall_struct_t gpMacCore_SetDefaultKeySource;
    gpMacCore_SetShortAddress_Input_marshall_struct_t gpMacCore_SetShortAddress;
    gpMacCore_SetExtendedAddress_Input_marshall_struct_t gpMacCore_SetExtendedAddress;
    gpMacCore_SetPanId_Input_marshall_struct_t gpMacCore_SetPanId;
    gpMacCore_GetPanId_Input_marshall_struct_t gpMacCore_GetPanId;
    gpMacCore_SetFrameCounter_Input_marshall_struct_t gpMacCore_SetFrameCounter;
    gpMacCore_SetDsn_Input_marshall_struct_t gpMacCore_SetDsn;
    gpMacCore_SetCurrentChannel_Input_marshall_struct_t gpMacCore_SetCurrentChannel;
    gpMacCore_SetBeaconPayload_Input_marshall_struct_t gpMacCore_SetBeaconPayload;
    gpMacCore_SetBeaconPayloadLength_Input_marshall_struct_t gpMacCore_SetBeaconPayloadLength;
    gpMacCore_SetRxOnWhenIdle_Input_marshall_struct_t gpMacCore_SetRxOnWhenIdle;
    gpMacCore_GetExtendedAddress_Input_marshall_struct_t gpMacCore_GetExtendedAddress;
    gpMacCore_SetMaxCsmaBackoffs_Input_marshall_struct_t gpMacCore_SetMaxCsmaBackoffs;
    gpMacCore_GetMaxCsmaBackoffs_Input_marshall_struct_t gpMacCore_GetMaxCsmaBackoffs;
    gpMacCore_GetDsn_Input_marshall_struct_t gpMacCore_GetDsn;
    gpMacCore_GetCurrentChannel_Input_marshall_struct_t gpMacCore_GetCurrentChannel;
    gpMacCore_SetNumberOfRetries_Input_marshall_struct_t gpMacCore_SetNumberOfRetries;
    gpMacCore_GetNumberOfRetries_Input_marshall_struct_t gpMacCore_GetNumberOfRetries;
    gpMacCore_GetFrameCounter_Input_marshall_struct_t gpMacCore_GetFrameCounter;
    gpMacCore_GetRxOnWhenIdle_Input_marshall_struct_t gpMacCore_GetRxOnWhenIdle;
    gpMacCore_GetShortAddress_Input_marshall_struct_t gpMacCore_GetShortAddress;
    gpMacCore_SetPanCoordShortAddress_Input_marshall_struct_t gpMacCore_SetPanCoordShortAddress;
    gpMacCore_SetPanCoordExtendedAddress_Input_marshall_struct_t gpMacCore_SetPanCoordExtendedAddress;
    gpMacCore_SetAssociationPermit_Input_marshall_struct_t gpMacCore_SetAssociationPermit;
    gpMacCore_SetDefaultTransmitPowers_Input_marshall_struct_t gpMacCore_SetDefaultTransmitPowers;
    gpMacCore_SetTransmitPower_Input_marshall_struct_t gpMacCore_SetTransmitPower;
    gpMacCore_GetTransmitPower_Input_marshall_struct_t gpMacCore_GetTransmitPower;
    gpMacCore_SetPanCoordinator_Input_marshall_struct_t gpMacCore_SetPanCoordinator;
    gpMacCore_GetPanCoordinator_Input_marshall_struct_t gpMacCore_GetPanCoordinator;
    gpMacCore_OrphanResponse_Input_marshall_struct_t gpMacCore_OrphanResponse;
    gpMacCore_GetSecurityEnabled_Input_marshall_struct_t gpMacCore_GetSecurityEnabled;
    gpMacCore_GetTransactionPersistenceTime_Input_marshall_struct_t gpMacCore_GetTransactionPersistenceTime;
    gpMacCore_SetTransactionPersistenceTime_Input_marshall_struct_t gpMacCore_SetTransactionPersistenceTime;
    gpMacCore_SetBeaconStarted_Input_marshall_struct_t gpMacCore_SetBeaconStarted;
    gpMacCore_GetBeaconStarted_Input_marshall_struct_t gpMacCore_GetBeaconStarted;
    gpMacCore_SetCoordExtendedAddress_Input_marshall_struct_t gpMacCore_SetCoordExtendedAddress;
    gpMacCore_GetCoordExtendedAddress_Input_marshall_struct_t gpMacCore_GetCoordExtendedAddress;
    gpMacCore_SetCoordShortAddress_Input_marshall_struct_t gpMacCore_SetCoordShortAddress;
    gpMacCore_GetCoordShortAddress_Input_marshall_struct_t gpMacCore_GetCoordShortAddress;
    gpMacCore_GetAssociationPermit_Input_marshall_struct_t gpMacCore_GetAssociationPermit;
    gpMacCore_GetBeaconPayload_Input_marshall_struct_t gpMacCore_GetBeaconPayload;
    gpMacCore_GetBeaconPayloadLength_Input_marshall_struct_t gpMacCore_GetBeaconPayloadLength;
    gpMacCore_SetIndicateBeaconNotifications_Input_marshall_struct_t gpMacCore_SetIndicateBeaconNotifications;
    gpMacCore_SetPromiscuousMode_Input_marshall_struct_t gpMacCore_SetPromiscuousMode;
    gpMacCore_SetMacVersion_Input_marshall_struct_t gpMacCore_SetMacVersion;
    gpMacCore_GetMacVersion_Input_marshall_struct_t gpMacCore_GetMacVersion;
    gpMacCore_StackAdded_Input_marshall_struct_t gpMacCore_StackAdded;
    gpMacCore_StackRemoved_Input_marshall_struct_t gpMacCore_StackRemoved;
    gpMacCore_GetIndicateBeaconNotifications_Input_marshall_struct_t gpMacCore_GetIndicateBeaconNotifications;
    gpMacCore_SetCCAMode_Input_marshall_struct_t gpMacCore_SetCCAMode;
    gpMacCore_GetCCAMode_Input_marshall_struct_t gpMacCore_GetCCAMode;
    gpMacCore_SetMinBE_Input_marshall_struct_t gpMacCore_SetMinBE;
    gpMacCore_GetMinBE_Input_marshall_struct_t gpMacCore_GetMinBE;
    gpMacCore_GetPromiscuousMode_Input_marshall_struct_t gpMacCore_GetPromiscuousMode;
    gpMacCore_PurgeRequest_Input_marshall_struct_t gpMacCore_PurgeRequest;
    gpMacCore_SetForwardPollIndications_Input_marshall_struct_t gpMacCore_SetForwardPollIndications;
    gpMacCore_GetForwardPollIndications_Input_marshall_struct_t gpMacCore_GetForwardPollIndications;
    gpMacCore_SetMaxBE_Input_marshall_struct_t gpMacCore_SetMaxBE;
    gpMacCore_GetMaxBE_Input_marshall_struct_t gpMacCore_GetMaxBE;
    gpMacCore_AddNeighbour_Input_marshall_struct_t gpMacCore_AddNeighbour;
    gpMacCore_RemoveNeighbour_Input_marshall_struct_t gpMacCore_RemoveNeighbour;
    gpMacCore_SetDataPendingMode_Input_marshall_struct_t gpMacCore_SetDataPendingMode;
    gpMacCore_SetAddressModeOverrideForBeacons_Input_marshall_struct_t gpMacCore_SetAddressModeOverrideForBeacons;
    gpMacCore_ClearNeighbours_Input_marshall_struct_t gpMacCore_ClearNeighbours;
    gpMacCore_SetCsmaMode_Input_marshall_struct_t gpMacCore_SetCsmaMode;
    gpMacCore_GetCsmaMode_Input_marshall_struct_t gpMacCore_GetCsmaMode;
    gpMacCore_ScheduleTimedTx_Input_marshall_struct_t gpMacCore_ScheduleTimedTx;
    gpMacCore_DataPending_QueueAdd_Input_marshall_struct_t gpMacCore_DataPending_QueueAdd;
    gpMacCore_DataPending_QueueRemove_Input_marshall_struct_t gpMacCore_DataPending_QueueRemove;
    gpMacCore_SetMinInterferenceLevels_Input_marshall_struct_t gpMacCore_SetMinInterferenceLevels;
    gpMacCore_DataPending_QueueClear_Input_marshall_struct_t gpMacCore_DataPending_QueueClear;
    gpMacCore_SetStackInRawMode_Input_marshall_struct_t gpMacCore_SetStackInRawMode;
    gpMacCore_GetStackInRawMode_Input_marshall_struct_t gpMacCore_GetStackInRawMode;
    gpMacCore_EnableEnhancedFramePending_Input_marshall_struct_t gpMacCore_EnableEnhancedFramePending;
    gpMacCore_EnableRxWindows_Input_marshall_struct_t gpMacCore_EnableRxWindows;
    gpMacCore_DisableRxWindows_Input_marshall_struct_t gpMacCore_DisableRxWindows;
    gpMacCore_EnableCsl_Input_marshall_struct_t gpMacCore_EnableCsl;
    gpMacCore_UpdateCslSampleTime_Input_marshall_struct_t gpMacCore_UpdateCslSampleTime;
    gpMacCore_ConfigureEnhAckProbing_Input_marshall_struct_t gpMacCore_ConfigureEnhAckProbing;
    gpMacCore_SetRetransmitOnCcaFail_Input_marshall_struct_t gpMacCore_SetRetransmitOnCcaFail;
    gpMacCore_GetRetransmitOnCcaFail_Input_marshall_struct_t gpMacCore_GetRetransmitOnCcaFail;
    gpMacCore_SetRetransmitRandomBackoff_Input_marshall_struct_t gpMacCore_SetRetransmitRandomBackoff;
    gpMacCore_GetRetransmitRandomBackoff_Input_marshall_struct_t gpMacCore_GetRetransmitRandomBackoff;
    gpMacCore_SetMinBeRetransmit_Input_marshall_struct_t gpMacCore_SetMinBeRetransmit;
    gpMacCore_GetMinBeRetransmit_Input_marshall_struct_t gpMacCore_GetMinBeRetransmit;
    gpMacCore_SetMaxBeRetransmit_Input_marshall_struct_t gpMacCore_SetMaxBeRetransmit;
    gpMacCore_GetMaxBeRetransmit_Input_marshall_struct_t gpMacCore_GetMaxBeRetransmit;
    UInt8 dummy; //ensure none empty union definition
} gpMacCore_Server_Input_union_t;

typedef union {
    gpMacCore_Reset_Output_marshall_struct_t gpMacCore_Reset;
    gpMacCore_Start_Output_marshall_struct_t gpMacCore_Start;
    gpMacCore_SetDeviceDescriptor_Output_marshall_struct_t gpMacCore_SetDeviceDescriptor;
    gpMacCore_GetDeviceDescriptor_Output_marshall_struct_t gpMacCore_GetDeviceDescriptor;
    gpMacCore_GetDeviceTableEntries_Output_marshall_struct_t gpMacCore_GetDeviceTableEntries;
    gpMacCore_SetKeyDescriptor_Output_marshall_struct_t gpMacCore_SetKeyDescriptor;
    gpMacCore_GetKeyDescriptor_Output_marshall_struct_t gpMacCore_GetKeyDescriptor;
    gpMacCore_SetSecurityLevelDescriptor_Output_marshall_struct_t gpMacCore_SetSecurityLevelDescriptor;
    gpMacCore_GetSecurityLevelDescriptor_Output_marshall_struct_t gpMacCore_GetSecurityLevelDescriptor;
    gpMacCore_GetSecurityLevelTableEntries_Output_marshall_struct_t gpMacCore_GetSecurityLevelTableEntries;
    gpMacCore_GetPanId_Output_marshall_struct_t gpMacCore_GetPanId;
    gpMacCore_GetExtendedAddress_Output_marshall_struct_t gpMacCore_GetExtendedAddress;
    gpMacCore_GetMaxCsmaBackoffs_Output_marshall_struct_t gpMacCore_GetMaxCsmaBackoffs;
    gpMacCore_GetDsn_Output_marshall_struct_t gpMacCore_GetDsn;
    gpMacCore_GetCurrentChannel_Output_marshall_struct_t gpMacCore_GetCurrentChannel;
    gpMacCore_GetNumberOfRetries_Output_marshall_struct_t gpMacCore_GetNumberOfRetries;
    gpMacCore_GetFrameCounter_Output_marshall_struct_t gpMacCore_GetFrameCounter;
    gpMacCore_GetRxOnWhenIdle_Output_marshall_struct_t gpMacCore_GetRxOnWhenIdle;
    gpMacCore_GetShortAddress_Output_marshall_struct_t gpMacCore_GetShortAddress;
    gpMacCore_GetTransmitPower_Output_marshall_struct_t gpMacCore_GetTransmitPower;
    gpMacCore_GetPanCoordinator_Output_marshall_struct_t gpMacCore_GetPanCoordinator;
    gpMacCore_GetSecurityEnabled_Output_marshall_struct_t gpMacCore_GetSecurityEnabled;
    gpMacCore_GetTransactionPersistenceTime_Output_marshall_struct_t gpMacCore_GetTransactionPersistenceTime;
    gpMacCore_GetBeaconStarted_Output_marshall_struct_t gpMacCore_GetBeaconStarted;
    gpMacCore_GetPanCoordExtendedAddress_Output_marshall_struct_t gpMacCore_GetPanCoordExtendedAddress;
    gpMacCore_GetCoordExtendedAddress_Output_marshall_struct_t gpMacCore_GetCoordExtendedAddress;
    gpMacCore_GetCoordShortAddress_Output_marshall_struct_t gpMacCore_GetCoordShortAddress;
    gpMacCore_GetAssociationPermit_Output_marshall_struct_t gpMacCore_GetAssociationPermit;
    gpMacCore_GetBeaconPayload_Output_marshall_struct_t gpMacCore_GetBeaconPayload;
    gpMacCore_GetBeaconPayloadLength_Output_marshall_struct_t gpMacCore_GetBeaconPayloadLength;
    gpMacCore_GetMacVersion_Output_marshall_struct_t gpMacCore_GetMacVersion;
    gpMacCore_GetIndicateBeaconNotifications_Output_marshall_struct_t gpMacCore_GetIndicateBeaconNotifications;
    gpMacCore_GetCCAMode_Output_marshall_struct_t gpMacCore_GetCCAMode;
    gpMacCore_GetMinBE_Output_marshall_struct_t gpMacCore_GetMinBE;
    gpMacCore_GetPromiscuousMode_Output_marshall_struct_t gpMacCore_GetPromiscuousMode;
    gpMacCore_GetForwardPollIndications_Output_marshall_struct_t gpMacCore_GetForwardPollIndications;
    gpMacCore_GetMaxBE_Output_marshall_struct_t gpMacCore_GetMaxBE;
    gpMacCore_AddNeighbour_Output_marshall_struct_t gpMacCore_AddNeighbour;
    gpMacCore_RemoveNeighbour_Output_marshall_struct_t gpMacCore_RemoveNeighbour;
    gpMacCore_SetDataPendingMode_Output_marshall_struct_t gpMacCore_SetDataPendingMode;
    gpMacCore_GetCsmaMode_Output_marshall_struct_t gpMacCore_GetCsmaMode;
    gpMacCore_ScheduleTimedTx_Output_marshall_struct_t gpMacCore_ScheduleTimedTx;
    gpMacCore_DataPending_QueueAdd_Output_marshall_struct_t gpMacCore_DataPending_QueueAdd;
    gpMacCore_DataPending_QueueRemove_Output_marshall_struct_t gpMacCore_DataPending_QueueRemove;
    gpMacCore_SetMinInterferenceLevels_Output_marshall_struct_t gpMacCore_SetMinInterferenceLevels;
    gpMacCore_DataPending_QueueClear_Output_marshall_struct_t gpMacCore_DataPending_QueueClear;
    gpMacCore_DataPendingGetAckDataPending_Output_marshall_struct_t gpMacCore_DataPendingGetAckDataPending;
    gpMacCore_GetStackInRawMode_Output_marshall_struct_t gpMacCore_GetStackInRawMode;
    gpMacCore_GetCurrentTimeUs_Output_marshall_struct_t gpMacCore_GetCurrentTimeUs;
    gpMacCore_ConfigureEnhAckProbing_Output_marshall_struct_t gpMacCore_ConfigureEnhAckProbing;
    gpMacCore_GetRetransmitOnCcaFail_Output_marshall_struct_t gpMacCore_GetRetransmitOnCcaFail;
    gpMacCore_GetRetransmitRandomBackoff_Output_marshall_struct_t gpMacCore_GetRetransmitRandomBackoff;
    gpMacCore_GetMinBeRetransmit_Output_marshall_struct_t gpMacCore_GetMinBeRetransmit;
    gpMacCore_GetMaxBeRetransmit_Output_marshall_struct_t gpMacCore_GetMaxBeRetransmit;
    UInt8 dummy; //ensure none empty union definition
} gpMacCore_Server_Output_union_t;

typedef union {
#if !defined(GP_COMP_MACDISPATCHER)
    gpMacCore_cbDataConfirm_Input_marshall_struct_t gpMacCore_cbDataConfirm;
#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */
#if !defined(GP_COMP_MACDISPATCHER)
    gpMacCore_cbDataIndication_Input_marshall_struct_t gpMacCore_cbDataIndication;
#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */
#if !defined(GP_COMP_MACDISPATCHER)
    gpMacCore_cbScanConfirm_Input_marshall_struct_t gpMacCore_cbScanConfirm;
#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */
#if !defined(GP_COMP_MACDISPATCHER)
    gpMacCore_cbBeaconNotifyIndication_Input_marshall_struct_t gpMacCore_cbBeaconNotifyIndication;
#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */
#if !defined(GP_COMP_MACDISPATCHER)
    gpMacCore_cbOrphanIndication_Input_marshall_struct_t gpMacCore_cbOrphanIndication;
#endif /* defined(GP_MACCORE_DIVERSITY_ASSOCIATION_ORIGINATOR) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !defined(GP_COMP_MACDISPATCHER)
    gpMacCore_cbSecurityFailureCommStatusIndication_Input_marshall_struct_t gpMacCore_cbSecurityFailureCommStatusIndication;
#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */
#if !defined(GP_COMP_MACDISPATCHER)
    gpMacCore_cbPollConfirm_Input_marshall_struct_t gpMacCore_cbPollConfirm;
#endif /* defined(GP_MACCORE_DIVERSITY_POLL_ORIGINATOR) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !defined(GP_COMP_MACDISPATCHER)
    gpMacCore_cbPollIndication_Input_marshall_struct_t gpMacCore_cbPollIndication;
#endif /* defined(GP_MACCORE_DIVERSITY_POLL_RECIPIENT) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !defined(GP_COMP_MACDISPATCHER)
    gpMacCore_cbAssociateConfirm_Input_marshall_struct_t gpMacCore_cbAssociateConfirm;
#endif /* defined(GP_MACCORE_DIVERSITY_ASSOCIATION_ORIGINATOR) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !defined(GP_COMP_MACDISPATCHER)
    gpMacCore_cbAssociateIndication_Input_marshall_struct_t gpMacCore_cbAssociateIndication;
#endif /* defined(GP_MACCORE_DIVERSITY_ASSOCIATION_RECIPIENT) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !defined(GP_COMP_MACDISPATCHER)
    gpMacCore_cbAssociateCommStatusIndication_Input_marshall_struct_t gpMacCore_cbAssociateCommStatusIndication;
#endif /* defined(GP_MACCORE_DIVERSITY_ASSOCIATION_RECIPIENT) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !defined(GP_COMP_MACDISPATCHER)
    gpMacCore_cbOrphanCommStatusIndication_Input_marshall_struct_t gpMacCore_cbOrphanCommStatusIndication;
#endif /* defined(GP_MACCORE_DIVERSITY_SCAN_ORPHAN_RECIPIENT) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !defined(GP_COMP_MACDISPATCHER)
    gpMacCore_cbValidStack_Input_marshall_struct_t gpMacCore_cbValidStack;
#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */
#if !defined(GP_COMP_MACDISPATCHER)
    gpMacCore_cbPurgeConfirm_Input_marshall_struct_t gpMacCore_cbPurgeConfirm;
#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */
#if !defined(GP_COMP_MACDISPATCHER)
    gpMacCore_cbPollNotify_Input_marshall_struct_t gpMacCore_cbPollNotify;
#endif /* defined(GP_MACCORE_DIVERSITY_POLL_RECIPIENT) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !(defined(GP_COMP_MACDISPATCHER))
    gpMacCore_cbSecurityFrameCounterIndication_Input_marshall_struct_t gpMacCore_cbSecurityFrameCounterIndication;
#endif /* !(defined(GP_COMP_MACDISPATCHER)) */
    UInt8 dummy; //ensure none empty union definition
} gpMacCore_Client_Input_union_t;


typedef union {
#if !defined(GP_COMP_MACDISPATCHER)
    gpMacCore_cbValidStack_Output_marshall_struct_t gpMacCore_cbValidStack;
#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */
    UInt8 dummy; //ensure none empty union definition
} gpMacCore_Client_Output_union_t;
/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

// Alias/enum copy macro's
#define gpMacCore_Result_t_buf2api(pDest, pSource, length, pIndex) UInt8_buf2api(pDest, pSource, length, pIndex)
#define gpMacCore_Result_t_api2buf(pDest, pSource, length, pIndex) UInt8_api2buf(pDest, pSource, length, pIndex)
#define gpMacCore_Result_t_buf2api_1(pDest, pSource, pIndex)       UInt8_buf2api_1(pDest, pSource, pIndex)
#define gpMacCore_Result_t_api2buf_1(pDest, pSource, pIndex)       UInt8_api2buf_1(pDest, pSource, pIndex)
#define gpMacCore_FrameType_t_buf2api(pDest, pSource, length, pIndex) UInt8_buf2api(pDest, pSource, length, pIndex)
#define gpMacCore_FrameType_t_api2buf(pDest, pSource, length, pIndex) UInt8_api2buf(pDest, pSource, length, pIndex)
#define gpMacCore_FrameType_t_buf2api_1(pDest, pSource, pIndex)       UInt8_buf2api_1(pDest, pSource, pIndex)
#define gpMacCore_FrameType_t_api2buf_1(pDest, pSource, pIndex)       UInt8_api2buf_1(pDest, pSource, pIndex)
#define gpMacCore_Command_t_buf2api(pDest, pSource, length, pIndex) UInt8_buf2api(pDest, pSource, length, pIndex)
#define gpMacCore_Command_t_api2buf(pDest, pSource, length, pIndex) UInt8_api2buf(pDest, pSource, length, pIndex)
#define gpMacCore_Command_t_buf2api_1(pDest, pSource, pIndex)       UInt8_buf2api_1(pDest, pSource, pIndex)
#define gpMacCore_Command_t_api2buf_1(pDest, pSource, pIndex)       UInt8_api2buf_1(pDest, pSource, pIndex)
#define gpMacCore_AddressMode_t_buf2api(pDest, pSource, length, pIndex) UInt8_buf2api(pDest, pSource, length, pIndex)
#define gpMacCore_AddressMode_t_api2buf(pDest, pSource, length, pIndex) UInt8_api2buf(pDest, pSource, length, pIndex)
#define gpMacCore_AddressMode_t_buf2api_1(pDest, pSource, pIndex)       UInt8_buf2api_1(pDest, pSource, pIndex)
#define gpMacCore_AddressMode_t_api2buf_1(pDest, pSource, pIndex)       UInt8_api2buf_1(pDest, pSource, pIndex)
#define gpMacCore_KeyIdLookupListEntries_t_buf2api(pDest, pSource, length, pIndex) UInt8_buf2api(pDest, pSource, length, pIndex)
#define gpMacCore_KeyIdLookupListEntries_t_api2buf(pDest, pSource, length, pIndex) UInt8_api2buf(pDest, pSource, length, pIndex)
#define gpMacCore_KeyIdLookupListEntries_t_buf2api_1(pDest, pSource, pIndex)       UInt8_buf2api_1(pDest, pSource, pIndex)
#define gpMacCore_KeyIdLookupListEntries_t_api2buf_1(pDest, pSource, pIndex)       UInt8_api2buf_1(pDest, pSource, pIndex)
#define gpMacCore_KeyDeviceListEntries_t_buf2api(pDest, pSource, length, pIndex) UInt8_buf2api(pDest, pSource, length, pIndex)
#define gpMacCore_KeyDeviceListEntries_t_api2buf(pDest, pSource, length, pIndex) UInt8_api2buf(pDest, pSource, length, pIndex)
#define gpMacCore_KeyDeviceListEntries_t_buf2api_1(pDest, pSource, pIndex)       UInt8_buf2api_1(pDest, pSource, pIndex)
#define gpMacCore_KeyDeviceListEntries_t_api2buf_1(pDest, pSource, pIndex)       UInt8_api2buf_1(pDest, pSource, pIndex)
#define gpMacCore_KeyUsageListEntries_t_buf2api(pDest, pSource, length, pIndex) UInt8_buf2api(pDest, pSource, length, pIndex)
#define gpMacCore_KeyUsageListEntries_t_api2buf(pDest, pSource, length, pIndex) UInt8_api2buf(pDest, pSource, length, pIndex)
#define gpMacCore_KeyUsageListEntries_t_buf2api_1(pDest, pSource, pIndex)       UInt8_buf2api_1(pDest, pSource, pIndex)
#define gpMacCore_KeyUsageListEntries_t_api2buf_1(pDest, pSource, pIndex)       UInt8_api2buf_1(pDest, pSource, pIndex)
#define gpMacCore_KeyTablesEntries_t_buf2api(pDest, pSource, length, pIndex) UInt8_buf2api(pDest, pSource, length, pIndex)
#define gpMacCore_KeyTablesEntries_t_api2buf(pDest, pSource, length, pIndex) UInt8_api2buf(pDest, pSource, length, pIndex)
#define gpMacCore_KeyTablesEntries_t_buf2api_1(pDest, pSource, pIndex)       UInt8_buf2api_1(pDest, pSource, pIndex)
#define gpMacCore_KeyTablesEntries_t_api2buf_1(pDest, pSource, pIndex)       UInt8_api2buf_1(pDest, pSource, pIndex)
#define gpMacCore_SecurityLevelTableEntries_t_buf2api(pDest, pSource, length, pIndex) UInt8_buf2api(pDest, pSource, length, pIndex)
#define gpMacCore_SecurityLevelTableEntries_t_api2buf(pDest, pSource, length, pIndex) UInt8_api2buf(pDest, pSource, length, pIndex)
#define gpMacCore_SecurityLevelTableEntries_t_buf2api_1(pDest, pSource, pIndex)       UInt8_buf2api_1(pDest, pSource, pIndex)
#define gpMacCore_SecurityLevelTableEntries_t_api2buf_1(pDest, pSource, pIndex)       UInt8_api2buf_1(pDest, pSource, pIndex)
#define gpMacCore_KeyIndex_t_buf2api(pDest, pSource, length, pIndex) UInt8_buf2api(pDest, pSource, length, pIndex)
#define gpMacCore_KeyIndex_t_api2buf(pDest, pSource, length, pIndex) UInt8_api2buf(pDest, pSource, length, pIndex)
#define gpMacCore_KeyIndex_t_buf2api_1(pDest, pSource, pIndex)       UInt8_buf2api_1(pDest, pSource, pIndex)
#define gpMacCore_KeyIndex_t_api2buf_1(pDest, pSource, pIndex)       UInt8_api2buf_1(pDest, pSource, pIndex)
#define gpMacCore_KeyIdMode_t_buf2api(pDest, pSource, length, pIndex) UInt8_buf2api(pDest, pSource, length, pIndex)
#define gpMacCore_KeyIdMode_t_api2buf(pDest, pSource, length, pIndex) UInt8_api2buf(pDest, pSource, length, pIndex)
#define gpMacCore_KeyIdMode_t_buf2api_1(pDest, pSource, pIndex)       UInt8_buf2api_1(pDest, pSource, pIndex)
#define gpMacCore_KeyIdMode_t_api2buf_1(pDest, pSource, pIndex)       UInt8_api2buf_1(pDest, pSource, pIndex)
#define gpMacCore_ScanType_t_buf2api(pDest, pSource, length, pIndex) UInt8_buf2api(pDest, pSource, length, pIndex)
#define gpMacCore_ScanType_t_api2buf(pDest, pSource, length, pIndex) UInt8_api2buf(pDest, pSource, length, pIndex)
#define gpMacCore_ScanType_t_buf2api_1(pDest, pSource, pIndex)       UInt8_buf2api_1(pDest, pSource, pIndex)
#define gpMacCore_ScanType_t_api2buf_1(pDest, pSource, pIndex)       UInt8_api2buf_1(pDest, pSource, pIndex)
#define gpMacCore_Attribute_t_buf2api(pDest, pSource, length, pIndex) UInt8_buf2api(pDest, pSource, length, pIndex)
#define gpMacCore_Attribute_t_api2buf(pDest, pSource, length, pIndex) UInt8_api2buf(pDest, pSource, length, pIndex)
#define gpMacCore_Attribute_t_buf2api_1(pDest, pSource, pIndex)       UInt8_buf2api_1(pDest, pSource, pIndex)
#define gpMacCore_Attribute_t_api2buf_1(pDest, pSource, pIndex)       UInt8_api2buf_1(pDest, pSource, pIndex)
#define gpMacCore_Index_t_buf2api(pDest, pSource, length, pIndex) UInt8_buf2api(pDest, pSource, length, pIndex)
#define gpMacCore_Index_t_api2buf(pDest, pSource, length, pIndex) UInt8_api2buf(pDest, pSource, length, pIndex)
#define gpMacCore_Index_t_buf2api_1(pDest, pSource, pIndex)       UInt8_buf2api_1(pDest, pSource, pIndex)
#define gpMacCore_Index_t_api2buf_1(pDest, pSource, pIndex)       UInt8_api2buf_1(pDest, pSource, pIndex)
#define gpMacCore_DeviceTablesEntries_t_buf2api(pDest, pSource, length, pIndex) UInt8_buf2api(pDest, pSource, length, pIndex)
#define gpMacCore_DeviceTablesEntries_t_api2buf(pDest, pSource, length, pIndex) UInt8_api2buf(pDest, pSource, length, pIndex)
#define gpMacCore_DeviceTablesEntries_t_buf2api_1(pDest, pSource, pIndex)       UInt8_buf2api_1(pDest, pSource, pIndex)
#define gpMacCore_DeviceTablesEntries_t_api2buf_1(pDest, pSource, pIndex)       UInt8_api2buf_1(pDest, pSource, pIndex)
#define gpMacCore_StackId_t_buf2api(pDest, pSource, length, pIndex) UInt8_buf2api(pDest, pSource, length, pIndex)
#define gpMacCore_StackId_t_api2buf(pDest, pSource, length, pIndex) UInt8_api2buf(pDest, pSource, length, pIndex)
#define gpMacCore_StackId_t_buf2api_1(pDest, pSource, pIndex)       UInt8_buf2api_1(pDest, pSource, pIndex)
#define gpMacCore_StackId_t_api2buf_1(pDest, pSource, pIndex)       UInt8_api2buf_1(pDest, pSource, pIndex)
#define gpMacCore_PanId_t_buf2api(pDest, pSource, length, pIndex) UInt16_buf2api(pDest, pSource, length, pIndex)
#define gpMacCore_PanId_t_api2buf(pDest, pSource, length, pIndex) UInt16_api2buf(pDest, pSource, length, pIndex)
#define gpMacCore_PanId_t_buf2api_1(pDest, pSource, pIndex)       UInt16_buf2api_1(pDest, pSource, pIndex)
#define gpMacCore_PanId_t_api2buf_1(pDest, pSource, pIndex)       UInt16_api2buf_1(pDest, pSource, pIndex)
#define gpMacCore_SuperFrameSpec_t_buf2api(pDest, pSource, length, pIndex) UInt16_buf2api(pDest, pSource, length, pIndex)
#define gpMacCore_SuperFrameSpec_t_api2buf(pDest, pSource, length, pIndex) UInt16_api2buf(pDest, pSource, length, pIndex)
#define gpMacCore_SuperFrameSpec_t_buf2api_1(pDest, pSource, pIndex)       UInt16_buf2api_1(pDest, pSource, pIndex)
#define gpMacCore_SuperFrameSpec_t_api2buf_1(pDest, pSource, pIndex)       UInt16_api2buf_1(pDest, pSource, pIndex)
#define gpMacCore_MacVersion_t_buf2api(pDest, pSource, length, pIndex) UInt8_buf2api(pDest, pSource, length, pIndex)
#define gpMacCore_MacVersion_t_api2buf(pDest, pSource, length, pIndex) UInt8_api2buf(pDest, pSource, length, pIndex)
#define gpMacCore_MacVersion_t_buf2api_1(pDest, pSource, pIndex)       UInt8_buf2api_1(pDest, pSource, pIndex)
#define gpMacCore_MacVersion_t_api2buf_1(pDest, pSource, pIndex)       UInt8_api2buf_1(pDest, pSource, pIndex)
#define gpMacCore_DataPendingMode_t_buf2api(pDest, pSource, length, pIndex) UInt8_buf2api(pDest, pSource, length, pIndex)
#define gpMacCore_DataPendingMode_t_api2buf(pDest, pSource, length, pIndex) UInt8_api2buf(pDest, pSource, length, pIndex)
#define gpMacCore_DataPendingMode_t_buf2api_1(pDest, pSource, pIndex)       UInt8_buf2api_1(pDest, pSource, pIndex)
#define gpMacCore_DataPendingMode_t_api2buf_1(pDest, pSource, pIndex)       UInt8_api2buf_1(pDest, pSource, pIndex)
#define gpMacCore_TxPower_t_buf2api(pDest, pSource, length, pIndex) Int8_buf2api(pDest, pSource, length, pIndex)
#define gpMacCore_TxPower_t_api2buf(pDest, pSource, length, pIndex) Int8_api2buf(pDest, pSource, length, pIndex)
#define gpMacCore_TxPower_t_buf2api_1(pDest, pSource, pIndex)       Int8_buf2api_1(pDest, pSource, pIndex)
#define gpMacCore_TxPower_t_api2buf_1(pDest, pSource, pIndex)       Int8_api2buf_1(pDest, pSource, pIndex)

// Structure copy functions
gpMarshall_AckStatus_t gpMacCore_DeviceDescriptor_t_buf2api(gpMacCore_DeviceDescriptor_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex );
void gpMacCore_DeviceDescriptor_t_api2buf(UInt8Buffer* pDest , const gpMacCore_DeviceDescriptor_t* pSource , UInt16 length , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_KeyUsageDescriptor_t_buf2api(gpMacCore_KeyUsageDescriptor_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex );
void gpMacCore_KeyUsageDescriptor_t_api2buf(UInt8Buffer* pDest , const gpMacCore_KeyUsageDescriptor_t* pSource , UInt16 length , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_KeyDeviceDescriptor_t_buf2api(gpMacCore_KeyDeviceDescriptor_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex );
void gpMacCore_KeyDeviceDescriptor_t_api2buf(UInt8Buffer* pDest , const gpMacCore_KeyDeviceDescriptor_t* pSource , UInt16 length , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_Security_t_buf2api(gpMacCore_Security_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex );
void gpMacCore_Security_t_api2buf(UInt8Buffer* pDest , const gpMacCore_Security_t* pSource , UInt16 length , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_AddressInfo_t_buf2api(gpMacCore_AddressInfo_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex );
void gpMacCore_AddressInfo_t_api2buf(UInt8Buffer* pDest , const gpMacCore_AddressInfo_t* pSource , UInt16 length , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_PanDescriptor_t_buf2api(gpMacCore_PanDescriptor_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex );
void gpMacCore_PanDescriptor_t_api2buf(UInt8Buffer* pDest , const gpMacCore_PanDescriptor_t* pSource , UInt16 length , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_KeyIdLookupDescriptor_t_buf2api(gpMacCore_KeyIdLookupDescriptor_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex );
void gpMacCore_KeyIdLookupDescriptor_t_api2buf(UInt8Buffer* pDest , const gpMacCore_KeyIdLookupDescriptor_t* pSource , UInt16 length , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_KeyDescriptor_t_buf2api(gpMacCore_KeyDescriptor_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex );
void gpMacCore_KeyDescriptor_t_api2buf(UInt8Buffer* pDest , const gpMacCore_KeyDescriptor_t* pSource , UInt16 length , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SecurityLevelDescriptor_t_buf2api(gpMacCore_SecurityLevelDescriptor_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex );
void gpMacCore_SecurityLevelDescriptor_t_api2buf(UInt8Buffer* pDest , const gpMacCore_SecurityLevelDescriptor_t* pSource , UInt16 length , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_MultiChannelOptions_t_buf2api(gpMacCore_MultiChannelOptions_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex );
void gpMacCore_MultiChannelOptions_t_api2buf(UInt8Buffer* pDest , const gpMacCore_MultiChannelOptions_t* pSource , UInt16 length , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_TxTimingOptions_t_buf2api(gpMacCore_TxTimingOptions_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex );
void gpMacCore_TxTimingOptions_t_api2buf(UInt8Buffer* pDest , const gpMacCore_TxTimingOptions_t* pSource , UInt16 length , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_DiagRxCntr_t_buf2api(gpMacCore_DiagRxCntr_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex );
void gpMacCore_DiagRxCntr_t_api2buf(UInt8Buffer* pDest , const gpMacCore_DiagRxCntr_t* pSource , UInt16 length , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_DiagTxCntr_t_buf2api(gpMacCore_DiagTxCntr_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex );
void gpMacCore_DiagTxCntr_t_api2buf(UInt8Buffer* pDest , const gpMacCore_DiagTxCntr_t* pSource , UInt16 length , UInt16* pIndex);

// Union copy functions
gpMarshall_AckStatus_t gpMacCore_Address_t_buf2api(UInt8 unionid , gpMacCore_Address_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex);
void gpMacCore_Address_t_api2buf(UInt8 unionid , UInt8Buffer* pDest , const gpMacCore_Address_t* pSource , UInt16 length , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_KeySource_t_buf2api(UInt8 unionid , gpMacCore_KeySource_t* pDest , UInt8Buffer* pSource , UInt16 length , UInt16* pIndex);
void gpMacCore_KeySource_t_api2buf(UInt8 unionid , UInt8Buffer* pDest , const gpMacCore_KeySource_t* pSource , UInt16 length , UInt16* pIndex);

// Server functions
gpMarshall_AckStatus_t gpMacCore_Reset_Input_buf2api(gpMacCore_Reset_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_Reset_Output_api2buf(UInt8Buffer* pDest , gpMacCore_Reset_Output_marshall_struct_t* pSourceoutput , gpMacCore_Reset_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_DataRequest_Input_buf2api(gpMacCore_DataRequest_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_ScanRequest_Input_buf2api(gpMacCore_ScanRequest_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_AssociateRequest_Input_buf2api(gpMacCore_AssociateRequest_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_AssociateResponse_Input_buf2api(gpMacCore_AssociateResponse_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_PollRequest_Input_buf2api(gpMacCore_PollRequest_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_Start_Input_buf2api(gpMacCore_Start_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_Start_Output_api2buf(UInt8Buffer* pDest , gpMacCore_Start_Output_marshall_struct_t* pSourceoutput , gpMacCore_Start_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetSecurityEnabled_Input_buf2api(gpMacCore_SetSecurityEnabled_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetDeviceDescriptor_Input_buf2api(gpMacCore_SetDeviceDescriptor_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetDeviceDescriptor_Output_api2buf(UInt8Buffer* pDest , gpMacCore_SetDeviceDescriptor_Output_marshall_struct_t* pSourceoutput , gpMacCore_SetDeviceDescriptor_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetDeviceDescriptor_Input_buf2api(gpMacCore_GetDeviceDescriptor_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetDeviceDescriptor_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetDeviceDescriptor_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetDeviceDescriptor_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetDeviceTableEntries_Input_buf2api(gpMacCore_SetDeviceTableEntries_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetDeviceTableEntries_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetDeviceTableEntries_Output_marshall_struct_t* pSourceoutput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetKeyDescriptor_Input_buf2api(gpMacCore_SetKeyDescriptor_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetKeyDescriptor_Output_api2buf(UInt8Buffer* pDest , gpMacCore_SetKeyDescriptor_Output_marshall_struct_t* pSourceoutput , gpMacCore_SetKeyDescriptor_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetKeyDescriptor_Input_buf2api(gpMacCore_GetKeyDescriptor_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetKeyDescriptor_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetKeyDescriptor_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetKeyDescriptor_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetKeyTableEntries_Input_buf2api(gpMacCore_SetKeyTableEntries_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetSecurityLevelDescriptor_Input_buf2api(gpMacCore_SetSecurityLevelDescriptor_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetSecurityLevelDescriptor_Output_api2buf(UInt8Buffer* pDest , gpMacCore_SetSecurityLevelDescriptor_Output_marshall_struct_t* pSourceoutput , gpMacCore_SetSecurityLevelDescriptor_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetSecurityLevelDescriptor_Input_buf2api(gpMacCore_GetSecurityLevelDescriptor_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetSecurityLevelDescriptor_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetSecurityLevelDescriptor_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetSecurityLevelDescriptor_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetSecurityLevelTableEntries_Input_buf2api(gpMacCore_SetSecurityLevelTableEntries_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetSecurityLevelTableEntries_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetSecurityLevelTableEntries_Output_marshall_struct_t* pSourceoutput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetDefaultKeySource_Input_buf2api(gpMacCore_SetDefaultKeySource_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetShortAddress_Input_buf2api(gpMacCore_SetShortAddress_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetExtendedAddress_Input_buf2api(gpMacCore_SetExtendedAddress_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetPanId_Input_buf2api(gpMacCore_SetPanId_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetPanId_Input_buf2api(gpMacCore_GetPanId_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetPanId_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetPanId_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetPanId_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetFrameCounter_Input_buf2api(gpMacCore_SetFrameCounter_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetDsn_Input_buf2api(gpMacCore_SetDsn_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetCurrentChannel_Input_buf2api(gpMacCore_SetCurrentChannel_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetBeaconPayload_Input_buf2api(gpMacCore_SetBeaconPayload_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetBeaconPayloadLength_Input_buf2api(gpMacCore_SetBeaconPayloadLength_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetRxOnWhenIdle_Input_buf2api(gpMacCore_SetRxOnWhenIdle_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetExtendedAddress_Input_buf2api(gpMacCore_GetExtendedAddress_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetExtendedAddress_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetExtendedAddress_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetExtendedAddress_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetMaxCsmaBackoffs_Input_buf2api(gpMacCore_SetMaxCsmaBackoffs_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetMaxCsmaBackoffs_Input_buf2api(gpMacCore_GetMaxCsmaBackoffs_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetMaxCsmaBackoffs_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetMaxCsmaBackoffs_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetMaxCsmaBackoffs_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetDsn_Input_buf2api(gpMacCore_GetDsn_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetDsn_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetDsn_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetDsn_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetCurrentChannel_Input_buf2api(gpMacCore_GetCurrentChannel_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetCurrentChannel_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetCurrentChannel_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetCurrentChannel_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetNumberOfRetries_Input_buf2api(gpMacCore_SetNumberOfRetries_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetNumberOfRetries_Input_buf2api(gpMacCore_GetNumberOfRetries_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetNumberOfRetries_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetNumberOfRetries_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetNumberOfRetries_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetFrameCounter_Input_buf2api(gpMacCore_GetFrameCounter_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetFrameCounter_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetFrameCounter_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetFrameCounter_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetRxOnWhenIdle_Input_buf2api(gpMacCore_GetRxOnWhenIdle_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetRxOnWhenIdle_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetRxOnWhenIdle_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetRxOnWhenIdle_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetShortAddress_Input_buf2api(gpMacCore_GetShortAddress_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetShortAddress_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetShortAddress_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetShortAddress_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetPanCoordShortAddress_Input_buf2api(gpMacCore_SetPanCoordShortAddress_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetPanCoordExtendedAddress_Input_buf2api(gpMacCore_SetPanCoordExtendedAddress_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetAssociationPermit_Input_buf2api(gpMacCore_SetAssociationPermit_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetDefaultTransmitPowers_Input_buf2api(gpMacCore_SetDefaultTransmitPowers_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetTransmitPower_Input_buf2api(gpMacCore_SetTransmitPower_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetTransmitPower_Input_buf2api(gpMacCore_GetTransmitPower_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetTransmitPower_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetTransmitPower_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetTransmitPower_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetPanCoordinator_Input_buf2api(gpMacCore_SetPanCoordinator_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetPanCoordinator_Input_buf2api(gpMacCore_GetPanCoordinator_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetPanCoordinator_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetPanCoordinator_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetPanCoordinator_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_OrphanResponse_Input_buf2api(gpMacCore_OrphanResponse_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetSecurityEnabled_Input_buf2api(gpMacCore_GetSecurityEnabled_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetSecurityEnabled_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetSecurityEnabled_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetSecurityEnabled_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetTransactionPersistenceTime_Input_buf2api(gpMacCore_GetTransactionPersistenceTime_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetTransactionPersistenceTime_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetTransactionPersistenceTime_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetTransactionPersistenceTime_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetTransactionPersistenceTime_Input_buf2api(gpMacCore_SetTransactionPersistenceTime_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetBeaconStarted_Input_buf2api(gpMacCore_SetBeaconStarted_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetBeaconStarted_Input_buf2api(gpMacCore_GetBeaconStarted_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetBeaconStarted_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetBeaconStarted_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetBeaconStarted_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
void gpMacCore_GetPanCoordExtendedAddress_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetPanCoordExtendedAddress_Output_marshall_struct_t* pSourceoutput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetCoordExtendedAddress_Input_buf2api(gpMacCore_SetCoordExtendedAddress_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetCoordExtendedAddress_Input_buf2api(gpMacCore_GetCoordExtendedAddress_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetCoordExtendedAddress_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetCoordExtendedAddress_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetCoordExtendedAddress_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetCoordShortAddress_Input_buf2api(gpMacCore_SetCoordShortAddress_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetCoordShortAddress_Input_buf2api(gpMacCore_GetCoordShortAddress_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetCoordShortAddress_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetCoordShortAddress_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetCoordShortAddress_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetAssociationPermit_Input_buf2api(gpMacCore_GetAssociationPermit_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetAssociationPermit_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetAssociationPermit_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetAssociationPermit_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetBeaconPayload_Input_buf2api(gpMacCore_GetBeaconPayload_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetBeaconPayload_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetBeaconPayload_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetBeaconPayload_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetBeaconPayloadLength_Input_buf2api(gpMacCore_GetBeaconPayloadLength_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetBeaconPayloadLength_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetBeaconPayloadLength_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetBeaconPayloadLength_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetIndicateBeaconNotifications_Input_buf2api(gpMacCore_SetIndicateBeaconNotifications_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetPromiscuousMode_Input_buf2api(gpMacCore_SetPromiscuousMode_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetMacVersion_Input_buf2api(gpMacCore_SetMacVersion_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetMacVersion_Input_buf2api(gpMacCore_GetMacVersion_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetMacVersion_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetMacVersion_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetMacVersion_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_StackAdded_Input_buf2api(gpMacCore_StackAdded_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_StackRemoved_Input_buf2api(gpMacCore_StackRemoved_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetIndicateBeaconNotifications_Input_buf2api(gpMacCore_GetIndicateBeaconNotifications_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetIndicateBeaconNotifications_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetIndicateBeaconNotifications_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetIndicateBeaconNotifications_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetCCAMode_Input_buf2api(gpMacCore_SetCCAMode_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetCCAMode_Input_buf2api(gpMacCore_GetCCAMode_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetCCAMode_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetCCAMode_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetCCAMode_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetMinBE_Input_buf2api(gpMacCore_SetMinBE_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetMinBE_Input_buf2api(gpMacCore_GetMinBE_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetMinBE_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetMinBE_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetMinBE_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetPromiscuousMode_Input_buf2api(gpMacCore_GetPromiscuousMode_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetPromiscuousMode_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetPromiscuousMode_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetPromiscuousMode_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_PurgeRequest_Input_buf2api(gpMacCore_PurgeRequest_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetForwardPollIndications_Input_buf2api(gpMacCore_SetForwardPollIndications_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetForwardPollIndications_Input_buf2api(gpMacCore_GetForwardPollIndications_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetForwardPollIndications_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetForwardPollIndications_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetForwardPollIndications_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetMaxBE_Input_buf2api(gpMacCore_SetMaxBE_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetMaxBE_Input_buf2api(gpMacCore_GetMaxBE_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetMaxBE_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetMaxBE_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetMaxBE_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_AddNeighbour_Input_buf2api(gpMacCore_AddNeighbour_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_AddNeighbour_Output_api2buf(UInt8Buffer* pDest , gpMacCore_AddNeighbour_Output_marshall_struct_t* pSourceoutput , gpMacCore_AddNeighbour_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_RemoveNeighbour_Input_buf2api(gpMacCore_RemoveNeighbour_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_RemoveNeighbour_Output_api2buf(UInt8Buffer* pDest , gpMacCore_RemoveNeighbour_Output_marshall_struct_t* pSourceoutput , gpMacCore_RemoveNeighbour_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetDataPendingMode_Input_buf2api(gpMacCore_SetDataPendingMode_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetDataPendingMode_Output_api2buf(UInt8Buffer* pDest , gpMacCore_SetDataPendingMode_Output_marshall_struct_t* pSourceoutput , gpMacCore_SetDataPendingMode_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetAddressModeOverrideForBeacons_Input_buf2api(gpMacCore_SetAddressModeOverrideForBeacons_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_ClearNeighbours_Input_buf2api(gpMacCore_ClearNeighbours_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetCsmaMode_Input_buf2api(gpMacCore_SetCsmaMode_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetCsmaMode_Input_buf2api(gpMacCore_GetCsmaMode_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetCsmaMode_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetCsmaMode_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetCsmaMode_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_ScheduleTimedTx_Input_buf2api(gpMacCore_ScheduleTimedTx_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_ScheduleTimedTx_Output_api2buf(UInt8Buffer* pDest , gpMacCore_ScheduleTimedTx_Output_marshall_struct_t* pSourceoutput , gpMacCore_ScheduleTimedTx_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_DataPending_QueueAdd_Input_buf2api(gpMacCore_DataPending_QueueAdd_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_DataPending_QueueAdd_Output_api2buf(UInt8Buffer* pDest , gpMacCore_DataPending_QueueAdd_Output_marshall_struct_t* pSourceoutput , gpMacCore_DataPending_QueueAdd_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_DataPending_QueueRemove_Input_buf2api(gpMacCore_DataPending_QueueRemove_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_DataPending_QueueRemove_Output_api2buf(UInt8Buffer* pDest , gpMacCore_DataPending_QueueRemove_Output_marshall_struct_t* pSourceoutput , gpMacCore_DataPending_QueueRemove_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetMinInterferenceLevels_Input_buf2api(gpMacCore_SetMinInterferenceLevels_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetMinInterferenceLevels_Output_api2buf(UInt8Buffer* pDest , gpMacCore_SetMinInterferenceLevels_Output_marshall_struct_t* pSourceoutput , gpMacCore_SetMinInterferenceLevels_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_DataPending_QueueClear_Input_buf2api(gpMacCore_DataPending_QueueClear_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_DataPending_QueueClear_Output_api2buf(UInt8Buffer* pDest , gpMacCore_DataPending_QueueClear_Output_marshall_struct_t* pSourceoutput , gpMacCore_DataPending_QueueClear_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
void gpMacCore_DataPendingGetAckDataPending_Output_api2buf(UInt8Buffer* pDest , gpMacCore_DataPendingGetAckDataPending_Output_marshall_struct_t* pSourceoutput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetStackInRawMode_Input_buf2api(gpMacCore_SetStackInRawMode_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetStackInRawMode_Input_buf2api(gpMacCore_GetStackInRawMode_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetStackInRawMode_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetStackInRawMode_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetStackInRawMode_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_EnableEnhancedFramePending_Input_buf2api(gpMacCore_EnableEnhancedFramePending_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_EnableRxWindows_Input_buf2api(gpMacCore_EnableRxWindows_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_DisableRxWindows_Input_buf2api(gpMacCore_DisableRxWindows_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_EnableCsl_Input_buf2api(gpMacCore_EnableCsl_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_UpdateCslSampleTime_Input_buf2api(gpMacCore_UpdateCslSampleTime_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetCurrentTimeUs_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetCurrentTimeUs_Output_marshall_struct_t* pSourceoutput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_ConfigureEnhAckProbing_Input_buf2api(gpMacCore_ConfigureEnhAckProbing_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_ConfigureEnhAckProbing_Output_api2buf(UInt8Buffer* pDest , gpMacCore_ConfigureEnhAckProbing_Output_marshall_struct_t* pSourceoutput , gpMacCore_ConfigureEnhAckProbing_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetRetransmitOnCcaFail_Input_buf2api(gpMacCore_SetRetransmitOnCcaFail_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetRetransmitOnCcaFail_Input_buf2api(gpMacCore_GetRetransmitOnCcaFail_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetRetransmitOnCcaFail_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetRetransmitOnCcaFail_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetRetransmitOnCcaFail_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetRetransmitRandomBackoff_Input_buf2api(gpMacCore_SetRetransmitRandomBackoff_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetRetransmitRandomBackoff_Input_buf2api(gpMacCore_GetRetransmitRandomBackoff_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetRetransmitRandomBackoff_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetRetransmitRandomBackoff_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetRetransmitRandomBackoff_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetMinBeRetransmit_Input_buf2api(gpMacCore_SetMinBeRetransmit_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetMinBeRetransmit_Input_buf2api(gpMacCore_GetMinBeRetransmit_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetMinBeRetransmit_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetMinBeRetransmit_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetMinBeRetransmit_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_SetMaxBeRetransmit_Input_buf2api(gpMacCore_SetMaxBeRetransmit_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
gpMarshall_AckStatus_t gpMacCore_GetMaxBeRetransmit_Input_buf2api(gpMacCore_GetMaxBeRetransmit_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetMaxBeRetransmit_Output_api2buf(UInt8Buffer* pDest , gpMacCore_GetMaxBeRetransmit_Output_marshall_struct_t* pSourceoutput , gpMacCore_GetMaxBeRetransmit_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
#if !defined(GP_COMP_MACDISPATCHER)
void gpMacCore_cbDataConfirm_Input_par2api(UInt8Buffer* pDest , gpMacCore_Result_t status , gpPd_Handle_t pdHandle , UInt16* pIndex);
#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */
#if !defined(GP_COMP_MACDISPATCHER)
void gpMacCore_cbDataIndication_Input_par2api(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* pSrcAddrInfo , gpMacCore_AddressInfo_t* pDstAddrInfo , UInt8 dsn , gpMacCore_Security_t* pSecOptions , gpPd_Loh_t pdLoh , gpMacCore_StackId_t stackId , UInt16* pIndex);
#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */
#if !defined(GP_COMP_MACDISPATCHER)
void gpMacCore_cbScanConfirm_Input_par2api(UInt8Buffer* pDest , gpMacCore_Result_t status , gpMacCore_ScanType_t scanType , UInt32 unscannedChannels , UInt8 resultListSize , UInt8* pEdScanResultList , UInt16* pIndex);
#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */
#if !defined(GP_COMP_MACDISPATCHER)
void gpMacCore_cbBeaconNotifyIndication_Input_par2api(UInt8Buffer* pDest , UInt8 bsn , gpMacCore_PanDescriptor_t* pPanDescriptor , gpMacCore_StackId_t stackId , UInt8 beaconPayloadLength , UInt8* pBeaconPayload , UInt16* pIndex);
#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */
#if !defined(GP_COMP_MACDISPATCHER)
void gpMacCore_cbOrphanIndication_Input_par2api(UInt8Buffer* pDest , MACAddress_t* pOrphanAddress , gpMacCore_StackId_t stackId , gpPd_TimeStamp_t rxTime , UInt16* pIndex);
#endif /* defined(GP_MACCORE_DIVERSITY_ASSOCIATION_ORIGINATOR) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !defined(GP_COMP_MACDISPATCHER)
void gpMacCore_cbSecurityFailureCommStatusIndication_Input_par2api(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* pSrcAddressInfo , gpMacCore_AddressInfo_t* pDstAddressInfo , gpMacCore_Result_t status , gpMacCore_StackId_t stackId , gpPd_TimeStamp_t txTime , UInt16* pIndex);
#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */
#if !defined(GP_COMP_MACDISPATCHER)
void gpMacCore_cbPollConfirm_Input_par2api(UInt8Buffer* pDest , gpMacCore_Result_t status , gpMacCore_AddressInfo_t* coordAddrInfo , gpPd_TimeStamp_t txTime , UInt16* pIndex);
#endif /* defined(GP_MACCORE_DIVERSITY_POLL_ORIGINATOR) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !defined(GP_COMP_MACDISPATCHER)
void gpMacCore_cbPollIndication_Input_par2api(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* addressInfo , gpMacCore_StackId_t stackId , gpPd_TimeStamp_t rxTime , UInt16* pIndex);
#endif /* defined(GP_MACCORE_DIVERSITY_POLL_RECIPIENT) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !defined(GP_COMP_MACDISPATCHER)
void gpMacCore_cbAssociateConfirm_Input_par2api(UInt8Buffer* pDest , UInt16 assocShortAddress , gpMacCore_Result_t status , gpPd_TimeStamp_t txTime , UInt16* pIndex);
#endif /* defined(GP_MACCORE_DIVERSITY_ASSOCIATION_ORIGINATOR) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !defined(GP_COMP_MACDISPATCHER)
void gpMacCore_cbAssociateIndication_Input_par2api(UInt8Buffer* pDest , gpMacCore_Address_t* pDeviceAddress , UInt8 capabilityInformation , gpMacCore_StackId_t stackId , gpPd_TimeStamp_t rxTime , UInt16* pIndex);
#endif /* defined(GP_MACCORE_DIVERSITY_ASSOCIATION_RECIPIENT) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !defined(GP_COMP_MACDISPATCHER)
void gpMacCore_cbAssociateCommStatusIndication_Input_par2api(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* pSrcAddressInfo , gpMacCore_AddressInfo_t* pDstAddressInfo , gpMacCore_Result_t status , gpMacCore_StackId_t stackId , gpPd_TimeStamp_t txTime , UInt16* pIndex);
#endif /* defined(GP_MACCORE_DIVERSITY_ASSOCIATION_RECIPIENT) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !defined(GP_COMP_MACDISPATCHER)
void gpMacCore_cbOrphanCommStatusIndication_Input_par2api(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* pSrcAddressInfo , gpMacCore_AddressInfo_t* pDstAddressInfo , gpMacCore_Result_t status , gpMacCore_StackId_t stackId , gpPd_TimeStamp_t txTime , UInt16* pIndex);
#endif /* defined(GP_MACCORE_DIVERSITY_SCAN_ORPHAN_RECIPIENT) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !defined(GP_COMP_MACDISPATCHER)
void gpMacCore_cbValidStack_Input_par2api(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_cbValidStack_Output_buf2par(Bool* valid , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */
#if !defined(GP_COMP_MACDISPATCHER)
void gpMacCore_cbPurgeConfirm_Input_par2api(UInt8Buffer* pDest , gpMacCore_Result_t status , gpPd_Handle_t pdHandle , UInt16* pIndex);
#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */
#if !defined(GP_COMP_MACDISPATCHER)
void gpMacCore_cbPollNotify_Input_par2api(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* addressInfo , gpMacCore_StackId_t stackId , gpPd_TimeStamp_t rxTime , gpPd_Handle_t pdHandle , Bool fromNeighbour , UInt16* pIndex);
#endif /* defined(GP_MACCORE_DIVERSITY_POLL_RECIPIENT) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !(defined(GP_COMP_MACDISPATCHER))
void gpMacCore_cbSecurityFrameCounterIndication_Input_par2api(UInt8Buffer* pDest , UInt32 frameCounter , gpMacCore_StackId_t stackId , UInt16* pIndex);
#endif /* !(defined(GP_COMP_MACDISPATCHER)) */

// Client functions
void gpMacCore_Reset_Input_par2buf(UInt8Buffer* pDest , Bool setDefaultPib , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_Reset_Output_buf2par(gpMacCore_Result_t* result , Bool setDefaultPib , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_DataRequest_Input_par2buf(UInt8Buffer* pDest , gpMacCore_AddressMode_t srcAddrMode , gpMacCore_AddressInfo_t* pDstAddressInfo , UInt8 txOptions , gpMacCore_Security_t* pSecOptions , gpMacCore_MultiChannelOptions_t multiChannelOptions , gpPd_Loh_t pdLoh , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_ScanRequest_Input_par2buf(UInt8Buffer* pDest , gpMacCore_ScanType_t scanType , UInt32 scanChannels , UInt8 scanDuration , UInt8 resultListSize , UInt8* pEdScanResultList , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_AssociateRequest_Input_par2buf(UInt8Buffer* pDest , UInt8 logicalChannel , gpMacCore_AddressInfo_t* coordAddrInfo , UInt8 capabilityInformation , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_AssociateResponse_Input_par2buf(UInt8Buffer* pDest , MACAddress_t* pDeviceAddress , UInt16 associateShortAddress , gpMacCore_Result_t status , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_PollRequest_Input_par2buf(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* coordAddrInfo , gpMacCore_Security_t* pSecOptions , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_Start_Input_par2buf(UInt8Buffer* pDest , gpMacCore_PanId_t panId , UInt8 logicalChannel , Bool panCoordinator , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_Start_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_PanId_t panId , UInt8 logicalChannel , Bool panCoordinator , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetSecurityEnabled_Input_par2buf(UInt8Buffer* pDest , Bool securityEnabled , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_SetDeviceDescriptor_Input_par2buf(UInt8Buffer* pDest , gpMacCore_DeviceDescriptor_t* pDeviceDescriptor , gpMacCore_Index_t index , UInt16* pIndex);
void gpMacCore_SetDeviceDescriptor_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_DeviceDescriptor_t* pDeviceDescriptor , gpMacCore_Index_t index , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetDeviceDescriptor_Input_par2buf(UInt8Buffer* pDest , gpMacCore_Index_t index , UInt16* pIndex);
void gpMacCore_GetDeviceDescriptor_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_DeviceDescriptor_t* pDeviceDescriptor , gpMacCore_Index_t index , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetDeviceTableEntries_Input_par2buf(UInt8Buffer* pDest , gpMacCore_DeviceTablesEntries_t deviceTableEntries , UInt16* pIndex);
void gpMacCore_GetDeviceTableEntries_Output_buf2par(gpMacCore_DeviceTablesEntries_t* deviceTableEntries , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetKeyDescriptor_Input_par2buf(UInt8Buffer* pDest , gpMacCore_KeyDescriptor_t* pKeyDescriptor , gpMacCore_Index_t index , UInt16* pIndex);
void gpMacCore_SetKeyDescriptor_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_KeyDescriptor_t* pKeyDescriptor , gpMacCore_Index_t index , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetKeyDescriptor_Input_par2buf(UInt8Buffer* pDest , gpMacCore_Index_t index , UInt16* pIndex);
void gpMacCore_GetKeyDescriptor_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_KeyDescriptor_t* pKeyDescriptor , gpMacCore_Index_t index , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetKeyTableEntries_Input_par2buf(UInt8Buffer* pDest , gpMacCore_KeyTablesEntries_t keyTableEntries , UInt16* pIndex);
void gpMacCore_SetSecurityLevelDescriptor_Input_par2buf(UInt8Buffer* pDest , gpMacCore_SecurityLevelDescriptor_t* pSecurityLevelDescriptor , gpMacCore_Index_t index , UInt16* pIndex);
void gpMacCore_SetSecurityLevelDescriptor_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_SecurityLevelDescriptor_t* pSecurityLevelDescriptor , gpMacCore_Index_t index , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetSecurityLevelDescriptor_Input_par2buf(UInt8Buffer* pDest , gpMacCore_Index_t index , UInt16* pIndex);
void gpMacCore_GetSecurityLevelDescriptor_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_SecurityLevelDescriptor_t* pSecurityLevelDescriptor , gpMacCore_Index_t index , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetSecurityLevelTableEntries_Input_par2buf(UInt8Buffer* pDest , gpMacCore_SecurityLevelTableEntries_t securityLevelTableEntries , UInt16* pIndex);
void gpMacCore_GetSecurityLevelTableEntries_Output_buf2par(gpMacCore_SecurityLevelTableEntries_t* securityLevelTableEntries , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetDefaultKeySource_Input_par2buf(UInt8Buffer* pDest , UInt8* pDefaultKeySource , UInt16* pIndex);
void gpMacCore_SetShortAddress_Input_par2buf(UInt8Buffer* pDest , UInt16 shortAddress , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_SetExtendedAddress_Input_par2buf(UInt8Buffer* pDest , MACAddress_t* pExtendedAddress , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_SetPanId_Input_par2buf(UInt8Buffer* pDest , UInt16 panId , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetPanId_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetPanId_Output_buf2par(gpMacCore_PanId_t* panId , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetFrameCounter_Input_par2buf(UInt8Buffer* pDest , UInt32 frameCounter , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_SetDsn_Input_par2buf(UInt8Buffer* pDest , UInt8 dsn , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_SetCurrentChannel_Input_par2buf(UInt8Buffer* pDest , UInt8 channel , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_SetBeaconPayload_Input_par2buf(UInt8Buffer* pDest , UInt8* pBeaconPayload , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_SetBeaconPayloadLength_Input_par2buf(UInt8Buffer* pDest , UInt8 beaconPayloadLength , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_SetRxOnWhenIdle_Input_par2buf(UInt8Buffer* pDest , Bool rxOnWhenIdle , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetExtendedAddress_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetExtendedAddress_Output_buf2par(MACAddress_t* pExtendedAddress , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetMaxCsmaBackoffs_Input_par2buf(UInt8Buffer* pDest , UInt8 maxCsmaBackoffs , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetMaxCsmaBackoffs_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetMaxCsmaBackoffs_Output_buf2par(UInt8* maxCsmaBackoffs , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetDsn_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetDsn_Output_buf2par(UInt8* dsn , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetCurrentChannel_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetCurrentChannel_Output_buf2par(UInt8* channel , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetNumberOfRetries_Input_par2buf(UInt8Buffer* pDest , UInt8 numberOfRetries , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetNumberOfRetries_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetNumberOfRetries_Output_buf2par(UInt8* numberOfRetries , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetFrameCounter_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetFrameCounter_Output_buf2par(UInt32* frameCounter , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetRxOnWhenIdle_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetRxOnWhenIdle_Output_buf2par(Bool* rxOnWhenIdle , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetShortAddress_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetShortAddress_Output_buf2par(UInt16* address , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetPanCoordShortAddress_Input_par2buf(UInt8Buffer* pDest , UInt16 panCoordShortAddress , UInt16* pIndex);
void gpMacCore_SetPanCoordExtendedAddress_Input_par2buf(UInt8Buffer* pDest , MACAddress_t* pPanCoordExtendedAddress , UInt16* pIndex);
void gpMacCore_SetAssociationPermit_Input_par2buf(UInt8Buffer* pDest , Bool associationPermit , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_SetDefaultTransmitPowers_Input_par2buf(UInt8Buffer* pDest , Int8* pDefaultTransmitPowerTable , UInt16* pIndex);
void gpMacCore_SetTransmitPower_Input_par2buf(UInt8Buffer* pDest , gpMacCore_TxPower_t transmitPower , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetTransmitPower_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetTransmitPower_Output_buf2par(Int8* transmitPower , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetPanCoordinator_Input_par2buf(UInt8Buffer* pDest , Bool panCoordinator , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetPanCoordinator_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetPanCoordinator_Output_buf2par(Bool* panCoordinator , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_OrphanResponse_Input_par2buf(UInt8Buffer* pDest , MACAddress_t* pOrphanAddress , UInt16 shortAddress , Bool associatedMember , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetSecurityEnabled_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetSecurityEnabled_Output_buf2par(Bool* securityEnabled , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetTransactionPersistenceTime_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetTransactionPersistenceTime_Output_buf2par(UInt16* time , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetTransactionPersistenceTime_Input_par2buf(UInt8Buffer* pDest , UInt16 time , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_SetBeaconStarted_Input_par2buf(UInt8Buffer* pDest , Bool BeaconStarted , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetBeaconStarted_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetBeaconStarted_Output_buf2par(Bool* BeaconStarted , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetPanCoordExtendedAddress_Output_buf2par(MACAddress_t* pPanCoordExtendedAddress , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetCoordExtendedAddress_Input_par2buf(UInt8Buffer* pDest , MACAddress_t* pPanCoordExtendedAddress , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetCoordExtendedAddress_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetCoordExtendedAddress_Output_buf2par(MACAddress_t* pPanCoordExtendedAddress , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetCoordShortAddress_Input_par2buf(UInt8Buffer* pDest , UInt16 panCoordShortAddress , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetCoordShortAddress_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetCoordShortAddress_Output_buf2par(UInt16* panCoordShortAddress , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetAssociationPermit_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetAssociationPermit_Output_buf2par(Bool* associationPermit , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetBeaconPayload_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetBeaconPayload_Output_buf2par(UInt8* pBeaconPayload , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetBeaconPayloadLength_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetBeaconPayloadLength_Output_buf2par(UInt8* beaconPayloadLength , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetIndicateBeaconNotifications_Input_par2buf(UInt8Buffer* pDest , Bool enable , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_SetPromiscuousMode_Input_par2buf(UInt8Buffer* pDest , UInt8 promiscuousMode , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_SetMacVersion_Input_par2buf(UInt8Buffer* pDest , gpMacCore_MacVersion_t macVersion , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetMacVersion_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetMacVersion_Output_buf2par(gpMacCore_MacVersion_t* macVersion , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_StackAdded_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_StackRemoved_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetIndicateBeaconNotifications_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetIndicateBeaconNotifications_Output_buf2par(Bool* enabled , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetCCAMode_Input_par2buf(UInt8Buffer* pDest , UInt8 cCAMode , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetCCAMode_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetCCAMode_Output_buf2par(UInt8* cCAMode , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetMinBE_Input_par2buf(UInt8Buffer* pDest , UInt8 minBE , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetMinBE_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetMinBE_Output_buf2par(UInt8* minBE , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_GetPromiscuousMode_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetPromiscuousMode_Output_buf2par(Bool* promiscuousMode , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_PurgeRequest_Input_par2buf(UInt8Buffer* pDest , gpPd_Handle_t pdHandle , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_SetForwardPollIndications_Input_par2buf(UInt8Buffer* pDest , Bool enable , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetForwardPollIndications_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetForwardPollIndications_Output_buf2par(Bool* enable , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetMaxBE_Input_par2buf(UInt8Buffer* pDest , UInt8 maxBE , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetMaxBE_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetMaxBE_Output_buf2par(UInt8* maxBE , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_AddNeighbour_Input_par2buf(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* pAddrInfo , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_AddNeighbour_Output_buf2par(Bool* result , gpMacCore_AddressInfo_t* pAddrInfo , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_RemoveNeighbour_Input_par2buf(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* pAddrInfo , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_RemoveNeighbour_Output_buf2par(Bool* result , gpMacCore_AddressInfo_t* pAddrInfo , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetDataPendingMode_Input_par2buf(UInt8Buffer* pDest , gpMacCore_DataPendingMode_t dataPendingMode , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_SetDataPendingMode_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_DataPendingMode_t dataPendingMode , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetAddressModeOverrideForBeacons_Input_par2buf(UInt8Buffer* pDest , UInt8 addressMode , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_ClearNeighbours_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_SetCsmaMode_Input_par2buf(UInt8Buffer* pDest , UInt8 csmaMode , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetCsmaMode_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetCsmaMode_Output_buf2par(UInt8* csmaMode , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_ScheduleTimedTx_Input_par2buf(UInt8Buffer* pDest , gpPd_Handle_t pdHandle , gpMacCore_TxTimingOptions_t timingOptions , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_ScheduleTimedTx_Output_buf2par(gpMacCore_Result_t* result , gpPd_Handle_t pdHandle , gpMacCore_TxTimingOptions_t timingOptions , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_DataPending_QueueAdd_Input_par2buf(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* pAddrInfo , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_DataPending_QueueAdd_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_AddressInfo_t* pAddrInfo , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_DataPending_QueueRemove_Input_par2buf(UInt8Buffer* pDest , gpMacCore_AddressInfo_t* pAddrInfo , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_DataPending_QueueRemove_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_AddressInfo_t* pAddrInfo , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetMinInterferenceLevels_Input_par2buf(UInt8Buffer* pDest , Int8* pInterferenceLevels , UInt16* pIndex);
void gpMacCore_SetMinInterferenceLevels_Output_buf2par(gpMacCore_Result_t* result , Int8* pInterferenceLevels , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_DataPending_QueueClear_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_DataPending_QueueClear_Output_buf2par(gpMacCore_Result_t* result , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_DataPendingGetAckDataPending_Output_buf2par(Bool* pending , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetStackInRawMode_Input_par2buf(UInt8Buffer* pDest , Bool rawModeEnabled , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetStackInRawMode_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetStackInRawMode_Output_buf2par(Bool* rawModeEnabled , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_EnableEnhancedFramePending_Input_par2buf(UInt8Buffer* pDest , Bool enableEnhancedFramePending , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_EnableRxWindows_Input_par2buf(UInt8Buffer* pDest , UInt32 dutyCycleOnTime , UInt32 dutyCyclePeriod , UInt16 recurrenceAmount , UInt32 startTime , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_DisableRxWindows_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_EnableCsl_Input_par2buf(UInt8Buffer* pDest , UInt16 dutyCyclePeriod , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_UpdateCslSampleTime_Input_par2buf(UInt8Buffer* pDest , UInt32 nextCslSampleTime , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetCurrentTimeUs_Output_buf2par(UInt32* currentTime , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_ConfigureEnhAckProbing_Input_par2buf(UInt8Buffer* pDest , UInt8 linkMetrics , MACAddress_t* pExtendedAddress , UInt16 shortAddress , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_ConfigureEnhAckProbing_Output_buf2par(gpMacCore_Result_t* result , UInt8 linkMetrics , MACAddress_t* pExtendedAddress , UInt16 shortAddress , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetRetransmitOnCcaFail_Input_par2buf(UInt8Buffer* pDest , Bool enable , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetRetransmitOnCcaFail_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetRetransmitOnCcaFail_Output_buf2par(Bool* enable , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetRetransmitRandomBackoff_Input_par2buf(UInt8Buffer* pDest , Bool enable , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetRetransmitRandomBackoff_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetRetransmitRandomBackoff_Output_buf2par(Bool* enable , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetMinBeRetransmit_Input_par2buf(UInt8Buffer* pDest , UInt8 minBERetransmit , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetMinBeRetransmit_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetMinBeRetransmit_Output_buf2par(UInt8* minBERetransmit , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_SetMaxBeRetransmit_Input_par2buf(UInt8Buffer* pDest , UInt8 maxBERetransmit , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetMaxBeRetransmit_Input_par2buf(UInt8Buffer* pDest , gpMacCore_StackId_t stackId , UInt16* pIndex);
void gpMacCore_GetMaxBeRetransmit_Output_buf2par(UInt8* maxBERetransmit , gpMacCore_StackId_t stackId , UInt8Buffer* pSource , UInt16* pIndex);
#if !defined(GP_COMP_MACDISPATCHER)
gpMarshall_AckStatus_t gpMacCore_cbDataConfirm_Input_buf2api(gpMacCore_cbDataConfirm_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */
#if !defined(GP_COMP_MACDISPATCHER)
gpMarshall_AckStatus_t gpMacCore_cbDataIndication_Input_buf2api(gpMacCore_cbDataIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */
#if !defined(GP_COMP_MACDISPATCHER)
gpMarshall_AckStatus_t gpMacCore_cbScanConfirm_Input_buf2api(gpMacCore_cbScanConfirm_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */
#if !defined(GP_COMP_MACDISPATCHER)
gpMarshall_AckStatus_t gpMacCore_cbBeaconNotifyIndication_Input_buf2api(gpMacCore_cbBeaconNotifyIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */
#if !defined(GP_COMP_MACDISPATCHER)
gpMarshall_AckStatus_t gpMacCore_cbOrphanIndication_Input_buf2api(gpMacCore_cbOrphanIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
#endif /* defined(GP_MACCORE_DIVERSITY_ASSOCIATION_ORIGINATOR) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !defined(GP_COMP_MACDISPATCHER)
gpMarshall_AckStatus_t gpMacCore_cbSecurityFailureCommStatusIndication_Input_buf2api(gpMacCore_cbSecurityFailureCommStatusIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */
#if !defined(GP_COMP_MACDISPATCHER)
gpMarshall_AckStatus_t gpMacCore_cbPollConfirm_Input_buf2api(gpMacCore_cbPollConfirm_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
#endif /* defined(GP_MACCORE_DIVERSITY_POLL_ORIGINATOR) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !defined(GP_COMP_MACDISPATCHER)
gpMarshall_AckStatus_t gpMacCore_cbPollIndication_Input_buf2api(gpMacCore_cbPollIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
#endif /* defined(GP_MACCORE_DIVERSITY_POLL_RECIPIENT) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !defined(GP_COMP_MACDISPATCHER)
gpMarshall_AckStatus_t gpMacCore_cbAssociateConfirm_Input_buf2api(gpMacCore_cbAssociateConfirm_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
#endif /* defined(GP_MACCORE_DIVERSITY_ASSOCIATION_ORIGINATOR) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !defined(GP_COMP_MACDISPATCHER)
gpMarshall_AckStatus_t gpMacCore_cbAssociateIndication_Input_buf2api(gpMacCore_cbAssociateIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
#endif /* defined(GP_MACCORE_DIVERSITY_ASSOCIATION_RECIPIENT) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !defined(GP_COMP_MACDISPATCHER)
gpMarshall_AckStatus_t gpMacCore_cbAssociateCommStatusIndication_Input_buf2api(gpMacCore_cbAssociateCommStatusIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
#endif /* defined(GP_MACCORE_DIVERSITY_ASSOCIATION_RECIPIENT) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !defined(GP_COMP_MACDISPATCHER)
gpMarshall_AckStatus_t gpMacCore_cbOrphanCommStatusIndication_Input_buf2api(gpMacCore_cbOrphanCommStatusIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
#endif /* defined(GP_MACCORE_DIVERSITY_SCAN_ORPHAN_RECIPIENT) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !defined(GP_COMP_MACDISPATCHER)
gpMarshall_AckStatus_t gpMacCore_cbValidStack_Input_buf2api(gpMacCore_cbValidStack_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
void gpMacCore_cbValidStack_Output_api2buf(UInt8Buffer* pDest , gpMacCore_cbValidStack_Output_marshall_struct_t* pSourceoutput , gpMacCore_cbValidStack_Input_marshall_struct_t* pSourceinput , UInt16* pIndex);
#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */
#if !defined(GP_COMP_MACDISPATCHER)
gpMarshall_AckStatus_t gpMacCore_cbPurgeConfirm_Input_buf2api(gpMacCore_cbPurgeConfirm_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
#endif /* defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER) */
#if !defined(GP_COMP_MACDISPATCHER)
gpMarshall_AckStatus_t gpMacCore_cbPollNotify_Input_buf2api(gpMacCore_cbPollNotify_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
#endif /* defined(GP_MACCORE_DIVERSITY_POLL_RECIPIENT) && (defined(GP_MACCORE_FORCE_INDICATION_DEFINITION)||!defined(GP_COMP_MACDISPATCHER)) */
#if !(defined(GP_COMP_MACDISPATCHER))
gpMarshall_AckStatus_t gpMacCore_cbSecurityFrameCounterIndication_Input_buf2api(gpMacCore_cbSecurityFrameCounterIndication_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex);
#endif /* !(defined(GP_COMP_MACDISPATCHER)) */

void gpMacCore_InitMarshalling(void);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // _GPMACCORE_MARSHALLING_H_


