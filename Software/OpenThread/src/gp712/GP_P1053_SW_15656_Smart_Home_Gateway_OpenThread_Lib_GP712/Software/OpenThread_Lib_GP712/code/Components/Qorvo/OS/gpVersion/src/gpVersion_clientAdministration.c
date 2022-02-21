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
 * $Header: //depot/release/Embedded/Components/Qorvo/OS/v2.10.2.0/comps/gpVersion/src/gpVersion_clientAdministration.c#1 $
 * $Change: 187624 $
 * $DateTime: 2021/12/20 10:58:50 $
 *
 */

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/
//#define GP_LOCAL_LOG

#include "gpAssert.h"
#include "gpVersion.h"
#include "gpLog.h"
#include "gpVersion_defs.h"

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

static Bool                             Version_ExchangeDone;
static gpVersion_ReleaseInfo_t          Version_ServerAppVersion;

/*****************************************************************************
 *                    External Data Definition
 *****************************************************************************/

/*****************************************************************************
 *                    Static Function Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/

void Version_InitClient(void)
{
    Version_ExchangeDone = false;
    MEMSET(&Version_ServerAppVersion, -1, sizeof(Version_ServerAppVersion));
}

static gpVersion_VersionStatusResult_t Version_ExchangeModuleCompatibility(UInt8 moduleIndex)
{
    gpVersion_VersionStatusResult_t moduleResult;
    gpVersion_ReleaseInfo_t apiVersion;

    GP_ASSERT_DEV_EXT(moduleIndex < GP_DIVERSITY_VERSION_MAX_MODULE_TABLE_SIZE);

    moduleResult = Version_NegotiateModuleVersion(Version_ModuleMapping[moduleIndex].moduleVersionInfo.moduleId,
                                                  Version_ModuleMapping[moduleIndex].moduleVersionInfo.nrOfVersions,
                                                  Version_ModuleMapping[moduleIndex].moduleVersionInfo.versionInfo,
                                                  &apiVersion);

    GP_LOG_PRINTF("Mod 0x%x r%i v%i.%i.%i.%i", 0,
                  Version_ModuleMapping[moduleIndex].moduleVersionInfo.moduleId,
                  moduleResult,
                  apiVersion.major,
                  apiVersion.minor,
                  apiVersion.revision,
                  apiVersion.patch);

    if (moduleResult == gpVersion_CompatibilityResultCompatible)
    {
        Version_UpdateModuleVersion(&(Version_ModuleMapping[moduleIndex]), apiVersion, 0xFFFFFFFF);
    }

    return moduleResult;
}

gpVersion_VersionStatusResult_t gpVersion_ExchangeCompatibility(void)
{
    gpVersion_ReleaseInfo_t ownSwVersion;
    gpVersion_VersionStatusResult_t appsCompatibilityResult;
    UIntLoop i;

    // Exchange application version number with the server.
    gpVersion_GetSoftwareVersion(&ownSwVersion);

    GP_LOG_PRINTF("Client v%i.%i.%i.%i", 0,
                   ownSwVersion.major,
                   ownSwVersion.minor,
                   ownSwVersion.revision,
                   ownSwVersion.patch);

    appsCompatibilityResult = Version_ExchangeGlobalVersion(ownSwVersion, &Version_ServerAppVersion);

    GP_LOG_PRINTF("Server r%i v%i.%i.%i.%i", 0,
                  appsCompatibilityResult,
                  Version_ServerAppVersion.major,
                  Version_ServerAppVersion.minor,
                  Version_ServerAppVersion.revision,
                  Version_ServerAppVersion.patch);

    if (appsCompatibilityResult == gpVersion_CompatibilityResultMaybeCompatible)
    {
        // Assume compatible. Each registered module API version will be checked anyway.
        appsCompatibilityResult = gpVersion_CompatibilityResultCompatible;
    }

    // Consider each registered module.
    for(i = 0; i < GP_DIVERSITY_VERSION_MAX_MODULE_TABLE_SIZE; i++)
    {
        // only check valid API's
        if(Version_ModuleMapping[i].moduleVersionInfo.moduleId != GP_VERSION_MODULE_ID_INVALID)
        {
            gpVersion_VersionStatusResult_t moduleResult;

            // Negotiate the API version of this module with the server.
            // This is necessary even when the application version numbers match;
            // application version number does not guarantee component APIs.
            moduleResult = Version_ExchangeModuleCompatibility(i);

            if (moduleResult != gpVersion_CompatibilityResultCompatible)
            {
                appsCompatibilityResult = gpVersion_CompatibilityResultNotCompatible;
                GP_LOG_SYSTEM_PRINTF("Warning: non matching API for module: %x. Communication not possible!", 0, Version_ModuleMapping[i].moduleVersionInfo.moduleId);
            }
        }
    }

    if (appsCompatibilityResult != gpVersion_CompatibilityResultCompatible)
    {
        gpVersion_DumpModuleMapping();
    }

    Version_ExchangeDone = true;
    return appsCompatibilityResult;
}

void gpVersion_GetServerVersion(gpVersion_ReleaseInfo_t* serverVersion)
{
    GP_ASSERT_DEV_EXT(Version_ExchangeDone);
    *serverVersion = Version_ServerAppVersion;
}

gpVersion_VersionStatusResult_t gpVersion_ExchangeGlobalVersion(gpVersion_ReleaseInfo_t clientInfo, gpVersion_ReleaseInfo_t* serverInfo)
{
    gpVersion_VersionStatusResult_t appsCompatibilityResult;

    appsCompatibilityResult = gpVersion_ExchangeCompatibility();
    gpVersion_GetServerVersion(serverInfo);

    return appsCompatibilityResult;
}

void gpVersion_RegisterModule(UInt8 moduleId, gpVersion_ReleaseInfo_t* versions, UInt8 nrOfVersions, gpVersion_cbSetModuleVersion_t cbSetModuleApiVersion)
{
    GP_LOG_PRINTF("gpVersion_RegisterModule %d", 0, moduleId);
    Version_RegisterModule_Common(moduleId, versions, nrOfVersions, cbSetModuleApiVersion);

    if (Version_ExchangeDone)
    {
        // Initial version exchange has already happened.
        // Negotiate the API version of this module immediately after it gets registered.
        UIntLoop i;
        for(i = 0; i < GP_DIVERSITY_VERSION_MAX_MODULE_TABLE_SIZE; i++)
        {
            if (Version_ModuleMapping[i].moduleVersionInfo.moduleId == moduleId)
            {
                gpVersion_VersionStatusResult_t moduleResult = Version_ExchangeModuleCompatibility(i);

                if (moduleResult != gpVersion_CompatibilityResultCompatible)
                {
                    GP_LOG_SYSTEM_PRINTF("Warning: non matching API for module: %x. Communication not possible!", 0, Version_ModuleMapping[i].moduleVersionInfo.moduleId);
                    GP_ASSERT_DEV_EXT(false);
                }

                return;
            }
        }

        GP_ASSERT_DEV_EXT(false); // module just registered but not in module table
    }
}

void gpVersion_DeRegisterModule(UInt8 moduleId)
{
    GP_LOG_PRINTF("gpVersion_DeRegisterModule %d", 0, moduleId);
    Version_DeRegisterModule_Common(moduleId);
}

