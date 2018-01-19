/**
* \file
* Memory manager private members.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_MEMORY_BASE_H
#define KZC_MEMORY_BASE_H


#include "kzc_memory_common.h"

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>
#include <system/thread/kzs_thread.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;


/** Memory manager delete function type definition. */
typedef kzsError (*KzcMemoryManagerDeletor)(struct KzcMemoryManager* memoryManager);
/** Memory manager alloc function type definition. */
typedef kzsError (*KzcMemoryAllocator)(const struct KzcMemoryManager* memoryManager, kzSizeT size, void** out_pointer MEMORY_MANAGER_DEBUG_PARAM_PRIVATE(kzString description));
/** Memory manager dealloc function type definition. */
typedef kzsError (*KzcMemoryDeallocator)(const struct KzcMemoryManager* memoryManager, void* pointer MEMORY_MANAGER_DEBUG_PARAM_PRIVATE(kzString description));


/** Memory manager. */
struct KzcMemoryManager
{
    enum KzcMemoryManagerType type; /**< Type of the memory manager. */
    kzSizeT size; /**< Total size for the memory manager, KZC_MEMORY_MANAGER_SIZE_UNSPECIFIED if not specified. */
    KzcMemoryManagerDeletor deletor; /**< Memory manager deletor function. */
    KzcMemoryAllocator allocator; /**< Memory allocator function. */
    KzcMemoryDeallocator deallocator; /**< Memory deallocator function. */
    KzsThreadId ownerThread; /**< The thread that created the memory manager. */
};


#ifdef KZC_MEMORY_DEBUG
#define KZC_MEMORY_MANAGER_GUARD_PRE_SIZE sizeof(kzSizeT)
#define KZC_MEMORY_MANAGER_GUARD_POST_SIZE sizeof(kzSizeT)
#endif


/** Initializes a memory manager. */
void kzcMemoryManagerInitialize_protected(struct KzcMemoryManager* manager, enum KzcMemoryManagerType type, KzcMemoryManagerDeletor deletor,
                                          KzcMemoryAllocator allocator, KzcMemoryDeallocator deallocator, kzSizeT size);

#if defined KZC_MEMORY_DEBUG && defined KZC_MEMORY_DEBUG_GUARD_AGGRESSIVELY
/** Fills the given pointer with guard data. */
void kzcMemoryFillUnallocated(kzByte* pointer, kzSizeT size);

/** Checks if the given pointer contains proper memory guards. */
kzBool kzcMemoryCheckUnallocated(const kzByte* pointer, kzSizeT size);
#endif


KZ_HEADER_END


#endif
