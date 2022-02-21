/*
 * Copyright (c) 2015-2016, GreenPeak Technologies
 * Copyright (c) 2019, Qorvo Inc
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
 * $Header: //depot/release/Embedded/Components/Qorvo/802_15_4/v2.10.2.0/comps/gpRxArbiter/src/gen/gpRxArbiter_wrapper_client.c#1 $
 * $Change: 187624 $
 * $DateTime: 2021/12/20 10:58:50 $
 */

/** @file "gpRxArbiter_wrapper_client.c"
 *
 *  RxArbiter
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
#include "gpModule.h"
#include "gpRxArbiter_clientServerCmdId.h"
#include "gpRxArbiter.h"
#include "gpRxArbiter_marshalling.h"
#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)
#include "gpVersion.h"
#endif

/*****************************************************************************
 *                    Typedef Definition
 *****************************************************************************/

/*****************************************************************************
 *                    Static Functions Declaration
 *****************************************************************************/

static void gpRxArbiter_HandleIndicationClient(UInt16 length, UInt8* pPayload, gpCom_CommunicationId_t communicationId);
static void RxArbiter_HandleConnectionClose(gpCom_CommunicationId_t communicationId);

/* <CodeGenerator Placeholder> AdditionalStaticFunctions */
static void gpRxArbiter_cbSetFaModeNotification(gpRxArbiter_StackId_t stackId, gpRxArbiter_FaMode_t mode);
static void gpRxArbiter_cbChannelUpdateNotification(gpRxArbiter_StackId_t stackId, UInt8 channel);
/* </CodeGenerator Placeholder> AdditionalStaticFunctions */
/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/

#define GP_COMPONENT_ID GP_COMPONENT_ID_RXARBITER
#define GP_MODULE_ID GP_COMPONENT_ID


#ifndef GP_RXARBITER_COMM_ID
#define GP_RXARBITER_COMM_ID GP_COM_DEFAULT_COMMUNICATION_ID
#endif

#define REGISTER_MODULE(handle)              GP_COM_REGISTER_MODULE(handle)
#define DATA_REQUEST(len,buf,commId)         GP_COM_DATA_REQUEST(len,buf,commId)
#define DATA_REQUEST_ACKED(len,buf,commId)   gpCom_DataRequestAndWaitForAck(GP_MODULE_ID, len, buf, commId, &gpRxArbiter_reqAcked, GPRXARBITER_GPCOMTIMEOUT_US, gpRxArbiter_Acknowledge_CmdId)

/*****************************************************************************
 *                    Static Data
 *****************************************************************************/

typedef union ackDataNeeded {
    UInt8 dataBuf0[1];
} ackDataNeeded_t;
static UInt8 gpRxArbiter_ackBuffer[1 + 1 + 1 + sizeof(ackDataNeeded_t)];
static Bool gpRxArbiter_reqAcked;
/* <CodeGenerator Placeholder> AdditionalStaticData */
static gpRxArbiter_cbSetFaMode_t      gpRxArbiter_SetFaModeCallback ;
static gpRxArbiter_cbChannelUpdate_t  gpRxArbiter_ChannelUpdateCallback ;
/* </CodeGenerator Placeholder> AdditionalStaticData */

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)
static Bool RxArbiter_clientApiVersionSelected = false;
#endif

/*****************************************************************************
 *                    Static Function Definitions
 *****************************************************************************/
/* <CodeGenerator Placeholder> AdditionalStaticFunctionDefinitions */
void gpRxArbiter_cbSetFaModeNotification(gpRxArbiter_StackId_t stackId, gpRxArbiter_FaMode_t mode)
{
    if (gpRxArbiter_SetFaModeCallback)
    {
        gpRxArbiter_SetFaModeCallback(stackId, mode) ;
    }
}

void gpRxArbiter_cbChannelUpdateNotification(gpRxArbiter_StackId_t stackId, UInt8 channel)
{
    if (gpRxArbiter_ChannelUpdateCallback)
    {
        gpRxArbiter_ChannelUpdateCallback(stackId, channel) ;
    }
}
/* </CodeGenerator Placeholder> AdditionalStaticFunctionDefinitions */

static void RxArbiter_HandleConnectionClose(gpCom_CommunicationId_t communicationId)
{
/* <CodeGenerator Placeholder> ConnectionCloseFunction */
    /* Manual update */
    NOT_USED(communicationId);
/* </CodeGenerator Placeholder> ConnectionCloseFunction */
}

static void gpRxArbiter_HandleIndicationClient(UInt16 length, UInt8* pPayload, gpCom_CommunicationId_t communicationId)
{
#define commandId pPayload[0]
    gpMarshall_AckStatus_t marshall_result;
    UInt16 _index = 1;
    gpRxArbiter_Client_Input_union_t input;
    UInt8 ackBuffer[1 + 1 + 1];
    UInt8 ackBytes = 0; /*No ack's on indication - fill in length when needed - 3+x */

    if(pPayload == NULL)
    {
        RxArbiter_HandleConnectionClose(communicationId);
        return;
    }

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(RxArbiter_clientApiVersionSelected);
#endif

    ackBuffer[0] = gpRxArbiter_Acknowledge_CmdId;
    ackBuffer[1] = gpMarshall_AckStatusSuccess;
    ackBuffer[2] = commandId;

    switch(commandId)
    {

        case gpRxArbiter_cbSetFaModeNotification_CmdId:
        {
            marshall_result = gpRxArbiter_cbSetFaModeNotification_Input_buf2api(&(input.gpRxArbiter_cbSetFaModeNotification) , pPayload , &_index);
            if (gpMarshall_AckStatusSuccess != marshall_result)
            {
                ackBuffer[1] = marshall_result;
                break;
            }

            gpRxArbiter_cbSetFaModeNotification(
                  input.gpRxArbiter_cbSetFaModeNotification.data.stackId
                , input.gpRxArbiter_cbSetFaModeNotification.data.mode
               );


            break;
        }
        case gpRxArbiter_cbChannelUpdateNotification_CmdId:
        {
            marshall_result = gpRxArbiter_cbChannelUpdateNotification_Input_buf2api(&(input.gpRxArbiter_cbChannelUpdateNotification) , pPayload , &_index);
            if (gpMarshall_AckStatusSuccess != marshall_result)
            {
                ackBuffer[1] = marshall_result;
                break;
            }

            gpRxArbiter_cbChannelUpdateNotification(
                  input.gpRxArbiter_cbChannelUpdateNotification.data.stackId
                , input.gpRxArbiter_cbChannelUpdateNotification.data.channel
               );


            break;
        }
        case gpRxArbiter_Acknowledge_CmdId:
        {
            GP_ASSERT_SYSTEM(length <= sizeof(gpRxArbiter_ackBuffer));
            MEMCPY(gpRxArbiter_ackBuffer, pPayload, length);
            gpRxArbiter_reqAcked = true;
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

/* <CodeGenerator Placeholder> AdditionalPublicFunctionDefinitions */
#if (GP_RX_ARBITER_NUMBER_OF_STACKS > 1) // manual
gpRxArbiter_Result_t gpRxArbiter_RegisterSetFaModeCallback(gpRxArbiter_StackId_t stackId, gpRxArbiter_cbSetFaMode_t cb)
{
    /* Manual update */
    NOT_USED(stackId);
    gpRxArbiter_Result_t result ;

    if (cb)
    {
        gpRxArbiter_SetFaModeCallback = cb ;

        result = gpRxArbiter_ResultSuccess ;
    }
    else
    {
        result = gpRxArbiter_ResultInvalidArgument ;
    }

    return result ;
}

gpRxArbiter_Result_t gpRxArbiter_RegisterChannelUpdateCallback(gpRxArbiter_StackId_t stackId, gpRxArbiter_cbChannelUpdate_t cb)
{
    /* Manual update */
    NOT_USED(stackId);
    gpRxArbiter_Result_t result ;

    if (cb)
    {
        gpRxArbiter_ChannelUpdateCallback = cb ;

        result = gpRxArbiter_ResultSuccess ;
    }
    else
    {
        result = gpRxArbiter_ResultInvalidArgument ;
    }

    return result ;
}
#endif // (GP_RX_ARBITER_NUMBER_OF_STACKS > 1) // manual
/* </CodeGenerator Placeholder> AdditionalPublicFunctionDefinitions */

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)
void gpRxArbiter_SetDefaultApiVersion(gpVersion_ModuleVersionInfo_t* moduleVersionInfo)
{
    RxArbiter_clientApiVersionSelected = true;
    //TBD
}
#endif //defined(GP_VERSION_DIVERSITY_GPCOM_CLIENT) && !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)


void gpRxArbiter_DeInit(void)
{
    gpCom_DeRegisterModule(GP_MODULE_ID);
}

void gpRxArbiter_Init(void)
{
#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)
    gpVersion_ReleaseInfo_t versions[1] = {{2,0,0,0}};
    RxArbiter_clientApiVersionSelected = false;
    gpVersion_RegisterModule(GP_MODULE_ID, versions,1,gpRxArbiter_SetDefaultApiVersion);
#endif //defined(GP_VERSION_DIVERSITY_GPCOM_CLIENT) && !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)
    REGISTER_MODULE(gpRxArbiter_HandleIndicationClient);
}

/*****************************************************************************
 *                    gpRxArbiter Require Functions
 *****************************************************************************/

gpRxArbiter_Result_t gpRxArbiter_ResetStack(gpRxArbiter_StackId_t stackId)
{
    UInt16 _index = 1;
    gpRxArbiter_Result_t result;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(RxArbiter_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpRxArbiter_ResetStack_CmdId;

    gpRxArbiter_ResetStack_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_RXARBITER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpRxArbiter_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpRxArbiter_ResetStack_CmdId == gpRxArbiter_ackBuffer[2]);

    _index = 3;
    gpRxArbiter_ResetStack_Output_buf2par(
          &result
        , stackId
        , gpRxArbiter_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpRxArbiter_ackBuffer));

#undef commandId
    return result;
}

gpRxArbiter_Result_t gpRxArbiter_SetStackChannel(UInt8 channel, gpRxArbiter_StackId_t stackId)
{
    UInt16 _index = 1;
    gpRxArbiter_Result_t result;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(RxArbiter_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpRxArbiter_SetStackChannel_CmdId;

    gpRxArbiter_SetStackChannel_Input_par2buf(dataBuf
        , channel
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_RXARBITER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpRxArbiter_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpRxArbiter_SetStackChannel_CmdId == gpRxArbiter_ackBuffer[2]);

    _index = 3;
    gpRxArbiter_SetStackChannel_Output_buf2par(
          &result
        , channel
        , stackId
        , gpRxArbiter_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpRxArbiter_ackBuffer));

#undef commandId
    return result;
}

UInt8 gpRxArbiter_GetStackChannel(gpRxArbiter_StackId_t stackId)
{
    UInt16 _index = 1;
    UInt8 channel;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(RxArbiter_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpRxArbiter_GetStackChannel_CmdId;

    gpRxArbiter_GetStackChannel_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_RXARBITER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpRxArbiter_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpRxArbiter_GetStackChannel_CmdId == gpRxArbiter_ackBuffer[2]);

    _index = 3;
    gpRxArbiter_GetStackChannel_Output_buf2par(
          &channel
        , stackId
        , gpRxArbiter_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpRxArbiter_ackBuffer));

#undef commandId
    return channel;
}

Bool gpRxArbiter_GetCurrentRxOnState(void)
{
    UInt16 _index = 1;
    Bool rxon;
    UInt8 dataBuf[1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(RxArbiter_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpRxArbiter_GetCurrentRxOnState_CmdId;

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_RXARBITER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpRxArbiter_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpRxArbiter_GetCurrentRxOnState_CmdId == gpRxArbiter_ackBuffer[2]);

    _index = 3;
    gpRxArbiter_GetCurrentRxOnState_Output_buf2par(
          &rxon
        , gpRxArbiter_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpRxArbiter_ackBuffer));

#undef commandId
    return rxon;
}

UInt8 gpRxArbiter_GetCurrentRxChannel(void)
{
    UInt16 _index = 1;
    UInt8 currentChannel;
    UInt8 dataBuf[1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(RxArbiter_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpRxArbiter_GetCurrentRxChannel_CmdId;

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_RXARBITER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpRxArbiter_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpRxArbiter_GetCurrentRxChannel_CmdId == gpRxArbiter_ackBuffer[2]);

    _index = 3;
    gpRxArbiter_GetCurrentRxChannel_Output_buf2par(
          &currentChannel
        , gpRxArbiter_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpRxArbiter_ackBuffer));

#undef commandId
    return currentChannel;
}

gpRxArbiter_Result_t gpRxArbiter_SetStackRxOn(Bool enable, gpRxArbiter_StackId_t stackId)
{
    UInt16 _index = 1;
    gpRxArbiter_Result_t result;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(RxArbiter_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpRxArbiter_SetStackRxOn_CmdId;

    gpRxArbiter_SetStackRxOn_Input_par2buf(dataBuf
        , enable
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_RXARBITER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpRxArbiter_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpRxArbiter_SetStackRxOn_CmdId == gpRxArbiter_ackBuffer[2]);

    _index = 3;
    gpRxArbiter_SetStackRxOn_Output_buf2par(
          &result
        , enable
        , stackId
        , gpRxArbiter_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpRxArbiter_ackBuffer));

#undef commandId
    return result;
}

Bool gpRxArbiter_GetStackRxOn(gpRxArbiter_StackId_t stackId)
{
    UInt16 _index = 1;
    Bool enable;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(RxArbiter_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpRxArbiter_GetStackRxOn_CmdId;

    gpRxArbiter_GetStackRxOn_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_RXARBITER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpRxArbiter_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpRxArbiter_GetStackRxOn_CmdId == gpRxArbiter_ackBuffer[2]);

    _index = 3;
    gpRxArbiter_GetStackRxOn_Output_buf2par(
          &enable
        , stackId
        , gpRxArbiter_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpRxArbiter_ackBuffer));

#undef commandId
    return enable;
}



Bool gpRxArbiter_GetDutyCycleEnabled(gpRxArbiter_StackId_t stackId)
{
    UInt16 _index = 1;
    Bool result;
    UInt8 dataBuf[1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(RxArbiter_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpRxArbiter_GetDutyCycleEnabled_CmdId;

    gpRxArbiter_GetDutyCycleEnabled_Input_par2buf(dataBuf
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_RXARBITER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpRxArbiter_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpRxArbiter_GetDutyCycleEnabled_CmdId == gpRxArbiter_ackBuffer[2]);

    _index = 3;
    gpRxArbiter_GetDutyCycleEnabled_Output_buf2par(
          &result
        , stackId
        , gpRxArbiter_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpRxArbiter_ackBuffer));

#undef commandId
    return result;
}

#if (GP_RX_ARBITER_NUMBER_OF_STACKS > 1)
gpRxArbiter_Result_t gpRxArbiter_SetStackPriority(UInt8 priority, gpRxArbiter_StackId_t stackId)
{
    UInt16 _index = 1;
    gpRxArbiter_Result_t result;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(RxArbiter_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpRxArbiter_SetStackPriority_CmdId;

    gpRxArbiter_SetStackPriority_Input_par2buf(dataBuf
        , priority
        , stackId
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_RXARBITER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpRxArbiter_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpRxArbiter_SetStackPriority_CmdId == gpRxArbiter_ackBuffer[2]);

    _index = 3;
    gpRxArbiter_SetStackPriority_Output_buf2par(
          &result
        , priority
        , stackId
        , gpRxArbiter_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpRxArbiter_ackBuffer));

#undef commandId
    return result;
}
#endif /* (GP_RX_ARBITER_NUMBER_OF_STACKS > 1) */

Bool gpRxArbiter_IsAnActiveChannel(gpRxArbiter_StackId_t stackId, UInt8 channel)
{
    UInt16 _index = 1;
    Bool result;
    UInt8 dataBuf[1 + 1 + 1];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(RxArbiter_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpRxArbiter_IsAnActiveChannel_CmdId;

    gpRxArbiter_IsAnActiveChannel_Input_par2buf(dataBuf
        , stackId
        , channel
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_RXARBITER_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpRxArbiter_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpRxArbiter_IsAnActiveChannel_CmdId == gpRxArbiter_ackBuffer[2]);

    _index = 3;
    gpRxArbiter_IsAnActiveChannel_Output_buf2par(
          &result
        , stackId
        , channel
        , gpRxArbiter_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpRxArbiter_ackBuffer));

#undef commandId
    return result;
}


