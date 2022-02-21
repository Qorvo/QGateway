/*
 * Copyright (c) 2010, 2012-2016, GreenPeak Technologies
 * Copyright (c) 2017, Qorvo Inc
 *
 * hal.c
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
 * $Header: //depot/release/Embedded/Components/Qorvo/HAL_PLATFORM/v2.10.2.0/comps/halLinux/user/src/hal_noradio.c#1 $
 * $Change: 187624 $
 * $DateTime: 2021/12/20 10:58:50 $
 *
 */

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/
#include "hal.h"
#include "hal_defs.h"
#ifdef GP_COMP_BSP
#include "gpBsp.h"
#endif //GP_COMP_BSP
#include "gpAssert.h"
#ifdef GP_COMP_CHIPEMU
#include "gpChipEmu.h"
#ifdef GP_COMP_GPHAL
#include "gpHal.h"
#endif //GP_COMP_GPHAL
#endif //GP_COMP_CHIPEMU

#include <stdio.h>
#include <string.h>
#include "gpLog.h"

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/
#define GP_COMPONENT_ID GP_COMPONENT_ID_HALLINUX

/*****************************************************************************
 *                    Type Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Static Data Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Public Data Definitions
 *****************************************************************************/
UInt8 l_n_atomic;

#ifdef GP_COMP_CHIPEMU
Bool bsp_linux_intena;
Bool bsp_linux_int;
hal_PollFunction_t gphal_cb;
#endif

/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/

#ifdef GP_COMP_CHIPEMU // GP_COMP_CHIPEMU
#define ENABLE_RADIO_INT()          do { bsp_linux_intena = true; } while (0)
#define DISABLE_RADIO_INT()         do { bsp_linux_intena = false; } while (0)
#define CLEAR_RADIO_INT()           do { bsp_linux_int = false; } while (0)
#define CHECK_RADIO_INT()           (bsp_linux_int)
#define IS_ENABLED_RADIO_INT()      (bsp_linux_intena)
#endif // GP_COMP_CHIPEMU

void hal_Init (void)
{
    setlinebuf(stdout);
    setlinebuf(stderr);

    halSched_Init();

    HAL_LED_INIT();
    HAL_BTN_INIT();
#ifdef GP_COMP_BSP
    gpBsp_init();
#endif //GP_COMP_BSP
#ifdef GP_DIVERSITY_BACKTRACE_ON_EXCEPTION
    hal_install_exception_handlers();
#endif //GP_DIVERSITY_BACKTRACE_ON_SIGNAL

#if defined(GP_COMP_GPHAL) && defined(GP_COMP_CHIPEMU)
//For emulation testing
    HAL_GP_HW_INIT();
#ifdef GP_COMP_GPHAL
    gpHal_Reset();
#endif
#endif //defined(GP_COMP_GPHAL) && defined(GP_COMP_CHIPEMU)
}

void hal_DeInit(void)
{
    halSched_DeInit();
}

void hal_Trigger_Wakeup(void)
{
#ifdef GP_COMP_CHIPEMU
    gpChipEmu_WakeUp_External();
#endif //GP_COMP_CHIPEMU
}

Bool hal_HandleRadioInterrupt(Bool execute)
{
#ifndef GP_COMP_CHIPEMU
    NOT_USED(execute);
#endif
#ifdef GP_COMP_CHIPEMU
    if (bsp_linux_int)
    {
        if(execute && (NULL != gphal_cb))
        {
            gphal_cb(1);
            CLEAR_RADIO_INT();
        }
        return true;
    }
#endif
    return false;
}

#ifdef GP_COMP_CHIPEMU
void hal_RegisterGPPollFunction(hal_PollFunction_t pollFunction)
{
    gphal_cb = pollFunction;
}

void hal_update_interrupt(void)
{
    UInt8 interrupt = gpChipEmu_GetInterruptPin();
    bsp_linux_int = !!interrupt;
}
#endif //GP_COMP_CHIPEMU

