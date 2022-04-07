/*
 * Copyright (c) 2013-2016, GreenPeak Technologies
 * Copyright (c) 2017-2019, Qorvo Inc
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
 * $Header: //depot/release/Embedded/Components/Qorvo/OS/v2.10.2.2/comps/gpVersion/inc/gpVersion.h#1 $
 * $Change: 190959 $
 * $DateTime: 2022/02/18 16:20:44 $
 *
 */

#ifndef _GP_VERSION_H_
#define _GP_VERSION_H_

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/

#include <global.h>

/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/

#ifndef GP_DIVERSITY_NR_OF_STACKS
#define GP_DIVERSITY_NR_OF_STACKS 1
#endif //GP_DIVERSITY_NR_OF_STACKS

#define GP_DIVERSITY_VERSION_MAX_MODULE_TABLE_SIZE  (8*GP_DIVERSITY_NR_OF_STACKS)
#define GP_DIVERSITY_VERSION_MAX_VERSIONS_SIZE      6

#define GP_VERSION_VERSION_FLATTEN(v)               (((UInt32)((v).major) << 24) | ((UInt32)((v).minor) << 16) | ((UInt32)((v).revision) << 8) | ((v).patch))
#define GP_VERSION_VERSIONS_EQUAL(v1, v2)           ((v1).major == (v2).major && (v1).minor == (v2).minor && (v1).revision == (v2).revision && (v1).patch == (v2).patch)
#define GP_VERSION_VERSIONS_SMALLER(v1, v2)         (GP_VERSION_VERSION_FLATTEN(v1) < GP_VERSION_VERSION_FLATTEN(v2))
#define GP_VERSION_VERSIONS_GREATER(v1, v2)         (GP_VERSION_VERSION_FLATTEN(v1) > GP_VERSION_VERSION_FLATTEN(v2))

#define GP_VERSION_MODULE_ID_INVALID            0xFF
#define GP_VERSION_VERSION_INDEX_INVALID        0xFF

#define GP_VERSION_MAKE_VERSION_STRING_FROM_PARTS(major,minor,revision,patch,cl) \
                                                    #major "." #minor "." #revision "." #patch " - CL" #cl
#define GP_VERSION_MAKE_VERSION_STRING(version,cl)  GP_VERSION_MAKE_VERSION_STRING_FROM_PARTS(version,cl)
#define GP_VERSION_STRING                           GP_VERSION_MAKE_VERSION_STRING(GP_VERSIONINFO_GLOBAL_VERSION,GP_CHANGELIST)

/*****************************************************************************
 *                    Type Definitions
 *****************************************************************************/

#define gpVersion_CompatibilityResultCompatible         0
#define gpVersion_CompatibilityResultMaybeCompatible    1
#define gpVersion_CompatibilityResultNotCompatible      2
#define gpVersion_CompatibilityResultInvalidParameter   0xFF
typedef UInt8 gpVersion_VersionStatusResult_t;

typedef UInt8 gpVersion_VersionNumber_t;

// defines release version
typedef struct {
    gpVersion_VersionNumber_t major;
    gpVersion_VersionNumber_t minor;
    gpVersion_VersionNumber_t revision;
    gpVersion_VersionNumber_t patch;
} gpVersion_ReleaseInfo_t;

// defines software information
typedef struct {
    gpVersion_ReleaseInfo_t version;
    UInt8                   ctrl;
    UInt8                   reserved;
    UInt16                  number;
    UInt32                  changeList;
} gpVersion_SoftwareInfo_t;

typedef struct {
    gpVersion_ReleaseInfo_t         versions[GP_DIVERSITY_VERSION_MAX_VERSIONS_SIZE];
} gpVersion_ModuleVersions_t;

// callback structure for all modules
typedef struct {
    UInt32                              commId;
    UInt8                               moduleId;
    UInt8                               nrOfVersions;
    UInt8                               selectedVersionIndex;
    gpVersion_ReleaseInfo_t             versionInfo[GP_DIVERSITY_VERSION_MAX_VERSIONS_SIZE];
} gpVersion_ModuleVersionInfo_t;

// callback type for wrappers
typedef void (*gpVersion_cbSetModuleVersion_t)(gpVersion_ModuleVersionInfo_t* moduleVersionInfo);

// structure that contains all useful module information
typedef struct {
    gpVersion_ModuleVersionInfo_t       moduleVersionInfo;
    gpVersion_cbSetModuleVersion_t      cbSetModuleApiVersion;
} gpVersion_ModuleInfo_t;

typedef struct {
    UInt32                              commId;
    UInt8                               moduleId;
    gpVersion_ReleaseInfo_t             version;
} gpVersion_ClientVersionMapping_t;

/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

void gpVersion_Init(void);

/** @brief Return the compile-time application version number.
 *  @param[out] swVersion  Buffer to hold version number.
 */
void gpVersion_GetSoftwareVersion(gpVersion_ReleaseInfo_t* swVersion);

/** @brief Return software information, including application version number and changelist number.
 *  @param[out] swInfo  Buffer to hold software information.
 */
void gpVersion_GetSoftwareInfo(gpVersion_SoftwareInfo_t* swInfo);

/** @brief Return the compile-time BaseComps version number.
 *  @param[out] pVersion  Buffer to hold version number.
 */
void gpVersion_GetBaseCompsVersion(gpVersion_ReleaseInfo_t* pVersion);

// for backward compatibility
#define gpVersion_GetBcVersion gpVersion_GetBaseCompsVersion

#ifdef GP_VERSIONINFO_BLE_COMPS
/** @brief Return the compile-time Components/Qorvo/BleController version number.
 *  @param[out] pVersion  Buffer to hold version number.
 */
void gpVersion_GetBleControllerVersion(gpVersion_ReleaseInfo_t* pVersion);
#endif //GP_VERSIONINFO_BLE_COMPS




UInt32 gpVersion_GetChangelist(void);

#if defined(GP_VERSION_DIVERSITY_GPCOM_CLIENT) 
/** @brief Register a module to the version administration.
 *
 *  This function is only available in client/server applications.
 *  It should be called for each module used accross the client/server barrier.
 *  This function is typically called by the clientwrapper/serverwrapper code
 *  of the corresponding module.
 *
 *  @param moduleId               GP_MODULE_ID of the module to be registered
 *  @param versions               Array of API versions supported for this module, preferred version first.
 *  @param nrOfVersions           Number of valid array elements in @a versions
 *  @param cbSetModuleApiVersion  Function to be called when an API version is selected
 */
void gpVersion_RegisterModule(UInt8 moduleId, gpVersion_ReleaseInfo_t* versions, UInt8 nrOfVersions, gpVersion_cbSetModuleVersion_t cbSetModuleApiVersion);

/** @brief De-register a module to the version administration.
 *
 *  This function is only available in client/server applications.
 *  It should be called for each module used accross the client/server barrier.
 *  This function is typically called by the clientwrapper/serverwrapper code
 *  of the corresponding module.
 *
 *  @param moduleId               GP_MODULE_ID of the module to be de-registered
 */
void gpVersion_DeRegisterModule(UInt8 moduleId);

#endif //defined(GP_VERSION_DIVERSITY_GPCOM_CLIENT) || defined(GP_VERSION_DIVERSITY_GPCOM_SERVER)

/* Dump Functions */
void gpVersion_DumpVersion(gpVersion_ReleaseInfo_t swVersion);
#ifdef GP_DIVERSITY_DEVELOPMENT
void gpVersion_DumpModuleMapping(void);
#endif //GP_DIVERSITY_DEVELOPMENT

#ifdef GP_VERSION_DIVERSITY_GPCOM_CLIENT

/** @brief Exchange version numbers and negotiate API compatibility between client and server.
 *
 *  This function is only available in client applications.
 *  It should be called once at the start of the application, as early as
 *  possible after component initialization.
 *
 *  @return gpVersion_CompatibilityResultCompatible    if all modules are compatible with the server API
 *  @return gpVersion_CompatibilityResultNotCompatible if some modules are incompatible with the server API
*/
gpVersion_VersionStatusResult_t gpVersion_ExchangeCompatibility(void);

/** @brief Return server version number.
 *
 *  This function is only available in client applications.
 *  It may be called after gpVersion_ExchangeCompatibility to obtain the
 *  server application version number.
 *
 *  @param[out] serverVersion  Buffer to hold version number.
 */
void gpVersion_GetServerVersion(gpVersion_ReleaseInfo_t* serverVersion);

//for backward compatibility - prefered to use gpVersion_ExchangeCompatibility()
gpVersion_VersionStatusResult_t gpVersion_ExchangeGlobalVersion(gpVersion_ReleaseInfo_t clientInfo, gpVersion_ReleaseInfo_t* serverInfo);

#endif //GP_VERSION_DIVERSITY_GPCOM_CLIENT

#ifdef __cplusplus
}
#endif

#endif // _GP_VERSION_H_

