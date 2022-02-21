/*
 * Copyright (c) 2017-2018, Qorvo Inc
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
 * $Header: //depot/release/Embedded/Components/Qorvo/802_15_4/v2.10.2.0/comps/gpMacDispatcher/src/gpMacDispatcher_callbacks.h#1 $
 * $Change: 187624 $
 * $DateTime: 2021/12/20 10:58:50 $
 *
 */

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/
#ifndef _GP_MACDISPATCHERCALLBACKS_H_
#define _GP_MACDISPATCHERCALLBACKS_H_

#include "global.h"
#include "gpMacCore.h"
#include "gpMacDispatcher.h"

/*****************************************************************************
 *                    Static Function Prototypes
 *****************************************************************************/

//Data callbacks

static void MacDispatcher_cbDataIndication(const gpMacCore_AddressInfo_t* pSrcAddrInfo, const gpMacCore_AddressInfo_t* pDstAddrInfo, UInt8 dsn,
                                           gpMacCore_Security_t *pSecOptions, gpPd_Loh_t pdLoh, gpMacDispatcher_StackId_t stackId);
static void MacDispatcher_cbDataConfirm(gpMacCore_Result_t status, UInt8 pdHandle, gpMacDispatcher_StackId_t stackId);
static void MacDispatcher_cbPurgeConfirm(gpMacCore_Result_t status, gpPd_Handle_t pdHandle, gpMacDispatcher_StackId_t stackId);
static void MacDispatcher_cbPollNotify(gpMacCore_AddressInfo_t* pAddrInfo, gpPd_TimeStamp_t rxTime, gpPd_Handle_t pdHandle, Bool fromNeighbour, gpMacDispatcher_StackId_t stackId);
static void MacDispatcher_cbPollIndication(gpMacCore_AddressInfo_t* pAddrInfo, gpPd_TimeStamp_t rxTime, gpMacDispatcher_StackId_t stackId);
static void MacDispatcher_cbPollConfirm(gpMacCore_Result_t status, gpMacCore_AddressInfo_t* pCoordAddrInfo, gpPd_TimeStamp_t txTime, gpMacDispatcher_StackId_t stackId);

//Misc callbacks
static void MacDispatcher_cbBeaconNotifyIndication(UInt8 bsn, gpMacCore_PanDescriptor_t* pPanDescriptor, UInt8 beaconPayloadLength , UInt8 *pBeaconPayload, gpMacDispatcher_StackId_t stackId);
static void MacDispatcher_cbAssociateIndication(gpMacCore_Address_t* pDeviceAddress, UInt8 capabilityInformation, gpPd_TimeStamp_t rxTime, gpMacDispatcher_StackId_t stackId);
static void MacDispatcher_cbAssociateCommStatusIndication(gpMacCore_AddressInfo_t* pSrcAddrInfo, gpMacCore_AddressInfo_t* pDstAddrInfo, gpMacCore_Result_t status, gpPd_TimeStamp_t txTime, gpMacDispatcher_StackId_t stackId);
static void MacDispatcher_cbOrphanIndication(MACAddress_t* pOrphanAddress, gpPd_TimeStamp_t rxTime, gpMacDispatcher_StackId_t stackId);
static void MacDispatcher_cbAssociateConfirm(UInt16 assocShortAddress, gpMacCore_Result_t status, gpPd_TimeStamp_t txTime, gpMacDispatcher_StackId_t stackId);
static void MacDispatcher_cbOrphanCommStatusIndication(gpMacCore_AddressInfo_t* pSrcAddrInfo, gpMacCore_AddressInfo_t* pDstAddrInfo, gpMacCore_Result_t status, gpPd_TimeStamp_t txTime, gpMacDispatcher_StackId_t stackId);
static void MacDispatcher_cbScanConfirm(gpMacCore_Result_t status, gpMacCore_ScanType_t scanType, UInt32 unscannedChannels, UInt8 resultListSize, UInt8* pEdScanResultList, gpMacDispatcher_StackId_t stackId);
static void MacDispatcher_cbSecurityFailureCommStatusIndication(gpMacCore_AddressInfo_t* pSrcAddrInfo, gpMacCore_AddressInfo_t* pDstAddrInfo, gpMacCore_Result_t status, gpPd_TimeStamp_t txTime, gpMacDispatcher_StackId_t stackId);
static void MacDispatcher_cbSecurityFrameCounterIndication(UInt32 frameCounter, gpMacDispatcher_StackId_t stackId);
static void MacDispatcher_cbDriverResetIndication(gpMacDispatcher_Result_t status, gpMacDispatcher_StackId_t stackId);

#endif //_GP_MACDISPATCHERCALLBACKS_H_
