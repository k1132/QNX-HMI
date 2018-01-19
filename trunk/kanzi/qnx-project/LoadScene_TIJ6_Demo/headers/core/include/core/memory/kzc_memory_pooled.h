/**
* \file
* Pooled memory manager.
* The pooled memory manager allocates memory from a constant-sized preallocated memory pools.
* This manager type tries to minimize memory fragmentation and is suitable for most common use cases.
* However, it is not intended for real-time memory allocation.
*
* This memory manager will not allocate more memory when there is no more free space in the memory pools,
* instead it will return ::KZS_ERROR_OUT_OF_MEMORY error.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_MEMORY_POOLED_H
#define KZC_MEMORY_POOLED_H


#include "kzc_memory_common.h"

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;


/** Creates a new pooled memory manager, which allocates the memory from preallocated memory pools.
* This memory manager will not allocate more memory when there is no more free space in the memory pools,
* instead it will return ::KZS_ERROR_OUT_OF_MEMORY error.
* \param parentManager A valid memory manager that is used for allocating the memory pools. This could be e.g.
                       a system memory manager (see \ref kzc_memory_system.h).
* \param poolCount Number of memory pools.
* \param poolSize Size of each memory pool.
* \param out_manager A pointer that is set to point to the new pooled memory manager on success.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzcMemoryManagerCreatePooledManager(const struct KzcMemoryManager* parentManager, kzUint poolCount,
                                             kzSizeT poolSize, struct KzcMemoryManager** out_manager);

/**
 * Dumps the memory content to the log using the ::KZS_LOG_LEVEL_INFO log level.
 * This function is only available for the pooled memory manager.
 * \param memoryManager The memory manager which contents to print.
 * \param memoryMap If ::KZ_TRUE, prints out offsets of each block in a pool.
 * \param sortBySize If ::KZ_TRUE, all memory allocations will be listed from the smallest to largest.
 *                   Otherwise, the order is the order in memory.
 * \return ::KZS_ERROR_ILLEGAL_ARGUMENT if the memory manager is not a pooled memory manager, ::KZS_SUCCESS on success.
 */
kzsError kzcMemoryDump(const struct KzcMemoryManager* memoryManager, kzBool memoryMap, kzBool sortBySize);

/** Logs all active memory allocations and their descriptions allocated with the given memory manager
* using the ::KZS_LOG_LEVEL_DETAIL log level.
* This function is only available for the pooled memory manager.
* \param memoryManager The memory manager which contents to print.
* \return ::KZS_ERROR_ILLEGAL_ARGUMENT if the memory manager is not a pooled memory manager, ::KZS_SUCCESS on success.
*/
kzsError kzcMemoryPrintDebugAllocations(const struct KzcMemoryManager* memoryManager);

/** Gets the maximum available block size of a pooled memory manager. */
kzSizeT kzcMemoryPooledGetMaximumAvailableSize(const struct KzcMemoryManager* memoryManager);

#ifdef KZC_MEMORY_MEASURE
/** Gets peak (lowest among the lifetime) maximum available block size from pooled memory manager. */
kzSizeT kzcMemoryPooledGetPeakMaximumAvailableSize(const struct KzcMemoryManager* memoryManager);
#endif


KZ_HEADER_END


#endif
