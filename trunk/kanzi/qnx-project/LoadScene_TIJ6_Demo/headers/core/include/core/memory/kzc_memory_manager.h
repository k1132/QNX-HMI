/**
* \file
* Core memory manager.
* Memory managers provide memory allocation and deallocation functionality.
* This header file provides the common interface for all Kanzi memory managers.
* There are four different types of Kanzi memory managers: system, pooled, quick and custom. The custom type provides a way to implement
* your own memory manager.
* See \ref kzc_memory_system.h, \ref kzc_memory_pooled.h, \ref kzc_memory_quick.h and \ref kzc_memory_custom.h for descriptions of each of them.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_MEMORY_MANAGER_H
#define KZC_MEMORY_MANAGER_H


#include "kzc_memory_common.h"

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/**
 * \struct KzcMemoryManager
 * Internal structure of a MemoryManager.
 */
struct KzcMemoryManager;


/** Constant for memory manager size that's unspecified. */
#define KZC_MEMORY_MANAGER_SIZE_UNSPECIFIED ((kzSizeT)-1)


/** Frees the memory allocated for a memory manager. */ 
kzsError kzcMemoryManagerDelete(struct KzcMemoryManager* memoryManager);


#ifdef KZC_MEMORY_DEBUG
    /** Allocates arbitrary memory pointer using the given memory manager. */
    #define kzcMemoryAllocPointer(manager_param, pointer_param, size_param, description_param) \
            kzcMemoryAllocPointer_private(manager_param, size_param, (void**)pointer_param, description_param)

    /** Allocates array of arbitrary type using the given memory manager. */
    #define kzcMemoryAllocArray(manager_param, array_param, length_param, description_param) \
            kzcMemoryAllocArray_private(manager_param, length_param, sizeof(*array_param), (void**)&array_param, description_param)

    /** Allocates an object of arbitrary type using the given memory manager. */
    #define kzcMemoryAllocVariable(manager_param, variable_param, description_param) \
            kzcMemoryAllocPointer_private(manager_param, sizeof(*variable_param), (void**)&variable_param, description_param)
#else
    /** Allocates arbitrary memory pointer using the given memory manager. */
    #define kzcMemoryAllocPointer(manager_param, pointer_param, size_param, description_param) \
            kzcMemoryAllocPointer_private(manager_param, size_param, (void**)pointer_param)

    /** Allocates array of arbitrary type using the given memory manager. */
    #define kzcMemoryAllocArray(manager_param, array_param, length_param, description_param) \
            kzcMemoryAllocArray_private(manager_param, length_param, sizeof(*array_param), (void**)&array_param)

    /** Allocates an object of arbitrary type using the given memory manager. */
    #define kzcMemoryAllocVariable(manager_param, variable_param, description_param) \
            kzcMemoryAllocPointer_private(manager_param, sizeof(*variable_param), (void**)&variable_param)
#endif


/** \see kzcMemoryAllocPointer. */
kzsError kzcMemoryAllocPointer_private(const struct KzcMemoryManager* memoryManager, kzSizeT size,
                                       void** out_pointer MEMORY_MANAGER_DEBUG_PARAM_PRIVATE(kzString description));
/** \see kzcMemoryAllocArray */
kzsError kzcMemoryAllocArray_private(const struct KzcMemoryManager* memoryManager, kzUint length, kzSizeT elementSize,
                                     void** out_array MEMORY_MANAGER_DEBUG_PARAM_PRIVATE(kzString description));

/**
 * Reallocates arbitrary memory pointer to the given new size.
 * This function behaves differently from C realloc function such that the given pointer may not be KZ_NULL and
 * the function never returns KZ_NULL in case of success.
 * The function returns a pointer containing the data of the given pointer up to the length of min(newSize, old size).
 * The old pointer is freed if new memory was allocated.
 */
kzsError kzcMemoryReallocPointer(void* pointer, kzSizeT oldSize, kzSizeT newSize, void** out_newPointer);


/** Frees an arbitrary pointer from memory manager. */
kzsError kzcMemoryFreePointer(void* pointer);
/** Frees an array from memory manager. */
kzsError kzcMemoryFreeArray(void* array);
/** Frees a variable from memory manager. */
kzsError kzcMemoryFreeVariable(void* variable);

#ifndef kzcIsValidPointer /* It is possible to override the functionality of kzcIsValidPointer with a macro. For example Kanzi PC-lint configuration does that. */
/** Checks if the given pointer is valid. */
kzBool kzcIsValidPointer(const void* pointer);
#endif
/** Checks if the given index is valid for the given array. */
kzBool kzcIsValidArrayIndex(const void* array, kzUint index);

/** Calculates a checksum of the given pointer. This value can later be used for checking if the memory content has been modified. */
kzU32 kzcMemoryCalculateChecksum(const void* pointer);

/** Gets the memory manager responsible of the given pointer. */
struct KzcMemoryManager* kzcMemoryGetManager(const void* pointer);

/** Returns the length of an array. */
kzUint kzcArrayLength(const void* array);

/** Gets memory manager type. */
enum KzcMemoryManagerType kzcMemoryManagerGetType(const struct KzcMemoryManager* memoryManager);

/** Gets size of memory manager in bytes. Returns KZC_MEMORY_MANAGER_SIZE_NOT_SPECIFIED if not specified. */
kzSizeT kzcMemoryManagerGetSize(const struct KzcMemoryManager* memoryManager);


/** Disowns a memory manager from its owning thread. Effectively allows transferring a memory manager to another thread. */
void kzcMemoryManagerDisownFromThread(struct KzcMemoryManager* memoryManager);


KZ_HEADER_END


#endif
