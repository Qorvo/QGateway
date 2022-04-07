/*
 * Copyright (c) 2010-2016, GreenPeak Technologies
 * Copyright (c) 2017, Qorvo Inc
 *
 * hal.h
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
 * $Header: //depot/release/Embedded/Components/Qorvo/HAL_PLATFORM/v2.10.2.0/comps/halLinux/user/inc/hal.h#1 $
 * $Change: 187624 $
 * $DateTime: 2021/12/20 10:58:50 $
 *
 */

#ifndef _HAL_H_
#define _HAL_H_

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/
#include "global.h"
#ifdef GP_COMP_BSP
#include "gpBsp.h"
#endif //GP_COMP_BSP
#ifdef GP_COMP_GPHAL
#include "gpHal_MSI.h"
#endif //GP_COMP_GPHAL

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_Extension.h"

#include <stdlib.h>
#include <time.h>
#include <pthread.h>

/*****************************************************************************
 *                    TIMER
 *****************************************************************************/

#if defined(GP_COMP_UNIT_TEST) && !defined(GP_HAL_DIVERSITY_USE_SELECT) && !defined(GP_UNITTEST_DIVERSITY_NO_FASTFORWARD)
//error : inserted by sunifdef: "#define HAL_FASTFORWARD_FOR_UNIT_TEST" contradicts -U at /mnt/c/WS_P1053_v1_5_0_2/Package/GP_P1053_SW_15655_Smart_Home_Gateway_OpenThread_Lib_QPG7015M/Software/OpenThread_Lib_QPG7015M/code/Components/Qorvo/HAL_PLATFORM/halLinux/user/inc/hal.h(63)
#endif //defined(GP_COMP_UNIT_TEST) && !defined(GP_HAL_DIVERSITY_USE_SELECT) && !defined(HAL_DIVERSITY_USE_LIBEV)&& !defined(GP_UNITTEST_DIVERSITY_NO_FASTFORWARD)

/* This implementation uses the time of the os to keep the time */
UInt32 hal_GetCurrentTime(void);
UInt32 hal_GetCurrentTime_1us(void);
#define HAL_TIMER_START(initialisationTime)

#define HAL_TIMER_STOP()

#define HAL_TIMER_GET_CURRENT_TIME(time) time = hal_GetCurrentTime()

#define HAL_TIMER_GET_CURRENT_TIME_1US(time) time = hal_GetCurrentTime_1us()

/*****************************************************************************
 *                    SPI
 *****************************************************************************/

#ifdef GP_COMP_GPHAL
int hal_spi_readRegExternal(gpHal_Address_t Address, UInt8* pData);
int hal_spi_writeRegExternal(gpHal_Address_t Address, UInt8 Data);
int hal_spi_readByteStreamExternal(gpHal_Address_t Address, UInt8 Length, UInt8* pBuffer);
int hal_spi_writeByteStreamExternal(gpHal_Address_t Address, UInt8 Length, const UInt8* pBuffer);
int hal_spi_readModifyWriteRegExternal(gpHal_Address_t Address, UInt8 mask, UInt8 Data);
#endif //GP_COMP_GPHAL

/** @ingroup SPI
 *
 * This macro initializes the SPI port used to communicate with the communication controller.
 *
 * Configuration:
 * - Microcontroller is the master, the communication controller is the slave.
 * - Chip select pin is output on the microcontroller and active Low, so when initialized the chip select pin needs to be high.
 * - The maximum clock speed the microcontroller can use to communicate with the comunication controller is 16 Mhz.
 * - The SPI mode used to communicate is mode 3. This means sample the bit on rising edge, change value on falling edge.
 * - No interrupts are used, the SPI protocol is implemented in a polled way.
*/
#define HAL_SPI_START()

/** @ingroup SPI
 * This macro sets the chip select pin low.
*/
#define HAL_SPI_SSN_LOW()
/** @ingroup SPI
 * This macro sets the chip select pin high.
*/
#define HAL_SPI_SSN_HIGH()

/** @ingroup SPI
 * This macro transmits 1 byte: x.
 * If the microcontroller has an SPI harware block:
 * - write the byte x to the communication controller using the tx buffer of the SPI block.
 * - wait until the tx buffer is empty.
 * If the microcontroller has no SPI hardware block the SPI communication needs to be implemented in software:
 * - at startup the clock signal is low.
 * - Set the MSB bit on the MOSI pin and pull up the clock line.
 * - Pull donw the clock line.
 * - Transmit the next bit using the same procedure as described above, do this 8 times to transmit the full byte
 *
 * @param x The byte that is transmitted, x is an unsigned 8 bit integer.
*/
#if !defined(GP_COMP_CHIPEMU) 
#define HAL_SPI_TX(x)
#else
UInt8 hal_msiHandleTx(UInt8 byte);
#define HAL_SPI_TX(x) hal_msiHandleTx(x)
#endif

/** @ingroup SPI
 * This macro is used to receives a byte and save it to x.
 *
 * If the microcontroller has an SPI harware block:
 * - write a 0 to the communication controller to generate a clock signal.
 * - wait until the SPI block is idle and read out the byte in the receive buffer and save this byte to x.
 * If the microcontroller has no SPI hardware block the SPI communication needs to be implemented in software:
 * - generate a clock signal on the clk line by driving the clock line from low to high.
 * - After the clock signal goes from low to high read out the value of the MISO pin.
 * - Pull down the clock signal.
 * - Repeat the previous steps 8 times. Now 1 byte is read out.
 * - The first bit read out is the MSB bit, the last bit is the LSB bit.
 *
 * @param x This byte returns the received value, x is an unsigned 8 bit integer.
*/
#if !defined(GP_COMP_CHIPEMU) 
#define HAL_SPI_RX(x)
#else
UInt8 hal_msiHandleRx(UInt8 byte);
#define HAL_SPI_RX(x) (x = hal_msiHandleRx(x))
#endif

/** @ingroup SPI
 * This macro is used to power down the SPI block.
 *
 * All pins used for SPI should be set low. Default the chip select pin should be set low.
 * Other pins could also need to be set low depending on the SPI block behavior
 *
*/
#define HAL_SPI_POWERDOWN()

/** @ingroup SPI
 * This macro is used to power up the SPI block.
 *
 * All pins used for SPI should be set to an active state. Default the chip select pin should be set high.
 * Other pins could also need to be set depending on the SPI block behavior.
 *
*/
#define HAL_SPI_POWERUP()
/*****************************************************************************
 *                    RADIO INTERRUPT
 *****************************************************************************/

Bool hal_HandleRadioInterrupt(Bool execute);

/** @ingroup RadioInterrupt Radio Interrupt
 * This macro configures the interrupt line connecting the radio with the microcontroller.
 * If the interruptCallback parameter is not NULL, the communication controller's interrupt is used to trigger in interrupt in the software. Implementation needs to be as described below.
 * - Sets the interrupt sense control to falling edge or low level.
 * - Registers the interrupt service routine: save the function that need to be called in a local variable.
 * - Clears the pending interrupt flag and enables the interrupt.
 * - The interrupt pin needs to be pulled-up by the microcontroller or en external circuit.
 *
 * If the interruptCallback parameter is NULL: the application will check the communication controller's interrupt line to see if an interrupt occured. Implementation needs to be as described below.
 * - Set the pin connected to the interrupt of the communication controller to input and pull up the line.
 * @param interruptCallback The parameter interruptCallback is the function that needs to be called if an interrupt from the communication controller occurs.
*/

#define HAL_RADIO_INTERRUPT_START(interruptCallback)

/** @ingroup RadioInterrupt Radio Interrupt
 * This macro returnes if the radio interrupt is enabled. If the radio interrupts are not used this macro needs to return true.
*/
//Execution of ISR is done in sleep code with select() function
#define HAL_RADIO_INT_CHECK_IF_OCCURED() hal_HandleRadioInterrupt(false)
#define HAL_RADIO_INT_EXEC_IF_OCCURED()  hal_HandleRadioInterrupt(true)

/*****************************************************************************
 *                    WAIT LOOP
 *****************************************************************************/

#ifdef GP_COMP_UNIT_TEST
#define HAL_WAIT_US(timeout)    \
    do                          \
    {                           \
        hal_GoToSleep(timeout); \
    } while(false)

#define HAL_WAIT_MS(timeout)           \
    do                                 \
    {                                  \
        hal_GoToSleep(timeout * 1000); \
    } while(false)
#else
#define HAL_WAIT_US(timeout)                              \
    do                                                    \
    {                                                     \
        struct timespec sleepTime;                        \
        sleepTime.tv_sec = (timeout) / 1000000;           \
        sleepTime.tv_nsec = ((timeout) % 1000000) * 1000; \
        nanosleep(&sleepTime, NULL);                      \
    } while(false)

#define HAL_WAIT_MS(timeout)                              \
    do                                                    \
    {                                                     \
        struct timespec sleepTime;                        \
        sleepTime.tv_sec = (timeout) / 1000;              \
        sleepTime.tv_nsec = ((timeout) % 1000) * 1000000; \
        nanosleep(&sleepTime, NULL);                      \
    } while(false)
#endif //GP_COMP_UNIT_TEST

/*****************************************************************************
 *                    WAKEUP Pin
 *****************************************************************************/
void hal_Trigger_Wakeup(void);
/** @ingroup WakeUp
 * This macro configures the wakeup pin. Puts the pin on digital output.
*/
#define HAL_WKUP_START()

/** @ingroup WakeUp
 * This macro drives the wake up pin high.
*/
#define HAL_SET_WKUP_ACTIVE() hal_Trigger_Wakeup()

/** @ingroup WakeUp
 * This macro drives the wake up pin low.
*/
#define HAL_SET_WKUP_INACTIVE()

/*****************************************************************************
 *                    RESET Pin
 *****************************************************************************/

void hal_Trigger_Reset(void);

/** @ingroup Reset
 * This macro drives the reset pin to the specified logical level.
*/
#ifndef GP_COMP_CHIPEMU
#define HAL_SET_RESET_ACTIVE(level) hal_Trigger_Reset()
#else
#define HAL_SET_RESET_ACTIVE(level) hal_msiInit(level)
#endif //GP_COMP_CHIPEMU

/** @ingroup Reset
 * This macro configures the reset pin. Puts the pin on digital input to not interfere with default state of the reset line.
 */
#ifndef GP_COMP_CHIPEMU
#define HAL_SET_RESET_INACTIVE()
#else
#define HAL_SET_RESET_INACTIVE() hal_msiInit(1)
#endif //GP_COMP_CHIPEMU

/** @ingroup Reset
 * This macro returns the logic level of the reset pin. It is used to select the correct reset method.
 */
#define HAL_GET_RESET_LEVEL() 0

/*****************************************************************************
 *                    Init Function
 *****************************************************************************/
void hal_Init(void);
void hal_DeInit(void);

#define HAL_INIT() hal_Init()

/*****************************************************************************
 *                    GLOBAL interrupt Function
 *****************************************************************************/

//Nested interrupt disabling mechanism only kept to keep checks in order throughout the code.
extern UInt8 l_n_atomic;

/** @ingroup globalInterrupts
 * This macro enables the global interrupts without incrementing the l_n_atomic counter.
 *
*/
#define HAL_FORCE_ENABLE_GLOBAL_INT()

/** @ingroup globalInterrupts
 * This macro disables the global interrupts without decrementing the l_n_atomic counter.
 *
*/
#define HAL_FORCE_DISABLE_GLOBAL_INT()

#define HAL_INITIALIZE_GLOBAL_INT() \
    {                               \
        l_n_atomic = 1;             \
    }

/** @ingroup globalInterrupts
 * This macro decrements the counter l_n_atomic. If l_n_atomic is 0 after the decrement the interrupts are enabled.
 *
*/

#define HAL_ENABLE_GLOBAL_INT() \
    do                          \
    {                           \
        l_n_atomic--;           \
    } while(false)

/** @ingroup globalInterrupts
 * This macro increments the counter l_n_atomic. If l_n_atomic is 1 after the increment the interrupts are disabled.
 *
*/
#define HAL_DISABLE_GLOBAL_INT() \
    do                           \
    {                            \
        l_n_atomic++;            \
    } while(false)

#define HAL_GLOBAL_INT_ENABLED() (l_n_atomic == 0)

/*****************************************************************************
 *                    Buttons
 *****************************************************************************/

/** @ingroup Buttons
 * This macro initializes the buttons. The pin(s) connected to the button(s) are configured as digital input.
 *
*/
#define HAL_BTN_INIT()

/** @ingroup Buttons
 * This macro reads out the value of button btn, possible values for btn are 1 or 2.
 * The value is returned by using the construction BUTTON_##btn and by defining BUTTON_1 and BUTTON_2 as the pin which is read out. Where the value 1 means button pressed and 0 means button not pressed.
 * If a pull-down circuit is used and a 0 means button pressed, the value needs to be inverted.
 *
 * @param btn The parameter btn is a unsigned 8 bit integer. The number of the used button is 1 or 2.
*/
#define HAL_BTN_PRESSED(btn) false

/*****************************************************************************
 *                    Leds
 *****************************************************************************/

/** @ingroup LEDS
 * This macro initializes the leds.
 * Led RED and led GRN are initialized in this macro. Leds are turned of at initialisation and the pins connected to the leds are put as digital output.
 *
*/

#define HAL_LED_INIT()

/** @ingroup LEDS
 * This macro clears a led. Possible values for led are RED or GRN.
 * This can be implemented by using the structure HAL_LED_CLR_##led() and by defining and implementing HAL_LED_CLR_GRN() and HAL_LED_CLR_RED().
 * @param led The parameter is RED or GRN.
*/
#define HAL_LED_CLR(led)

/** @ingroup LEDS
 * This macro sets a led. Possible values for led are RED or GRN.
 * This can be implemented by using the structure HAL_LED_SET_##led() and by defining and implementing HAL_LED_SET_GRN() and HAL_LED_SET_RED().
 * @param led The parameter is RED or GRN.
*/
#define HAL_LED_SET(led)

/** @ingroup LEDS
 * This macro reads out the value of a led. Possible values for led are RED or GRN.
 * This can be implemented by using the structure HAL_LED_TST_##led() and by defining and implementing HAL_LED_TST_GRN() and HAL_LED_TST_RED().
 * @param led The parameter is RED or GRN.
*/
#define HAL_LED_TST(led)

/** @ingroup LEDS
 * This macro reads out the value of a led and inverts it. Possible values for led are RED or GRN.
 * This can be implemented by using the structure HAL_LED_TGL_##led() and by defining and implementing HAL_LED_TGL_GRN() and HAL_LED_TGL_RED().
 * @param led The parameter is RED or GRN.
*/
#define HAL_LED_TGL(led)

/** @ingroup LEDS
 * This macro initializes the leds.
 * Led RED and led GRN are initialized in this macro.
 *
*/

#define HAL_USERLED_INIT()

/** @ingroup LEDS
 * This macro clears a userled. Possible values for led are YEL or BLU.
 * This can be implemented by using the structure HAL_USERLED_CLR_##led() and by defining and implementing HAL_USERLED_CLR_YEL() and HAL_USERLED_CLR_BLU().
 * @param led The parameter is BLU or YEL.
*/
#define HAL_USERLED_CLR(led)

/** @ingroup LEDS
 * This macro sets a userled. Possible values for led are YEL or BLU.
 * This can be implemented by using the structure HAL_USERLED_SET_##led() and by defining and implementing HAL_USERLED_SET_YEL() and HAL_USERLED_SET_BLU().
 * @param led The parameter is BLU or YEL.
*/
#define HAL_USERLED_SET(led)

/** @ingroup LEDS
 * This macro reads out the value of a userled. Possible values for led are YEL or BLU.
 * This can be implemented by using the structure HAL_USERLED_TST_##led() and by defining and implementing HAL_USERLED_TST_YEL() and HAL_USERLED_TST_BLU().
 * @param led The parameter is BLU or YEL.
*/
#define HAL_USERLED_TST(led)

/** @ingroup LEDS
 * This macro reads out the value of a userled and inverts it. Possible values for led are YEL or BLU.
 * This can be implemented by using the structure HAL_USERLED_TGL_##led() and by defining and implementing HAL_USERLED_TGL_YEL() and HAL_LED_USERTGL_BLU().
 * @param led The parameter is BLU or YEL.
*/
#define HAL_USERLED_TGL(led)

/*****************************************************************************
 *                    RESET REASON
 *****************************************************************************/

#define hal_ResetReason_Unspecified 0x0
typedef UInt8 hal_ResetReason_t;

#define HAL_GET_RESET_REASON() (hal_ResetReason_Unspecified)

/*****************************************************************************
 *                    UART
 *****************************************************************************/

void hal_InitUART(hal_cbUartRx_t RxISR, hal_cbUartGetTxData_t TxISR);
void hal_TxUART(void);
void hal_RxUART(UInt8 id);
/* This implementation uses stdin and stdout*/
#define HAL_UART_COM_START(cbUartRx, cbUartGetTxData) hal_InitUART(cbUartRx, cbUartGetTxData)
#define HAL_UART_COM_STOP()

#define HAL_UART_COM_POWERDOWN()   \
    do                             \
    {                              \
        hal_UartRxEnabled = false; \
        hal_UartTxEnabled = false; \
    } while(false)

#define HAL_UART_COM_POWERUP()    \
    do                            \
    {                             \
        hal_UartRxEnabled = true; \
        hal_UartTxEnabled = true; \
    } while(false)

#define HAL_UART_COM_TX_NEW_DATA() hal_TxUART()
#define HAL_UART_COM_TX_ENABLED()  (hal_UartTxEnabled)

#define hal_UartPollRx() hal_RxUART(0)

#define hal_UartPollTx() HAL_UART_COM_TX_NEW_DATA()

#define HAL_UART_SCOM_START(cbUartRx, cbUartGetTxData) hal_InitUART(cbUartRx, cbUartGetTxData)
#define HAL_UART_SCOM_STOP()                         \
    do                                               \
    {                                                \
        GP_ASSERT_SYSTEM(false); /* not supported */ \
    } while(0)

#define HAL_UART_SCOM_POWERDOWN()  \
    do                             \
    {                              \
        hal_UartRxEnabled = false; \
        hal_UartTxEnabled = false; \
    } while(false)

#define HAL_UART_SCOM_POWERUP()   \
    do                            \
    {                             \
        hal_UartRxEnabled = true; \
        hal_UartTxEnabled = true; \
    } while(false)

#define HAL_UART_SCOM_TX_NEW_DATA() hal_TxUART()

/*****************************************************************************
 *                    RESET UC
 *****************************************************************************/

/** @ingroup ResetUC
 * This macro resets the application.
 *
*/
#define HAL_RESET_UC() abort() //Stop application and produce core dump (if system supports it)
/*****************************************************************************
 *                    SLEEP UC
 *****************************************************************************/
GP_API void hal_GoToSleep(UInt32 time);

#define HAL_SLEEP_INDEFINITE_SLEEP_TIME 0xFFFFFFFF
#define HAL_SLEEP_MAX_SLEEP_TIME        0xFFFFFFFE

#define HAL_DISABLE_SLEEP_UC()
#define HAL_ENABLE_SLEEP_UC()
#define HAL_SLEEP_UC_1US(time) hal_GoToSleep(time)

/*****************************************************************************
 *                    WATCHDOG
 *****************************************************************************/

#define HAL_WDT_ENABLE(timeout) \
    do                          \
    {                           \
    } while(false)
#define HAL_WDT_DISABLE() \
    do                    \
    {                     \
    } while(false)
#define HAL_WDT_RESET() \
    do                  \
    {                   \
    } while(false)
#define HAL_WDT_FORCE_TRIGGER() \
    do                          \
    {                           \
    } while(false)

/*****************************************************************************
 *                    BACKTRACE STACK DUMP
 *****************************************************************************/

#ifdef GP_DIVERSITY_BACKTRACE_ON_ASSERT
void hal_dump_backtrace(UInt8 maxlevel);
#endif //GP_DIVERSITY_BACKTRACE_ON_ASSERT
#ifdef GP_DIVERSITY_BACKTRACE_ON_EXCEPTION
#ifndef GP_DIVERSITY_BACKTRACE_ON_ASSERT
#error GP_DIVERSITY_BACKTRACE_ON_EXCEPTION requires GP_DIVERSITY_BACKTRACE_ON_ASSERT
#endif //GP_DIVERSITY_BACKTRACE_ON_ASSERT
void hal_install_exception_handlers(void);
#endif //GP_DIVERSITY_BACKTRACE_ON_EXCEPTION

/*****************************************************************************
 *                    HEAP DEBUG
 *****************************************************************************/

/** @brief Returns heap usage information
 *
 *  @return pInUse Currently allocated bytes on heap
 *  @return pReserved Memory
 *  @return pMax   Maximum used heap. Will grow during operation, but will stay at that number.
*/
void hal_GetHeapInUse(UInt32* pInUse, UInt32* pReserved, UInt32* pMax);

/*****************************************************************************
 *                    File descriptor/pipe registration
 *****************************************************************************/

#define HAL_NR_OF_PIPE_HANDLES  10
#define HAL_PIPE_INVALID_HANDLE 0xFF

typedef UInt8 hal_pipeHandle_t;

hal_pipeHandle_t hal_GetPipeHandle(hal_PollFunction_t pollFunction);
void hal_ReadFromPipe(hal_pipeHandle_t handle, UInt8* pData, UInt32 length);
void hal_WriteToPipe(hal_pipeHandle_t handle, UInt8* pData, UInt32 length);

void hal_RegisterPollFunction(int fd, hal_PollFunction_t pollFunction);
void hal_UnRegisterPollFunction(int fd);

void hal_SetPollFunction_write(int fd, hal_PollFunction_t pollFunction);

Bool hal_HandleFds(Bool execute);

/*****************************************************************************
 *                    MUTEX
 *****************************************************************************/

#define HAL_CRITICAL_SECTION_TYPE        pthread_mutex_t
#define HAL_CRITICAL_SECTION_DEF(pMutex) pthread_mutex_t* pMutex;
#define HAL_CREATE_MUTEX(pMutex)                  \
    do                                            \
    {                                             \
        pMutex = malloc(sizeof(pthread_mutex_t)); \
        pthread_mutex_init(pMutex, NULL);         \
    } while(0)
#define HAL_DESTROY_MUTEX(pMutex)      \
    do                                 \
    {                                  \
        pthread_mutex_destroy(pMutex); \
        free(pMutex);                  \
        pMutex = NULL;                 \
    } while(0)
#define HAL_ACQUIRE_MUTEX(pMutex)   \
    do                              \
    {                               \
        pthread_mutex_lock(pMutex); \
    } while(0)
#define HAL_RELEASE_MUTEX(pMutex)     \
    do                                \
    {                                 \
        pthread_mutex_unlock(pMutex); \
    } while(0)
#define HAL_VALID_MUTEX(pMutex)       (pMutex != NULL)
#define HAL_IS_MUTEX_ACQUIRED(pMutex) ( \
    {int __result = pthread_mutex_trylock(pMutex);\
    if(0 == __result) { pthread_mutex_unlock(pMutex); }; \
    __result; })


/*****************************************************************************
 *                    ChipEmu and Unit/Stack tests
 *****************************************************************************/

#ifdef GP_COMP_CHIPEMU
void hal_update_interrupt(void);
#endif //GP_COMP_CHIPEMU

Bool hal_Select(UInt32 time, Bool Execute);
void hal_WakeEventloop(void);
void hal_ClearWakeUpEvent(void);

#if defined(GP_COMP_CHIPEMU)
typedef void (*hal_cbFastForwardSleep_t)(UInt32 requestedSleepTime, UInt64* clockCounter);
void hal_RegisterFastForwardSleepCallback(hal_cbFastForwardSleep_t cbFFSleep);
#endif //defined(HAL_FASTFORWARD_FOR_UNIT_TEST) || defined(GP_COMP_CHIPEMU)

/*****************************************************************************
 *                    Random
 *****************************************************************************/
#ifdef __cplusplus
}
#endif //__cplusplus

#endif //_HAL_H_
