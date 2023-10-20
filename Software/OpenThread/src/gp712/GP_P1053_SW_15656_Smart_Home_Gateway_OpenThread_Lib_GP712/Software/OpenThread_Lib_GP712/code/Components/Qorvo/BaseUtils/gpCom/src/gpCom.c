/*
 * Copyright (c) 2008-2016, GreenPeak Technologies
 * Copyright (c) 2017-2019, Qorvo Inc
 *
 * gpCom.c
 *
 * This file contains the implementation of the serial communication module.
 * It implements the GreenPeak serial protocol.
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
 *
 */

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

#define GP_COMPONENT_ID GP_COMPONENT_ID_COM

#include "gpCom.h"
#include "gpCom_defs.h"

#include "gpLog.h"
#include "gpAssert.h"

#include "gpSched.h"

#include "hal.h"

extern HAL_CRITICAL_SECTION_DEF(Com_MultiThreadingMutex)

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/
#ifdef GP_COM_DIVERSITY_TXBUFFER_ALMOST_FULL_CALLBACK
#ifndef GP_COM_MAX_TX_BUFFER_SIZE
#define GP_COM_MAX_TX_BUFFER_SIZE 1536
#endif
#define TX_BUFFER_CALCULATE_USAGE_PERCENTAGE(val) (UInt16)((100 - val * 100 / GP_COM_MAX_TX_BUFFER_SIZE))
#define COMM_ID_SLOT_NB                           (4) /* currently tx buffer almost full indication is supported for max 4 interfaces: UART1, UART2, SPI, SHMEM */
#define EMPTY_COMM_ID_SLOT                        (0x00000000)
#define EMPTY_COMM_ID_SLOT_BITFLAG                (0x80)
#endif
/*****************************************************************************
 *                    Type Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Static Data Definitions
 *****************************************************************************/

Bool         gpCom_Initialized = false;

#ifdef GP_COM_DIVERSITY_TXBUFFER_ALMOST_FULL_CALLBACK
static gpCom_cbTxBufferAlmostFull_t gpCom_TxBufferAlmostFullCb = NULL;
#endif
/*****************************************************************************
 *                    External Data Definition
 *****************************************************************************/

#if defined(GP_COM_DIVERSITY_UNLOCK_TX_AFTER_RX)
Bool gpCom_TxLocked;
#endif

#ifdef GP_COM_DIVERSITY_TXBUFFER_ALMOST_FULL_CALLBACK
#error "Defined protocols cannot be used in this configuration together with GP_COM_DIVERSITY_TXBUFFER_ALMOST_FULL_CALLBACK"
#endif
/*****************************************************************************
 *                    Static Function Prototypes
 *****************************************************************************/
#if defined(GP_COM_DIVERSITY_PACKET_FILTERING) && !defined(GP_COM_COMM_ID_IOCTL_KERN)
UInt8 gpCom_TxBufferUsagePercent(void);
#endif //def GP_COM_DIVERSITY_PACKET_FILTERING && !GP_COM_COMM_ID_IOCTL_KERN

#ifdef GP_COM_DIVERSITY_TXBUFFER_ALMOST_FULL_CALLBACK
static void Com_CheckTxBufferOverTreshhold(gpCom_CommunicationId_t commId);
static void Com_CheckTxBufferBelowTreshold(void);
#endif
/*****************************************************************************
 *                    Static Function Definitions
 *****************************************************************************/
#ifdef GP_COM_DIVERSITY_TXBUFFER_ALMOST_FULL_CALLBACK
static UInt8 Com_FindConnIdInTxBufferAlmostFull(gpCom_CommunicationId_t commId)
{
    UInt8 tmpIdx = 0x7F;
    for(UInt8 index = 0; index < COMM_ID_SLOT_NB; index++)
    {
        if(Com_TxBufferAlmostFullCommIds[index] == commId)
        {
            tmpIdx = index;
            break;
        }
        else if(Com_TxBufferAlmostFullCommIds[index] == EMPTY_COMM_ID_SLOT)
        {
            if(!(tmpIdx & EMPTY_COMM_ID_SLOT_BITFLAG))
            {
                /* first empty slot was found, store it and iterate over rest of the array*/
                tmpIdx = EMPTY_COMM_ID_SLOT_BITFLAG | index;
            }
        }
    }
    return tmpIdx;
}

static void Com_CheckTxBufferOverTreshhold(gpCom_CommunicationId_t commId)
{
    UInt16 usagePerc = 0;

    if(!gpCom_TxBufferAlmostFullCb)
    {
        return;
    }

    usagePerc = TX_BUFFER_CALCULATE_USAGE_PERCENTAGE(gpCom_GetFreeBufferSpace(0, commId));

    if(usagePerc > GP_COM_TXBUFFER_ALMOST_FULL_TRESHOLD_PERCENT)
    {
        UInt8 index = Com_FindConnIdInTxBufferAlmostFull(commId);
        GP_ASSERT_SYSTEM(index != 0x7F);

        if(index & EMPTY_COMM_ID_SLOT_BITFLAG) /* current connId is not stored in Com_TxBufferAlmostFull array - call cb and store it there */
        {
            index &= ~(EMPTY_COMM_ID_SLOT_BITFLAG);
            Com_TxBufferAlmostFullCommIds[index] = commId;
            gpCom_TxBufferAlmostFullCb(Com_TxBufferAlmostFullCommIds[index], true);
        }
        else
        {
            /* connId already present in Com_TxBufferAlmostFull - do nothing */
        }
    }
}

static void Com_CheckTxBufferBelowTreshold(void)
{
    if(!gpCom_TxBufferAlmostFullCb)
    {
        return;
    }

    for(UInt8 index = 0; index < COMM_ID_SLOT_NB; index++)
    {
        if((Com_TxBufferAlmostFullCommIds[index] != EMPTY_COMM_ID_SLOT))
        {
            UInt16 usagePerc = TX_BUFFER_CALCULATE_USAGE_PERCENTAGE(gpCom_GetFreeBufferSpace(0, Com_TxBufferAlmostFullCommIds[index]));
            if(usagePerc < GP_COM_TXBUFFER_ALMOST_FULL_TRESHOLD_PERCENT)
            {
                gpCom_TxBufferAlmostFullCb(Com_TxBufferAlmostFullCommIds[index], false);
                Com_TxBufferAlmostFullCommIds[index] = EMPTY_COMM_ID_SLOT;
            }
        }
    }
}
#endif
/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/

void gpCom_Init(void)
{

    Com_InitRx();

#if defined(GP_DIVERSITY_COM_UART) || defined(GP_COM_DIVERSITY_SERIAL_SPI)
    gpComSerial_Init();
#endif //GP_DIVERSITY_COM_UART
    {
        gpComIoctl_Init();
    }



#ifdef GP_COM_DIVERSITY_TXBUFFER_ALMOST_FULL_CALLBACK
    gpCom_TxBufferAlmostFullCb = NULL;
#endif
}

Bool gpCom_DataRequest(UInt8 moduleID, UInt16 length, UInt8* pData, gpCom_CommunicationId_t commId)
{
    Bool ret = false;

#if defined(GP_COM_DIVERSITY_PACKET_FILTERING) && !defined(GP_COM_COMM_ID_IOCTL_KERN)
    // Check if the packet should be dropped:
    if(gpCom_FilterIsPacketDataToReject(gpCom_TxBufferUsagePercent(), moduleID, length, pData, commId))
    {
        return true;
    }
#endif //def GP_COM_DIVERSITY_PACKET_FILTERING

    //GP_LOG_SYSTEM_PRINTF("TX m=%02x l=%d d=%02x...",0,moduleID, length, pData[0]);
#if defined(GP_DIVERSITY_COM_UART) || defined(GP_COM_DIVERSITY_SERIAL_SPI)
    if(GP_COMM_ID_CARRIED_BY(commId,GP_COM_COMM_ID_UART1)
    || GP_COMM_ID_CARRIED_BY(commId,GP_COM_COMM_ID_UART2)
    || GP_COMM_ID_CARRIED_BY(commId,GP_COM_COMM_ID_STMUSB)
    || GP_COMM_ID_CARRIED_BY(commId,GP_COM_COMM_ID_SPI)
    || GP_COMM_ID_CARRIED_BY(commId,GP_COM_COMM_ID_USB))
    {
        ret = gpComSerial_DataRequest(moduleID, length, pData, commId);
    }
    else
#endif
    if(GP_COMM_ID_CARRIED_BY(commId, GP_COM_COMM_ID_IOCTL_KERN1)
    || GP_COMM_ID_CARRIED_BY(commId, GP_COM_COMM_ID_IOCTL_KERN2)
    || GP_COMM_ID_CARRIED_BY(commId, GP_COM_COMM_ID_IOCTL_USER1)
    || GP_COMM_ID_CARRIED_BY(commId, GP_COM_COMM_ID_IOCTL_USER2)
    || GP_COMM_ID_CARRIED_BY(commId, GP_COM_COMM_ID_IOCTL_USER3)
    || GP_COMM_ID_CARRIED_BY(commId, GP_COM_COMM_ID_IOCTL_USER4)
    )
    {
        ret = gpComIoctl_DataRequest(moduleID, length, pData, commId);
    }
    else
    {
        ret = false;
    }

#ifdef GP_COM_DIVERSITY_TXBUFFER_ALMOST_FULL_CALLBACK
    if(ret == true)
    {
        Com_CheckTxBufferOverTreshhold(commId);
    }
#endif

    if (ret == false
        && !(moduleID == GP_COMPONENT_ID_COM && pData[0] == 0xfe && pData[2] == 0x08 /*gpComLinkEvent_Ping_CmdId*/ )
    )
    {
        GP_ASSERT_SYSTEM(ret);
    }
    return ret;

}

UInt16 gpCom_GetFreeBufferSpace(UInt8 moduleID, gpCom_CommunicationId_t commId)
{
    NOT_USED(moduleID);
#if ! defined(GP_DIVERSITY_COM_UART) 
    NOT_USED(commId);
#endif //not defined GP_DIVERSITY_COM_UART
#if defined(GP_DIVERSITY_COM_UART) || defined(GP_COM_DIVERSITY_SERIAL_SPI)
    if(GP_COMM_ID_CARRIED_BY(commId,GP_COM_COMM_ID_UART1)
    || GP_COMM_ID_CARRIED_BY(commId,GP_COM_COMM_ID_UART2)
    || GP_COMM_ID_CARRIED_BY(commId,GP_COM_COMM_ID_STMUSB)
    || GP_COMM_ID_CARRIED_BY(commId,GP_COM_COMM_ID_SPI)
    || GP_COMM_ID_CARRIED_BY(commId,GP_COM_COMM_ID_USB))
    {
        return gpComSerial_GetFreeSpace(commId);
    }
    else
#endif
    GP_ASSERT_DEV_EXT(false);
    {
        return 0;
    }
}

//Redirection functions
Bool gpCom_GetTXEnable(void)
{
    Bool enabled = false;

#if defined(GP_DIVERSITY_COM_UART) || defined(GP_COM_DIVERSITY_SERIAL_SPI)
    enabled |= gpComSerial_GetTXEnable();
#endif
    enabled |= gpComIoctl_GetTXEnable();

    return enabled;
}

Bool gpCom_TXDataPending(void)
{

    Bool pending = false;

#if defined(GP_DIVERSITY_COM_UART) || defined(GP_COM_DIVERSITY_SERIAL_SPI)
    pending |= gpComSerial_TXDataPending();
#endif
    pending |= gpComIoctl_TXDataPending();

    return pending;
}


void gpCom_Flush(void)
{

#if defined(GP_DIVERSITY_COM_UART) || defined(GP_COM_DIVERSITY_SERIAL_SPI)
    gpComSerial_Flush();
#endif
    gpComIoctl_Flush();
}

void gpCom_DeInit(void)
{
    Com_DeInitRx();

#if defined(GP_DIVERSITY_COM_UART) || defined(GP_COM_DIVERSITY_SERIAL_SPI)
    gpComSerial_DeInit();
#endif
    gpComIoctl_DeInit();
}

void gpCom_HandleTx(void)
{
#if defined(GP_DIVERSITY_COM_UART) || defined(GP_COM_DIVERSITY_SERIAL_SPI)
    gpComSerial_HandleTx();
#endif
    gpComIoctl_HandleTx();
#ifdef GP_COM_DIVERSITY_TXBUFFER_ALMOST_FULL_CALLBACK
    Com_CheckTxBufferBelowTreshold();
#endif
}

Bool gpCom_DataRequestAndWaitForAck(UInt8 moduleID, UInt16 length, UInt8* pData, gpCom_CommunicationId_t commId, Bool *reqAcked, UInt32 timeout, UInt8 ackId)
{
    Bool ret;
    Bool timedOut = false;

    HAL_ACQUIRE_MUTEX(Com_MultiThreadingMutex);
    *reqAcked = false;
    ret = gpCom_DataRequest(moduleID, length, pData, commId);

    //Just wait for ACK if data request was a success
    if(ret)
    {
        UInt32 endPollTime = timeout + gpSched_GetCurrentTime();

        while(!timedOut)
        {
            gpCom_HandleTx();
            gpCom_HandleRxBlocking(true, ackId);
            if(!(*reqAcked))
            {
                if(!gpSched_TimeCompareLower(gpSched_GetCurrentTime(), endPollTime))
                {
                    timedOut = true;
                }
            }
            else
            {
                break;
            }
        }
    }
    HAL_RELEASE_MUTEX(Com_MultiThreadingMutex);

    if(timedOut)
    {
        GP_LOG_SYSTEM_PRINTF("WFack fail m:%x l:%u [%x Id:%lx",0, moduleID, length, pData[0], (long unsigned int)commId);
        GP_ASSERT_SYSTEM(false);
    }

    return ret;
}




#ifdef GP_COM_DIVERSITY_TXBUFFER_ALMOST_FULL_CALLBACK
gpCom_cbTxBufferAlmostFull_t gpCom_RegisterTxBufferAlmostFull(gpCom_cbTxBufferAlmostFull_t cb)
{
    gpCom_cbTxBufferAlmostFull_t oldCb = gpCom_TxBufferAlmostFullCb;

    gpCom_TxBufferAlmostFullCb = cb;
    return oldCb;
}
#endif
