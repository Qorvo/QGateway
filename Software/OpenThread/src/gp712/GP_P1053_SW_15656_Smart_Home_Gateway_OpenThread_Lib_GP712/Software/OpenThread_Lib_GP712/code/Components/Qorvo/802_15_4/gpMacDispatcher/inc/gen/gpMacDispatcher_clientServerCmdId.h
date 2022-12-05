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
 * $Header: //depot/release/Embedded/Components/Qorvo/802_15_4/v2.10.3.1/comps/gpMacDispatcher/inc/gen/gpMacDispatcher_clientServerCmdId.h#1 $
 * $Change: 197210 $
 * $DateTime: 2022/10/13 16:52:00 $
 */

/** @file "gpMacDispatcher_clientServerCmdId.h"
 *
 *  MAC Dispatcher
 *
 *  Client Server Link Command IDs
*/

#ifndef _GPMACDISPATCHER_CLIENTSERVERCMDID_H_
#define _GPMACDISPATCHER_CLIENTSERVERCMDID_H_

/*****************************************************************************
 *                    Common timeout
 *****************************************************************************/

#ifndef GPMACDISPATCHER_GPCOMTIMEOUT_US
#define GPMACDISPATCHER_GPCOMTIMEOUT_US 10000000UL //10s
#endif //GPMACDISPATCHER_GPCOMTIMEOUT_US

/*****************************************************************************
 *                    Component Specific Command IDs
 *****************************************************************************/

#define gpMacDispatcher_Init_CmdId                                   0x01 /*01*/
#define gpMacDispatcher_RegisterNetworkStack_CmdId                   0x02 /*02*/
#define gpMacDispatcher_UnRegisterNetworkStack_CmdId                 0x03 /*03*/
#define gpMacDispatcher_LockClaim_CmdId                              0x05 /*05*/
#define gpMacDispatcher_LockRelease_CmdId                            0x06 /*06*/
#define gpMacDispatcher_LockedByThisStack_CmdId                      0x07 /*07*/
#define gpMacDispatcher_Locked_CmdId                                 0x08 /*08*/
#define gpMacDispatcher_Reset_CmdId                                  0x09 /*09*/
#define gpMacDispatcher_DataRequest_CmdId                            0x0c /*12*/
#define gpMacDispatcher_ScanRequest_CmdId                            0x11 /*17*/
#define gpMacDispatcher_AssociateRequest_CmdId                       0x14 /*20*/
#define gpMacDispatcher_AssociateResponse_CmdId                      0x17 /*23*/
#define gpMacDispatcher_PollRequest_CmdId                            0x1c /*28*/
#define gpMacDispatcher_PurgeRequest_CmdId                           0x21 /*33*/
#define gpMacDispatcher_Start_CmdId                                  0x24 /*36*/
#define gpMacDispatcher_OrphanResponse_CmdId                         0x2b /*43*/
#define gpMacDispatcher_SetPanId_CmdId                               0x2e /*46*/
#define gpMacDispatcher_GetPanId_CmdId                               0x2f /*47*/
#define gpMacDispatcher_SetShortAddress_CmdId                        0x30 /*48*/
#define gpMacDispatcher_GetShortAddress_CmdId                        0x31 /*49*/
#define gpMacDispatcher_SetExtendedAddress_CmdId                     0x32 /*50*/
#define gpMacDispatcher_GetExtendedAddress_CmdId                     0x33 /*51*/
#define gpMacDispatcher_SetDsn_CmdId                                 0x34 /*52*/
#define gpMacDispatcher_GetDsn_CmdId                                 0x35 /*53*/
#define gpMacDispatcher_SetCurrentChannel_CmdId                      0x36 /*54*/
#define gpMacDispatcher_GetCurrentChannel_CmdId                      0x37 /*55*/
#define gpMacDispatcher_SetBeaconPayload_CmdId                       0x38 /*56*/
#define gpMacDispatcher_GetBeaconPayload_CmdId                       0x39 /*57*/
#define gpMacDispatcher_SetBeaconPayloadLength_CmdId                 0x3a /*58*/
#define gpMacDispatcher_GetBeaconPayloadLength_CmdId                 0x3b /*59*/
#define gpMacDispatcher_SetTxAntenna_CmdId                           0x3c /*60*/
#define gpMacDispatcher_GetTxAntenna_CmdId                           0x3d /*61*/
#define gpMacDispatcher_SetRxOnWhenIdle_CmdId                        0x3e /*62*/
#define gpMacDispatcher_GetRxOnWhenIdle_CmdId                        0x3f /*63*/
#define gpMacDispatcher_GetTransactionPersistenceTime_CmdId          0x40 /*64*/
#define gpMacDispatcher_SetTransactionPersistenceTime_CmdId          0x41 /*65*/
#define gpMacDispatcher_SetBeaconStarted_CmdId                       0x42 /*66*/
#define gpMacDispatcher_GetBeaconStarted_CmdId                       0x43 /*67*/
#define gpMacDispatcher_SetCoordShortAddress_CmdId                   0x44 /*68*/
#define gpMacDispatcher_GetCoordShortAddress_CmdId                   0x45 /*69*/
#define gpMacDispatcher_SetCoordExtendedAddress_CmdId                0x46 /*70*/
#define gpMacDispatcher_GetCoordExtendedAddress_CmdId                0x47 /*71*/
#define gpMacDispatcher_SetPromiscuousMode_CmdId                     0x48 /*72*/
#define gpMacDispatcher_GetPromiscuousMode_CmdId                     0x49 /*73*/
#define gpMacDispatcher_SetAssociationPermit_CmdId                   0x4a /*74*/
#define gpMacDispatcher_GetAssociationPermit_CmdId                   0x4b /*75*/
#define gpMacDispatcher_SetSecurityEnabled_CmdId                     0x4c /*76*/
#define gpMacDispatcher_GetSecurityEnabled_CmdId                     0x4d /*77*/
#define gpMacDispatcher_SetNumberOfRetries_CmdId                     0x4f /*79*/
#define gpMacDispatcher_GetNumberOfRetries_CmdId                     0x50 /*80*/
#define gpMacDispatcher_SetMaxCsmaBackoffs_CmdId                     0x51 /*81*/
#define gpMacDispatcher_GetMaxCsmaBackoffs_CmdId                     0x52 /*82*/
#define gpMacDispatcher_SetDefaultTransmitPowers_CmdId               0x53 /*83*/
#define gpMacDispatcher_SetTransmitPower_CmdId                       0x54 /*84*/
#define gpMacDispatcher_GetTransmitPower_CmdId                       0x55 /*85*/
#define gpMacDispatcher_SetCCAMode_CmdId                             0x56 /*86*/
#define gpMacDispatcher_GetCCAMode_CmdId                             0x57 /*87*/
#define gpMacDispatcher_SetPanCoordinator_CmdId                      0x58 /*88*/
#define gpMacDispatcher_GetPanCoordinator_CmdId                      0x59 /*89*/
#define gpMacDispatcher_SetMinBE_CmdId                               0x5a /*90*/
#define gpMacDispatcher_GetMinBE_CmdId                               0x5b /*91*/
#define gpMacDispatcher_SetIndicateBeaconNotifications_CmdId         0x5c /*92*/
#define gpMacDispatcher_GetIndicateBeaconNotifications_CmdId         0x5d /*93*/
#define gpMacDispatcher_SetMacVersion_CmdId                          0x60 /*96*/
#define gpMacDispatcher_GetMacVersion_CmdId                          0x61 /*97*/
#define gpMacDispatcher_SetForwardPollIndications_CmdId              0x64 /*100*/
#define gpMacDispatcher_GetForwardPollIndications_CmdId              0x65 /*101*/
#define gpMacDispatcher_DataPending_QueueAdd_CmdId                   0x66 /*102*/
#define gpMacDispatcher_DataPending_QueueRemove_CmdId                0x67 /*103*/
#define gpMacDispatcher_SetMinInterferenceLevels_CmdId               0x68 /*104*/
#define gpMacDispatcher_SetMaxBE_CmdId                               0x69 /*105*/
#define gpMacDispatcher_GetMaxBE_CmdId                               0x6a /*106*/
#define gpMacDispatcher_SetDeviceDescriptor_CmdId                    0x6e /*110*/
#define gpMacDispatcher_GetDeviceDescriptor_CmdId                    0x6f /*111*/
#define gpMacDispatcher_SetDeviceTableEntries_CmdId                  0x70 /*112*/
#define gpMacDispatcher_GetDeviceTableEntries_CmdId                  0x71 /*113*/
#define gpMacDispatcher_SetKeyDescriptor_CmdId                       0x72 /*114*/
#define gpMacDispatcher_GetKeyDescriptor_CmdId                       0x73 /*115*/
#define gpMacDispatcher_SetKeyTableEntries_CmdId                     0x74 /*116*/
#define gpMacDispatcher_SetSecurityLevelDescriptor_CmdId             0x75 /*117*/
#define gpMacDispatcher_GetSecurityLevelDescriptor_CmdId             0x76 /*118*/
#define gpMacDispatcher_SetSecurityLevelTableEntries_CmdId           0x77 /*119*/
#define gpMacDispatcher_GetSecurityLevelTableEntries_CmdId           0x78 /*120*/
#define gpMacDispatcher_SetDefaultKeySource_CmdId                    0x79 /*121*/
#define gpMacDispatcher_SetFrameCounter_CmdId                        0x7a /*122*/
#define gpMacDispatcher_GetFrameCounter_CmdId                        0x7b /*123*/
#define gpMacDispatcher_SetPanCoordShortAddress_CmdId                0x7c /*124*/
#define gpMacDispatcher_SetPanCoordExtendedAddress_CmdId             0x7d /*125*/
#define gpMacDispatcher_GetPanCoordExtendedAddress_CmdId             0x7e /*126*/
#define gpMacDispatcher_AddNeighbour_CmdId                           0x81 /*129*/
#define gpMacDispatcher_RemoveNeighbour_CmdId                        0x82 /*130*/
#define gpMacDispatcher_SetDataPendingMode_CmdId                     0x83 /*131*/
#define gpMacDispatcher_SetLqiThresholdForTest_CmdId                 0x84 /*132*/
#define gpMacDispatcher_SetAddressModeOverrideForBeacons_CmdId       0x85 /*133*/
#define gpMacDispatcher_ClearNeighbours_CmdId                        0x86 /*134*/
#define gpMacDispatcher_SetCsmaMode_CmdId                            0x8b /*139*/
#define gpMacDispatcher_GetCsmaMode_CmdId                            0x8c /*140*/
#define gpMacDispatcher_DataPending_QueueClear_CmdId                 0x8d /*141*/
#define gpMacDispatcher_ScheduleTimedTx_CmdId                        0x8e /*142*/
#define gpMacDispatcher_SetRegionalDomainSettings_CmdId              0x8f /*143*/
#define gpMacDispatcher_GetRegionalDomainSettings_CmdId              0x90 /*144*/
#define gpMacDispatcher_SetAutoTxAntennaToggling_CmdId               0x91 /*145*/
#define gpMacDispatcher_GetAutoTxAntennaToggling_CmdId               0x92 /*146*/
#define gpMacDispatcher_SetMultipleChannelTable_CmdId                0x93 /*147*/
#define gpMacDispatcher_SetStackInRawMode_CmdId                      0x94 /*148*/
#define gpMacDispatcher_GetStackInRawMode_CmdId                      0x95 /*149*/
#define gpMacDispatcher_SetRawModeEncryptionKeys_CmdId               0x96 /*150*/
#define gpMacDispatcher_SetRawModeNonceFields_CmdId                  0x97 /*151*/
#define gpMacDispatcher_EnableEnhancedFramePending_CmdId             0x98 /*152*/
#define gpMacDispatcher_EnableRxWindows_CmdId                        0x99 /*153*/
#define gpMacDispatcher_DisableRxWindows_CmdId                       0x9a /*154*/
#define gpMacDispatcher_EnableCsl_CmdId                              0x9b /*155*/
#define gpMacDispatcher_UpdateCslSampleTime_CmdId                    0x9c /*156*/
#define gpMacDispatcher_GetCurrentTimeUs_CmdId                       0x9d /*157*/
#define gpMacDispatcher_ConfigureEnhAckProbing_CmdId                 0x9e /*158*/
#define gpMacDispatcher_SetRetransmitOnCcaFail_CmdId                 0x9f /*159*/
#define gpMacDispatcher_GetRetransmitOnCcaFail_CmdId                 0xa0 /*160*/
#define gpMacDispatcher_SetRetransmitRandomBackoff_CmdId             0xa1 /*161*/
#define gpMacDispatcher_GetRetransmitRandomBackoff_CmdId             0xa2 /*162*/
#define gpMacDispatcher_SetMinBeRetransmit_CmdId                     0xa3 /*163*/
#define gpMacDispatcher_GetMinBeRetransmit_CmdId                     0xa4 /*164*/
#define gpMacDispatcher_SetMaxBeRetransmit_CmdId                     0xa5 /*165*/
#define gpMacDispatcher_GetMaxBeRetransmit_CmdId                     0xa6 /*166*/
#define MacDispatcher_cbDataConfirm_CmdId                            0x0d /*13*/
#define MacDispatcher_cbDataIndication_CmdId                         0x0f /*15*/
#define MacDispatcher_cbScanConfirm_CmdId                            0x12 /*18*/
#define MacDispatcher_cbAssociateIndication_CmdId                    0x15 /*21*/
#define MacDispatcher_cbAssociateConfirm_CmdId                       0x18 /*24*/
#define MacDispatcher_cbAssociateCommStatusIndication_CmdId          0x1a /*26*/
#define MacDispatcher_cbPollConfirm_CmdId                            0x1d /*29*/
#define MacDispatcher_cbPollIndication_CmdId                         0x1f /*31*/
#define MacDispatcher_cbPurgeConfirm_CmdId                           0x22 /*34*/
#define MacDispatcher_cbBeaconNotifyIndication_CmdId                 0x25 /*37*/
#define MacDispatcher_cbOrphanIndication_CmdId                       0x27 /*39*/
#define MacDispatcher_cbOrphanCommStatusIndication_CmdId             0x29 /*41*/
#define MacDispatcher_cbSecurityFailureCommStatusIndication_CmdId    0x2c /*44*/
#define MacDispatcher_cbDriverResetIndication_CmdId                  0x62 /*98*/
#define MacDispatcher_cbPollNotify_CmdId                             0x7f /*127*/
#define MacDispatcher_cbSecurityFrameCounterIndication_CmdId         0x89 /*137*/

/*****************************************************************************
 *                    Fixed Command IDs
 *****************************************************************************/

#define gpMacDispatcher_Acknowledge_CmdId                                   0xfe /*254*/
#define gpMacDispatcher_GetServerCompatibilityNumber_CmdId                  0xfd /*253*/

#endif //_GPMACDISPATCHER_CLIENTSERVERCMDID_H_

