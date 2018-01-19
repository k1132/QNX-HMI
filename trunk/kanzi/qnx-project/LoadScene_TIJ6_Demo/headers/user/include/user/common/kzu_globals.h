/**
 * \file
 * Global storage. This module can be used for storing user level global data.
 * Warning: Such global data is not thread safe unless explicitly synchronized.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_GLOBALS_H
#define KZU_GLOBALS_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;


/** Initializes globals. */
kzsError kzuGlobalsInitialize(const struct KzcMemoryManager* memoryManager);

/** Uninitializes globals. */
kzsError kzuGlobalsUninitialize(void);

/** Put data to global storage. */
kzsError kzuGlobalsPut(kzString name, const void* data);

/** Get data from global storage. Returns KZ_NULL if no data is associated with the given name. */
void* kzuGlobalsGet(kzString name);


KZ_HEADER_END


#endif
