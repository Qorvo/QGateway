/*
 * Copyright (c) 2014, GreenPeak Technologies
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
 * $Header$
 * $Change$
 * $DateTime$
 *
 */

/*****************************************************************************
 *                    Includes Definitions
 *****************************************************************************/
#include "gpVersion.h"
#include "gpVersion_defs.h"
#include "gpLog.h"


#ifdef GP_DIVERSITY_JUMPTABLES
#include "gpJumpTables.h"
#endif // GP_DIVERSITY_JUMPTABLES
#ifdef GP_DIVERSITY_ROMUSAGE_FOR_MATTER
#include "gpJumpTablesMatter.h"
#endif //GP_DIVERSITY_ROMUSAGE_FOR_MATTER

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


// changelist is 3 bytes and LSB is reserved
static const ROM gpVersion_SoftwareInfo_t FLASH_PROGMEM gpVersionSw LINKER_SECTION(".version_sw")
        = {{GP_VERSIONINFO_GLOBAL_VERSION},0x00,0,0,((0x00FFFFFFUL & GP_CHANGELIST)<<8)};
static const ROM gpVersion_ReleaseInfo_t FLASH_PROGMEM gpVersionBaseComps = {GP_VERSIONINFO_BASE_COMPS};
static const ROM gpVersion_ReleaseInfo_t FLASH_PROGMEM gpVersionBleController = {GP_VERSIONINFO_BLE_COMPS};

/*****************************************************************************
 *                    External Data Definition
 *****************************************************************************/

/*****************************************************************************
 *                    Static Function Definitions
 *****************************************************************************/

/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/

void gpVersion_GetSoftwareVersion(gpVersion_ReleaseInfo_t* swVersion)
{
    MEMCPY_P(swVersion, &(gpVersionSw.version), sizeof(gpVersion_ReleaseInfo_t));
}


void gpVersion_GetSoftwareInfo(gpVersion_SoftwareInfo_t* swInfo)
{
    MEMCPY_P(swInfo, &gpVersionSw, sizeof(gpVersion_SoftwareInfo_t));

}

void gpVersion_GetBaseCompsVersion(gpVersion_ReleaseInfo_t* pVersion)
{
    MEMCPY_P(pVersion, &gpVersionBaseComps, sizeof(gpVersion_ReleaseInfo_t));
}

void gpVersion_GetBleControllerVersion(gpVersion_ReleaseInfo_t* pVersion)
{
    MEMCPY_P(pVersion, &gpVersionBleController, sizeof(gpVersion_ReleaseInfo_t));
}



UInt8 gpVersion_GetNrtRomVersion(void)
{
    UInt8 nrtRomVersion = 0;

#ifdef GP_DIVERSITY_JUMPTABLES
    nrtRomVersion = gpJumpTables_GetRomVersionFromRom();
#endif //GP_DIVERSITY_JUMPTABLES

    return nrtRomVersion;
}

UInt8 gpVersion_GetMinimalMatterRomVersion(void)
{
    UInt8 minMatterRomVersion = 0;

#ifdef GP_DIVERSITY_ROMUSAGE_FOR_MATTER
    minMatterRomVersion = GPJUMPTABLESMATTER_MIN_ROMVERSION;
#endif //GP_DIVERSITY_ROMUSAGE_FOR_MATTER

    return minMatterRomVersion;
}

UInt8 gpVersion_GetMatterRomVersion(void)
{
    UInt8 matterRomVersion = 0;

#ifdef GP_DIVERSITY_ROMUSAGE_FOR_MATTER
    matterRomVersion = gpJumpTablesMatter_GetVersion();
#endif //GP_DIVERSITY_ROMUSAGE_FOR_MATTER

    return matterRomVersion;
}

UInt32 gpVersion_GetChangelist(void)
{
    return GP_CHANGELIST;
}

void gpVersion_DumpVersion(gpVersion_ReleaseInfo_t swVersion)
{
   GP_LOG_SYSTEM_PRINTF("Version is: v%i.%i.%i.%i",0, swVersion.major, swVersion.minor, swVersion.revision, swVersion.patch);
}

