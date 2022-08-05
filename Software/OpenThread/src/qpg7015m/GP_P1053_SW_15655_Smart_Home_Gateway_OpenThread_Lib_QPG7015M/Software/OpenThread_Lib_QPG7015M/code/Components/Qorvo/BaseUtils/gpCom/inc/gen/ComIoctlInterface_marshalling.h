
/*
 * Copyright (c) 2017, Qorvo Inc
 *
 *   This file contains the implementation of the ComIoctlInterface API protocol.
 *
 *
 *   Marshalling structures and functions
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
 * $Header: //depot/main/Embedded/Components/Qorvo/BaseUtils/v2.10.3.1/comps/gpCom/inc/gen/ComIoctlInterface_marshalling.h#1 $
 * $Change: 195340 $
 * $DateTime: 2022/06/17 14:57:48 $
 *
 */


#ifndef _COMIOCTLINTERFACE_MARSHALLING_H_
#define _COMIOCTLINTERFACE_MARSHALLING_H_

//DOCUMENTATION COMIOCTLINTERFACE: no @file required as all documented items are refered to a group

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/
#include <global.h>
#include "ComIoctlInterface.h"

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Type Definitions
 *****************************************************************************/




typedef struct {
    UInt8 moduleID;
    UInt32 commId;
    UInt16 length;
    UInt8* pIoctlPayload;
} writeMsg_Input_struct_t;

typedef struct {
    writeMsg_Input_struct_t data;
    UInt8 pIoctlPayload[GP_COM_MAX_PACKET_PAYLOAD_SIZE];
} writeMsg_Input_marshall_struct_t;

typedef struct {
    UInt16 maxLength;
} readMsg_Input_struct_t;

typedef struct {
    readMsg_Input_struct_t data;
} readMsg_Input_marshall_struct_t;

typedef struct {
    UInt8* moduleID;
    UInt32* commId;
    UInt16* length;
    UInt8* pIoctlPayload;
} readMsg_Output_struct_t;

typedef struct {
    readMsg_Output_struct_t data;
    UInt8 moduleID[1];
    UInt32 commId[1];
    UInt16 length[1];
    UInt8 pIoctlPayload[GP_COM_MAX_PACKET_PAYLOAD_SIZE];
} readMsg_Output_marshall_struct_t;


typedef union {
    writeMsg_Input_marshall_struct_t writeMsg;
    readMsg_Input_marshall_struct_t readMsg;
} ComIoctlInterface_Server_Input_union_t;

typedef union {
    readMsg_Output_marshall_struct_t readMsg;
} ComIoctlInterface_Server_Output_union_t;

/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

// Alias/enum copy macro's

// Structure copy functions

// Server functions
gpMarshall_AckStatus_t writeMsg_Input_buf2api( writeMsg_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex );
gpMarshall_AckStatus_t readMsg_Input_buf2api( readMsg_Input_marshall_struct_t* pDest , UInt8Buffer* pSource , UInt16* pIndex );
void readMsg_Output_api2buf( UInt8Buffer* pDest , readMsg_Output_marshall_struct_t* pSourceoutput , readMsg_Input_marshall_struct_t* pSourceinput , UInt16* pIndex );

// Client functions
void writeMsg_Input_par2buf( UInt8Buffer* pDest , UInt8 moduleID , UInt32 commId , UInt16 length , UInt8* pIoctlPayload , UInt16* pIndex );
void readMsg_Input_par2buf( UInt8Buffer* pDest , UInt16 maxLength , UInt16* pIndex );
void readMsg_Output_buf2par( UInt16 maxLength , UInt8* moduleID , UInt32* commId , UInt16* length , UInt8* pIoctlPayload , UInt8Buffer* pSource , UInt16* pIndex );

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // _COMIOCTLINTERFACE_MARSHALLING_H_


