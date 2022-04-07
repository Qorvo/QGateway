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

/** @file "qorvo_internals.h"
 *
 */

#ifndef _QORVO_INTERNALS_H_
#define _QORVO_INTERNALS_H_

/*
 * Enabled components
 */

#define GP_COMP_ASSERT
#define GP_COMP_BASECOMPS
#define GP_COMP_BSP
#define GP_COMP_BSPCOMMON
#define GP_COMP_COM
#define GP_COMP_HALLINUX
#define GP_COMP_LOG
#define GP_COMP_MACDISPATCHER
#define GP_COMP_PD
#define GP_COMP_POOLMEM
#define GP_COMP_QVOT
#define GP_COMP_RANDOM
#define GP_COMP_RXARBITER
#define GP_COMP_SCHED
#define GP_COMP_STAT
#define GP_COMP_UTILS
#define GP_COMP_VERSION
#define GP_COMP_WMRK

/*
 * Components numeric ids
 */

#define GP_COMPONENT_ID_APP                                   1
#define GP_COMPONENT_ID_ASSERT                                29
#define GP_COMPONENT_ID_BASECOMPS                             35
#define GP_COMPONENT_ID_BSP                                   8
#define GP_COMPONENT_ID_BSPCOMMON                             62
#define GP_COMPONENT_ID_COM                                   10
#define GP_COMPONENT_ID_ENCRYPTION                            124
#define GP_COMPONENT_ID_GPHAL                                 7
#define GP_COMPONENT_ID_HALLINUX                              6
#define GP_COMPONENT_ID_LOG                                   11
#define GP_COMPONENT_ID_MACCORE                               109
#define GP_COMPONENT_ID_MACDISPATCHER                         114
#define GP_COMPONENT_ID_PAD                                   126
#define GP_COMPONENT_ID_PD                                    104
#define GP_COMPONENT_ID_POOLMEM                               106
#define GP_COMPONENT_ID_QVOT                                  157
#define GP_COMPONENT_ID_RANDOM                                108
#define GP_COMPONENT_ID_RESET                                 33
#define GP_COMPONENT_ID_RXARBITER                             2
#define GP_COMPONENT_ID_SCHED                                 9
#define GP_COMPONENT_ID_STAT                                  22
#define GP_COMPONENT_ID_UTILS                                 4
#define GP_COMPONENT_ID_VERSION                               129
#define GP_COMPONENT_ID_WMRK                                  51

/*
 * Component: gpAssert
 */

#define GP_DIVERSITY_BACKTRACE_ON_ASSERT

/*
 * Component: gpBaseComps
 */

#define GP_RANDOM_DIVERSITY_GPCOM_CLIENT

/*
 * Component: gpBspCommon
 */

#define GP_DIVERSITY_LINUX_GENERAL_32KHZ

/*
 * Component: gpCom
 */

#define GP_COM_DIVERSITY_IOCTL

/*
 * Component: gpEncryption
 */

#define GP_ENCRYPTION_DIVERSITY_MARSHAL

/*
 * Component: gpMacCore
 */

#define GP_MACCORE_DIVERSITY_ADDRESSMODEOVERRIDEFORBEACONS
#define GP_MACCORE_DIVERSITY_MARSHAL
#define GP_MACCORE_DIVERSITY_SECURITY_ENABLED

/*
 * Component: gpMacDispatcher
 */

#define GP_MACDISPATCHER_DIVERSITY_MARSHAL

/*
 * Component: gpPd
 */

#define GP_DIVERSITY_PD_USE_RAM_VARIANT
#define GP_PD_DIVERSITY_MARSHAL

/*
 * Component: gpRandom
 */

#define GP_RANDOM_DIVERSITY_MARSHAL

/*
 * Component: gpRxArbiter
 */

#define GP_RXARBITER_DIVERSITY_MARSHAL

/*
 * Component: gpSched
 */

#define GP_HAL_DIVERSITY_USE_SELECT
#define GP_SCHED_DIVERSITY_SLEEP

/*
 * Component: gpStat
 */

#define GP_DIVERSITY_STATISTICS

/*
 * Component: gpVersion
 */

#define GP_VERSION_DIVERSITY_MARSHAL

/*
 * Component: qvOT
 */

#define QVOT_DIVERSITY_GLUE_ONLY_BUILD

/*
 * Other flags
 */

#define GP_ASSERT_DIVERSITY_MARSHAL
#define GP_BSPCOMMON_DIVERSITY_MARSHAL
#define GP_BSP_DIVERSITY_MARSHAL
#define GP_DIVERSITY_BACKTRACE_ON_EXCEPTION
#define GP_DIVERSITY_DEVELOPMENT
#define GP_DIVERSITY_KEEP_NRT_IN_FLASH
#define GP_DIVERSITY_LOG
#define GP_DIVERSITY_NO_RADIO_INIT
#define GP_DIVERSITY_NR_OF_STACKS                             2
#define GP_HAL_DIVERSITY_MARSHAL
#define GP_LOG_DIVERSITY_MARSHAL
#define GP_MACDISPATCHER_DIVERSITY_GPCOM_CLIENT
#define GP_PAD_DIVERSITY_MARSHAL
#define GP_POOLMEM_DIVERSITY_MARSHAL
#define GP_RESET_DIVERSITY_MARSHAL
#define GP_RXARBITER_DIVERSITY_GPCOM_CLIENT
#define GP_SCHED_DEFAULT_GOTOSLEEP_THRES                      1000
#define GP_SCHED_DIVERSITY_MARSHAL
#define GP_STAT_DIVERSITY_MARSHAL
#define GP_UTILS_DIVERSITY_MARSHAL
#define GP_VERSION_DIVERSITY_GPCOM_CLIENT
#define GP_WMRK_DIVERSITY_MARSHAL
#define OPENTHREAD_COMMISSIONER
#define QORVOOPENTHREAD_MAX_CHILDREN                          10

#endif //_QORVO_INTERNALS_H_
