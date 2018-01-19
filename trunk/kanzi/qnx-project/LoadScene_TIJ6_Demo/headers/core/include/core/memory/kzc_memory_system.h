/**
* \file
* System memory manager.
* System memory manager simply allocates and deallocates memory with the C library's malloc() and free() functions.
* This memory manager is thread-safe in POSIX-compatible operating systems.
* When using KzaApplication, the system memory manager returned by ::kzaApplicationGetSystemMemoryManager() can be used.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_MEMORY_SYSTEM_H
#define KZC_MEMORY_SYSTEM_H


#include "kzc_memory_common.h"

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;


/** Creates a new memory manager, which allocates and deallocates memory with the C library's malloc() and free() functions.
* \param out_manager A pointer that is set to point to the new memory manager on success.
* \return ::KZS_SUCCESS on success.
*/
kzsError kzcMemoryManagerCreateSystemManager(struct KzcMemoryManager** out_manager);


KZ_HEADER_END


#endif
