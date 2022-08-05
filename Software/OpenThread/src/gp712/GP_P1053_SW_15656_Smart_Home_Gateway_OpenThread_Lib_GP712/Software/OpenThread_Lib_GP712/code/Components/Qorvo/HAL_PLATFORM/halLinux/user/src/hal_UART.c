/*
 * Copyright (c) 2010-2016, GreenPeak Technologies
 * Copyright (c) 2017, Qorvo Inc
 *
 * hal_UART.c
 *   Hardware Abstraction Layer for stdin/stdout as UART on Linux.
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
 * $Header: //depot/main/Embedded/Components/Qorvo/HAL_PLATFORM/v2.10.3.1/comps/halLinux/user/src/hal_UART.c#1 $
 * $Change: 195340 $
 * $DateTime: 2022/06/17 14:57:48 $
 *
 */

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

#include "hal.h"
#include "hal_defs.h"
#include <stdio.h>
#include "termios.h"

#define GP_COMPONENT_ID GP_COMPONENT_ID_HALLINUX

/*****************************************************************************
 *                    Static Data Definitions
 *****************************************************************************/

static hal_cbUartRx_t            cbUartRx         = NULL;
static hal_cbUartGetTxData_t       cbUartGetTxData  = NULL;
Bool hal_UartRxEnabled;
Bool hal_UartTxEnabled;

/*****************************************************************************
 *                    Static Function Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/
void hal_InitUART( hal_cbUartRx_t RxISR, hal_cbUartGetTxData_t TxISR )
{
    /* register RX and TX isr */
    cbUartRx          = RxISR;
    cbUartGetTxData   = TxISR;

    hal_UartRxEnabled = false;
    hal_UartTxEnabled = true;

        printf("_____%s",__FUNCTION__);
    if(RxISR != NULL)
    {
        int res;
        struct termios newT;

        res = tcgetattr(fileno(stdin), &newT);
        if(res == 0)
        {
            hal_UartRxEnabled = true;
            hal_RegisterPollFunction(fileno(stdin),hal_RxUART);
            newT.c_lflag &= (~ICANON); //one char @ a time
            newT.c_cc[VTIME] = 1;
            newT.c_cc[VMIN] = 1; //generate interrupt when at least 1 char is received

            tcsetattr(fileno(stdin), TCSANOW, &newT);
        }
    }
}

void hal_TxUART(void)
{
    if(hal_UartTxEnabled && cbUartGetTxData)
    {
        while(true)
        {
            Int16 sendData;
            sendData = cbUartGetTxData();
            if(sendData != -1)
            {
                putchar((sendData));
                fflush(stdout);
            }
            else
            {
                break;
            }
        }
    }
}
void hal_RxUART(UInt8 id)
{
    NOT_USED(id);
    if(hal_UartRxEnabled)
    {
        int receiveData;

        receiveData = getchar();
        if(receiveData != EOF)
        {

#if defined(HAL_DIVERSITY_UART_RX_BUFFER_CALLBACK)
            cbUartRx((UInt8*)&receiveData,1);
#else
            cbUartRx(receiveData);
#endif
        }
    }
}
