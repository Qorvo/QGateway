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
 * $Header: //depot/release/Embedded/Components/Qorvo/BaseUtils/v2.10.2.0/comps/gpRandom/src/gen/gpRandom_wrapper_client.c#1 $
 * $Change: 187624 $
 * $DateTime: 2021/12/20 10:58:50 $
 */

/** @file "gpRandom_wrapper_client.c"
 *
 *  Random generator component
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
#include "gpRandom_clientServerCmdId.h"
#include "gpRandom.h"
#include "gpRandom_marshalling.h"
#if defined(GP_VERSION_DIVERSITY_GPCOM_CLIENT) && !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)
#include "gpVersion.h"
#endif

/*****************************************************************************
 *                    Typedef Definition
 *****************************************************************************/

/*****************************************************************************
 *                    Static Functions Declaration
 *****************************************************************************/

static void gpRandom_HandleIndicationClient(UInt16 length, UInt8* pPayload, gpCom_CommunicationId_t communicationId);
static void Random_HandleConnectionClose(gpCom_CommunicationId_t communicationId);

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/

#define GP_COMPONENT_ID GP_COMPONENT_ID_RANDOM
#define GP_MODULE_ID GP_COMPONENT_ID


#ifndef GP_RANDOM_COMM_ID
#define GP_RANDOM_COMM_ID GP_COM_DEFAULT_COMMUNICATION_ID
#endif

#define REGISTER_MODULE(handle)              GP_COM_REGISTER_MODULE(handle)
#define DATA_REQUEST(len,buf,commId)         GP_COM_DATA_REQUEST(len,buf,commId)
#define DATA_REQUEST_ACKED(len,buf,commId)   gpCom_DataRequestAndWaitForAck(GP_MODULE_ID, len, buf, commId, &gpRandom_reqAcked, GPRANDOM_GPCOMTIMEOUT_US, gpRandom_Acknowledge_CmdId)

/*****************************************************************************
 *                    Static Data
 *****************************************************************************/

typedef union ackDataNeeded {
    UInt8 dataBuf0[1+25];
    UInt8 dataBuf1[1];
    UInt8 dataBuf2[1+25+1];
    UInt8 dataBuf3[1+255];
} ackDataNeeded_t;
static UInt8 gpRandom_ackBuffer[1 + 1 + 1 + sizeof(ackDataNeeded_t)];
static Bool gpRandom_reqAcked;

#if defined(GP_VERSION_DIVERSITY_GPCOM_CLIENT) && !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)
static Bool Random_clientApiVersionSelected = false;
#endif

/*****************************************************************************
 *                    Static Function Definitions
 *****************************************************************************/

static void Random_HandleConnectionClose(gpCom_CommunicationId_t communicationId)
{
}

static void gpRandom_HandleIndicationClient(UInt16 length, UInt8* pPayload, gpCom_CommunicationId_t communicationId)
{
#define commandId pPayload[0]
    UInt8 ackBuffer[1 + 1 + 1];
    UInt8 ackBytes = 0; /*No ack's on indication - fill in length when needed - 3+x */

    if(pPayload == NULL)
    {
        Random_HandleConnectionClose(communicationId);
        return;
    }

#if defined(GP_VERSION_DIVERSITY_GPCOM_CLIENT) && !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && (GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION)
    GP_ASSERT_DEV_EXT(Random_clientApiVersionSelected);
#endif

    ackBuffer[0] = gpRandom_Acknowledge_CmdId;
    ackBuffer[1] = gpMarshall_AckStatusSuccess;
    ackBuffer[2] = commandId;

    switch(commandId)
    {

        case gpRandom_Acknowledge_CmdId:
        {
            GP_ASSERT_SYSTEM(length <= sizeof(gpRandom_ackBuffer));
            MEMCPY(gpRandom_ackBuffer, pPayload, length);
            gpRandom_reqAcked = true;
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


#if defined(GP_VERSION_DIVERSITY_GPCOM_CLIENT) && !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)
void gpRandom_SetDefaultApiVersion(gpVersion_ModuleVersionInfo_t* moduleVersionInfo)
{
    Random_clientApiVersionSelected = true;
    //TBD
}
#endif //defined(GP_VERSION_DIVERSITY_GPCOM_CLIENT) && !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)


void gpRandom_DeInit(void)
{
    gpCom_DeRegisterModule(GP_MODULE_ID);
}

void gpRandom_Init(void)
{
#if defined(GP_VERSION_DIVERSITY_GPCOM_CLIENT) && !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)
    gpVersion_ReleaseInfo_t versions[1] = {{2,0,0,0}};
    Random_clientApiVersionSelected = false;
    gpVersion_RegisterModule(GP_MODULE_ID, versions,1,gpRandom_SetDefaultApiVersion);
#endif //defined(GP_VERSION_DIVERSITY_GPCOM_CLIENT) && !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)
    REGISTER_MODULE(gpRandom_HandleIndicationClient);
}

/*****************************************************************************
 *                    gpRandom Require Functions
 *****************************************************************************/

void gpRandom_GetNewSequence(UInt8 nmbrRandomBytes, UInt8* pBuffer)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1];

#if defined(GP_VERSION_DIVERSITY_GPCOM_CLIENT) && !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && (GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION)
    GP_ASSERT_DEV_EXT(Random_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpRandom_GetNewSequence_CmdId;

    gpRandom_GetNewSequence_Input_par2buf(dataBuf
        , nmbrRandomBytes
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_RANDOM_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpRandom_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpRandom_GetNewSequence_CmdId == gpRandom_ackBuffer[2]);

    _index = 3;
    gpRandom_GetNewSequence_Output_buf2par(
          nmbrRandomBytes
        , pBuffer
        , gpRandom_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpRandom_ackBuffer));

#undef commandId
}




void gpRandom_GetFromDRBG(UInt8 nmbrRandomBytes, UInt8* pBuffer)
{
    UInt16 _index = 1;
    UInt8 dataBuf[1 + 1];

#if defined(GP_VERSION_DIVERSITY_GPCOM_CLIENT) && !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && (GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION)
    GP_ASSERT_DEV_EXT(Random_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = gpRandom_GetFromDRBG_CmdId;

    gpRandom_GetFromDRBG_Input_par2buf(dataBuf
        , nmbrRandomBytes
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_RANDOM_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpRandom_ackBuffer[1]);
    GP_ASSERT_SYSTEM(gpRandom_GetFromDRBG_CmdId == gpRandom_ackBuffer[2]);

    _index = 3;
    gpRandom_GetFromDRBG_Output_buf2par(
          nmbrRandomBytes
        , pBuffer
        , gpRandom_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpRandom_ackBuffer));

#undef commandId
}


