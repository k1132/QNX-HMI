/**
 * \file
 * User header.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_USER_H
#define KZU_USER_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;


/** Initializes the user layer common. */
kzsError kzuUserInitialize(const struct KzcMemoryManager* memoryManager);

/** Uninitializes the user layer common. */
kzsError kzuUserUninitialize(void);


KZ_HEADER_END


#endif
