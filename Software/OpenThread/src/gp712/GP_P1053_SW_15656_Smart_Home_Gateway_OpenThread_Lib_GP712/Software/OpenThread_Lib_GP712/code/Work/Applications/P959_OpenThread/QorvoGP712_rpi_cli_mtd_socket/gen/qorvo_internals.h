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
#define GP_COMP_COM
#define GP_COMP_MACDISPATCHER
#define GP_COMP_PD
#define GP_COMP_POOLMEM
#define GP_COMP_RANDOM
#define GP_COMP_VERSION

/*
 * Components numeric ids
 */

#define GP_COMPONENT_ID_APP                                1
#define GP_COMPONENT_ID_ASSERT                             29
#define GP_COMPONENT_ID_BASECOMPS                          35
#define GP_COMPONENT_ID_BSP                                8
#define GP_COMPONENT_ID_COM                                10
#define GP_COMPONENT_ID_ENCRYPTION                         124
#define GP_COMPONENT_ID_GPHAL                              7
#define GP_COMPONENT_ID_HALLINUX                           6
#define GP_COMPONENT_ID_LOG                                11
#define GP_COMPONENT_ID_MACCORE                            109
#define GP_COMPONENT_ID_MACDISPATCHER                      114
#define GP_COMPONENT_ID_PAD                                126
#define GP_COMPONENT_ID_PD                                 104
#define GP_COMPONENT_ID_POOLMEM                            106
#define GP_COMPONENT_ID_QVOT                               157
#define GP_COMPONENT_ID_RANDOM                             108
#define GP_COMPONENT_ID_RESET                              33
#define GP_COMPONENT_ID_RXARBITER                          2
#define GP_COMPONENT_ID_SCHED                              9
#define GP_COMPONENT_ID_STAT                               22
#define GP_COMPONENT_ID_UTILS                              4
#define GP_COMPONENT_ID_VERSION                            129
#define GP_COMPONENT_ID_WMRK                               51

/*
 * Other flags
 */

#define GP_DIVERSITY_LOG
#define GP_DIVERSITY_NR_OF_STACKS                          2
#define GP_GIT_SHA                                         2334f506f9cba16a755256babb1eb0a69878a600
#define GP_GIT_SHA_SHORT                                   2334f
#define GP_SCHED_DEFAULT_GOTOSLEEP_THRES                   1000

#endif //_QORVO_INTERNALS_H_
