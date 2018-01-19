/**
* \file
* Threaded memory manager.
* Wraps another memory manager within thread guards.
* The thread guards are enabled by default and can be toggled with ::kzcMemoryThreadedSetLockingEnabled().
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_MEMORY_THREADED_H
#define KZC_MEMORY_THREADED_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;


/**
 * \struct KzcThreadedMemoryManager
 * Threaded memory manager.
 */
struct KzcThreadedMemoryManager;


/**
 * Creates a new memory manager, which wraps another memory manager but introduces thread-safety into
 * allocations.
 */
kzsError kzcMemoryManagerCreateThreadedManager(struct KzcMemoryManager* parentManager, struct KzcMemoryManager** out_memoryManager);

/** Checks whether the given memory manager is threaded memory manager or not. */
kzBool kzcMemoryIsThreadedManager(const struct KzcMemoryManager* memoryManager);

/** Get the parent memory manager from a threaded memory manager. */
struct KzcMemoryManager* kzcMemoryThreadedGetParentManager(const struct KzcMemoryManager* memoryManager);

/** Is locking enabled? */
kzBool kzcMemoryThreadedIsLockingEnabled(const struct KzcMemoryManager* memoryManager);

/**
 * Enable or disable locking on threaded memory manager.
 *
 * Note that ongoing memory management may have unexpected results if locking is turned off while multiple
 * threads are using the manager. Only turn locking on or off when only one thread can be accessing
 * the manager.
 */
void kzcMemoryThreadedSetLockingEnabled(struct KzcMemoryManager* memoryManager, kzBool enabled);


KZ_HEADER_END


#endif
