/**
* \file
* Core memory manager base definitions and functions.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_MEMORY_COMMON_H
#define KZC_MEMORY_COMMON_H


#include <system/kzs_types.h>
#include <system/wrappers/kzs_memory.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/**
 * If defined, the following memory debugging features are enabled:
 * <ul>
 *   <li>Memory allocations are tracked with string descriptions. This uses some extra memory.
 *   <li>Guard data is written and checked in the beginning and end of allocated memory. This also uses more memory and reduces performance slightly.
 *   <li>Checks that memory managers are invoked only on the thread that created them.
 * </ul>
 */
#ifdef _DEBUG
#define KZC_MEMORY_DEBUG
#define KZC_MEMORY_MEASURE
#define KZC_MEMORY_DEBUG_CHECK_THREAD
#endif

#if 0
/**
 * If defined, all unallocated memory in pooled memory manager is written with guard data and checked while allocating.
 * This does not use any additional memory, but can severely reduce performance.
 * This flag has no effect unless KZC_MEMORY_DEBUG is enabled as well.
 */
#define KZC_MEMORY_DEBUG_GUARD_AGGRESSIVELY
#if 1
/**
 * If defined, a released memory is NOT marked as available for reusing. This helps debugging by ensuring that
 * kzcIsValidPointer always returns KZ_FALSE after the pointer has been freed, because the same address cannot be reallocated.
 * When this is enabled, repeated alloc/free will eventually cause an out of memory error.
 * This flag has no effect unless both KZC_MEMORY_DEBUG and KZC_MEMORY_DEBUG_GUARD_AGGRESSIVELY are enabled as well.
 */
#define KZC_MEMORY_DEBUG_PREVENT_REUSE
#endif
#endif


#ifdef KZC_MEMORY_DEBUG
    /** This macro is used to add description parameter for memory management functions. */
    #define MEMORY_MANAGER_DEBUG_PARAM_PRIVATE(x) , x
#else
    /** This macro is used to add description parameter for memory management functions. */
    #define MEMORY_MANAGER_DEBUG_PARAM_PRIVATE(x)
#endif


/** Type of a memory manager. */
enum KzcMemoryManagerType {
    KZC_MEMORY_MANAGER_TYPE_SYSTEM, /**< System memory manager. */
    KZC_MEMORY_MANAGER_TYPE_POOLED, /**< Pooled memory manager. */
    KZC_MEMORY_MANAGER_TYPE_QUICK,  /**< Quick memory manager. */
    KZC_MEMORY_MANAGER_TYPE_CUSTOM  /**< Custom memory manager. */
};


KZ_HEADER_END


#endif
