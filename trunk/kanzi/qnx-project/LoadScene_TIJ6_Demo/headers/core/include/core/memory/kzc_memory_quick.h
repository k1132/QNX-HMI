/**
* \file
* Quick memory manager.
* The quick memory manager allocates memory from a constant-sized preallocated memory chunk in linear order.
* This manager type is optimized for speed and is intended for real-time memory allocation, such as
* temporary allocations for each rendering frame. The quick memory manager is not thread-safe.
*
* The quick memory manager does not have complicated internal bookkeeping structures, it simply
* keeps a pointer to the last allocated block and satisfies any following allocation by assigning
* it space directly following the last allocated block. Deallocation of individual blocks is not
* supported at all. This means that this memory manager is prone to memory fragmentation and
* should not be used for other than temporary allocations. Every time the current allocated chunk
* of memory runs out, the quick memory manager allocates another one of roughly the same size
* (or the requested size in the case it is larger than the current chunk's size).
*
* Since the quick memory manager does not support deallocation of individual pointers, the whole
* chunk of memory must be deallocated at once using ::kzcMemoryManagerResetQuickManager(). Notice
* that this will invalidate all memory allocated with the same quick memory manager.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_MEMORY_QUICK_H
#define KZC_MEMORY_QUICK_H


#include "kzc_memory_common.h"

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzcQuickMemoryManager;


/**
 * Creates a new quick memory manager, which allocates the memory linearly from a preallocated chunk of memory.
 * See the top of this file for more information on the quick memory manager.
 * \param parentManager The memory manager that is used for allocating the memory chunks.
 *                      This can be e.g. a system memory manager (\ref kzc_memory_system.h).
 * \param size Size of the initial memory chunk.
 * \param out_memoryManager A pointer that is set to point to the new quick manager manager on success.
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzcMemoryManagerCreateQuickManager(const struct KzcMemoryManager* parentManager, kzSizeT size,
                                            struct KzcMemoryManager** out_memoryManager);

/** Checks whether the given memory manager is a quick memory manager or not.
* \param memoryManager A valid memory manager.
* \return ::KZ_TRUE if the memory manager is a quick memory manager, otherwise ::KZ_FALSE.
*/
kzBool kzcMemoryIsQuickManager(const struct KzcMemoryManager* memoryManager);

/**
 * Frees every pointer allocated with the given quick memory manager.
 * \param memoryManager A valid quick memory manager.
 * \return ::KZS_ERROR_ILLEGAL_OPERATION if the memory manager is not a quick memory manager, ::KZS_SUCCESS on success.
 */
kzsError kzcMemoryManagerResetQuickManager(const struct KzcMemoryManager* memoryManager);


KZ_HEADER_END


#endif
