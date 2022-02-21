#ifndef _GPBSP_IF_LINUX_GENERAL_H_
#define _GPBSP_IF_LINUX_GENERAL_H_

/*
 * Copyright (c) 2010-2014, GreenPeak Technologies
 * Copyright (c) 2017, Qorvo Inc
 *
 * gpBsp_if_linux_general_32kHZ.h
 *   Board support package for linux based devices with RD05
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
 * $Header: //depot/release/Embedded/Components/Qorvo/BSP/v2.10.2.0/comps/gpBspCommon/inc/gpBsp_if_linux_general_32kHZ.h#1 $
 * $Change: 187624 $
 * $DateTime: 2021/12/20 10:58:50 $
 *


 */

/*****************************************************************************
 *                    BSP configuration interface
 *****************************************************************************/

// Chip driver should support reset pin usage
#define GP_BSP_RESET_PIN_USED() 1

#define GP_BSP_32KHZ_CRYSTAL_AVAILABLE() 1

#define GP_BSP_USE_WDT_TIMER() 0

/*****************************************************************************
 *                    Radio interface
 *****************************************************************************/

#define GP_INT_IS_1             0
#define CLEAR_RADIO_INT()
#define CONFIG_INTERRUPT_LINE()

#define BSP_INIT()

/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/
/*****************************************************************************
 *                    SCOM Definitions
 *****************************************************************************/
#define GP_BSP_UART_SCOM_BAUDRATE      115200


void gpBsp_init(void);

#endif  // _GPBSP_IF_LINUX_GENERAL_H_

