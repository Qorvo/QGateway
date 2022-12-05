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
 * $Header: //depot/release/Embedded/Components/Qorvo/802_15_4/v2.10.3.1/comps/gpMacDispatcher/src/gen/gpMacDispatcher_wrapper_client.c#1 $
 * $Change: 197210 $
 * $DateTime: 2022/10/13 16:52:00 $
 */

/** @file "gpMacDispatcher_wrapper_client.c"
 *
 *  MAC Dispatcher
 *
 *  Wrapper implementation
*/

/*****************************************************************************
 *                    Includes Definition
 *****************************************************************************/

#include "hal.h"
#include "gpUtils.h"
#include "gpLog.h"
#include "gpAssert.h"
#include "gpSched.h"
#include "gpCom.h"
#include "gpPd.h"
#include "gpModule.h"
#include "gpMacDispatcher_clientServerCmdId.h"
#include "gpMacDispatcher.h"
#include "gpMacDispatcher_marshalling.h"
#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)
#include "gpVersion.h"
#endif
/* <CodeGenerator Placeholder> AdditionalIncludes */
#include "gpMacDispatcher_def.h"
#include "gpMacDispatcher_callbacks.h"
/* </CodeGenerator Placeholder> AdditionalIncludes */

/*****************************************************************************
 *                    Typedef Definition
 *****************************************************************************/

/*****************************************************************************
 *                    Static Functions Declaration
 *****************************************************************************/

static void gpMacDispatcher_HandleIndicationClient(UInt16 length, UInt8* pPayload, gpCom_CommunicationId_t communicationId);
static void MacDispatcher_HandleConnectionClose(gpCom_CommunicationId_t communicationId);

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/

#define GP_COMPONENT_ID GP_COMPONENT_ID_MACDISPATCHER
#define GP_MODULE_ID GP_COMPONENT_ID


#ifndef GP_MACDISPATCHER_COMM_ID
#define GP_MACDISPATCHER_COMM_ID GP_COM_DEFAULT_COMMUNICATION_ID
#endif

#define REGISTER_MODULE(handle)              GP_COM_REGISTER_MODULE(handle)
#define DATA_REQUEST(len,buf,commId)         GP_COM_DATA_REQUEST(len,buf,commId)
#define DATA_REQUEST_ACKED(len,buf,commId)   gpCom_DataRequestAndWaitForAck(GP_MODULE_ID, len, buf, commId, &gpMacDispatcher_reqAcked, GPMACDISPATCHER_GPCOMTIMEOUT_US, gpMacDispatcher_Acknowledge_CmdId)

/*****************************************************************************
 *                    Static Data
 *****************************************************************************/

typedef union ackDataNeeded {
    UInt8 dataBuf0[1];
    UInt8 dataBuf1[(2) * 1];
    UInt8 dataBuf2[1+8*1];
    UInt8 dataBuf3[1+GP_MACCORE_MAX_BEACON_PAYLOAD_LENGTH];
    UInt8 dataBuf4[(2*1 + 2*1 + 8*1 + 4*1 + 1)+1];
    UInt8 dataBuf5[(GP_MACCORE_NUMBER_OF_KEY_ID_LOOKUP_DESCRIPTORS*(9 + 1) + 1 + GP_MACCORE_NUMBER_OF_KEY_DEVICE_DESCRIPTORS*((2*1 + 2*1 + 8*1 + 4*1 + 1) + 1 + 1) + 1 + GP_MACCORE_NUMBER_OF_KEY_USAGE_DESCRIPTORS*(1 + 1) + 1 + 16)+1];
    UInt8 dataBuf6[(1 + 1 + 1 + 1)+1];
    UInt8 dataBuf7[(4) * 1];
    UInt8 dataBuf8[8*1];
    UInt8 dataBuf9[1+4*1+1+16];
} ackDataNeeded_t;
static UInt8 gpMacDispatcher_ackBuffer[1 + 1 + 1 + sizeof(ackDataNeeded_t)];
static Bool gpMacDispatcher_reqAcked;
/* <CodeGenerator Placeholder> AdditionalStaticData */
STATIC UInt8* gpMacDispatcher_pResultList = NULL; //Manual - EDScan list
STATIC UInt8  gpMacDispatcher_ClientLockedStack[GP_DIVERSITY_NR_OF_STACKS];
/* </CodeGenerator Placeholder> AdditionalStaticData */

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)
static Bool MacDispatcher_clientApiVersionSelected = false;
#endif

/*****************************************************************************
 *                    Static Function Definitions
 *****************************************************************************/
/* <CodeGenerator Placeholder> AdditionalStaticFunctionDefinitions */

// Define static functions MacDispatcher_cbXXX() to call registered API callbacks.
#include "gpMacDispatcher_callbacks.c"

/* </CodeGenerator Placeholder> AdditionalStaticFunctionDefinitions */

static void MacDispatcher_HandleConnectionClose(gpCom_CommunicationId_t communicationId)
{
/* <CodeGenerator Placeholder> ConnectionCloseFunction */
    GP_LOG_PRINTF("%s on commId=%x vs macDispComm=%x",0, __FUNCTION__, communicationId, GP_MACDISPATCHER_COMM_ID);
    if(GP_MACDISPATCHER_COMM_ID == communicationId)
    {
        //All stacks disconnected - only 1 server used
        UInt8 stackId;
        for (stackId = 0; stackId < GP_DIVERSITY_NR_OF_STACKS; ++stackId)
        {
            gpMacDispatcher_ClientLockedStack[stackId] = 0;
            MacDispatcher_cbDriverResetIndication(0, stackId);
        }
        MacDispatcher_InitStackMapping();
    }
/* </CodeGenerator Placeholder> ConnectionCloseFunction */
}

static void gpMacDispatcher_HandleIndicationClient(UInt16 length, UInt8* pPayload, gpCom_CommunicationId_t communicationId)
{
#define commandId pPayload[0]
    gpMarshall_AckStatus_t marshall_result;
    UInt16 _index = 1;
    gpMacDispatcher_Client_Input_union_t input;
    UInt8 ackBuffer[1 + 1 + 1];
    UInt8 ackBytes = 0; /*No ack's on indication - fill in length when needed - 3+x */

    if(pPayload == NULL)
    {
        MacDispatcher_HandleConnectionClose(communicationId);
        return;
    }

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

    ackBuffer[0] = gpMacDispatcher_Acknowledge_CmdId;
    ackBuffer[1] = gpMarshall_AckStatusSuccess;
    ackBuffer[2] = commandId;

    switch(commandId)
    {

        case MacDispatcher_cbDataConfirm_CmdId:
        {
            marshall_result = MacDispatcher_cbDataConfirm_Input_buf2api(&(input.MacDispatcher_cbDataConfirm) , pPayload , &_index);
            if (gpMarshall_AckStatusSuccess != marshall_result)
            {
                ackBuffer[1] = marshall_result;
                break;
            }

/* <CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbDataConfirm */
            if(input.MacDispatcher_cbDataConfirm.data.stackId < GP_DIVERSITY_NR_OF_STACKS)
            {
                if(gpMacDispatcher_ClientLockedStack[input.MacDispatcher_cbDataConfirm.data.stackId])
                {
                    break;
                }
            }
/* </CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbDataConfirm */

            MacDispatcher_cbDataConfirm(
                  input.MacDispatcher_cbDataConfirm.data.status
                , input.MacDispatcher_cbDataConfirm.data.pdHandle
                , input.MacDispatcher_cbDataConfirm.data.stackId
               );


            break;
        }
        case MacDispatcher_cbDataIndication_CmdId:
        {
            marshall_result = MacDispatcher_cbDataIndication_Input_buf2api(&(input.MacDispatcher_cbDataIndication) , pPayload , &_index);
            if (gpMarshall_AckStatusSuccess != marshall_result)
            {
                ackBuffer[1] = marshall_result;
                break;
            }

/* <CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbDataIndication */
            if(input.MacDispatcher_cbDataIndication.data.stackId < GP_DIVERSITY_NR_OF_STACKS)
            {
                if(gpMacDispatcher_ClientLockedStack[input.MacDispatcher_cbDataIndication.data.stackId])
                {
                    //MacDispatcher_cbDataIndication_Input_buf2api claims a pd, we need to free here
                    gpPd_FreePd(input.MacDispatcher_cbDataIndication.data.pdLoh.handle);
                    break;
                }
            }
/* </CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbDataIndication */

            MacDispatcher_cbDataIndication(
                  input.MacDispatcher_cbDataIndication.data.pSrcAddrInfo
                , input.MacDispatcher_cbDataIndication.data.pDstAddrInfo
                , input.MacDispatcher_cbDataIndication.data.dsn
                , input.MacDispatcher_cbDataIndication.data.pSecOptions
                , input.MacDispatcher_cbDataIndication.data.pdLoh
                , input.MacDispatcher_cbDataIndication.data.stackId
               );


            break;
        }
        case MacDispatcher_cbScanConfirm_CmdId:
        {
/* <CodeGenerator Placeholder> SpecialCall_MacDispatcher_cbScanConfirm */
            input.MacDispatcher_cbScanConfirm.data.pEdScanResultList = gpMacDispatcher_pResultList;
            gpMacDispatcher_pResultList = NULL;
            marshall_result = MacDispatcher_cbScanConfirm_Input_buf2api( &(input.MacDispatcher_cbScanConfirm) , pPayload , &_index );
            if (gpMarshall_AckStatusSuccess != marshall_result)
            {
                ackBuffer[1] = marshall_result;
                break;
            }

            if(input.MacDispatcher_cbScanConfirm.data.stackId < GP_DIVERSITY_NR_OF_STACKS)
            {
                if(gpMacDispatcher_ClientLockedStack[input.MacDispatcher_cbScanConfirm.data.stackId])
                {
                    break;
                }
            }

            MacDispatcher_cbScanConfirm(
                  input.MacDispatcher_cbScanConfirm.data.status
                , input.MacDispatcher_cbScanConfirm.data.scanType
                , input.MacDispatcher_cbScanConfirm.data.unscannedChannels
                , input.MacDispatcher_cbScanConfirm.data.resultListSize
                , input.MacDispatcher_cbScanConfirm.data.pEdScanResultList
                , input.MacDispatcher_cbScanConfirm.data.stackId
                );
/* </CodeGenerator Placeholder> SpecialCall_MacDispatcher_cbScanConfirm */


            break;
        }
        case MacDispatcher_cbAssociateIndication_CmdId:
        {
            marshall_result = MacDispatcher_cbAssociateIndication_Input_buf2api(&(input.MacDispatcher_cbAssociateIndication) , pPayload , &_index);
            if (gpMarshall_AckStatusSuccess != marshall_result)
            {
                ackBuffer[1] = marshall_result;
                break;
            }

/* <CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbAssociateIndication */
            if(input.MacDispatcher_cbAssociateIndication.data.stackId < GP_DIVERSITY_NR_OF_STACKS)
            {
                if(gpMacDispatcher_ClientLockedStack[input.MacDispatcher_cbAssociateIndication.data.stackId])
                {
                    break;
                }
            }
/* </CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbAssociateIndication */

            MacDispatcher_cbAssociateIndication(
                  input.MacDispatcher_cbAssociateIndication.data.pDeviceAddress
                , input.MacDispatcher_cbAssociateIndication.data.capabilityInformation
                , input.MacDispatcher_cbAssociateIndication.data.rxTime
                , input.MacDispatcher_cbAssociateIndication.data.stackId
               );


            break;
        }
        case MacDispatcher_cbAssociateConfirm_CmdId:
        {
            marshall_result = MacDispatcher_cbAssociateConfirm_Input_buf2api(&(input.MacDispatcher_cbAssociateConfirm) , pPayload , &_index);
            if (gpMarshall_AckStatusSuccess != marshall_result)
            {
                ackBuffer[1] = marshall_result;
                break;
            }

/* <CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbAssociateConfirm */
            if(input.MacDispatcher_cbAssociateConfirm.data.stackId < GP_DIVERSITY_NR_OF_STACKS)
            {
                if(gpMacDispatcher_ClientLockedStack[input.MacDispatcher_cbAssociateConfirm.data.stackId])
                {
                    break;
                }
            }
/* </CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbAssociateConfirm */

            MacDispatcher_cbAssociateConfirm(
                  input.MacDispatcher_cbAssociateConfirm.data.assocShortAddress
                , input.MacDispatcher_cbAssociateConfirm.data.status
                , input.MacDispatcher_cbAssociateConfirm.data.txTime
                , input.MacDispatcher_cbAssociateConfirm.data.stackId
               );


            break;
        }
        case MacDispatcher_cbAssociateCommStatusIndication_CmdId:
        {
            marshall_result = MacDispatcher_cbAssociateCommStatusIndication_Input_buf2api(&(input.MacDispatcher_cbAssociateCommStatusIndication) , pPayload , &_index);
            if (gpMarshall_AckStatusSuccess != marshall_result)
            {
                ackBuffer[1] = marshall_result;
                break;
            }

/* <CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbAssociateCommStatusIndication */
            if(input.MacDispatcher_cbAssociateCommStatusIndication.data.stackId < GP_DIVERSITY_NR_OF_STACKS)
            {
                if(gpMacDispatcher_ClientLockedStack[input.MacDispatcher_cbAssociateCommStatusIndication.data.stackId])
                {
                    break;
                }
            }
/* </CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbAssociateCommStatusIndication */

            MacDispatcher_cbAssociateCommStatusIndication(
                  input.MacDispatcher_cbAssociateCommStatusIndication.data.pSrcAddrInfo
                , input.MacDispatcher_cbAssociateCommStatusIndication.data.pDstAddrInfo
                , input.MacDispatcher_cbAssociateCommStatusIndication.data.status
                , input.MacDispatcher_cbAssociateCommStatusIndication.data.txTime
                , input.MacDispatcher_cbAssociateCommStatusIndication.data.stackId
               );


            break;
        }
        case MacDispatcher_cbPollConfirm_CmdId:
        {
            marshall_result = MacDispatcher_cbPollConfirm_Input_buf2api(&(input.MacDispatcher_cbPollConfirm) , pPayload , &_index);
            if (gpMarshall_AckStatusSuccess != marshall_result)
            {
                ackBuffer[1] = marshall_result;
                break;
            }

/* <CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbPollConfirm */
            if(input.MacDispatcher_cbPollConfirm.data.stackId < GP_DIVERSITY_NR_OF_STACKS)
            {
                if(gpMacDispatcher_ClientLockedStack[input.MacDispatcher_cbPollConfirm.data.stackId])
                {
                    break;
                }
            }
/* </CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbPollConfirm */

            MacDispatcher_cbPollConfirm(
                  input.MacDispatcher_cbPollConfirm.data.status
                , input.MacDispatcher_cbPollConfirm.data.coordAddrInfo
                , input.MacDispatcher_cbPollConfirm.data.txTime
                , input.MacDispatcher_cbPollConfirm.data.stackId
               );


            break;
        }
        case MacDispatcher_cbPollIndication_CmdId:
        {
            marshall_result = MacDispatcher_cbPollIndication_Input_buf2api(&(input.MacDispatcher_cbPollIndication) , pPayload , &_index);
            if (gpMarshall_AckStatusSuccess != marshall_result)
            {
                ackBuffer[1] = marshall_result;
                break;
            }

/* <CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbPollIndication */
            if(input.MacDispatcher_cbPollIndication.data.stackId < GP_DIVERSITY_NR_OF_STACKS)
            {
                if(gpMacDispatcher_ClientLockedStack[input.MacDispatcher_cbPollIndication.data.stackId])
                {
                    break;
                }
            }
/* </CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbPollIndication */

            MacDispatcher_cbPollIndication(
                  input.MacDispatcher_cbPollIndication.data.addressInfo
                , input.MacDispatcher_cbPollIndication.data.rxTime
                , input.MacDispatcher_cbPollIndication.data.stackId
               );


            break;
        }
        case MacDispatcher_cbPurgeConfirm_CmdId:
        {
            marshall_result = MacDispatcher_cbPurgeConfirm_Input_buf2api(&(input.MacDispatcher_cbPurgeConfirm) , pPayload , &_index);
            if (gpMarshall_AckStatusSuccess != marshall_result)
            {
                ackBuffer[1] = marshall_result;
                break;
            }

/* <CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbPurgeConfirm */
            if(input.MacDispatcher_cbPurgeConfirm.data.stackId < GP_DIVERSITY_NR_OF_STACKS)
            {
                if(gpMacDispatcher_ClientLockedStack[input.MacDispatcher_cbPurgeConfirm.data.stackId])
                {
                    break;
                }
            }
/* </CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbPurgeConfirm */

            MacDispatcher_cbPurgeConfirm(
                  input.MacDispatcher_cbPurgeConfirm.data.status
                , input.MacDispatcher_cbPurgeConfirm.data.pdHandle
                , input.MacDispatcher_cbPurgeConfirm.data.stackId
               );


            break;
        }
        case MacDispatcher_cbBeaconNotifyIndication_CmdId:
        {
            marshall_result = MacDispatcher_cbBeaconNotifyIndication_Input_buf2api(&(input.MacDispatcher_cbBeaconNotifyIndication) , pPayload , &_index);
            if (gpMarshall_AckStatusSuccess != marshall_result)
            {
                ackBuffer[1] = marshall_result;
                break;
            }

/* <CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbBeaconNotifyIndication */
            if(input.MacDispatcher_cbBeaconNotifyIndication.data.stackId < GP_DIVERSITY_NR_OF_STACKS)
            {
                if(gpMacDispatcher_ClientLockedStack[input.MacDispatcher_cbBeaconNotifyIndication.data.stackId])
                {
                    break;
                }
            }
/* </CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbBeaconNotifyIndication */

            MacDispatcher_cbBeaconNotifyIndication(
                  input.MacDispatcher_cbBeaconNotifyIndication.data.bsn
                , input.MacDispatcher_cbBeaconNotifyIndication.data.pPanDescriptor
                , input.MacDispatcher_cbBeaconNotifyIndication.data.beaconPayloadLength
                , input.MacDispatcher_cbBeaconNotifyIndication.data.pBeaconPayload
                , input.MacDispatcher_cbBeaconNotifyIndication.data.stackId
               );


            break;
        }
        case MacDispatcher_cbOrphanIndication_CmdId:
        {
            marshall_result = MacDispatcher_cbOrphanIndication_Input_buf2api(&(input.MacDispatcher_cbOrphanIndication) , pPayload , &_index);
            if (gpMarshall_AckStatusSuccess != marshall_result)
            {
                ackBuffer[1] = marshall_result;
                break;
            }

/* <CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbOrphanIndication */
            if(input.MacDispatcher_cbOrphanIndication.data.stackId < GP_DIVERSITY_NR_OF_STACKS)
            {
                if(gpMacDispatcher_ClientLockedStack[input.MacDispatcher_cbOrphanIndication.data.stackId])
                {
                    break;
                }
            }
/* </CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbOrphanIndication */

            MacDispatcher_cbOrphanIndication(
                  input.MacDispatcher_cbOrphanIndication.data.pOrphanAddress
                , input.MacDispatcher_cbOrphanIndication.data.rxTime
                , input.MacDispatcher_cbOrphanIndication.data.stackId
               );


            break;
        }
        case MacDispatcher_cbOrphanCommStatusIndication_CmdId:
        {
            marshall_result = MacDispatcher_cbOrphanCommStatusIndication_Input_buf2api(&(input.MacDispatcher_cbOrphanCommStatusIndication) , pPayload , &_index);
            if (gpMarshall_AckStatusSuccess != marshall_result)
            {
                ackBuffer[1] = marshall_result;
                break;
            }

/* <CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbOrphanCommStatusIndication */
            if(input.MacDispatcher_cbOrphanCommStatusIndication.data.stackId < GP_DIVERSITY_NR_OF_STACKS)
            {
                if(gpMacDispatcher_ClientLockedStack[input.MacDispatcher_cbOrphanCommStatusIndication.data.stackId])
                {
                    break;
                }
            }
/* </CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbOrphanCommStatusIndication */

            MacDispatcher_cbOrphanCommStatusIndication(
                  input.MacDispatcher_cbOrphanCommStatusIndication.data.pSrcAddrInfo
                , input.MacDispatcher_cbOrphanCommStatusIndication.data.pDstAddrInfo
                , input.MacDispatcher_cbOrphanCommStatusIndication.data.status
                , input.MacDispatcher_cbOrphanCommStatusIndication.data.txTime
                , input.MacDispatcher_cbOrphanCommStatusIndication.data.stackId
               );


            break;
        }
        case MacDispatcher_cbSecurityFailureCommStatusIndication_CmdId:
        {
            marshall_result = MacDispatcher_cbSecurityFailureCommStatusIndication_Input_buf2api(&(input.MacDispatcher_cbSecurityFailureCommStatusIndication) , pPayload , &_index);
            if (gpMarshall_AckStatusSuccess != marshall_result)
            {
                ackBuffer[1] = marshall_result;
                break;
            }

/* <CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbSecurityFailureCommStatusIndication */
            if(input.MacDispatcher_cbSecurityFailureCommStatusIndication.data.stackId < GP_DIVERSITY_NR_OF_STACKS)
            {
                if(gpMacDispatcher_ClientLockedStack[input.MacDispatcher_cbSecurityFailureCommStatusIndication.data.stackId])
                {
                    break;
                }
            }
/* </CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbSecurityFailureCommStatusIndication */

            MacDispatcher_cbSecurityFailureCommStatusIndication(
                  input.MacDispatcher_cbSecurityFailureCommStatusIndication.data.pSrcAddrInfo
                , input.MacDispatcher_cbSecurityFailureCommStatusIndication.data.pDstAddrInfo
                , input.MacDispatcher_cbSecurityFailureCommStatusIndication.data.status
                , input.MacDispatcher_cbSecurityFailureCommStatusIndication.data.txTime
                , input.MacDispatcher_cbSecurityFailureCommStatusIndication.data.stackId
               );


            break;
        }
        case MacDispatcher_cbDriverResetIndication_CmdId:
        {
            marshall_result = MacDispatcher_cbDriverResetIndication_Input_buf2api(&(input.MacDispatcher_cbDriverResetIndication) , pPayload , &_index);
            if (gpMarshall_AckStatusSuccess != marshall_result)
            {
                ackBuffer[1] = marshall_result;
                break;
            }

/* <CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbDriverResetIndication */
            if(input.MacDispatcher_cbDriverResetIndication.data.stackId < GP_DIVERSITY_NR_OF_STACKS)
            {
                if(input.MacDispatcher_cbDriverResetIndication.data.status == 0xFF) //indication was triggered in the end of a reset call to inform reset has finished
                {
                    //Free up any callbacks to client - reset has completed
                    if(gpMacDispatcher_ClientLockedStack[input.MacDispatcher_cbDriverResetIndication.data.stackId] > 0)
                    {
                        gpMacDispatcher_ClientLockedStack[input.MacDispatcher_cbDriverResetIndication.data.stackId]--;
                    }
                    break;
                }
            }
/* </CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbDriverResetIndication */

            MacDispatcher_cbDriverResetIndication(
                  input.MacDispatcher_cbDriverResetIndication.data.status
                , input.MacDispatcher_cbDriverResetIndication.data.stackId
               );


            break;
        }
        case MacDispatcher_cbPollNotify_CmdId:
        {
            marshall_result = MacDispatcher_cbPollNotify_Input_buf2api(&(input.MacDispatcher_cbPollNotify) , pPayload , &_index);
            if (gpMarshall_AckStatusSuccess != marshall_result)
            {
                ackBuffer[1] = marshall_result;
                break;
            }

/* <CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbPollNotify */
            if(input.MacDispatcher_cbPollNotify.data.stackId < GP_DIVERSITY_NR_OF_STACKS)
            {
                if(gpMacDispatcher_ClientLockedStack[input.MacDispatcher_cbPollNotify.data.stackId])
                {
                    break;
                }
            }
/* </CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbPollNotify */

            MacDispatcher_cbPollNotify(
                  input.MacDispatcher_cbPollNotify.data.addressInfo
                , input.MacDispatcher_cbPollNotify.data.rxTime
                , input.MacDispatcher_cbPollNotify.data.pdHandle
                , input.MacDispatcher_cbPollNotify.data.fromNeighbour
                , input.MacDispatcher_cbPollNotify.data.stackId
               );


            break;
        }
        case MacDispatcher_cbSecurityFrameCounterIndication_CmdId:
        {
            marshall_result = MacDispatcher_cbSecurityFrameCounterIndication_Input_buf2api(&(input.MacDispatcher_cbSecurityFrameCounterIndication) , pPayload , &_index);
            if (gpMarshall_AckStatusSuccess != marshall_result)
            {
                ackBuffer[1] = marshall_result;
                break;
            }

/* <CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbSecurityFrameCounterIndication */
            if(input.MacDispatcher_cbSecurityFrameCounterIndication.data.stackId < GP_DIVERSITY_NR_OF_STACKS)
            {
                if(gpMacDispatcher_ClientLockedStack[input.MacDispatcher_cbSecurityFrameCounterIndication.data.stackId])
                {
                    break;
                }
            }
/* </CodeGenerator Placeholder> ResetCheck_MacDispatcher_cbSecurityFrameCounterIndication */

            MacDispatcher_cbSecurityFrameCounterIndication(
                  input.MacDispatcher_cbSecurityFrameCounterIndication.data.frameCounter
                , input.MacDispatcher_cbSecurityFrameCounterIndication.data.stackId
               );


            break;
        }
        case gpMacDispatcher_Acknowledge_CmdId:
        {
            GP_ASSERT_SYSTEM(length <= sizeof(gpMacDispatcher_ackBuffer));
            MEMCPY(gpMacDispatcher_ackBuffer, pPayload, length);
            gpMacDispatcher_reqAcked = true;
            return;
        }
        default:
        {
            GP_ASSERT_DEV_INT(false);
            break;
        }
    }
#undef commandId
    if(0 < ackBytes)
    {
        DATA_REQUEST(ackBytes, ackBuffer, communicationId);
    }
}
/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/


#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)
void gpMacDispatcher_SetDefaultApiVersion(gpVersion_ModuleVersionInfo_t* moduleVersionInfo)
{
    MacDispatcher_clientApiVersionSelected = true;
    //TBD
}
#endif //defined(GP_VERSION_DIVERSITY_GPCOM_CLIENT) && !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)


void gpMacDispatcher_DeInit(void)
{
    gpCom_DeRegisterModule(GP_MODULE_ID);
}

void gpMacDispatcher_Init(void)
{
/* <CodeGenerator Placeholder> Init */
    MacDispatcher_InitStackMapping();

    {
    UInt8 i;
    for(i=0; i < GP_DIVERSITY_NR_OF_STACKS; i++)
    {
        gpMacDispatcher_ClientLockedStack[i] = 0;
    }
    }
/* </CodeGenerator Placeholder> Init */

    gpMacDispatcher_InitMarshalling();

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)
    gpVersion_ReleaseInfo_t versions[1] = {{2,7,0,0}};
    MacDispatcher_clientApiVersionSelected = false;
    gpVersion_RegisterModule(GP_MODULE_ID, versions,1,gpMacDispatcher_SetDefaultApiVersion);
#endif //defined(GP_VERSION_DIVERSITY_GPCOM_CLIENT) && !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)
    REGISTER_MODULE(gpMacDispatcher_HandleIndicationClient);
}

/*****************************************************************************
 *                    gpMacDispatcher Require Functions
 *****************************************************************************/

gpMacDispatcher_StackId_t gpMacDispatcher_RegisterNetworkStack(gpMacDispatcher_StringIdentifier_t* stringIdentifier)
{
    UInt16 _index = 1;
    gpMacDispatcher_StackId_t stackId;
    UInt8 dataBuf[1 + 1 + (5)];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_RegisterNetworkStack_CmdId;

    gpMacDispatcher_RegisterNetworkStack_Input_par2buf(dataBuf
        , stringIdentifier
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_RegisterNetworkStack_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_RegisterNetworkStack_Output_buf2par(
          &stackId
        , stringIdentifier
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return stackId;
}

gpMacCore_Result_t gpMacDispatcher_UnRegisterNetworkStack(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    gpMacCore_Result_t result;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_UnRegisterNetworkStack_CmdId;

    gpMacDispatcher_UnRegisterNetworkStack_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_UnRegisterNetworkStack_CmdId == gpMacDispatcher_ackBuffer[2]);

/* <CodeGenerator Placeholder> AdditionalBehavior_gpMacDispatcher_UnRegisterNetworkStack */
    MacDispatcher_UnRegisterCallbacks(stackId);
    gpMacDispatcher_ClientLockedStack[stackId] = 0;
/* </CodeGenerator Placeholder> AdditionalBehavior_gpMacDispatcher_UnRegisterNetworkStack */

    _index = 3;
    gpMacDispatcher_UnRegisterNetworkStack_Output_buf2par(
          &result
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return result;
}

Bool gpMacDispatcher_LockClaim(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    Bool result;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_LockClaim_CmdId;

    gpMacDispatcher_LockClaim_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_LockClaim_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_LockClaim_Output_buf2par(
          &result
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return result;
}

void gpMacDispatcher_LockRelease(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_LockRelease_CmdId;

    gpMacDispatcher_LockRelease_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_LockRelease_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

Bool gpMacDispatcher_LockedByThisStack(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    Bool locked;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_LockedByThisStack_CmdId;

    gpMacDispatcher_LockedByThisStack_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_LockedByThisStack_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_LockedByThisStack_Output_buf2par(
          &locked
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return locked;
}

Bool gpMacDispatcher_Locked(void)
{
    UInt16 _index = 1;
    Bool locked;
    UInt8 dataBuf[1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_Locked_CmdId;

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_Locked_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_Locked_Output_buf2par(
          &locked
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return locked;
}

gpMacDispatcher_Result_t gpMacDispatcher_Reset(Bool setDefaultPib, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    gpMacDispatcher_Result_t result;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_Reset_CmdId;

    gpMacDispatcher_Reset_Input_par2buf(dataBuf
        , setDefaultPib
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_Reset_CmdId == gpMacDispatcher_ackBuffer[2]);

/* <CodeGenerator Placeholder> AdditionalBehavior_gpMacDispatcher_Reset */
    //Lock any callbacks for this stack until reset indication is received
    if(stackId < GP_DIVERSITY_NR_OF_STACKS)
    {
        gpMacDispatcher_ClientLockedStack[stackId]++;
    }
/* </CodeGenerator Placeholder> AdditionalBehavior_gpMacDispatcher_Reset */

    _index = 3;
    gpMacDispatcher_Reset_Output_buf2par(
          &result
        , setDefaultPib
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return result;
}

void gpMacDispatcher_DataRequest(gpMacCore_AddressMode_t srcAddrMode, gpMacCore_AddressInfo_t* pDstAddressInfo, UInt8 txOptions, gpMacCore_Security_t* pSecOptions, gpMacCore_MultiChannelOptions_t multiChannelOptions, gpPd_Loh_t pdLoh, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1 + (max(2*1,8*1) + 2*1 + 1) + 1 + 1 + (1 + 1 + max(4,8) + 1) + (3) + (2*1 + 2*0 + 128 + 1) + 128 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_DataRequest_CmdId;

    gpMacDispatcher_DataRequest_Input_par2buf(dataBuf
        , srcAddrMode
        , pDstAddressInfo
        , txOptions
        , pSecOptions
        , multiChannelOptions
        , pdLoh
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMacDispatcher_DataRequest_CmdId == gpMacDispatcher_ackBuffer[2]);
/* <CodeGenerator Placeholder> gpMacDispatcher_DataRequest_StatusCheck */
    /* Manual added begin:*/
    if(gpMarshall_AckStatusSuccess != gpMacDispatcher_ackBuffer[1])
    {
        MacDispatcher_cbDataConfirm(gpMacCore_ResultTransactionOverflow, pdLoh.handle, stackId);
    }
    /* Manual added end*/
/* </CodeGenerator Placeholder> gpMacDispatcher_DataRequest_StatusCheck */


#undef commandId
}

void gpMacDispatcher_ScanRequest(gpMacCore_ScanType_t scanType, UInt32 scanChannels, UInt8 scanDuration, UInt8 resultListSize, UInt8* pResultList, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 4*1 + 1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_ScanRequest_CmdId;

    gpMacDispatcher_ScanRequest_Input_par2buf(dataBuf
        , scanType
        , scanChannels
        , scanDuration
        , resultListSize
        , pResultList
        , stackId
        , &_index);
/* <CodeGenerator Placeholder> SpecialOutputParameterHandling_gpMacDispatcher_ScanRequest_pResultList */
    if ((pResultList!= NULL) && (gpMacDispatcher_pResultList != NULL))
    {
        MacDispatcher_cbScanConfirm(gpMacCore_ResultTransactionOverflow, scanType, scanChannels, 0, pResultList,stackId);
        return;
    }
    else
    {
        //Do not assign result list on a Stop request
        if (scanType != gpMacCore_ScanTypeStop)
        {
            gpMacDispatcher_pResultList = pResultList;
        }
    }
/* </CodeGenerator Placeholder> SpecialOutputParameterHandling_gpMacDispatcher_ScanRequest_pResultList */

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_ScanRequest_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

void gpMacDispatcher_AssociateRequest(UInt8 logicalChannel, gpMacCore_AddressInfo_t* coordAddrInfo, UInt8 capabilityInformation, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1 + (max(2*1,8*1) + 2*1 + 1) + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_AssociateRequest_CmdId;

    gpMacDispatcher_AssociateRequest_Input_par2buf(dataBuf
        , logicalChannel
        , coordAddrInfo
        , capabilityInformation
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_AssociateRequest_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

void gpMacDispatcher_AssociateResponse(MACAddress_t* pDeviceAddress, UInt16 associateShortAddress, gpMacCore_Result_t status, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 8*1 + 2*1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_AssociateResponse_CmdId;

    gpMacDispatcher_AssociateResponse_Input_par2buf(dataBuf
        , pDeviceAddress
        , associateShortAddress
        , status
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_AssociateResponse_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

void gpMacDispatcher_PollRequest(gpMacCore_AddressInfo_t* coordAddrInfo, gpMacCore_Security_t* pSecOptions, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + (max(2*1,8*1) + 2*1 + 1) + 1 + (1 + 1 + max(4,8) + 1) + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_PollRequest_CmdId;

    gpMacDispatcher_PollRequest_Input_par2buf(dataBuf
        , coordAddrInfo
        , pSecOptions
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_PollRequest_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

void gpMacDispatcher_PurgeRequest(gpPd_Handle_t pdHandle, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_PurgeRequest_CmdId;

    gpMacDispatcher_PurgeRequest_Input_par2buf(dataBuf
        , pdHandle
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_PurgeRequest_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

gpMacCore_Result_t gpMacDispatcher_Start(gpMacCore_PanId_t panId, UInt8 logicalChannel, Bool panCoordinator, UInt8 stackId)
{
    UInt16 _index = 1;
    gpMacCore_Result_t returnValue;
    UInt8 dataBuf[1 + 2*1 + 1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_Start_CmdId;

    gpMacDispatcher_Start_Input_par2buf(dataBuf
        , panId
        , logicalChannel
        , panCoordinator
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_Start_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_Start_Output_buf2par(
          &returnValue
        , panId
        , logicalChannel
        , panCoordinator
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return returnValue;
}

void gpMacDispatcher_OrphanResponse(MACAddress_t* pOrphanAddress, UInt16 shortAddress, Bool associatedMember, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 8*1 + 2*1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_OrphanResponse_CmdId;

    gpMacDispatcher_OrphanResponse_Input_par2buf(dataBuf
        , pOrphanAddress
        , shortAddress
        , associatedMember
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_OrphanResponse_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

void gpMacDispatcher_SetPanId(UInt16 panId, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 2*1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetPanId_CmdId;

    gpMacDispatcher_SetPanId_Input_par2buf(dataBuf
        , panId
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetPanId_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

gpMacCore_PanId_t gpMacDispatcher_GetPanId(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    gpMacCore_PanId_t panId;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetPanId_CmdId;

    gpMacDispatcher_GetPanId_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetPanId_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetPanId_Output_buf2par(
          &panId
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return panId;
}

void gpMacDispatcher_SetShortAddress(UInt16 shortAddress, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 2*1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetShortAddress_CmdId;

    gpMacDispatcher_SetShortAddress_Input_par2buf(dataBuf
        , shortAddress
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetShortAddress_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

UInt16 gpMacDispatcher_GetShortAddress(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt16 address;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetShortAddress_CmdId;

    gpMacDispatcher_GetShortAddress_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetShortAddress_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetShortAddress_Output_buf2par(
          &address
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return address;
}

void gpMacDispatcher_SetExtendedAddress(MACAddress_t* pExtendedAddress, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 8*1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetExtendedAddress_CmdId;

    gpMacDispatcher_SetExtendedAddress_Input_par2buf(dataBuf
        , pExtendedAddress
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetExtendedAddress_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

void gpMacDispatcher_GetExtendedAddress(MACAddress_t* pExtendedAddress, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetExtendedAddress_CmdId;

    gpMacDispatcher_GetExtendedAddress_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetExtendedAddress_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetExtendedAddress_Output_buf2par(
          pExtendedAddress
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
}

void gpMacDispatcher_SetDsn(UInt8 dsn, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetDsn_CmdId;

    gpMacDispatcher_SetDsn_Input_par2buf(dataBuf
        , dsn
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetDsn_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

UInt8 gpMacDispatcher_GetDsn(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dsn;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetDsn_CmdId;

    gpMacDispatcher_GetDsn_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetDsn_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetDsn_Output_buf2par(
          &dsn
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return dsn;
}

void gpMacDispatcher_SetCurrentChannel(UInt8 channel, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetCurrentChannel_CmdId;

    gpMacDispatcher_SetCurrentChannel_Input_par2buf(dataBuf
        , channel
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetCurrentChannel_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

UInt8 gpMacDispatcher_GetCurrentChannel(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 channel;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetCurrentChannel_CmdId;

    gpMacDispatcher_GetCurrentChannel_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetCurrentChannel_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetCurrentChannel_Output_buf2par(
          &channel
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return channel;
}

void gpMacDispatcher_SetBeaconPayload(UInt8* pBeaconPayload, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + GP_MACCORE_MAX_BEACON_PAYLOAD_LENGTH + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetBeaconPayload_CmdId;

    gpMacDispatcher_SetBeaconPayload_Input_par2buf(dataBuf
        , pBeaconPayload
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetBeaconPayload_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

void gpMacDispatcher_GetBeaconPayload(UInt8* pBeaconPayload, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetBeaconPayload_CmdId;

    gpMacDispatcher_GetBeaconPayload_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetBeaconPayload_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetBeaconPayload_Output_buf2par(
          pBeaconPayload
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
}

void gpMacDispatcher_SetBeaconPayloadLength(UInt8 beaconPayloadLength, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetBeaconPayloadLength_CmdId;

    gpMacDispatcher_SetBeaconPayloadLength_Input_par2buf(dataBuf
        , beaconPayloadLength
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetBeaconPayloadLength_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

UInt8 gpMacDispatcher_GetBeaconPayloadLength(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 beaconPayloadLength;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetBeaconPayloadLength_CmdId;

    gpMacDispatcher_GetBeaconPayloadLength_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetBeaconPayloadLength_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetBeaconPayloadLength_Output_buf2par(
          &beaconPayloadLength
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return beaconPayloadLength;
}



void gpMacDispatcher_SetRxOnWhenIdle(Bool rxOnWhenIdle, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetRxOnWhenIdle_CmdId;

    gpMacDispatcher_SetRxOnWhenIdle_Input_par2buf(dataBuf
        , rxOnWhenIdle
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetRxOnWhenIdle_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

Bool gpMacDispatcher_GetRxOnWhenIdle(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    Bool rxOnWhenIdle;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetRxOnWhenIdle_CmdId;

    gpMacDispatcher_GetRxOnWhenIdle_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetRxOnWhenIdle_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetRxOnWhenIdle_Output_buf2par(
          &rxOnWhenIdle
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return rxOnWhenIdle;
}

UInt16 gpMacDispatcher_GetTransactionPersistenceTime(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt16 time;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetTransactionPersistenceTime_CmdId;

    gpMacDispatcher_GetTransactionPersistenceTime_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetTransactionPersistenceTime_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetTransactionPersistenceTime_Output_buf2par(
          &time
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return time;
}

void gpMacDispatcher_SetTransactionPersistenceTime(UInt16 time, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 2*1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetTransactionPersistenceTime_CmdId;

    gpMacDispatcher_SetTransactionPersistenceTime_Input_par2buf(dataBuf
        , time
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetTransactionPersistenceTime_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

void gpMacDispatcher_SetBeaconStarted(Bool beaconStarted, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetBeaconStarted_CmdId;

    gpMacDispatcher_SetBeaconStarted_Input_par2buf(dataBuf
        , beaconStarted
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetBeaconStarted_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

Bool gpMacDispatcher_GetBeaconStarted(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    Bool beaconStarted;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetBeaconStarted_CmdId;

    gpMacDispatcher_GetBeaconStarted_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetBeaconStarted_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetBeaconStarted_Output_buf2par(
          &beaconStarted
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return beaconStarted;
}

void gpMacDispatcher_SetCoordShortAddress(UInt16 coordShortAddress, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 2*1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetCoordShortAddress_CmdId;

    gpMacDispatcher_SetCoordShortAddress_Input_par2buf(dataBuf
        , coordShortAddress
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetCoordShortAddress_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

UInt16 gpMacDispatcher_GetCoordShortAddress(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt16 coordShortAddress;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetCoordShortAddress_CmdId;

    gpMacDispatcher_GetCoordShortAddress_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetCoordShortAddress_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetCoordShortAddress_Output_buf2par(
          &coordShortAddress
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return coordShortAddress;
}

void gpMacDispatcher_SetCoordExtendedAddress(MACAddress_t* pCoordExtendedAddress, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 8*1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetCoordExtendedAddress_CmdId;

    gpMacDispatcher_SetCoordExtendedAddress_Input_par2buf(dataBuf
        , pCoordExtendedAddress
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetCoordExtendedAddress_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

void gpMacDispatcher_GetCoordExtendedAddress(MACAddress_t* pCoordExtendedAddress, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetCoordExtendedAddress_CmdId;

    gpMacDispatcher_GetCoordExtendedAddress_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetCoordExtendedAddress_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetCoordExtendedAddress_Output_buf2par(
          pCoordExtendedAddress
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
}

void gpMacDispatcher_SetPromiscuousMode(UInt8 promiscuousMode, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetPromiscuousMode_CmdId;

    gpMacDispatcher_SetPromiscuousMode_Input_par2buf(dataBuf
        , promiscuousMode
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetPromiscuousMode_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

Bool gpMacDispatcher_GetPromiscuousMode(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    Bool promiscuousMode;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetPromiscuousMode_CmdId;

    gpMacDispatcher_GetPromiscuousMode_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetPromiscuousMode_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetPromiscuousMode_Output_buf2par(
          &promiscuousMode
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return promiscuousMode;
}

void gpMacDispatcher_SetAssociationPermit(Bool associationPermit, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetAssociationPermit_CmdId;

    gpMacDispatcher_SetAssociationPermit_Input_par2buf(dataBuf
        , associationPermit
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetAssociationPermit_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

Bool gpMacDispatcher_GetAssociationPermit(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    Bool associationPermit;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetAssociationPermit_CmdId;

    gpMacDispatcher_GetAssociationPermit_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetAssociationPermit_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetAssociationPermit_Output_buf2par(
          &associationPermit
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return associationPermit;
}

void gpMacDispatcher_SetSecurityEnabled(Bool securityEnabled, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetSecurityEnabled_CmdId;

    gpMacDispatcher_SetSecurityEnabled_Input_par2buf(dataBuf
        , securityEnabled
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetSecurityEnabled_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

Bool gpMacDispatcher_GetSecurityEnabled(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    Bool securityEnabled;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetSecurityEnabled_CmdId;

    gpMacDispatcher_GetSecurityEnabled_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetSecurityEnabled_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetSecurityEnabled_Output_buf2par(
          &securityEnabled
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return securityEnabled;
}

void gpMacDispatcher_SetNumberOfRetries(UInt8 numberOfRetries, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetNumberOfRetries_CmdId;

    gpMacDispatcher_SetNumberOfRetries_Input_par2buf(dataBuf
        , numberOfRetries
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetNumberOfRetries_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

UInt8 gpMacDispatcher_GetNumberOfRetries(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 numberOfRetries;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetNumberOfRetries_CmdId;

    gpMacDispatcher_GetNumberOfRetries_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetNumberOfRetries_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetNumberOfRetries_Output_buf2par(
          &numberOfRetries
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return numberOfRetries;
}

void gpMacDispatcher_SetMaxCsmaBackoffs(UInt8 maxCsmaBackoffs, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetMaxCsmaBackoffs_CmdId;

    gpMacDispatcher_SetMaxCsmaBackoffs_Input_par2buf(dataBuf
        , maxCsmaBackoffs
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetMaxCsmaBackoffs_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

UInt8 gpMacDispatcher_GetMaxCsmaBackoffs(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 maxCsmaBackoffs;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetMaxCsmaBackoffs_CmdId;

    gpMacDispatcher_GetMaxCsmaBackoffs_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetMaxCsmaBackoffs_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetMaxCsmaBackoffs_Output_buf2par(
          &maxCsmaBackoffs
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return maxCsmaBackoffs;
}

void gpMacDispatcher_SetDefaultTransmitPowers(Int8* pDefaultTransmitPowerTable)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 16];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetDefaultTransmitPowers_CmdId;

    gpMacDispatcher_SetDefaultTransmitPowers_Input_par2buf(dataBuf
        , pDefaultTransmitPowerTable
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetDefaultTransmitPowers_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

void gpMacDispatcher_SetTransmitPower(gpMacCore_TxPower_t transmitPower, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetTransmitPower_CmdId;

    gpMacDispatcher_SetTransmitPower_Input_par2buf(dataBuf
        , transmitPower
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetTransmitPower_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

Int8 gpMacDispatcher_GetTransmitPower(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    Int8 transmitPower;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetTransmitPower_CmdId;

    gpMacDispatcher_GetTransmitPower_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetTransmitPower_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetTransmitPower_Output_buf2par(
          &transmitPower
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return transmitPower;
}

void gpMacDispatcher_SetCCAMode(UInt8 cCAMode, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetCCAMode_CmdId;

    gpMacDispatcher_SetCCAMode_Input_par2buf(dataBuf
        , cCAMode
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetCCAMode_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

UInt8 gpMacDispatcher_GetCCAMode(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 cCAMode;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetCCAMode_CmdId;

    gpMacDispatcher_GetCCAMode_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetCCAMode_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetCCAMode_Output_buf2par(
          &cCAMode
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return cCAMode;
}

void gpMacDispatcher_SetPanCoordinator(Bool panCoordinator, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetPanCoordinator_CmdId;

    gpMacDispatcher_SetPanCoordinator_Input_par2buf(dataBuf
        , panCoordinator
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetPanCoordinator_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

Bool gpMacDispatcher_GetPanCoordinator(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    Bool panCoordinator;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetPanCoordinator_CmdId;

    gpMacDispatcher_GetPanCoordinator_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetPanCoordinator_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetPanCoordinator_Output_buf2par(
          &panCoordinator
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return panCoordinator;
}

void gpMacDispatcher_SetMinBE(UInt8 minBE, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetMinBE_CmdId;

    gpMacDispatcher_SetMinBE_Input_par2buf(dataBuf
        , minBE
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetMinBE_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

UInt8 gpMacDispatcher_GetMinBE(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 minBE;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetMinBE_CmdId;

    gpMacDispatcher_GetMinBE_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetMinBE_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetMinBE_Output_buf2par(
          &minBE
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return minBE;
}

void gpMacDispatcher_SetIndicateBeaconNotifications(Bool enable, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetIndicateBeaconNotifications_CmdId;

    gpMacDispatcher_SetIndicateBeaconNotifications_Input_par2buf(dataBuf
        , enable
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetIndicateBeaconNotifications_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

Bool gpMacDispatcher_GetIndicateBeaconNotifications(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    Bool enable;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetIndicateBeaconNotifications_CmdId;

    gpMacDispatcher_GetIndicateBeaconNotifications_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetIndicateBeaconNotifications_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetIndicateBeaconNotifications_Output_buf2par(
          &enable
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return enable;
}

void gpMacDispatcher_SetMacVersion(gpMacCore_MacVersion_t macVersion, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetMacVersion_CmdId;

    gpMacDispatcher_SetMacVersion_Input_par2buf(dataBuf
        , macVersion
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetMacVersion_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

gpMacCore_MacVersion_t gpMacDispatcher_GetMacVersion(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    gpMacCore_MacVersion_t macVersion;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetMacVersion_CmdId;

    gpMacDispatcher_GetMacVersion_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetMacVersion_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetMacVersion_Output_buf2par(
          &macVersion
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return macVersion;
}

void gpMacDispatcher_SetForwardPollIndications(Bool enable, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetForwardPollIndications_CmdId;

    gpMacDispatcher_SetForwardPollIndications_Input_par2buf(dataBuf
        , enable
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetForwardPollIndications_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

Bool gpMacDispatcher_GetForwardPollIndications(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    Bool enable;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetForwardPollIndications_CmdId;

    gpMacDispatcher_GetForwardPollIndications_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetForwardPollIndications_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetForwardPollIndications_Output_buf2par(
          &enable
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return enable;
}

gpMacCore_Result_t gpMacDispatcher_DataPending_QueueAdd(gpMacCore_AddressInfo_t* pAddrInfo, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    gpMacCore_Result_t result;
    UInt8 dataBuf[1 + 1 + (max(2*1,8*1) + 2*1 + 1) + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_DataPending_QueueAdd_CmdId;

    gpMacDispatcher_DataPending_QueueAdd_Input_par2buf(dataBuf
        , pAddrInfo
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_DataPending_QueueAdd_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_DataPending_QueueAdd_Output_buf2par(
          &result
        , pAddrInfo
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return result;
}

gpMacCore_Result_t gpMacDispatcher_DataPending_QueueRemove(gpMacCore_AddressInfo_t* pAddrInfo, gpMacCore_StackId_t stackId)
{
    UInt16 _index = 1;
    gpMacCore_Result_t result;
    UInt8 dataBuf[1 + 1 + (max(2*1,8*1) + 2*1 + 1) + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_DataPending_QueueRemove_CmdId;

    gpMacDispatcher_DataPending_QueueRemove_Input_par2buf(dataBuf
        , pAddrInfo
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_DataPending_QueueRemove_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_DataPending_QueueRemove_Output_buf2par(
          &result
        , pAddrInfo
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return result;
}

void gpMacDispatcher_SetMinInterferenceLevels(Int8* pInterferenceLevels)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetMinInterferenceLevels_CmdId;

    gpMacDispatcher_SetMinInterferenceLevels_Input_par2buf(dataBuf
        , pInterferenceLevels
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetMinInterferenceLevels_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

void gpMacDispatcher_SetMaxBE(UInt8 maxBE, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetMaxBE_CmdId;

    gpMacDispatcher_SetMaxBE_Input_par2buf(dataBuf
        , maxBE
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetMaxBE_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

UInt8 gpMacDispatcher_GetMaxBE(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 maxBE;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetMaxBE_CmdId;

    gpMacDispatcher_GetMaxBE_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetMaxBE_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetMaxBE_Output_buf2par(
          &maxBE
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return maxBE;
}

gpMacCore_Result_t gpMacDispatcher_SetDeviceDescriptor(gpMacCore_DeviceDescriptor_t* pDeviceDescriptor, gpMacCore_Index_t index, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    gpMacCore_Result_t result;
    UInt8 dataBuf[1 + 1 + (2*1 + 2*1 + 8*1 + 4*1 + 1) + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetDeviceDescriptor_CmdId;

    gpMacDispatcher_SetDeviceDescriptor_Input_par2buf(dataBuf
        , pDeviceDescriptor
        , index
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetDeviceDescriptor_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_SetDeviceDescriptor_Output_buf2par(
          &result
        , pDeviceDescriptor
        , index
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return result;
}

gpMacCore_Result_t gpMacDispatcher_GetDeviceDescriptor(gpMacCore_DeviceDescriptor_t* pDeviceDescriptor, gpMacCore_Index_t index, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    gpMacCore_Result_t result;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetDeviceDescriptor_CmdId;

    gpMacDispatcher_GetDeviceDescriptor_Input_par2buf(dataBuf
        , index
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetDeviceDescriptor_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetDeviceDescriptor_Output_buf2par(
          &result
        , pDeviceDescriptor
        , index
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return result;
}

void gpMacDispatcher_SetDeviceTableEntries(gpMacCore_DeviceTablesEntries_t deviceTableEntries, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetDeviceTableEntries_CmdId;

    gpMacDispatcher_SetDeviceTableEntries_Input_par2buf(dataBuf
        , deviceTableEntries
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetDeviceTableEntries_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

gpMacCore_DeviceTablesEntries_t gpMacDispatcher_GetDeviceTableEntries(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    gpMacCore_DeviceTablesEntries_t deviceTableEntries;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetDeviceTableEntries_CmdId;

    gpMacDispatcher_GetDeviceTableEntries_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetDeviceTableEntries_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetDeviceTableEntries_Output_buf2par(
          &deviceTableEntries
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return deviceTableEntries;
}

gpMacCore_Result_t gpMacDispatcher_SetKeyDescriptor(gpMacCore_KeyDescriptor_t* pKeyDescriptor, gpMacCore_Index_t index, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    gpMacCore_Result_t result;
    UInt8 dataBuf[1 + 1 + (GP_MACCORE_NUMBER_OF_KEY_ID_LOOKUP_DESCRIPTORS*(9 + 1) + 1 + GP_MACCORE_NUMBER_OF_KEY_DEVICE_DESCRIPTORS*((2*1 + 2*1 + 8*1 + 4*1 + 1) + 1 + 1) + 1 + GP_MACCORE_NUMBER_OF_KEY_USAGE_DESCRIPTORS*(1 + 1) + 1 + 16) + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetKeyDescriptor_CmdId;

    gpMacDispatcher_SetKeyDescriptor_Input_par2buf(dataBuf
        , pKeyDescriptor
        , index
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetKeyDescriptor_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_SetKeyDescriptor_Output_buf2par(
          &result
        , pKeyDescriptor
        , index
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return result;
}

gpMacCore_Result_t gpMacDispatcher_GetKeyDescriptor(gpMacCore_KeyDescriptor_t* pKeyDescriptor, gpMacCore_Index_t index, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    gpMacCore_Result_t result;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetKeyDescriptor_CmdId;

    gpMacDispatcher_GetKeyDescriptor_Input_par2buf(dataBuf
        , index
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetKeyDescriptor_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetKeyDescriptor_Output_buf2par(
          &result
        , pKeyDescriptor
        , index
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return result;
}

void gpMacDispatcher_SetKeyTableEntries(gpMacCore_KeyTablesEntries_t keyTableEntries, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetKeyTableEntries_CmdId;

    gpMacDispatcher_SetKeyTableEntries_Input_par2buf(dataBuf
        , keyTableEntries
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetKeyTableEntries_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

gpMacCore_Result_t gpMacDispatcher_SetSecurityLevelDescriptor(gpMacCore_SecurityLevelDescriptor_t* pSecurityLevelDescriptor, gpMacCore_Index_t index, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    gpMacCore_Result_t result;
    UInt8 dataBuf[1 + 1 + (1 + 1 + 1 + 1) + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetSecurityLevelDescriptor_CmdId;

    gpMacDispatcher_SetSecurityLevelDescriptor_Input_par2buf(dataBuf
        , pSecurityLevelDescriptor
        , index
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetSecurityLevelDescriptor_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_SetSecurityLevelDescriptor_Output_buf2par(
          &result
        , pSecurityLevelDescriptor
        , index
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return result;
}

gpMacCore_Result_t gpMacDispatcher_GetSecurityLevelDescriptor(gpMacCore_SecurityLevelDescriptor_t* pSecurityLevelDescriptor, gpMacCore_Index_t index, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    gpMacCore_Result_t result;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetSecurityLevelDescriptor_CmdId;

    gpMacDispatcher_GetSecurityLevelDescriptor_Input_par2buf(dataBuf
        , index
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetSecurityLevelDescriptor_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetSecurityLevelDescriptor_Output_buf2par(
          &result
        , pSecurityLevelDescriptor
        , index
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return result;
}

void gpMacDispatcher_SetSecurityLevelTableEntries(gpMacCore_SecurityLevelTableEntries_t securityLevelTableEntries, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetSecurityLevelTableEntries_CmdId;

    gpMacDispatcher_SetSecurityLevelTableEntries_Input_par2buf(dataBuf
        , securityLevelTableEntries
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetSecurityLevelTableEntries_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

gpMacCore_SecurityLevelTableEntries_t gpMacDispatcher_GetSecurityLevelTableEntries(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    gpMacCore_SecurityLevelTableEntries_t securityLevelTableEntries;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetSecurityLevelTableEntries_CmdId;

    gpMacDispatcher_GetSecurityLevelTableEntries_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetSecurityLevelTableEntries_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetSecurityLevelTableEntries_Output_buf2par(
          &securityLevelTableEntries
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return securityLevelTableEntries;
}

void gpMacDispatcher_SetDefaultKeySource(UInt8* pDefaultKeySource, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 8 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetDefaultKeySource_CmdId;

    gpMacDispatcher_SetDefaultKeySource_Input_par2buf(dataBuf
        , pDefaultKeySource
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetDefaultKeySource_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

void gpMacDispatcher_SetFrameCounter(UInt32 frameCounter, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 4*1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetFrameCounter_CmdId;

    gpMacDispatcher_SetFrameCounter_Input_par2buf(dataBuf
        , frameCounter
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetFrameCounter_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

UInt32 gpMacDispatcher_GetFrameCounter(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt32 frameCounter;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetFrameCounter_CmdId;

    gpMacDispatcher_GetFrameCounter_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetFrameCounter_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetFrameCounter_Output_buf2par(
          &frameCounter
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return frameCounter;
}

void gpMacDispatcher_SetPanCoordShortAddress(UInt16 panCoordShortAddress, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 2*1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetPanCoordShortAddress_CmdId;

    gpMacDispatcher_SetPanCoordShortAddress_Input_par2buf(dataBuf
        , panCoordShortAddress
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetPanCoordShortAddress_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

void gpMacDispatcher_SetPanCoordExtendedAddress(MACAddress_t* pPanCoordExtendedAddress, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 8*1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetPanCoordExtendedAddress_CmdId;

    gpMacDispatcher_SetPanCoordExtendedAddress_Input_par2buf(dataBuf
        , pPanCoordExtendedAddress
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetPanCoordExtendedAddress_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

void gpMacDispatcher_GetPanCoordExtendedAddress(MACAddress_t* pPanCoordExtendedAddress, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetPanCoordExtendedAddress_CmdId;

    gpMacDispatcher_GetPanCoordExtendedAddress_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetPanCoordExtendedAddress_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetPanCoordExtendedAddress_Output_buf2par(
          pPanCoordExtendedAddress
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
}

Bool gpMacDispatcher_AddNeighbour(gpMacCore_AddressInfo_t* pAddrInfo, gpMacCore_StackId_t stackId)
{
    UInt16 _index = 1;
    Bool result;
    UInt8 dataBuf[1 + 1 + (max(2*1,8*1) + 2*1 + 1) + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_AddNeighbour_CmdId;

    gpMacDispatcher_AddNeighbour_Input_par2buf(dataBuf
        , pAddrInfo
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_AddNeighbour_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_AddNeighbour_Output_buf2par(
          &result
        , pAddrInfo
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return result;
}

Bool gpMacDispatcher_RemoveNeighbour(gpMacCore_AddressInfo_t* pAddrInfo, gpMacCore_StackId_t stackId)
{
    UInt16 _index = 1;
    Bool result;
    UInt8 dataBuf[1 + 1 + (max(2*1,8*1) + 2*1 + 1) + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_RemoveNeighbour_CmdId;

    gpMacDispatcher_RemoveNeighbour_Input_par2buf(dataBuf
        , pAddrInfo
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_RemoveNeighbour_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_RemoveNeighbour_Output_buf2par(
          &result
        , pAddrInfo
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return result;
}

gpMacCore_Result_t gpMacDispatcher_SetDataPendingMode(gpMacCore_DataPendingMode_t dataPendingMode, gpMacCore_StackId_t stackId)
{
    UInt16 _index = 1;
    gpMacCore_Result_t result;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetDataPendingMode_CmdId;

    gpMacDispatcher_SetDataPendingMode_Input_par2buf(dataBuf
        , dataPendingMode
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetDataPendingMode_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_SetDataPendingMode_Output_buf2par(
          &result
        , dataPendingMode
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return result;
}


void gpMacDispatcher_SetAddressModeOverrideForBeacons(UInt8 addressMode, gpMacCore_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetAddressModeOverrideForBeacons_CmdId;

    gpMacDispatcher_SetAddressModeOverrideForBeacons_Input_par2buf(dataBuf
        , addressMode
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetAddressModeOverrideForBeacons_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

void gpMacDispatcher_ClearNeighbours(gpMacCore_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_ClearNeighbours_CmdId;

    gpMacDispatcher_ClearNeighbours_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_ClearNeighbours_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

void gpMacDispatcher_SetCsmaMode(UInt8 csmaMode, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetCsmaMode_CmdId;

    gpMacDispatcher_SetCsmaMode_Input_par2buf(dataBuf
        , csmaMode
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetCsmaMode_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

UInt8 gpMacDispatcher_GetCsmaMode(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 csmaMode;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetCsmaMode_CmdId;

    gpMacDispatcher_GetCsmaMode_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetCsmaMode_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetCsmaMode_Output_buf2par(
          &csmaMode
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return csmaMode;
}

gpMacCore_Result_t gpMacDispatcher_DataPending_QueueClear(gpMacCore_StackId_t stackId)
{
    UInt16 _index = 1;
    gpMacCore_Result_t result;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_DataPending_QueueClear_CmdId;

    gpMacDispatcher_DataPending_QueueClear_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_DataPending_QueueClear_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_DataPending_QueueClear_Output_buf2par(
          &result
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return result;
}







void gpMacDispatcher_SetStackInRawMode(Bool rawModeEnabled, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetStackInRawMode_CmdId;

    gpMacDispatcher_SetStackInRawMode_Input_par2buf(dataBuf
        , rawModeEnabled
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetStackInRawMode_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

Bool gpMacDispatcher_GetStackInRawMode(gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    Bool rawModeEnabled;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetStackInRawMode_CmdId;

    gpMacDispatcher_GetStackInRawMode_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetStackInRawMode_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetStackInRawMode_Output_buf2par(
          &rawModeEnabled
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return rawModeEnabled;
}



void gpMacDispatcher_EnableEnhancedFramePending(Bool enableEnhancedFramePending, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_EnableEnhancedFramePending_CmdId;

    gpMacDispatcher_EnableEnhancedFramePending_Input_par2buf(dataBuf
        , enableEnhancedFramePending
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_EnableEnhancedFramePending_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}






gpMacCore_Result_t gpMacDispatcher_ConfigureEnhAckProbing(UInt8 linkMetrics, MACAddress_t* pExtendedAddress, UInt16 shortAddress, gpMacDispatcher_StackId_t stackId)
{
    UInt16 _index = 1;
    gpMacCore_Result_t result;
    UInt8 dataBuf[1 + 1 + 1 + 8*1 + 2*1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_ConfigureEnhAckProbing_CmdId;

    gpMacDispatcher_ConfigureEnhAckProbing_Input_par2buf(dataBuf
        , linkMetrics
        , pExtendedAddress
        , shortAddress
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_ConfigureEnhAckProbing_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_ConfigureEnhAckProbing_Output_buf2par(
          &result
        , linkMetrics
        , pExtendedAddress
        , shortAddress
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return result;
}

void gpMacDispatcher_SetRetransmitOnCcaFail(Bool enable, gpMacCore_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetRetransmitOnCcaFail_CmdId;

    gpMacDispatcher_SetRetransmitOnCcaFail_Input_par2buf(dataBuf
        , enable
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetRetransmitOnCcaFail_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

Bool gpMacDispatcher_GetRetransmitOnCcaFail(gpMacCore_StackId_t stackId)
{
    UInt16 _index = 1;
    Bool enable;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetRetransmitOnCcaFail_CmdId;

    gpMacDispatcher_GetRetransmitOnCcaFail_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetRetransmitOnCcaFail_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetRetransmitOnCcaFail_Output_buf2par(
          &enable
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return enable;
}

void gpMacDispatcher_SetRetransmitRandomBackoff(Bool enable, gpMacCore_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetRetransmitRandomBackoff_CmdId;

    gpMacDispatcher_SetRetransmitRandomBackoff_Input_par2buf(dataBuf
        , enable
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetRetransmitRandomBackoff_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

Bool gpMacDispatcher_GetRetransmitRandomBackoff(gpMacCore_StackId_t stackId)
{
    UInt16 _index = 1;
    Bool enable;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetRetransmitRandomBackoff_CmdId;

    gpMacDispatcher_GetRetransmitRandomBackoff_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetRetransmitRandomBackoff_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetRetransmitRandomBackoff_Output_buf2par(
          &enable
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return enable;
}

void gpMacDispatcher_SetMinBeRetransmit(UInt8 minBERetransmit, gpMacCore_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetMinBeRetransmit_CmdId;

    gpMacDispatcher_SetMinBeRetransmit_Input_par2buf(dataBuf
        , minBERetransmit
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetMinBeRetransmit_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

UInt8 gpMacDispatcher_GetMinBeRetransmit(gpMacCore_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 minBERetransmit;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetMinBeRetransmit_CmdId;

    gpMacDispatcher_GetMinBeRetransmit_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetMinBeRetransmit_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetMinBeRetransmit_Output_buf2par(
          &minBERetransmit
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return minBERetransmit;
}

void gpMacDispatcher_SetMaxBeRetransmit(UInt8 maxBERetransmit, gpMacCore_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_SetMaxBeRetransmit_CmdId;

    gpMacDispatcher_SetMaxBeRetransmit_Input_par2buf(dataBuf
        , maxBERetransmit
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_SetMaxBeRetransmit_CmdId == gpMacDispatcher_ackBuffer[2]);


#undef commandId
}

UInt8 gpMacDispatcher_GetMaxBeRetransmit(gpMacCore_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 maxBERetransmit;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(MacDispatcher_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpMacDispatcher_GetMaxBeRetransmit_CmdId;

    gpMacDispatcher_GetMaxBeRetransmit_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_MACDISPATCHER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpMacDispatcher_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpMacDispatcher_GetMaxBeRetransmit_CmdId == gpMacDispatcher_ackBuffer[2]);

    _index = 3;
    gpMacDispatcher_GetMaxBeRetransmit_Output_buf2par(
          &maxBERetransmit
        , stackId
        , gpMacDispatcher_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpMacDispatcher_ackBuffer));

#undef commandId
    return maxBERetransmit;
}

