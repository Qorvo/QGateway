/*
 * Copyright (c) 2010, 2013-2016, GreenPeak Technologies
 * Copyright (c) 2017, Qorvo Inc
 *
 * hal_defs.h
 *   Hardware Abstraction Layer for linux based devices.
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
 * $Header: //depot/main/Embedded/Components/Qorvo/HAL_PLATFORM/v2.10.3.1/comps/halLinux/user/src/hal_defs.h#1 $
 * $Change: 195340 $
 * $DateTime: 2022/06/17 14:57:48 $
 *
 */

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/
#include "hal.h"
#include <sys/socket.h>

/*****************************************************************************
 *                    Type Definitions
 *****************************************************************************/
typedef enum
{
    halSocket_state_idle,
    halSocket_state_active,
    halSocket_state_exited
} halSocket_state_t;

typedef struct
{
    UInt32 socketId;
    halSocket_state_t state;
    Bool isClient;
    struct sockaddr addr;
    pthread_t rfReadThread;
} halSocket_t;

/*****************************************************************************
 *                    Public Data Declarations
 *****************************************************************************/
#if defined(GP_COMP_CHIPEMU)
extern UInt64 hal_ClockCounter;
#endif //GP_COMP_UNIT_TEST

/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/

void halSched_Init(void);
void halSched_DeInit(void);

 void halSocket_RegisterPollFunction(int fd);
 void* halSocket_readThread(void *pClientSocketId);
 int hal_GetServerSocket(halSocket_t* socketInfo, char* host, int port);
 int halSocket_ListenForClients(char *path, int port);

int halUART_SetNonSpecialBaudRate(int fd, UInt32 baudrate);
