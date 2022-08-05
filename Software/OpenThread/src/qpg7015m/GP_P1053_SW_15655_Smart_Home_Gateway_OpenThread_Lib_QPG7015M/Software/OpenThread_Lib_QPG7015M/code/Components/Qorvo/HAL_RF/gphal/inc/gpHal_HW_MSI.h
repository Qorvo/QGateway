/*
 * Copyright (c) 2009-2016, GreenPeak Technologies
 * Copyright (c) 2017, Qorvo Inc
 *
 * gpHal_HW_MSI.h
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
 * $Header: //depot/main/Embedded/Components/Qorvo/HAL_RF/v2.10.3.1/comps/gphal/inc/gpHal_HW_MSI.h#1 $
 * $Change: 195340 $
 * $DateTime: 2022/06/17 14:57:48 $
 *
 */

#ifndef _GPHAL_HW_MSI_H_
#define _GPHAL_HW_MSI_H_

/**
 * @file gpHal_HW_MSI.h
 * @brief This file contains the functions dependent on the choice of MCU : MSI, Interrupts,...
 * This particular file does it using the MSI protcol + our own hal functionality
 */

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

#include "gpBsp.h"       //uC MSI (SPI/I2C) functions
#include "hal.h"         //uC INT functions

//this header implements GP_HAL_READ_REG, GP_HAL_WRITE_REG etc.
#include "gpHal_MSI.h"
//Get chip specific MSI definitions
#include "gpHal_reg.h"

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/

/*****************************************************************************
 *                   Functional Macro Definitions
 *****************************************************************************/
//------------------------------------------------------------------------------

//Initialize MSI and wakeup,interrupt and reset pins
/** @brief Micro processor dependent macro to initialize communication interface and reset,interrupt and wakeup pins. */
#define HAL_GP_HW_INIT()           { HAL_WKUP_START(); HAL_SET_RESET_INACTIVE(); GP_MSI_INIT(); CONFIG_INTERRUPT_LINE(); }

//------------------------------------------------------------------------------
//  INTERRUPT CONTROL COMMANDS
//------------------------------------------------------------------------------

#ifndef HAL_ISR_RADIO_INTERRUPT_START
#define HAL_ISR_RADIO_INTERRUPT_START(x)    // not implemented yet for all ucHal variants
#endif

//Register interrupt GP
/** @brief Intializes the interrupt line at micro processor side.
 *
 * This macro configures the pin on which the GP chip INTOUTn pin is connected as an input pin and configures the interrupt
 * attached to this pin as a low level interrupt.
*/
#define HAL_GP_INTERRUPT_INIT()                        \
    do {                                               \
        HAL_ISR_RADIO_INTERRUPT_START( gpHal_ISR_Interrupt );  \
        HAL_RADIO_INTERRUPT_START( gpHal_Interrupt );  \
    } while(0)
//------------------------------------------------------------------------------
//  I/O CONTROL COMMANDS
//------------------------------------------------------------------------------

/** @brief Puts a high signal on the WKUP pin of the GP chip.
 *
 * Wakeup of the GP chip is done on a falling edge of the WKUP pin.
*/
#define HAL_GP_SET_WAKEUP()         HAL_SET_WKUP_ACTIVE()
/** @brief Puts a low signal on the WKUP pin of the GP chip.
 *
 * Wakeup of the GP chip is done on a falling edge of the WKUP pin.
*/
#define HAL_GP_CLR_WAKEUP()         HAL_SET_WKUP_INACTIVE()


#define HAL_GP_PULSE_WAKEUP() \
do{                     \
    HAL_GP_SET_WAKEUP();\
    HAL_GP_CLR_WAKEUP();\
}while(false);

/** @brief Sets the reset of the GP chip active.
 *
 * This macro sets and holds the GP chip in a reset state.
 */
#define HAL_GP_SET_RESET(level)     HAL_SET_RESET_ACTIVE(level)
/** @brief Puts the reset of the GP chip inactive
 *
 * This macro releases the reset of the GP chip.
*/
#define HAL_GP_CLR_RESET()          HAL_SET_RESET_INACTIVE()

#endif  /* _GPHAL_HW_MSI_H_ */
