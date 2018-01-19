/**
* \file
* General wrapper utilities.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_WRAPPER_H
#define KZS_WRAPPER_H


#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Converts a NULL value of a pointer to KZ_NULL value. For valid pointers does nothing. */
#define KZS_WRAP_NULL(pointer) ((pointer) == NULL ? KZ_NULL : (pointer))


KZ_HEADER_END


#endif
