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
 */

/** @file "qorvo_config.h"
 *
 */

#ifndef _QORVO_CONFIG_H_
#define _QORVO_CONFIG_H_

/*
 * Version info
 */

#define GP_CHANGELIST                                      144207
#define GP_VERSIONINFO_APP                                 QorvoGP712_rpi_cli_mtd_socket
#define GP_VERSIONINFO_BASE_COMPS                          0,0,0,0
#define GP_VERSIONINFO_BLE_COMPS                           2,10,3,1
#define GP_VERSIONINFO_DATE                                2023-07-06
#define GP_VERSIONINFO_GLOBAL_VERSION                      1,2,0,4
#define GP_VERSIONINFO_HOST                                UNKNOWN
#define GP_VERSIONINFO_PROJECT                             P959_OpenThread
#define GP_VERSIONINFO_USER                                ak105542@UNKNOWN


/*
 * Component: gpAssert
 */

/* Length of the filename string to be printed */
#define GP_ASSERT_DIVERSITY_LOG_FILENAME_LENGTH            160


/*
 * Component: gpBsp
 */

/* Contains filename of BSP header file to include */
#define GP_BSP_FILENAME                                    "gpBsp_linux_user.h"


/*
 * Component: gpCom
 */

/* To be specified when using multiple comms */
#define GP_COM_DEFAULT_COMMUNICATION_ID                    GP_COM_COMM_ID_IOCTL_USER1

/* Maximum amount of modules supported for Rx handling by gpCom. Environment already calculates minimal required module ID's */
#define GP_COM_MAX_NUMBER_OF_MODULE_IDS                    10

#define GP_COM_MAX_PACKET_PAYLOAD_SIZE                     500

#define GP_COM_RX_PACKET_BUFFERS                           50


/*
 * Component: gpPoolMem
 */

/* Number of packet descriptors */
#define GP_PD_NR_OF_HANDLES                                20


/*
 * Component: gpSched
 */

#define GP_SCHED_EVENT_LIST_SIZE                           50

/* Don't include the implementation for our mainloop MAIN_FUNCTION_NAME */
#define GP_SCHED_EXTERNAL_MAIN

/* Callback after every main loop iteration. */
#define GP_SCHED_NR_OF_IDLE_CALLBACKS                      0


#include "qorvo_internals.h"

#endif //_QORVO_CONFIG_H_
