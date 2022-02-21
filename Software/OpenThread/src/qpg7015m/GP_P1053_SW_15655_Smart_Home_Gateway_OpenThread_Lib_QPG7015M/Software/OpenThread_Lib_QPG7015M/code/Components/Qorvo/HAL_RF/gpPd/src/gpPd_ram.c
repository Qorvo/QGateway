/*
 * Copyright (c) 2011-2016, GreenPeak Technologies
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
 * $Header: //depot/release/Embedded/Components/Qorvo/HAL_RF/v2.10.2.0/comps/gpPd/src/gpPd_ram.c#1 $
 * $Change: 187624 $
 * $DateTime: 2021/12/20 10:58:50 $
 *
 */

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

//#define GP_LOCAL_LOG
#if defined(GP_COMP_GPHAL) 
#include "gpHal.h"
#endif //defined(GP_COMP_GPHAL) && !defined(GP_DIVERSITY_GPHAL_COPROC)
#include "gpPoolMem.h"
/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Functional Macro Definitions
 *****************************************************************************/

#define PD_CHECK_HANDLE_VALID(pdHandle)      (pdHandle < GP_PD_NR_OF_HANDLES)
#define PD_CHECK_HANDLE_IN_USE(pdHandle)     (gpPd_Descriptors[pdHandle])
#define PD_CHECK_HANDLE_ACCESSIBLE(pdHandle) (PD_CHECK_HANDLE_VALID(pdHandle) && PD_CHECK_HANDLE_IN_USE(pdHandle))


#define PBM_CHECK_HANDLE_ACCESSIBLE(PbmHandle)    (GP_HAL_CHECK_PBM_VALID(PbmHandle) && GP_HAL_IS_PBM_ALLOCATED(PbmHandle))

// Only allowed for ZigBee pds
#define PD_WRAP_OFFSET(offset)              (offset &= 0x7f)
#if defined(GP_COMP_GPHAL) 
#define PD_TMP_SIZE 128
#endif // defined(GP_COMP_GPHAL) && !defined(GP_DIVERSITY_GPHAL_COPROC)

#define PD_CHECK_HANDLE_INPUT_NO_RETURN(pdHandle) do { \
    if(!PD_CHECK_HANDLE_ACCESSIBLE(pdHandle)) \
    { \
        GP_ASSERT_DEV_EXT(false); \
        return; \
    } \
} while(false)

#define PD_CHECK_HANDLE_INPUT_WITH_RETURN(pdHandle, retVal) do { \
    if(!PD_CHECK_HANDLE_ACCESSIBLE(pdHandle)) \
    { \
        GP_ASSERT_DEV_EXT(false); \
        return retVal; \
    } \
} while(false)

/*****************************************************************************
 *                    Type Definitions
 *****************************************************************************/



/*****************************************************************************
 *                    Static Data Definitions
 *****************************************************************************/

//Pointers to Packet buffers and meta-data
gpPd_Descriptor_t* gpPd_Descriptors[GP_PD_NR_OF_HANDLES];

#if defined(GP_COMP_GPHAL) 
// lookup table to bind a PD to a PBM
static gpPd_Handle_t Pd_Pbm2pd[GPHAL_NUMBER_OF_PBMS_USED];
static UInt8 Pd_NmbrOfPbmsClaimedBySw;
#endif //defined(GP_COMP_GPHAL) && !defined(GP_DIVERSITY_GPHAL_COPROC)

/*****************************************************************************
 *                    External Data Definition
 *****************************************************************************/

/*****************************************************************************
 *                    Static Function Prototypes
 *****************************************************************************/

#if defined(GP_COMP_GPHAL) 
static void Pd_RestoreFromPbm(UInt8 pbmHandle, UInt8 pbmOffset, UInt8 pbmLength, gpPd_Handle_t pdHandle);
static void Pd_CopyToPbm(UInt8 pbmHandle, UInt8 offset, UInt8 length);
#endif //defined(GP_COMP_GPHAL) && !defined(GP_DIVERSITY_GPHAL_COPROC)

/*****************************************************************************
 *                    Static Function Definitions
 *****************************************************************************/

static void    Pd_Init(void);
static void    Pd_DeInit(void);

//Descriptor handling
static gpPd_Handle_t        Pd_GetPd(gpPd_BufferType_t type, UInt16 size);
static void                 Pd_FreePd(gpPd_Handle_t pdHandle);
static gpPd_Result_t        Pd_CheckPdValid(gpPd_Handle_t pdHandle);
static gpPd_BufferType_t    Pd_GetPdType(gpPd_Handle_t pdHandle);
#if defined(GP_COMP_GPHAL) 
static UInt8                Pd_GetPBM(UInt8 pdHandle);
static UInt8                Pd_AllocatePBM(gpPd_Handle_t pdHandle,UInt16 size);
#endif

//Data handling
static UInt8         Pd_ReadByte(gpPd_Handle_t pdHandle, gpPd_Offset_t offset);
static void          Pd_WriteByte(gpPd_Handle_t pdHandle, gpPd_Offset_t offset, UInt8 byte);
static void          Pd_ReadByteStream(gpPd_Handle_t pdHandle, gpPd_Offset_t offset, UInt8 length, UInt8* pData);
static void          Pd_WriteByteStream(gpPd_Handle_t pdHandle, gpPd_Offset_t offset, UInt8 length, UInt8* pData);

//Properties handling
static gpPd_Rssi_t  Pd_GetRssi(gpPd_Handle_t pdHandle);
static void         Pd_SetRssi(gpPd_Handle_t pdHandle, gpPd_Rssi_t rssi);
static gpPd_Lqi_t   Pd_GetLqi(gpPd_Handle_t pdHandle);
static void         Pd_SetLqi(gpPd_Handle_t pdHandle, gpPd_Lqi_t lqi);
static UInt32       Pd_GetRxTimestamp(gpPd_Handle_t pdHandle);
#ifndef GP_MACDISPATCHER_DIVERSITY_GPCOM_CLIENT
static UInt32       Pd_GetRxTimestampChip(gpPd_Handle_t pdHandle);
#endif /* GP_MACDISPATCHER_DIVERSITY_GPCOM_CLIENT */
static void         Pd_SetRxTimestamp(gpPd_Handle_t pdHandle, gpPd_TimeStamp_t timestamp);
static UInt32       Pd_GetTxTimestamp(gpPd_Handle_t pdHandle);
static UInt16*      Pd_GetPhaseSamplesBuffer(gpPd_Handle_t pdHandle);
static UInt8        Pd_GetTxRetryCntr(gpPd_Handle_t pdHandle);
static void         Pd_SetFramePendingAfterTx(gpPd_Handle_t pdHandle, UInt8 framePending);
static UInt8        Pd_GetFramePendingAfterTx(gpPd_Handle_t pdHandle);

/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/

static void Pd_Init(void)
{
    UInt8 i;

    for(i = 0; i < GP_PD_NR_OF_HANDLES; i++)
    {
        gpPd_Descriptors[i] = NULL;
    }
    //Cleanup lookup table
#if defined(GP_COMP_GPHAL) 
    Pd_NmbrOfPbmsClaimedBySw=0;
    for(i = 0; i < GPHAL_NUMBER_OF_PBMS_USED; i++)
    {
        Pd_Pbm2pd[i] = GP_PD_INVALID_HANDLE;
    }
#endif //defined(GP_COMP_GPHAL) && !defined(GP_DIVERSITY_GPHAL_COPROC)
#ifdef GP_COMP_UNIT_TEST
    gpPd_InitUnit();
#endif // GP_COMP_UNIT_TEST
}

static void Pd_DeInit(void)
{
    UInt8 i;

    for(i = 0; i < GP_PD_NR_OF_HANDLES; i++)
    {
        if(gpPd_Descriptors[i] != NULL)
        {
            Pd_FreePd(i);
        }
    }
}

static gpPd_Handle_t Pd_AllocatePdHandle(void)
{
    gpPd_Handle_t pdHandle;
    for(pdHandle = 0; pdHandle < GP_PD_NR_OF_HANDLES; pdHandle++)
    {
        if(!PD_CHECK_HANDLE_IN_USE(pdHandle))
        {
            return pdHandle;
        }
    }
    return GP_PD_INVALID_HANDLE;
}

#if defined(GP_COMP_GPHAL) 
static UInt8 Pd_AllocatePBM(gpPd_Handle_t pdHandle,UInt16 size)
{
    UInt8 pbmHandle;
    pbmHandle = gpHal_GetHandle(size);
    if(!GP_HAL_CHECK_PBM_VALID(pbmHandle))
    {
        return GP_PBM_INVALID_HANDLE;
    }
    Pd_NmbrOfPbmsClaimedBySw++;
    Pd_Pbm2pd[pbmHandle] = pdHandle;
    return pbmHandle;
}
#endif

void* Pd_AllocatePdMemory(gpPd_Handle_t pdHandle, gpPd_BufferType_t type)
{
    UInt16 mallocsize;
    {
        mallocsize = sizeof(gpPd_Descriptor_t);
    }
    return GP_POOLMEM_MALLOC(mallocsize);
}

static gpPd_Handle_t Pd_GetPd(gpPd_BufferType_t type, UInt16 size)
{
    gpPd_Handle_t pdHandle = 0;

    if(!GP_PD_IS_BUFFERTYPE_VALID(type))
    {
        GP_LOG_SYSTEM_PRINTF("inv 1",0);
        return GP_PD_INVALID_HANDLE;
    }


    if(type == gpPd_BufferTypeZigBee)
    {
        // Make sure size is always 128 when using ZigBee, since current PD ram has only support for one size for all PDs
        GP_ASSERT_DEV_EXT(GP_PD_BUFFER_SIZE == 0x80);
    }
    pdHandle = Pd_AllocatePdHandle();
    if (pdHandle == GP_PD_INVALID_HANDLE)
    {
        GP_LOG_PRINTF("G 0xFF",0);
        return GP_PD_INVALID_HANDLE;
    }


    gpPd_Descriptors[pdHandle] = Pd_AllocatePdMemory(pdHandle, type);

    if (!gpPd_Descriptors[pdHandle])
    {
        GP_LOG_SYSTEM_PRINTF("No mem for Pd found",0);
        return GP_PD_INVALID_HANDLE;
    }

    gpPd_Descriptors[pdHandle]->type = type;
    return pdHandle;

}

static void Pd_FreePd(gpPd_Handle_t pdHandle)
{
    GP_LOG_PRINTF("F %i",0,(UInt16)pdHandle);

    if (pdHandle == GP_PD_INVALID_HANDLE)
    {
        return;
    }

    if (( pdHandle < GP_PD_NR_OF_HANDLES ) && gpPd_Descriptors[pdHandle] != NULL )
    {
        gpPoolMem_Free(gpPd_Descriptors[pdHandle]);
        gpPd_Descriptors[pdHandle] = NULL;
#if defined(GP_COMP_GPHAL) 
        {
        UInt8 pbmHandle;
        for(pbmHandle = 0; pbmHandle < GPHAL_NUMBER_OF_PBMS_USED; pbmHandle++)
        {
            if(Pd_Pbm2pd[pbmHandle] == pdHandle)
            {
                Pd_Pbm2pd[pbmHandle] = GP_PD_INVALID_HANDLE;
            }
        }
        }
#endif


        return;
    }
    else
    {
        GP_ASSERT_DEV_EXT(false); //Make no fun about freeing unused handles!
    }
}
#if defined(GP_COMP_GPHAL) 
static void Pd_FreePBM(UInt8 pbmHandle)
{
    GP_ASSERT_DEV_EXT(Pd_NmbrOfPbmsClaimedBySw);
    Pd_NmbrOfPbmsClaimedBySw--;
    gpHal_FreeHandle(pbmHandle);
    Pd_Pbm2pd[pbmHandle] = GP_PD_INVALID_HANDLE;
#if defined(GP_COMP_UNIT_TEST)
    if( Pd_NmbrOfPbmsClaimedBySw == 0 )
    {
        gpHal_GoToSleepWhenIdle(true);
    }
#endif // GP_DIVERSITY_GPHAL_EXTERN
}

static UInt8 Pd_GetPBM( UInt8 pdHandle )
{
    UInt8 pbmHandle;

    GP_ASSERT_DEV_EXT(PD_CHECK_HANDLE_ACCESSIBLE(pdHandle));

    //Check if pdHandle is already in table
    for(pbmHandle = 0; pbmHandle < GPHAL_NUMBER_OF_PBMS_USED; pbmHandle++)
    {
        if(Pd_Pbm2pd[pbmHandle] == pdHandle)
        {
            //Would indicate duplicate use of handle for request
            GP_LOG_SYSTEM_PRINTF("pbm %u<>handle %u exists",0, pbmHandle, pdHandle);
            GP_ASSERT_DEV_EXT(false);
            return GP_PBM_INVALID_HANDLE;
        }
    }
#if defined(GP_COMP_UNIT_TEST)
    if(Pd_NmbrOfPbmsClaimedBySw == 0)
    {
        gpHal_GoToSleepWhenIdle(false);
    }
#endif // GP_DIVERSITY_GPHAL_EXTERN
    //Allocate PBM
//#warning implement size for gppd ram - SW-4772
    pbmHandle = Pd_AllocatePBM(pdHandle, PD_TMP_SIZE);
    if(!GP_HAL_CHECK_PBM_VALID(pbmHandle))
    {
#if defined(GP_COMP_UNIT_TEST)
        if(Pd_NmbrOfPbmsClaimedBySw == 0)
        {
            gpHal_GoToSleepWhenIdle(true);
        }
#endif // GP_DIVERSITY_GPHAL_EXTERN
        return GP_PBM_INVALID_HANDLE;
    }

    return pbmHandle;
}

gpPd_Handle_t Pd_GetPdFromPBM(UInt8 pbmHandle)
{
    //Protect out of range access
    if(pbmHandle >= GPHAL_NUMBER_OF_PBMS_USED)
    {
        return GP_PD_INVALID_HANDLE;
    }

    return Pd_Pbm2pd[pbmHandle];
}
#endif //defined(GP_COMP_GPHAL) && !defined(GP_DIVERSITY_GPHAL_COPROC)

static gpPd_Result_t Pd_CheckPdValid(gpPd_Handle_t pdHandle)
{
    gpPd_Result_t result = gpPd_ResultValidHandle;

    if(!PD_CHECK_HANDLE_VALID(pdHandle))
    {
        result = gpPd_ResultInvalidHandle;
    }
    else if(!PD_CHECK_HANDLE_IN_USE(pdHandle))
    {
        result = gpPd_ResultNotInUse;
    }
    GP_LOG_PRINTF("Chck %i %i",0,(UInt16)pdHandle, (UInt16)result);

    return result;
}

gpPd_BufferType_t Pd_GetPdType(gpPd_Handle_t pdHandle)
{
    PD_CHECK_HANDLE_INPUT_WITH_RETURN(pdHandle, gpPd_BufferTypeInvalid);
    return gpPd_Descriptors[pdHandle]->type;
}

//------------------------------
// Data
//------------------------------

static UInt8 Pd_ReadByte(gpPd_Handle_t pdHandle, gpPd_Offset_t offset)
{
    GP_LOG_PRINTF("R %i %i",0,(UInt16)pdHandle, (UInt16)offset);
    PD_CHECK_HANDLE_INPUT_WITH_RETURN(pdHandle, 0xFF);

    if(gpPd_Descriptors[pdHandle]->type == gpPd_BufferTypeZigBee)
    {
        PD_WRAP_OFFSET(offset);
    }

    return gpPd_Descriptors[pdHandle]->buffer[offset];
}

static void Pd_WriteByte(gpPd_Handle_t pdHandle, gpPd_Offset_t offset, UInt8 byte)
{
    GP_LOG_PRINTF("W %i %i %x access %x",0,(UInt16)pdHandle, (UInt16)offset, (UInt16)byte, PD_CHECK_HANDLE_ACCESSIBLE(pdHandle) );
    PD_CHECK_HANDLE_INPUT_NO_RETURN(pdHandle);

    if(gpPd_Descriptors[pdHandle]->type == gpPd_BufferTypeZigBee)
    {
        PD_WRAP_OFFSET(offset);
    }

    gpPd_Descriptors[pdHandle]->buffer[offset] = byte;
}

static void Pd_ReadByteStream(gpPd_Handle_t pdHandle, gpPd_Offset_t offset, UInt8 length, UInt8* pData)
{
    UInt8 splitlength = 0;
    GP_LOG_PRINTF("RS %i %i %i",0,(UInt16)pdHandle, (UInt16)offset, (UInt16)length);
    PD_CHECK_HANDLE_INPUT_NO_RETURN(pdHandle);

    if(gpPd_Descriptors[pdHandle]->type == gpPd_BufferTypeZigBee)
    {
        PD_WRAP_OFFSET(offset);
        // Out of bounds: 2 times memcpy (before and after cyclic part)
        if(offset + length > GP_PD_BUFFER_SIZE)
        {
            // split in 2
            splitlength = (length + offset) - GP_PD_BUFFER_SIZE ;
            // read first part of pd and copy it to second part of pData
            MEMCPY( &pData[length-splitlength] , &gpPd_Descriptors[pdHandle]->buffer[0] , splitlength);
        }
    }

    // write first part or full part
    MEMCPY( pData , &gpPd_Descriptors[pdHandle]->buffer[offset] , length-splitlength);
}

static void Pd_WriteByteStream(gpPd_Handle_t pdHandle, gpPd_Offset_t offset, UInt8 length, UInt8* pData)
{
    UInt8 splitlength = 0;
    GP_LOG_PRINTF("WS %i %i %i",0,(UInt16)pdHandle, (UInt16)offset, (UInt16)length);
    PD_CHECK_HANDLE_INPUT_NO_RETURN(pdHandle);

    if(gpPd_Descriptors[pdHandle]->type == gpPd_BufferTypeZigBee)
    {
        PD_WRAP_OFFSET(offset);
        // Out of bounds: 2 times memcpy (before and after cyclic part)
        if(offset + length > GP_PD_BUFFER_SIZE)
        {
            // split in 2
            splitlength = (length + offset) - GP_PD_BUFFER_SIZE ;
            // write second part of pData to first part of pd.
            //          to address 0,                    , from &pData[length-splitLength]  , splitLength
            MEMCPY(&gpPd_Descriptors[pdHandle]->buffer[0] , &pData[length-splitlength] , splitlength);
        }
    }

    // write first part or full part
    MEMCPY(&gpPd_Descriptors[pdHandle]->buffer[offset], pData, length-splitlength);
}

//------------------------------
// Attributes
//------------------------------

static gpPd_Rssi_t Pd_GetRssi(gpPd_Handle_t pdHandle)
{
    PD_CHECK_HANDLE_INPUT_WITH_RETURN(pdHandle, 0);
    return gpPd_Descriptors[pdHandle]->attr.rx.rssi;
}

static void Pd_SetRssi(gpPd_Handle_t pdHandle, gpPd_Rssi_t rssi)
{
    PD_CHECK_HANDLE_INPUT_NO_RETURN(pdHandle);
    gpPd_Descriptors[pdHandle]->attr.rx.rssi = rssi;
}

static gpPd_Lqi_t Pd_GetLqi(gpPd_Handle_t pdHandle)
{
    PD_CHECK_HANDLE_INPUT_WITH_RETURN(pdHandle, 0);
    return gpPd_Descriptors[pdHandle]->attr.rx.lqi;
}

static void Pd_SetLqi(gpPd_Handle_t pdHandle, gpPd_Lqi_t lqi)
{
    PD_CHECK_HANDLE_INPUT_NO_RETURN(pdHandle);
    gpPd_Descriptors[pdHandle]->attr.rx.lqi = lqi;
}

static UInt32 Pd_GetRxTimestamp(gpPd_Handle_t pdHandle)
{
    PD_CHECK_HANDLE_INPUT_WITH_RETURN(pdHandle, 0);
    return gpPd_Descriptors[pdHandle]->attr.rx.rxTimestamp;
}

#ifndef GP_MACDISPATCHER_DIVERSITY_GPCOM_CLIENT
static UInt32 Pd_GetRxTimestampChip(gpPd_Handle_t pdHandle)
{
    PD_CHECK_HANDLE_INPUT_WITH_RETURN(pdHandle, 0);
    return gpPd_Descriptors[pdHandle]->attr.rx.rxTimestampChip;
}
#endif /* GP_MACDISPATCHER_DIVERSITY_GPCOM_CLIENT */

static void Pd_SetRxTimestamp(gpPd_Handle_t pdHandle, gpPd_TimeStamp_t timestamp)
{
    PD_CHECK_HANDLE_INPUT_NO_RETURN(pdHandle);
    gpPd_Descriptors[pdHandle]->attr.rx.rxTimestamp = timestamp;
}

static UInt32 Pd_GetTxTimestamp(gpPd_Handle_t pdHandle)
{
    PD_CHECK_HANDLE_INPUT_WITH_RETURN(pdHandle, 0);
    return gpPd_Descriptors[pdHandle]->attr.txcfm.txTimestamp;
}

static void Pd_SetTxTimestamp(gpPd_Handle_t pdHandle, gpPd_TimeStamp_t timestamp)
{
    PD_CHECK_HANDLE_INPUT_NO_RETURN(pdHandle);
    gpPd_Descriptors[pdHandle]->attr.txcfm.txTimestamp = timestamp;
}

static UInt16* Pd_GetPhaseSamplesBuffer(gpPd_Handle_t pdHandle)
{
    NOT_USED(pdHandle);
    return NULL;
}

static gpPd_Lqi_t Pd_GetTxAckLqi(gpPd_Handle_t pdHandle)
{
    PD_CHECK_HANDLE_INPUT_WITH_RETURN(pdHandle, 0);
    return gpPd_Descriptors[pdHandle]->attr.txcfm.ackLqi;
}

static UInt8 Pd_GetTxCCACntr(gpPd_Handle_t pdHandle)
{
    PD_CHECK_HANDLE_INPUT_WITH_RETURN(pdHandle, 0);
    return gpPd_Descriptors[pdHandle]->attr.txcfm.txCCACntr;
}

static UInt8 Pd_GetTxRetryCntr(gpPd_Handle_t pdHandle)
{
    PD_CHECK_HANDLE_INPUT_WITH_RETURN(pdHandle, 0);
    return gpPd_Descriptors[pdHandle]->attr.txcfm.txRetryCntr;

}

static void Pd_SetTxRetryCntr(gpPd_Handle_t pdHandle, UInt8 txRetryCntr)
{
    PD_CHECK_HANDLE_INPUT_NO_RETURN(pdHandle);
    gpPd_Descriptors[pdHandle]->attr.txcfm.txRetryCntr = txRetryCntr;
}

static UInt8 Pd_GetFramePendingAfterTx(gpPd_Handle_t pdHandle)
{
    PD_CHECK_HANDLE_INPUT_WITH_RETURN(pdHandle, 0);
    return gpPd_Descriptors[pdHandle]->attr.txcfm.framePendingFromTxPbm;

}

static void Pd_SetFramePendingAfterTx(gpPd_Handle_t pdHandle, UInt8 framePending)
{
    PD_CHECK_HANDLE_INPUT_NO_RETURN(pdHandle);
    gpPd_Descriptors[pdHandle]->attr.txcfm.framePendingFromTxPbm = framePending;

}

static UInt8 Pd_GetRxChannel(gpPd_Handle_t pdHandle)
{
    PD_CHECK_HANDLE_INPUT_WITH_RETURN(pdHandle, 0);
    return gpPd_Descriptors[pdHandle]->attr.rx.rxChannel;

}

static void Pd_SetRxChannel(gpPd_Handle_t pdHandle, UInt8 rxChannel)
{
    PD_CHECK_HANDLE_INPUT_NO_RETURN(pdHandle);
    gpPd_Descriptors[pdHandle]->attr.rx.rxChannel = rxChannel;

}
//------------------------------
// Helper functions
//------------------------------

static gpPd_Handle_t Pd_CopyPd(gpPd_Handle_t pdHandle)
{
    gpPd_Handle_t pdHandleCopy;

    PD_CHECK_HANDLE_INPUT_WITH_RETURN(pdHandle, GP_PD_INVALID_HANDLE);
    pdHandleCopy = gpPd_GetPd();
    if(pdHandleCopy != GP_PD_INVALID_HANDLE )
    {
        MEMCPY( &gpPd_Descriptors[pdHandleCopy]->attr,  &gpPd_Descriptors[pdHandle]->attr, sizeof(gpPd_Descriptors[pdHandle]->attr));
        MEMCPY( gpPd_Descriptors[pdHandleCopy]->buffer, gpPd_Descriptors[pdHandle]->buffer, GP_PD_BUFFER_SIZE);
    }
    return pdHandleCopy;
}

#if defined(GP_COMP_GPHAL) 
static void Pd_RestoreFromPbm(UInt8 pbmHandle, UInt8 pbmOffset, UInt8 pbmLength, gpPd_Handle_t pdHandle)
{
    gpHal_Address_t address;
    UInt8 splitlength = 0;

    address = GP_HAL_PBM_ENTRY2ADDR(pbmHandle);

    if(gpPd_Descriptors[pdHandle]->type == gpPd_BufferTypeZigBee)
    {
        PD_WRAP_OFFSET(pbmOffset);
        // copy PBM -> RAM
        // if PBM is cyclic PD should also be cyclic (exact copy): Copy to 2 parts
        if(pbmOffset + pbmLength > GP_PD_BUFFER_SIZE)
        {
            // split in 2
            splitlength = (pbmOffset + pbmLength) - GP_PD_BUFFER_SIZE;
            GP_HAL_READ_DATA_IN_PBM(address, gpPd_Descriptors[pdHandle]->buffer, splitlength, 0);
        }
    }

    // write first part or full part
    GP_HAL_READ_DATA_IN_PBM(address, &gpPd_Descriptors[pdHandle]->buffer[pbmOffset], (pbmLength - splitlength), pbmOffset);
}

static void Pd_CopyToPbm(UInt8 pbmHandle, UInt8 offset, UInt8 length)
{
    UInt8 splitLength = 0;
    gpPd_Handle_t pdHandle;
    gpHal_Address_t address = GP_HAL_PBM_ENTRY2ADDR(pbmHandle);

    pdHandle = Pd_GetPdFromPBM(pbmHandle);
    GP_ASSERT_DEV_EXT(PD_CHECK_HANDLE_ACCESSIBLE(pdHandle));

    if(gpPd_Descriptors[pdHandle]->type == gpPd_BufferTypeZigBee)
    {
        if(offset + length > GP_PD_BUFFER_SIZE)
        {// split in 2
            splitLength = (offset + length) - GP_PD_BUFFER_SIZE;
            GP_HAL_WRITE_DATA_IN_PBM(address, gpPd_Descriptors[pdHandle]->buffer, splitLength, 0);
        }
    }

    // write first part or full part
    GP_HAL_WRITE_DATA_IN_PBM(address, &gpPd_Descriptors[pdHandle]->buffer[offset], length-splitLength,offset);
}

//--------------------
// Request/indications
//--------------------

static UInt8 Pd_DataRequest(gpPd_Loh_t *p_PdLoh)
{
    UInt8 pbmHandle;
    GP_ASSERT_DEV_EXT(p_PdLoh);

    pbmHandle = Pd_GetPBM(p_PdLoh->handle);
    if(!GP_HAL_CHECK_PBM_VALID(pbmHandle))
    {
        return GP_PD_INVALID_HANDLE;
    }

    if(gpPd_Descriptors[p_PdLoh->handle]->type == gpPd_BufferTypeZigBee)
    {
        PD_WRAP_OFFSET(p_PdLoh->offset);
    }
    {
        // Copy RAM -> PBM
        Pd_CopyToPbm(pbmHandle,p_PdLoh->offset,p_PdLoh->length);
    }

    return pbmHandle;
}



static void Pd_DataIndication(UInt8 pbmHandle, gpPd_Offset_t pbmOffset, gpPd_Length_t pbmLength, gpPd_Loh_t *p_PdLoh, gpPd_BufferType_t type)
{
    GP_ASSERT_DEV_EXT(p_PdLoh);
    // get RAM PD
    // This should be the max RX size (chip dependent)

    {
        p_PdLoh->handle = Pd_GetPd(type, GP_PD_BUFFER_SIZE);
    }

    if( p_PdLoh->handle != GP_PD_INVALID_HANDLE )
    {
        gpPd_TimeStamp_t rxTimeStampChip;
        gpPd_TimeStamp_t currentChipTime;
        UInt32 currentHostTime;

        gpPd_Descriptors[p_PdLoh->handle]->type = type;

        // Copy PBM -> RAM
        Pd_RestoreFromPbm(pbmHandle, pbmOffset, pbmLength, p_PdLoh->handle);
        p_PdLoh->offset = pbmOffset;
        p_PdLoh->length = pbmLength;

        // copy LQI, RSSI, rx channel
        gpPd_Descriptors[p_PdLoh->handle]->attr.rx.lqi = gpHal_GetLQI(pbmHandle);
        gpPd_Descriptors[p_PdLoh->handle]->attr.rx.rssi = gpHal_GetRSSI(pbmHandle);
        gpPd_Descriptors[p_PdLoh->handle]->attr.rx.rxChannel = gpHal_GetRxedChannel(pbmHandle);

        // Get timestamp + correct
        gpHal_GetRxTimestamp(pbmHandle, &rxTimeStampChip);
        gpPd_Descriptors[p_PdLoh->handle]->attr.rx.rxTimestampChip = rxTimeStampChip;

        // convert "chip time basis" to "host time basis"
        gpHal_GetTime(&currentChipTime);
        HAL_TIMER_GET_CURRENT_TIME_1US(currentHostTime);
        gpPd_Descriptors[p_PdLoh->handle]->attr.rx.rxTimestamp = currentHostTime - (currentChipTime - rxTimeStampChip);

    }
    {
        // Free PBM
        gpHal_FreeHandle(pbmHandle);
    }
}

static UInt8 Pd_SecRequest(gpPd_Handle_t pdHandle, UInt8 dataOffset, UInt8 dataLength, UInt8 auxOffset, UInt8 auxLength )
{
    UInt8 pbmHandle;

    //Allocate PBM
    pbmHandle = Pd_GetPBM(pdHandle);
    if(!GP_HAL_CHECK_PBM_VALID(pbmHandle))
    {
        return GP_PBM_INVALID_HANDLE;
    }

    if(gpPd_Descriptors[pdHandle]->type == gpPd_BufferTypeZigBee)
    {
        PD_WRAP_OFFSET(dataOffset);
        PD_WRAP_OFFSET(auxOffset);
    }

    if(dataLength > 0)
    {
        //Copy data
        Pd_CopyToPbm(pbmHandle,dataOffset,dataLength);
    }
    if(auxLength > 0)
    {
        //Copy aux
        Pd_CopyToPbm(pbmHandle,auxOffset,auxLength);
    }
    return pbmHandle;
}

static gpPd_Handle_t Pd_cbSecConfirm(UInt8 pbmHandle, UInt8 dataOffset, UInt8 dataLength)
{
    // Get previous claimed RAM PD
    gpPd_Handle_t pdHandle;

    pdHandle = Pd_GetPdFromPBM(pbmHandle);
    PD_CHECK_HANDLE_INPUT_WITH_RETURN(pdHandle, GP_PD_INVALID_HANDLE);

    if(gpPd_Descriptors[pdHandle]->type == gpPd_BufferTypeZigBee)
    {
        PD_WRAP_OFFSET(dataOffset);
    }
    {
        // Copy PBM -> RAM
        Pd_RestoreFromPbm(pbmHandle, dataOffset, dataLength, pdHandle);
        // free PBM and keep lookup table clean
        Pd_FreePBM(pbmHandle);
    }

    return pdHandle;
}

static UInt8 Pd_PurgeRequest(gpPd_Handle_t pdHandle)
{
    UInt8 pbmHandle;
    //check if Pd valid
    PD_CHECK_HANDLE_INPUT_WITH_RETURN(pdHandle, GP_PD_INVALID_HANDLE);

    //Lookup corresponding PBM from Pd
    for (pbmHandle = 0; pbmHandle < GPHAL_NUMBER_OF_PBMS_USED; pbmHandle++)
    {
        if (Pd_Pbm2pd[pbmHandle] == pdHandle && PBM_CHECK_HANDLE_ACCESSIBLE(pbmHandle))
        {
            return pbmHandle;
        }
    }
    //Invalid Pd given.
    GP_LOG_PRINTF("PdHandle %x not found!",0,pdHandle);
    return GP_PD_INVALID_HANDLE;
}

static void Pd_cbPurgeConfirm(UInt8 pbmHandle)
{
    gpPd_Handle_t pdHandle;

    //Check associated pdHandle
    pdHandle = Pd_GetPdFromPBM(pbmHandle);

    PD_CHECK_HANDLE_INPUT_NO_RETURN(pdHandle);

    //Free PBM and keep lookup table free
    Pd_FreePBM(pbmHandle);
}

#endif //defined(GP_COMP_GPHAL) && !defined(GP_DIVERSITY_GPHAL_COPROC)

