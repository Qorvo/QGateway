
#ifndef _GPBSP_LINUX_USER_H_
#define _GPBSP_LINUX_USER_H_

/*
 * Copyright (c) 2012-2014, 2016, GreenPeak Technologies
 * Copyright (c) 2017, Qorvo Inc
 *
 * gpBsp_linux_user.h
 *   This file stubs gpBsp macro's for Pc unit tests
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
 * $Header: //depot/main/Embedded/Components/Qorvo/BSP/v2.10.3.1/comps/gpBsp/inc/gpBsp_linux_user.h#1 $
 * $Change: 195340 $
 * $DateTime: 2022/06/17 14:57:48 $
 *
 */

/*****************************************************************************
 *                    BSP configuration interface
 *****************************************************************************/

#define GP_BSP_32KHZ_CRYSTAL_AVAILABLE() (0)
#define BSP_INIT()
#define GP_INT_IS_1 (0)
#define CONFIG_INTERRUPT_LINE()

void gpBsp_init(void);


#endif   //_GPBSP_LINUX_USER_H_

