
/*
 * Copyright (c) 2009-2016, GreenPeak Technologies
 * Copyright (c) 2017-2019, Qorvo Inc
 *
 * gpStat.c
 *
 * This file implements the generic statistics component
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

//#define GP_LOCAL_LOG

// General includes
#include "gpStat.h"
#include "gpLog.h"
#include "gpAssert.h"


/*****************************************************************************
 *                    Macro Definitions
 *****************************************************************************/

#define GP_COMPONENT_ID GP_COMPONENT_ID_STAT

#include "gpSched.h"
#define GP_STAT_GET_TIME()  gpSched_GetCurrentTime()

#define STAT_LOG_FORMAT_LENGTH 9 //"T:%lu l:%i!"

/*****************************************************************************
 *                    Type Definitions
 *****************************************************************************/

typedef struct {
    UInt32 time;
    UInt16 line;
    UInt8 compId;
    char funcName[GP_STAT_MAX_NAME_CHARS];
    FLASH_STRING pFileName; //Internally only storing pointer for RAM optimization
} Stat_Sample_t;

/*****************************************************************************
 *                    Static Data Definitions
 *****************************************************************************/

Bool                         gpStat_Initialized = false;
#if GP_STAT_NUMBER_OF_COUNTERS > 0
gpStat_StatisticsCounter_t   gpStat_StatisticsCounters[GP_STAT_NUMBER_OF_COUNTERS];
#endif
#if GP_STAT_NUMBER_OF_MINMAX > 0
gpStat_StatisticsMinMax_t    gpStat_StatisticsMinMax[GP_STAT_NUMBER_OF_MINMAX];
#endif
#if GP_STAT_NUMBER_OF_STOPWATCHES > 0
gpStat_StatisticsStopwatch_t gpStat_StatisticsStopwatches[GP_STAT_NUMBER_OF_STOPWATCHES];
#endif
#if GP_STAT_NUMBER_OF_SAMPLES > 0
Stat_Sample_t                gpStat_Samples[GP_STAT_NUMBER_OF_SAMPLES];
UInt8                        gpStat_SampleIndex = 0;
#endif
#if GP_STAT_NUMBER_OF_HEAP_SAMPLES > 0
gpStat_HeapSample_t          gpStat_HeapSamples[GP_STAT_NUMBER_OF_HEAP_SAMPLES];
UInt8                        gpStat_HeapSampleIndex = 0;
#endif //GP_STAT_NUMBER_OF_HEAP_SAMPLES

/*****************************************************************************
 *                    External Data Definition
 *****************************************************************************/

/*****************************************************************************
 *                    Static Function Prototypes
 *****************************************************************************/

#if GP_STAT_NUMBER_OF_COUNTERS > 0
static void Stat_DumpCounter(gpStat_StatisticsCounter_t* pCounter, Int32 increment);
static gpStat_StatisticsCounter_t* Stat_GetCounter(gpStat_CounterID_t id);
#endif
#if GP_STAT_NUMBER_OF_MINMAX > 0
static gpStat_StatisticsMinMax_t* Stat_GetMinMax(gpStat_MinMaxID_t id);
#endif
#if GP_STAT_NUMBER_OF_STOPWATCHES > 0
static gpStat_StatisticsStopwatch_t* Stat_GetStopwatch(gpStat_StopwatchID_t id);
#endif
#if (GP_STAT_NUMBER_OF_COUNTERS > 0) || (GP_STAT_NUMBER_OF_MINMAX > 0) || (GP_STAT_NUMBER_OF_STOPWATCHES > 0)
static void Stat_ErrorID(gpStat_CounterID_t id);
#endif
static void Stat_LogSample(Stat_Sample_t* sample);
#if GP_STAT_NUMBER_OF_SAMPLES > 0
static void Stat_InitSampling(void);
#endif
#if GP_STAT_NUMBER_OF_HEAP_SAMPLES > 0
static void Stat_InitHeapSampling(void);
#endif
/*****************************************************************************
 *                    Static Function Definitions
 *****************************************************************************/

#if GP_STAT_NUMBER_OF_COUNTERS > 0
void Stat_DumpCounter(gpStat_StatisticsCounter_t* pCounter, Int32 increment)
{
#ifdef GP_DIVERSITY_LOG
    GP_LOG_SYSTEM_PRINTF("Inc cnt %s %lu (%li)",0, pCounter->name, (unsigned long int)pCounter->counter, (long int)increment);
#endif //GP_DIVERSITY_LOG
}

gpStat_StatisticsCounter_t* Stat_GetCounter(gpStat_CounterID_t id)
{
    //Incrementstep == 0 - unused counter
    if(id < GP_STAT_NUMBER_OF_COUNTERS && (gpStat_StatisticsCounters[id].incrementStep != 0))
    {
        return &(gpStat_StatisticsCounters[id]);
    }
    else
    {
        return NULL;
    }
}
#endif
#if GP_STAT_NUMBER_OF_MINMAX > 0
gpStat_StatisticsMinMax_t* Stat_GetMinMax(gpStat_MinMaxID_t id)
{
    //' ' as first character in name - unused object
    if(id < GP_STAT_NUMBER_OF_COUNTERS  && (gpStat_StatisticsMinMax[id].name[0]!=' '))
    {
        return &(gpStat_StatisticsMinMax[id]);
    }
    else
    {
        return NULL;
    }
}
#endif
#if GP_STAT_NUMBER_OF_STOPWATCHES > 0
gpStat_StatisticsStopwatch_t* Stat_GetStopwatch(gpStat_StopwatchID_t id)
{
    //' ' as first character in name - unused object
    if(id < GP_STAT_NUMBER_OF_STOPWATCHES && (gpStat_StatisticsStopwatches[id].name[0]!=' '))
    {
        return &(gpStat_StatisticsStopwatches[id]);
    }
    else
    {
        return NULL;
    }
}
#endif
void Stat_LogSample(Stat_Sample_t* sample)
{
    //Copy filename after ':'
    char buffer[STAT_LOG_FORMAT_LENGTH+GP_STAT_MAX_NAME_CHARS*2+1] = "T:%lu %i:";
    UInt8 fileNameLength= 0;

    STRNCPY_P(&buffer[STAT_LOG_FORMAT_LENGTH], sample->pFileName, GP_STAT_MAX_NAME_CHARS);
    fileNameLength = min(STRLEN_P(sample->pFileName), GP_STAT_MAX_NAME_CHARS);

    buffer[STAT_LOG_FORMAT_LENGTH+fileNameLength] = ' ';
    STRNCPY(&buffer[STAT_LOG_FORMAT_LENGTH+fileNameLength+1], sample->funcName, GP_STAT_MAX_NAME_CHARS);

    gpLog_Printf(sample->compId, false, (FLASH_STRING)buffer, 0, sample->time, sample->line);
    gpLog_Flush();
}
#if GP_STAT_NUMBER_OF_SAMPLES > 0
void Stat_InitSampling(void)
{
    //Clear samples
    gpStat_SampleIndex = 0;
    MEMSET((UInt8*)gpStat_Samples, 0, sizeof(Stat_Sample_t)*GP_STAT_NUMBER_OF_SAMPLES);
}
#endif
#if GP_STAT_NUMBER_OF_HEAP_SAMPLES > 0
void Stat_InitHeapSampling(void)
{
    gpStat_HeapSampleIndex = 0;
    MEMSET((UInt8*)gpStat_HeapSamples, 0, sizeof(gpStat_HeapSamples));
}
void Stat_LogHeapSample(gpStat_HeapSample_t* pSample)
{
    GP_LOG_SYSTEM_PRINTF("T:%lu %lu" ,0, (long unsigned int)pSample->time, (long unsigned int)pSample->heapInUse);
}
#endif
#if (GP_STAT_NUMBER_OF_COUNTERS > 0) || (GP_STAT_NUMBER_OF_MINMAX > 0) || (GP_STAT_NUMBER_OF_STOPWATCHES > 0)
void Stat_ErrorID(gpStat_CounterID_t id)
{
#ifndef GP_LOCAL_LOG
    NOT_USED(id);
#endif
    GP_LOG_PRINTF("faulty ID %i",2,(UInt16)id);
    GP_ASSERT_DEV_EXT(false);
}
#endif

/*****************************************************************************
 *                    Public Function Definitions
 *****************************************************************************/

void gpStat_Init(void)
{
    if(!gpStat_Initialized)
    {
        gpStat_Clear();
    }
    gpStat_Initialized = true;

    GP_LOG_PRINTF("Init",0);
}

void gpStat_Clear(void)
{
    UIntLoop id = 0;

#if GP_STAT_NUMBER_OF_COUNTERS > 0
    for(id= 0; id < GP_STAT_NUMBER_OF_COUNTERS; id++)
    {
        MEMSET(gpStat_StatisticsCounters[id].name,' ' ,GP_STAT_MAX_NAME_LENGTH);
        gpStat_StatisticsCounters[id].incrementStep  = 0; //no counting up or down
        gpStat_StatisticsCounters[id].counter        = 0;
    }
#endif
#if GP_STAT_NUMBER_OF_MINMAX > 0
    for(id= 0; id < GP_STAT_NUMBER_OF_MINMAX; id++)
    {
        MEMSET(gpStat_StatisticsMinMax[id].name,' ' ,GP_STAT_MAX_NAME_LENGTH);
        gpStat_StatisticsMinMax[id].count = 0;
        gpStat_StatisticsMinMax[id].max   = 0;
        gpStat_StatisticsMinMax[id].min   = 0xFFFFFFFF;
        gpStat_StatisticsMinMax[id].sum   = 0;
        gpStat_StatisticsMinMax[id].sum2  = 0;
    }
#endif
#if GP_STAT_NUMBER_OF_STOPWATCHES > 0
    for(id= 0; id < GP_STAT_NUMBER_OF_STOPWATCHES; id++)
    {
        MEMSET(gpStat_StatisticsStopwatches[id].name,' ' ,GP_STAT_MAX_NAME_LENGTH);
    }
#endif
#if GP_STAT_NUMBER_OF_SAMPLES > 0
    Stat_InitSampling();
#endif
#if GP_STAT_NUMBER_OF_HEAP_SAMPLES > 0
    Stat_InitHeapSampling();
#endif
    NOT_USED(id);
}

#if GP_STAT_NUMBER_OF_COUNTERS > 0
//----------------------------------------
// Counter
//----------------------------------------

gpStat_CounterID_t gpStat_RegisterCounter(FLASH_STRING name, Int8 incrementStep)
{
    gpStat_CounterID_t id;

    //Find free counter ID
    for(id = 0; id < GP_STAT_NUMBER_OF_COUNTERS; id++)
    {
        if(gpStat_StatisticsCounters[id].incrementStep == 0) break;
    }
    //No free counter ID left
    if(id == GP_STAT_NUMBER_OF_COUNTERS)
    {
        GP_LOG_PRINTF("Cnt full",0);
        GP_ASSERT_DEV_EXT(false);
        return 0xFF;
    }

    //Copy name
    //Copy untill we reach \0 character
    STRNCPY_P(gpStat_StatisticsCounters[id].name, name, GP_STAT_MAX_NAME_LENGTH);

    //Set increment step
    gpStat_StatisticsCounters[id].incrementStep = incrementStep;

    //Clear counter
    gpStat_StatisticsCounters[id].counter = 0;

    GP_LOG_PRINTF("Cnt reg %i",2,(UInt16)id);
    return id;
}

void gpStat_FreeCounter(gpStat_CounterID_t id)
{
    gpStat_StatisticsCounter_t* pCounter = Stat_GetCounter(id);
    if(pCounter)
    {
        GP_LOG_PRINTF("Cnt free %i",2,(UInt16)id);
        pCounter->incrementStep = 0;
        MEMSET(gpStat_StatisticsCounters[id].name,' ' ,GP_STAT_MAX_NAME_LENGTH);
    }
    else
    {
        Stat_ErrorID(id);
    }
}

void gpStat_ResetCounter(gpStat_CounterID_t id)
{
    gpStat_StatisticsCounter_t* pCounter = Stat_GetCounter(id);

    if(pCounter)
    {
        GP_LOG_PRINTF("Cnt reset %i",2,(UInt16)id);
        pCounter->counter = 0;
    }
    else
    {
        Stat_ErrorID(id);
    }
}

void gpStat_IncrementCounter(gpStat_CounterID_t id)
{
    gpStat_StatisticsCounter_t* pCounter = Stat_GetCounter(id);

    if(pCounter)
    {
        pCounter->counter += pCounter->incrementStep;
        Stat_DumpCounter(pCounter, pCounter->incrementStep);
    }
    else
    {
        Stat_ErrorID(id);
    }
}

void gpStat_IncreaseCounter(gpStat_CounterID_t id, Int32 value)
{
    gpStat_StatisticsCounter_t* pCounter = Stat_GetCounter(id);

    if(pCounter)
    {
        pCounter->counter += value;
        Stat_DumpCounter(pCounter, value);
    }
    else
    {
        Stat_ErrorID(id);
    }
}

UInt32 gpStat_GetCounter(gpStat_CounterID_t id)
{
   gpStat_StatisticsCounter_t* pCounter = Stat_GetCounter(id);

    if(pCounter)
    {
        return pCounter->counter;
    }
    else
    {
        Stat_ErrorID(id);
        return 0xFFFFFFFF;
    }
}
#endif

#if GP_STAT_NUMBER_OF_MINMAX > 0
//----------------------------------------
// Min/Max
//----------------------------------------

gpStat_MinMaxID_t  gpStat_RegisterMinMax(FLASH_STRING name)
{
    gpStat_MinMaxID_t id;

    //Find free counter ID
    for(id = 0; id < GP_STAT_NUMBER_OF_COUNTERS; id++)
    {
        if(gpStat_StatisticsMinMax[id].name[0] == ' ') break;
    }
    //No free counter ID left
    if(id == GP_STAT_NUMBER_OF_COUNTERS)
    {
        GP_LOG_PRINTF("MiMa full",0);
        GP_ASSERT_DEV_EXT(false);
        return 0xFF;
    }

    //Copy name
    //Copy untill we reach \0 character
    STRNCPY_P(gpStat_StatisticsMinMax[id].name, name, GP_STAT_MAX_NAME_LENGTH);

    //Clear counter
    gpStat_StatisticsMinMax[id].min = 0xffffffff;
    gpStat_StatisticsMinMax[id].max = 0x0;

    GP_LOG_PRINTF("MiMa reg %i",2,(UInt16)id);
    return id;
}

void gpStat_FreeMinMax(gpStat_CounterID_t id)
{
    gpStat_StatisticsMinMax_t* pMinMax = Stat_GetMinMax(id);
    if(pMinMax)
    {
        GP_LOG_PRINTF("MinMax free %i",2,(UInt16)id);
        MEMSET(gpStat_StatisticsMinMax[id].name,' ' ,GP_STAT_MAX_NAME_LENGTH);
    }
    else
    {
        Stat_ErrorID(id);
    }
}

Bool gpStat_SetMinMax(gpStat_MinMaxID_t id , UInt32 value)
{
    gpStat_StatisticsMinMax_t* pMinMax = Stat_GetMinMax(id);
    Bool overflow = false;

    if(pMinMax)
    {
        //count overflow
        if(pMinMax->count == 0xFFFF)
        {
            overflow = true;
        }
        pMinMax->count++;

        //sum overflow
        if(0xFFFFFFFF-value <= pMinMax->sum)
        {
            overflow = true;
        }
        pMinMax->sum += value;

        //sum2 overflows
        if((value >= 0xFFFF) || (0xFFFFFFFF-(value*value) <= pMinMax->sum2))
        {
            overflow = true;
        }
        pMinMax->sum2 += (value*value) ;

        if(pMinMax->max < value )
        {
            pMinMax->max = value;
        }

        if(pMinMax->min > value )
        {
            pMinMax->min = value;
        }
        //Stat_DumpCounter(pCounter, pCounter->incrementStep);
    }
    else
    {
        Stat_ErrorID(id);
    }

    return overflow;
}

UInt32 gpStat_GetCount(gpStat_MinMaxID_t id)
{
    gpStat_StatisticsMinMax_t* pMinMax = Stat_GetMinMax(id);

    if(pMinMax)
    {
        return pMinMax->count;
    }

    Stat_ErrorID(id);
    return 0;
}

UInt32 gpStat_GetMin(gpStat_MinMaxID_t id)
{
    gpStat_StatisticsMinMax_t* pMinMax = Stat_GetMinMax(id);

    if(pMinMax)
    {
        return pMinMax->min;
    }

    Stat_ErrorID(id);
    return 0xFFFFFFFF;
}

UInt32 gpStat_GetMax(gpStat_MinMaxID_t id)
{
   gpStat_StatisticsMinMax_t* pMinMax = Stat_GetMinMax(id);

   if(pMinMax)
   {
       return pMinMax->max;
   }

    Stat_ErrorID(id);
    return 0;
}

UInt32 gpStat_GetSum(gpStat_MinMaxID_t id)
{
    gpStat_StatisticsMinMax_t* pMinMax = Stat_GetMinMax(id);

    if(pMinMax)
    {
        return pMinMax->sum;
    }

    Stat_ErrorID(id);
    return 0;
}

UInt32 gpStat_GetAverage(gpStat_MinMaxID_t id)
{
    gpStat_StatisticsMinMax_t* pMinMax = Stat_GetMinMax(id);

    if(pMinMax)
    {
        if(pMinMax->count == 0)
        {
            return 0;
        }
        return (pMinMax->sum / pMinMax->count);
    }

    Stat_ErrorID(id);
    return 0;
}

UInt32 gpStat_GetVariance(gpStat_MinMaxID_t id)
{
    gpStat_StatisticsMinMax_t* pMinMax = Stat_GetMinMax(id);

    if(pMinMax)
    {
        if(pMinMax->count == 0)
        {
            return 0;
        }
        return (pMinMax->sum2 / pMinMax->count) - ((pMinMax->sum / pMinMax->count)*(pMinMax->sum / pMinMax->count));
    }
    else
    {
        Stat_ErrorID(id);
        return 0;
    }
}

void gpStat_ResetMinMax(gpStat_MinMaxID_t id)
{
    gpStat_StatisticsMinMax_t* pMinMax = Stat_GetMinMax(id);

    if(pMinMax)
    {
        GP_LOG_PRINTF("MiMa reset %i",2,(UInt16)id);
        pMinMax->count = 0;
        pMinMax->min   = 0xFFFFFFFF;
        pMinMax->max   = 0;
        pMinMax->sum   = 0;
        pMinMax->sum2  = 0;
    }
    else
    {
        Stat_ErrorID(id);
    }
}
#endif

#if GP_STAT_NUMBER_OF_STOPWATCHES > 0
//----------------------------------------
// Stopwatches
//----------------------------------------

gpStat_StopwatchID_t gpStat_RegisterStopwatch(FLASH_STRING name)
{
    gpStat_StopwatchID_t id;

    //Find free counter ID
    for(id = 0; id < GP_STAT_NUMBER_OF_STOPWATCHES; id++)
    {
        if(gpStat_StatisticsStopwatches[id].name[0] == ' ') break;
    }
    //No free counter ID left
    if(id == GP_STAT_NUMBER_OF_STOPWATCHES)
    {
        GP_LOG_PRINTF("Stopwatch full",0);
        GP_ASSERT_DEV_EXT(false);
        return 0xFF;
    }

    //Copy name
    //Copy untill we reach \0 character
    STRNCPY_P(gpStat_StatisticsStopwatches[id].name, name, GP_STAT_MAX_NAME_LENGTH);

    //Clear counter
    gpStat_StatisticsStopwatches[id].time = 0;

    GP_LOG_PRINTF("Stopwatch reg %i",2,(UInt16)id);
    return id;
}

void gpStat_FreeStopwatch(gpStat_StopwatchID_t id)
{
    gpStat_StatisticsStopwatch_t* pStopwatch = Stat_GetStopwatch(id);

    if(pStopwatch)
    {
        GP_LOG_PRINTF("Stopwatch free %i",2,(UInt16)id);
        MEMSET(gpStat_StatisticsStopwatches[id].name,' ' ,GP_STAT_MAX_NAME_LENGTH);
    }
    else
    {
        Stat_ErrorID(id);
    }
}

void gpStat_StartStopwatch(gpStat_StopwatchID_t id)
{
    gpStat_StatisticsStopwatch_t* pStopwatch = Stat_GetStopwatch(id);

    if(pStopwatch)
    {
        pStopwatch->time = GP_STAT_GET_TIME();
    }
    else
    {
        Stat_ErrorID(id);
    }
}

UInt32 gpStat_StopStopwatch(gpStat_StopwatchID_t id)
{
    gpStat_StatisticsStopwatch_t* pStopwatch = Stat_GetStopwatch(id);

    if(pStopwatch)
    {
        UInt32 time = GP_STAT_GET_TIME();

        if(time >= pStopwatch->time) //check if no overflow is triggered
        {
            return (time - pStopwatch->time);
        }
    }
    else
    {
        Stat_ErrorID(id);
    }

    return 0xFFFFFFFF;
}
#endif

#if GP_STAT_NUMBER_OF_SAMPLES > 0
//----------------------------------------
// Sampling
//----------------------------------------

void gpStat_SampleTime(UInt8 compId, FLASH_STRING filename, FLASH_STRING funcName, UInt16 line)
{
    UInt32 currentTime;
    Stat_Sample_t* pSample;

    currentTime = GP_STAT_GET_TIME();

    //Circular buffer - not using modulo for speed
    gpStat_SampleIndex = (gpStat_SampleIndex < (GP_STAT_NUMBER_OF_SAMPLES-1)) ? (gpStat_SampleIndex+1) : 0;

    //Store sample info
    pSample = &gpStat_Samples[gpStat_SampleIndex];

    pSample->compId = compId;
    pSample->line   = line;
    pSample->pFileName = filename;
    STRNCPY_P(pSample->funcName, funcName, GP_STAT_MAX_NAME_CHARS);
    pSample->time   = currentTime;

    //gpLog_Printf(compId, true, funcName, 0);
    //GP_LOG_SYSTEM_PRINTF("Sample overhead:%lu %i",0,GP_STAT_GET_TIME()-currentTime, (UInt16)gpStat_SampleIndex);
}

//API functions

void gpStat_ReturnSamples(void)
{
    UIntLoop i;
    for(i = 1; i < GP_STAT_NUMBER_OF_SAMPLES+1; i++)
    {
        //Start from oldest sample - current index refers to last filled in sample
        Stat_Sample_t* pSample = &gpStat_Samples[(gpStat_SampleIndex+i) % GP_STAT_NUMBER_OF_SAMPLES];

        if (pSample->compId != 0)
        {
#ifdef GP_DIVERSITY_LOG
            Stat_LogSample(pSample);
#endif //GP_DIVERSITY_LOG
        }
    }
    Stat_InitSampling();
}

#endif
#if GP_STAT_NUMBER_OF_HEAP_SAMPLES > 0
//Measuring general consumption - some filtering can be applied on short term changes and size jumps
#define GP_STAT_HEAP_SAMPLE_SIZE_RESOLUTION 0  //amount of bytes
#define GP_STAT_HEAP_SAMPLE_TIME_RESOLUTION 5000 //5ms

void gpStat_SampleHeap(UInt32 heapInUse)
{
    UInt32 currentTime;
    gpStat_HeapSample_t* pSample;

    currentTime = GP_STAT_GET_TIME();

    if((dist(heapInUse, gpStat_HeapSamples[gpStat_HeapSampleIndex].heapInUse) <= GP_STAT_HEAP_SAMPLE_SIZE_RESOLUTION) || /*difference granularity*/
       (dist(currentTime, gpStat_HeapSamples[gpStat_HeapSampleIndex].time) < GP_STAT_HEAP_SAMPLE_TIME_RESOLUTION) /*time granularity */
       )
    {
        //Don't sample if there is little change or it's a rapid fluctuation
        return;
    }

    //Circular buffer - not using modulo for speed
    gpStat_HeapSampleIndex = (gpStat_HeapSampleIndex < (number_of_elements(gpStat_HeapSamples)-1)) ? (gpStat_HeapSampleIndex+1) : 0;

    //Store sample info
    pSample = &gpStat_HeapSamples[gpStat_HeapSampleIndex];

    pSample->time      = currentTime;
    pSample->heapInUse = heapInUse;
}

void gpStat_ReturnSamplesHeap(void)
{
    UIntLoop i;
    for(i = 1; i < number_of_elements(gpStat_HeapSamples)+1; i++)
    {
        //Start from oldest sample - current index refers to last filled in sample
        gpStat_HeapSample_t* pSample = &gpStat_HeapSamples[(gpStat_HeapSampleIndex+i) % number_of_elements(gpStat_HeapSamples)];

        if (pSample->time != 0)
        {
#ifdef GP_DIVERSITY_LOG
            Stat_LogHeapSample(pSample);
            gpLog_Flush();
#endif //GP_DIVERSITY_LOG
        }
    }
    Stat_InitHeapSampling();
}
#endif //GP_STAT_NUMBER_OF_HEAP_SAMPLES

