#define GP_COMPONENT_ID GP_COMPONENT_ID_APP

#include "gpLog.h"

#include <openthread/instance.h>

// #define GP_LOCAL_LOG

void qorvoThreadApp_Main()
{
    GP_LOG_PRINTF(">> TEST APP STARTED", 0);
}

void qorvoThreadApp_Init(otInstance *sInstance)
{
    GP_LOG_PRINTF(">> TEST APP INIT", 0);
}
