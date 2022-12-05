/**
 * This file contains a the implementation of the gpCom over a UNIX socket
 *
 * Copyright (c) 2015-2016, GreenPeak Technologies
 * Copyright (c) 2017-2019, Qorvo Inc
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
 * $Header: //depot/release/Embedded/Components/Qorvo/BaseUtils/v2.10.3.1/comps/gpCom/src/gpCom_IoctlUser.c#1 $
 * $Change: 197210 $
 * $DateTime: 2022/10/13 16:52:00 $
 *
 */

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/
#define GP_COMPONENT_ID GP_COMPONENT_ID_COM

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

#include "hal.h"
#include "gpUtils.h"
#include "gpCom.h"
#include "gpCom_defs.h"

#include "ComIoctlInterface_marshalling.h"
#include "gpLog.h"
#include "gpAssert.h"

#include "gpSched.h"

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/
#ifdef GP_COM_DEVICE_FILE_NAME
#define COM_DEVICE_FILE_NAME XSTRINGIFY(GP_COM_DEVICE_FILE_NAME)
#else
#define COM_DEVICE_FILE_NAME "/dev/gp"
#endif //def COM_DEVICE_FILE_NAME
/*****************************************************************************
 *                    Type Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Static Data Definitions
 *****************************************************************************/

//State variables
int Com_IoctlFd = -1;

/*****************************************************************************
 *                    Static Function Prototypes
 *****************************************************************************/

void ComIoctl_FlushRx(void);

/*****************************************************************************
 *                    Static Function Definitions
 *****************************************************************************/

void ComIoctl_ConnectionClose(void)
{
    GP_LOG_SYSTEM_PRINTF("Closing connections",0);
    Com_ConnectionClose(GP_COM_COMM_ID_IOCTL_USER);
    gpComIoctl_DeInit();
    gpComIoctl_Init();

    GP_ASSERT_SYSTEM(false);
}

Bool ComIoctl_PollFunction(void)
{
    UInt8 UserspaceBuffer[32+GP_COM_MAX_PACKET_PAYLOAD_SIZE];
    UInt16 Index = 0;
    gpCom_Packet_t* pPacket;
    int ret;

    MEMSET(&UserspaceBuffer, 0, sizeof(UserspaceBuffer));
    if(Com_IoctlFd < 0)
    {
        GP_LOG_SYSTEM_PRINTF("Driver not opened? fd:%d",0,Com_IoctlFd);
        goto ComIoctl_PollFunction_NoFd;
    }

    pPacket = Com_GetFreePacket();
    if (!pPacket) {
        GP_LOG_PRINTF("No gpCom_PacketBuffer available",0);
        goto ComIoctl_PollFunction_NoPacketBuffer;
    }

    readMsg_Input_par2buf( (UInt8Buffer*)UserspaceBuffer, GP_COM_MAX_PACKET_PAYLOAD_SIZE, &Index );

    ret = ioctl(Com_IoctlFd, GP_IOCTL_READ_STREAM_MSG, UserspaceBuffer);
    Index = 0;
    readMsg_Output_buf2par(GP_COM_MAX_PACKET_PAYLOAD_SIZE, &pPacket->moduleID, &pPacket->commId, &pPacket->length , pPacket->packet, (UInt8Buffer*)UserspaceBuffer , &Index);
    if (ret<0)
    {
        switch (errno)
        {
            case ENOMEM:
                GP_LOG_SYSTEM_PRINTF("%s: gpOsal_ErrorNoMemory, Userspace allocation too small for packet in kernel: %u < %u",0, __FUNCTION__, GP_COM_MAX_PACKET_PAYLOAD_SIZE, pPacket->length);
                GP_ASSERT_SYSTEM(false);
                break;

            case ENOTTY:
                GP_LOG_SYSTEM_PRINTF("gpOsal_ErrorInvalidIoctl",0);
                break;

            case ENODATA:
                //No data available
                break;

            case ENODEV:
                //Device not available during recover, avoid flood of prints
                break;

            default:
                GP_LOG_SYSTEM_PRINTF("Errornumber: %d",0,errno);
                break;
        }
        goto ComIoctl_PollFunction_IoctlFail;
    }
    GP_LOG_PRINTF("got msg mid=0x%02X len=%d commid=%lx [ %02x %02x %02x %02x %02x %02x %02x %02x ]", 0,
    pPacket->moduleID, pPacket->length, (long unsigned int)pPacket->commId,
    pPacket->packet[0],
    pPacket->packet[1],
    pPacket->packet[2],
    pPacket->packet[3],
    pPacket->packet[4],
    pPacket->packet[5],
    pPacket->packet[6],
    pPacket->packet[7]
    );


    //gpLog_PrintBuffer(pPacket->length, pPacket->packet);

    if(!Com_AddPendingPacket(pPacket))
    {
        Com_FreePacket(pPacket);
        GP_LOG_SYSTEM_PRINTF("No space for handling",0);
    }

    return true;

ComIoctl_PollFunction_IoctlFail:
    Com_FreePacket(pPacket);
ComIoctl_PollFunction_NoPacketBuffer:
ComIoctl_PollFunction_NoFd:
    return false;
}

void ComIoctl_PollHandler(UInt8 fd)
{
    NOT_USED(fd);
    ComIoctl_PollFunction();
}

void ComIoctl_FlushRx(void)
{
    while(ComIoctl_PollFunction());
}

void ComIoctl_SignalIOHandler(int sig, siginfo_t *siginfo, void* context)
{
    NOT_USED(sig);
    NOT_USED(siginfo);
    NOT_USED(context);
    GP_LOG_SYSTEM_PRINTF("Driver reset detected",0);
    gpSched_ScheduleEvent(0, ComIoctl_ConnectionClose);
}

/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/
void gpComIoctl_Init (void)
{
    int oldFlags;
    struct sigaction act;

    Com_IoctlFd = open(COM_DEVICE_FILE_NAME, O_RDWR|O_CLOEXEC);
    if (Com_IoctlFd < 0)
    {
        GP_LOG_SYSTEM_PRINTF("Can't open device file: %s", 0, COM_DEVICE_FILE_NAME);
        GP_ASSERT_SYSTEM(false);
        return;
    }

    memset(&act, 0, sizeof(act));
    act.sa_sigaction = &ComIoctl_SignalIOHandler;
    act.sa_flags = SA_SIGINFO;
    if(sigaction(SIGIO, &act, NULL) < 0)
    {
        GP_LOG_SYSTEM_PRINTF("Can't assign SIGIO",0);
        GP_ASSERT_SYSTEM(false);
        return;
    }

    fcntl(Com_IoctlFd, F_SETOWN, getpid());
    //FASYNC needs to be set through fcntl
    oldFlags = fcntl(Com_IoctlFd, F_GETFL);
    fcntl(Com_IoctlFd, F_SETFL, oldFlags | FASYNC);

    hal_RegisterPollFunction(Com_IoctlFd, ComIoctl_PollHandler);
}

Bool gpComIoctl_GetTXEnable(void)
{
    return (Com_IoctlFd >= 0);
}

void gpComIoctl_DeInit(void)
{
    if(Com_IoctlFd >= 0)
    {
        hal_UnRegisterPollFunction(Com_IoctlFd);
        close(Com_IoctlFd);
        Com_IoctlFd = -1;
    }
}

Bool gpComIoctl_DataRequest(UInt8 moduleID, UInt16 length, UInt8* pData, gpCom_CommunicationId_t commId)
{
    UInt8 UserspaceBuffer[32+GP_COM_MAX_PACKET_PAYLOAD_SIZE];
    UInt16 Index = 0;
    int ret;

    if (Com_IoctlFd < 0) {
       return false;
    }

    MEMSET(&UserspaceBuffer, 0, sizeof(UserspaceBuffer));

    GP_ASSERT_DEV_INT(GP_COM_COMM_ID_IOCTL_USER  & commId); // return path hardcodes this value

    writeMsg_Input_par2buf( (UInt8Buffer*)UserspaceBuffer , moduleID , commId , length , pData , &Index);
    GP_ASSERT_SYSTEM(Index < sizeof(UserspaceBuffer));

    ret = ioctl(Com_IoctlFd, GP_IOCTL_WRITE_STREAM_MSG, UserspaceBuffer);
    if(ret < 0)
    {
        switch (errno)
        {
            case ENOMEM:
                GP_LOG_SYSTEM_PRINTF("%s: gpOsal_ErrorNoMemory, Userspace allocation too small for packet in kernel: %u < %u",0, __FUNCTION__, GP_COM_MAX_PACKET_PAYLOAD_SIZE, length);
                GP_ASSERT_SYSTEM(false);
                break;
            case ENOTTY:
                GP_LOG_SYSTEM_PRINTF("gpOsal_ErrorInvalidIoctl",0);
                break;
            case ENODATA:
                //No data available
                break;
            case ENODEV:
                //Device not available during recover, avoid flood of prints
                break;
            default:
                GP_LOG_SYSTEM_PRINTF("Errornumber: %d",0,errno);
                break;
        }
        return false;
    }
    else
    {
        return true;
    }
}

void gpComIoctl_HandleTx(void)
{

}

void gpComIoctl_Flush(void)
{
    //No Tx side flush needed
}

Bool gpComIoctl_TXDataPending(void)
{
/* A datarequest will handover any tx data directly to the ioctl fd, so at no point will
   there be any tx data pending */
    return false;
}

