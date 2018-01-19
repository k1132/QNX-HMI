/**
* \file
* Custom memory manager.
* Custom memory manager provides a way to plug in arbitrary memory allocation mechanisms. A custom Kanzi memory manager can
* be created with ::kzcMemoryManagerCreateCustomManager() by passing your own allocation and deallocation functions.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_MEMORY_CUSTOM_H
#define KZC_MEMORY_CUSTOM_H


#include "kzc_memory_common.h"

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzcCustomMemoryManager;


/** Memory allocation function type. Used for custom memory managers.
* \param customData The customData pointer passed to ::kzcMemoryManagerCreateCustomManager().
* \param size Requested number of bytes to allocate.
* \param out_pointer A pointer that should be set to point to the beginning of the allocated memory area.
* \return The function should return ::KZS_SUCCESS on success.
*/
typedef kzsError (*KzcMemoryAllocFunction)(void* customData, kzSizeT size, void** out_pointer);
/** Memory deallocation function type. Used for custom memory managers.
* \param customData The customData pointer passed to ::kzcMemoryManagerCreateCustomManager().
* \param pointer Pointer to the beginning of the memory area to free.
* \return The function should return ::KZS_SUCCESS on success.
*/
typedef kzsError (*KzcMemoryFreeFunction)(void* customData, void* pointer);


/**
 * Creates a new memory manager, which allocates the memory with custom memory allocation functions.
 * \param allocator Memory allocation function to call when memory is allocated with this memory manager.
 * \param deallocator Memory deallocation function to call when memory is freed with this memory manager.
 * \param customData Arbitrary pointer passed to the allocator and deallocator functions.
 * \param out_memoryManager A pointer that is set to point to the new memory manager on success.
 * \return ::KZS_SUCCESS on success.
 */
kzsError kzcMemoryManagerCreateCustomManager(KzcMemoryAllocFunction allocator, KzcMemoryFreeFunction deallocator,
                                             void* customData, struct KzcMemoryManager** out_memoryManager);


KZ_HEADER_END


#endif
