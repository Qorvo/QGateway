/*
 * Copyright (c) 2015-2016, GreenPeak Technologies
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
 * $Header: //depot/release/Embedded/Components/Qorvo/OS/v2.10.2.0/comps/gpVersion/src/gen/gpVersion_wrapper_client.c#1 $
 * $Change: 187624 $
 * $DateTime: 2021/12/20 10:58:50 $
 */

/** @file "gpVersion_wrapper_client.c"
 *
 *  GPVERSION
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
#include "gpVersion_clientServerCmdId.h"
#include "gpVersion.h"
#include "gpVersion_marshalling.h"
#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)
#include "gpVersion.h"
#endif
/* <CodeGenerator Placeholder> AdditionalIncludes */
#include "gpVersion_defs.h"
/* </CodeGenerator Placeholder> AdditionalIncludes */

/*****************************************************************************
 *                    Typedef Definition
 *****************************************************************************/

/*****************************************************************************
 *                    Static Functions Declaration
 *****************************************************************************/

static void gpVersion_HandleIndicationClient(UInt16 length, UInt8* pPayload, gpCom_CommunicationId_t communicationId);
static void Version_HandleConnectionClose(gpCom_CommunicationId_t communicationId);

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/

#define GP_COMPONENT_ID GP_COMPONENT_ID_VERSION
#define GP_MODULE_ID GP_COMPONENT_ID


#ifndef GP_VERSION_COMM_ID
#define GP_VERSION_COMM_ID GP_COM_DEFAULT_COMMUNICATION_ID
#endif

#define REGISTER_MODULE(handle)              GP_COM_REGISTER_MODULE(handle)
#define DATA_REQUEST(len,buf,commId)         GP_COM_DATA_REQUEST(len,buf,commId)
#define DATA_REQUEST_ACKED(len,buf,commId)   gpCom_DataRequestAndWaitForAck(GP_MODULE_ID, len, buf, commId, &gpVersion_reqAcked, GPVERSION_GPCOMTIMEOUT_US, gpVersion_Acknowledge_CmdId)

/* <CodeGenerator Placeholder> AdditionalMacros */
#define gpVersion_ResultInvalidParameter gpVersion_CompatibilityResultInvalidParameter
/* </CodeGenerator Placeholder> AdditionalMacros */
/*****************************************************************************
 *                    Static Data
 *****************************************************************************/

typedef union ackDataNeeded {
    UInt8 dataBuf0[(1 + 1 + 1 + 1)+1];
} ackDataNeeded_t;
static UInt8 gpVersion_ackBuffer[1 + 1 + 1 + sizeof(ackDataNeeded_t)];
static Bool gpVersion_reqAcked;

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)
static Bool Version_clientApiVersionSelected = false;
#endif

/*****************************************************************************
 *                    Static Function Definitions
 *****************************************************************************/

static void Version_HandleConnectionClose(gpCom_CommunicationId_t communicationId)
{
}

static void gpVersion_HandleIndicationClient(UInt16 length, UInt8* pPayload, gpCom_CommunicationId_t communicationId)
{
#define commandId pPayload[0]
    UInt8 ackBuffer[1 + 1 + 1];
    UInt8 ackBytes = 0; /*No ack's on indication - fill in length when needed - 3+x */

    if(pPayload == NULL)
    {
        Version_HandleConnectionClose(communicationId);
        return;
    }

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(Version_clientApiVersionSelected);
#endif

    ackBuffer[0] = gpVersion_Acknowledge_CmdId;
    ackBuffer[1] = gpMarshall_AckStatusSuccess;
    ackBuffer[2] = commandId;

    switch(commandId)
    {

        case gpVersion_Acknowledge_CmdId:
        {
            GP_ASSERT_SYSTEM(length <= sizeof(gpVersion_ackBuffer));
            MEMCPY(gpVersion_ackBuffer, pPayload, length);
            gpVersion_reqAcked = true;
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
void gpVersion_SetDefaultApiVersion(gpVersion_ModuleVersionInfo_t* moduleVersionInfo)
{
    Version_clientApiVersionSelected = true;
    //TBD
}
#endif //defined(GP_VERSION_DIVERSITY_GPCOM_CLIENT) && !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)


void gpVersion_DeInit(void)
{
/* <CodeGenerator Placeholder> DeInit */
    Version_Init();
    Version_InitClient();
/* </CodeGenerator Placeholder> DeInit */

    gpCom_DeRegisterModule(GP_MODULE_ID);
}

void gpVersion_Init(void)
{
/* <CodeGenerator Placeholder> Init */
    Version_Init();
    Version_InitClient();
/* </CodeGenerator Placeholder> Init */

    gpVersion_InitMarshalling();

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)
    gpVersion_ReleaseInfo_t versions[1] = {{2,0,0,0}};
    Version_clientApiVersionSelected = false;
    gpVersion_RegisterModule(GP_MODULE_ID, versions,1,gpVersion_SetDefaultApiVersion);
#endif //defined(GP_VERSION_DIVERSITY_GPCOM_CLIENT) && !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION)
    REGISTER_MODULE(gpVersion_HandleIndicationClient);
}

/*****************************************************************************
 *                    gpVersion Require Functions
 *****************************************************************************/

gpVersion_VersionStatusResult_t Version_ExchangeGlobalVersion(gpVersion_ReleaseInfo_t clientInfo, gpVersion_ReleaseInfo_t* serverInfo)
{
    UInt16 _index = 1;
    gpVersion_VersionStatusResult_t result;
    UInt8 dataBuf[1 + (1 + 1 + 1 + 1)];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(Version_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = Version_ExchangeGlobalVersion_CmdId;

    Version_ExchangeGlobalVersion_Input_par2buf(dataBuf
        , clientInfo
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_VERSION_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpVersion_ackBuffer[1]);
    GP_ASSERT_SYSTEM(Version_ExchangeGlobalVersion_CmdId == gpVersion_ackBuffer[2]);

    _index = 3;
    Version_ExchangeGlobalVersion_Output_buf2par(
          &result
        , clientInfo
        , serverInfo
        , gpVersion_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpVersion_ackBuffer));

#undef commandId
    return result;
}

gpVersion_VersionStatusResult_t Version_NegotiateModuleVersion(UInt8 moduleId, UInt8 nrOfClientVersions, gpVersion_ReleaseInfo_t* pClientVersions, gpVersion_ReleaseInfo_t* serverInfo)
{
    UInt16 _index = 1;
    gpVersion_VersionStatusResult_t result;
    UInt8 dataBuf[1 + 1 + 1 + 1 + 6*(1 + 1 + 1 + 1)];

#if !defined(GP_VERSION_DIVERSITY_NO_MODULE_VERSION) && GP_COMPONENT_ID != GP_COMPONENT_ID_VERSION
    GP_ASSERT_DEV_EXT(Version_clientApiVersionSelected);
#endif

#define commandId                                           dataBuf[0]

    commandId = Version_NegotiateModuleVersion_CmdId;

    Version_NegotiateModuleVersion_Input_par2buf(dataBuf
        , moduleId
        , nrOfClientVersions
        , pClientVersions
        , &_index);

    GP_ASSERT_SYSTEM(_index <= sizeof(dataBuf));
    DATA_REQUEST_ACKED(_index, dataBuf, GP_VERSION_COMM_ID);

    GP_ASSERT_SYSTEM(gpMarshall_AckStatusSuccess == gpVersion_ackBuffer[1]);
    GP_ASSERT_SYSTEM(Version_NegotiateModuleVersion_CmdId == gpVersion_ackBuffer[2]);

    _index = 3;
    Version_NegotiateModuleVersion_Output_buf2par(
          &result
        , moduleId
        , nrOfClientVersions
        , pClientVersions
        , serverInfo
        , gpVersion_ackBuffer
        , &_index);
    GP_ASSERT_SYSTEM(_index <= sizeof(gpVersion_ackBuffer));

#undef commandId
    return result;
}


