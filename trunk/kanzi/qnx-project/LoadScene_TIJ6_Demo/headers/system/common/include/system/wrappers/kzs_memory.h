/**
* \file
* System memory manager.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_MEMORY_H
#define KZS_MEMORY_H


#include <system/debug/kzs_counter.h>
#include <system/wrappers/kzs_wrapper.h>

#include <stddef.h>
#include <stdlib.h>
#include <string.h>


KZ_HEADER_BEGIN


/** Enable debug output for every allocation and deallocation of system memory. */
#define DEBUG_ALLOCATIONS 0

#if DEBUG_ALLOCATIONS
#include <stdio.h>
#endif


/** Memory allocation size type. */
typedef size_t kzSizeT;


/** Initialize system memory management. */
kzsError kzsMemoryInitialize(void);

/** Uninitialize system memory management. */
kzsError kzsMemoryUninitialize(void);


/** System level malloc. */
void* kzsMalloc(kzSizeT size);

/** System level malloc. */
void* kzsRealloc(void* pointer, kzSizeT newSize);

/** System level free. */
void kzsFree(void* pointer);

/** System level memcpy. */
KZ_INLINE void kzsMemcpy(void* destinationPointer, const void* sourcePointer, kzSizeT size)
{
    memcpy(destinationPointer, sourcePointer, size);
    kzsCounterIncrease("kzsMemcpy");
}

/** System level memmove. */
KZ_INLINE void kzsMemmove(void* destinationPointer, const void* sourcePointer, kzSizeT size)
{
    memmove(destinationPointer, sourcePointer, size);
    kzsCounterIncrease("kzsMemmove");
}

/** System level memset. */
KZ_INLINE void kzsMemset(void* pointer, kzInt valueToSet, kzSizeT size)
{
    memset(pointer, valueToSet, size);
    kzsCounterIncrease("kzsMemset");
}


/** Gets the number of active memory allocations. This returns a non-zero number only in debug builds. */
kzUint kzsMemoryGetAllocationCount(void);

/** Resets the number of active memory allocations. */
void kzsMemoryResetAllocationCount(void);


KZ_HEADER_END


#endif
