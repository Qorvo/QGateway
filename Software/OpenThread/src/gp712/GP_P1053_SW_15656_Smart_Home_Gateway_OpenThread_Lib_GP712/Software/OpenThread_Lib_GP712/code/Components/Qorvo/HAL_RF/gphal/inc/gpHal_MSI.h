/*
 * Copyright (c) 2009-2010, 2012-2016, GreenPeak Technologies
 * Copyright (c) 2017, 2019, Qorvo Inc
 *
 * gpHal_MSI.h
 *
 * This file contains the functions dependent on the choice of MCU : MSI, Interrupts,...
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
 * $Header: //depot/main/Embedded/Components/Qorvo/HAL_RF/v2.10.3.1/comps/gphal/inc/gpHal_MSI.h#1 $
 * $Change: 195340 $
 * $DateTime: 2022/06/17 14:57:48 $
 *
 */

#ifndef _GPHAL_MSI_H_
#define _GPHAL_MSI_H_

/**
 * @file gpHal_MSI.h
 * @brief This file declares functions to access the radio over the MSI protocol.
 */

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

#include "global.h"

#include "gpBsp.h"       //uC SPI functions
#include "hal.h"         //uC INT functions

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Type Definitions
 *****************************************************************************/

typedef UInt16 gpHal_Address_t;

#define gphal_msi_resultSuccess     0
#define gphal_msi_resultFailure     1
typedef UInt8 gphal_msi_result_t;


/*****************************************************************************
 *                    Static Data Definitions
 *****************************************************************************/

extern gphal_msi_result_t gpHal_msi_lastMsiResult;

/*****************************************************************************
 *                   Functional Macro Definitions
 *****************************************************************************/
//------------------------------------------------------------------------------


//GP Register Access
GP_API UInt8 readRegExternal           (gpHal_Address_t Address);
GP_API void  readByteStreamExternal    (gpHal_Address_t Address, UInt8* pBuffer, UInt8 Length);
GP_API void  writeRegExternal          (gpHal_Address_t Address, UInt8 Data);
GP_API void  writeByteStreamExternal   (gpHal_Address_t Address, const UInt8* pBuffer, UInt8 Length);
GP_API void  readModifyWriteRegExternal(gpHal_Address_t Address, UInt8 Mask, UInt8 Data);

/** @brief Read register access macro.
 *
 *  This is the raw macro for reading registers.
 *
 *  Depending on the processor the macros are used on, access to the registers is
 *  direct (embedded processor) or using SPI/I2C (external processor).
 *
 * @param Address  The address of the register.
*/
#define GP_HAL_READ_REG(Address)                                  readRegExternal(Address)
/** @brief Write register access macro.
 *
 *  This is the raw macro for writing registers.
 *
 *  Depending on the processor the macros are used on, access to the registers is
 *  direct (embedded processor) or using SPI/I2C (external processor).
 *
 * @param Address  The address of the register.
 * @param Data     The data to write.
*/
#define GP_HAL_WRITE_REG(Address,Data)                            writeRegExternal(Address, Data)
/** @brief Read byte stream access macro.
 *
 *  This is the raw macro for reading bytes from consecutive registers.
 *
 *  Depending on the processor the macros are used on, access to the registers is
 *  direct (embedded processor) or using SPI/I2C (external processor).
 *
 * @param Address  The address of the first register to access.
 * @param pBuffer  The pointer to the buffer that receives the read data.
 * @param Length   The number of bytes to read.
*/
#define GP_HAL_READ_BYTE_STREAM(Address, pBuffer, Length)         readByteStreamExternal(Address, (UInt8*)pBuffer, Length)
/** @brief Write byte stream access macro.
 *
 *  This is the raw macro for writing bytes to consecutive registers.
 *
 *  Depending on the processor the macros are used on, access to the registers is
 *  direct (embedded processor) or using SPI/I2C (external processor).
 *
 * @param Address  The address of the first register to access.
 * @param pBuffer  The pointer to the buffer that contains the data to write.
 * @param Length   The number of bytes to write.
*/
#define GP_HAL_WRITE_BYTE_STREAM(Address,pBuffer, Length)         writeByteStreamExternal(Address, (const UInt8*)pBuffer, Length)

/** @brief Read-moify-write access macro.
 *
 *  This is the raw macro for changing register bits with a read-modify-write action.
 *
 *  Depending on the processor the macros are used on, access to the registers is
 *  direct (embedded processor) or using SPI/I2C (external processor).
 *
 * @param Register  The address of the register.
 * @param Mask      The read-modify-write mask.
 * @param Data      The value to write.
*/
#define GP_HAL_READMODIFYWRITE_REG(Address, Mask, Data)   readModifyWriteRegExternal(Address, Mask, Data)


#endif  /* _GPHAL_MSI_H_ */
