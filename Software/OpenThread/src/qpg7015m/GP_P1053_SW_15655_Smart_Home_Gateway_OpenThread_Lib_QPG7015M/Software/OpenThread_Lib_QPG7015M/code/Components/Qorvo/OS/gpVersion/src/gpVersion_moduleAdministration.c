/*
 * Copyright (c) 2014-2016, GreenPeak Technologies
 * Copyright (c) 2017, 2019, Qorvo Inc
 *
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
 * $Header: //depot/release/Embedded/Components/Qorvo/OS/v2.10.3.1/comps/gpVersion/src/gpVersion_moduleAdministration.c#1 $
 * $Change: 197210 $
 * $DateTime: 2022/10/13 16:52:00 $
 *
 */

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/
#include "gpVersion.h"
#include "gpVersion_defs.h"
#include "gpLog.h"
#include "gpAssert.h"

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/
#define GP_COMPONENT_ID GP_COMPONENT_ID_VERSION

/*****************************************************************************
 *                    Functional Macro Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Type Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Static Function Prototypes
 *****************************************************************************/

/*****************************************************************************
 *                    Static Data Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    External Data Definition
 *****************************************************************************/

gpVersion_ModuleInfo_t  Version_ModuleMapping[GP_DIVERSITY_VERSION_MAX_MODULE_TABLE_SIZE];

/*****************************************************************************
 *                    Static Function Definitions
 *****************************************************************************/


/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/
void Version_Init(void)
{
    MEMSET(Version_ModuleMapping, -1, sizeof(gpVersion_ModuleInfo_t)*GP_DIVERSITY_VERSION_MAX_MODULE_TABLE_SIZE);
}

void Version_UpdateModuleVersion(gpVersion_ModuleInfo_t* moduleInfo, gpVersion_ReleaseInfo_t apiVersion, UInt32 commId)
{
    UIntLoop i;

    GP_ASSERT_DEV_EXT(moduleInfo->moduleVersionInfo.nrOfVersions <= GP_DIVERSITY_VERSION_MAX_VERSIONS_SIZE);

    moduleInfo->moduleVersionInfo.commId = commId;
    moduleInfo->moduleVersionInfo.selectedVersionIndex = GP_VERSION_VERSION_INDEX_INVALID;
    for (i = 0; i < moduleInfo->moduleVersionInfo.nrOfVersions; i++)
    {
        if (GP_VERSION_VERSIONS_EQUAL(moduleInfo->moduleVersionInfo.versionInfo[i], apiVersion))
        {
            moduleInfo->moduleVersionInfo.selectedVersionIndex = i;
            break;
        }
    }

    GP_ASSERT_DEV_EXT(moduleInfo->moduleVersionInfo.selectedVersionIndex < moduleInfo->moduleVersionInfo.nrOfVersions);

    if (moduleInfo->cbSetModuleApiVersion)
    {
        moduleInfo->cbSetModuleApiVersion(&(moduleInfo->moduleVersionInfo));
    }
}

void gpVersion_DumpModuleMapping(void)
{
    UIntLoop i,j;

    GP_LOG_SYSTEM_PRINTF("Module Mapping...",0);
    for(i = 0; i < GP_DIVERSITY_VERSION_MAX_MODULE_TABLE_SIZE; i++)
    {
        if(Version_ModuleMapping[i].moduleVersionInfo.moduleId != 0xFF)
        {
            GP_LOG_SYSTEM_PRINTF("Module: %x sel=%i", 0,
                                 Version_ModuleMapping[i].moduleVersionInfo.moduleId,
                                 Version_ModuleMapping[i].moduleVersionInfo.selectedVersionIndex);
            for(j=0; j < Version_ModuleMapping[i].moduleVersionInfo.nrOfVersions; j++)
            {
                gpVersion_DumpVersion(Version_ModuleMapping[i].moduleVersionInfo.versionInfo[j]);
            }
        }
    }
    GP_LOG_SYSTEM_PRINTF("End of module list",0);
}

void Version_RegisterModule_Common(UInt8 moduleId, gpVersion_ReleaseInfo_t* versions, UInt8 nrOfVersions, gpVersion_cbSetModuleVersion_t cbSetModuleApiVersion)
{
    UIntLoop i;

    for(i = 0; i < GP_DIVERSITY_VERSION_MAX_MODULE_TABLE_SIZE; i++)
    {
        if(Version_ModuleMapping[i].moduleVersionInfo.moduleId == 0xFF)
        {
            Version_ModuleMapping[i].moduleVersionInfo.moduleId = moduleId;
            Version_ModuleMapping[i].moduleVersionInfo.nrOfVersions = nrOfVersions;
            Version_ModuleMapping[i].cbSetModuleApiVersion = cbSetModuleApiVersion;
            GP_ASSERT_SYSTEM(nrOfVersions <= GP_DIVERSITY_VERSION_MAX_VERSIONS_SIZE);
            MEMCPY(&Version_ModuleMapping[i].moduleVersionInfo.versionInfo, &versions[0], sizeof(gpVersion_ReleaseInfo_t)*nrOfVersions);
            return;
        }
    }
    GP_ASSERT_DEV_EXT(false);   // table is full
}

void Version_DeRegisterModule_Common(UInt8 moduleId)
{
    UIntLoop i;

    for(i = 0; i < GP_DIVERSITY_VERSION_MAX_MODULE_TABLE_SIZE; i++)
    {
        if(Version_ModuleMapping[i].moduleVersionInfo.moduleId == moduleId)
        {
            Version_ModuleMapping[i].moduleVersionInfo.moduleId = 0xFF;
        }
    }
}

