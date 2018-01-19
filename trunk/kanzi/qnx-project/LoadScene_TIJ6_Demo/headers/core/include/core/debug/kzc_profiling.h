/**
 * \file
 * Core level components of performance profiler.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZC_PROFILING_H
#define KZC_PROFILING_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>

#include <system/debug/kzs_profiling.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzcDynamicArray;


#define KZC_PROFILING_VALUE_NONE 0          /**< Bit mask for none. Usable as a sorting parameter. */
#define KZC_PROFILING_VALUE_TOTAL_TIME 1    /**< Bit mask for total/cumulative time spent in a function. */
#define KZC_PROFILING_VALUE_SELF_TIME 2     /**< Bit mask for time spent in the function itself (not in children). */
#define KZC_PROFILING_VALUE_HIT_COUNT 4     /**< Bit mask for function hit count. */
#define KZC_PROFILING_VALUE_MINIMUM_TIME 8  /**< Bit mask for minimum time spent in a function. */
#define KZC_PROFILING_VALUE_AVERAGE_TIME 16 /**< Bit mask for average time spent in a function. */
#define KZC_PROFILING_VALUE_MAXIMUM_TIME 32 /**< Bit mask for maximum time spent in a function. */
#define KZC_PROFILING_VALUE_ALL (1 + 2 + 4 + 8 + 16 + 32) /**< Bit mask for all information. */


/** Struct containing output data from profiling. */
struct KzcProfilingSummaryData
{
    kzUint hitCount;            /**< How many times the function was called. Average per profiling sample. */
    kzFloat minimumTime;        /**< Minimum time spent in the function, in ms. */
    kzFloat maximumTime;        /**< Maximum time spent in the function, in ms. */
    kzFloat totalTime;          /**< Total time spent in the function, in ms. Average per profiling sample. */
    kzFloat selfTime;           /**< Time spent in the function but not in any children, in ms. Average per profiling sample. */
    kzFloat averageTime;        /**< Average time spent in the function, in ms. Average per profiling sample. */
};


/**
* Outputs per-function profiling data to Kanzi log with DETAILS log level.
* \param memoryManager Memory manager to use for formatting output.
* \param outputMask Bit mask of enabled output values. See KZC_PROFILING_VALUE_*.
* \param sortMethod Sorting method of values. One of KZC_PROFILING_VALUE_*.
*/
kzsError kzcProfilingOutputList(const struct KzcMemoryManager* memoryManager, kzUint outputMask, kzUint sortMethod);

/**
* Outputs profiling data in tree form to dynamic array.
* \param memoryManager Memory manager to use for formatting output.
* \param outputMask Bit mask of enabled output values. See KZC_PROFILING_VALUE_*.
* \param sortMethod Sorting method of values. One of KZC_PROFILING_VALUE_*.
*/
kzsError kzcProfilingOutputTreeToArray(const struct KzcMemoryManager* memoryManager, kzUint outputMask, kzUint sortMethod, struct KzcDynamicArray** out_results);
/**
* Outputs profiling data in tree form to Kanzi log with DETAILS log level.
* \param memoryManager Memory manager to use for formatting output.
* \param outputMask Bit mask of enabled output values. See KZC_PROFILING_VALUE_*.
* \param sortMethod Sorting method of values. One of KZC_PROFILING_VALUE_*.
*/
kzsError kzcProfilingOutputTree(const struct KzcMemoryManager* memoryManager, kzUint outputMask, kzUint sortMethod);

/** 
 * Returns the profiling summary for all measurements with the specified name. 
 * \param name Name of profiling measurements.
 * \param outputMask Bit mask of enabled output values. See KZC_PROFILING_VALUE_*.
 * \param summary Pointer to KzcProfilingSummaryData struct where the results will be written.
 * \return The number of found measurements matching specified name.
 */
 kzUint kzcProfilingGetSummaryForName(kzString name, kzUint outputMask, struct KzcProfilingSummaryData* summary);


KZ_HEADER_END


#endif
