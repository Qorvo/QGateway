/*
 * Copyright (c) 2020, Qorvo Inc
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
 * $Header: //depot/main/Embedded/Components/Qorvo/HAL_PLATFORM/v2.10.3.1/comps/halLinux/user/src/hal_Heap.c#1 $
 * $Change: 195340 $
 * $DateTime: 2022/06/17 14:57:48 $
 *
 */

/** @file "hal_Heap.c"
 *
 *  Heap analysis functionality
*/

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

//#define DEBUG

#include "hal.h"
#include <malloc.h>

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/

#define GP_COMPONENT_ID GP_COMPONENT_ID_HALLINUX

/*****************************************************************************
 *                    Public Function Implementations
 *****************************************************************************/

void hal_GetHeapInUse(UInt32* pInUse, UInt32* pReserved, UInt32* pMax)
{
    //No Heap
    *pInUse = 0x0;
    *pReserved = 0x0;
    *pMax = 0x0;
}
