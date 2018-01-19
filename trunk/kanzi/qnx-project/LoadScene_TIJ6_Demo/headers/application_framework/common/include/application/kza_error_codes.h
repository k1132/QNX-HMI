/**
 * \file
 * Application framework error codes.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZA_ERROR_CODES_H
#define KZA_ERROR_CODES_H


#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Application framework error codes have reserved range of 40000 - 49999 */

/* Framework error codes. (40000 - 49999) */
#define KZA_ERROR_INITIALIZATION_FAILED (kzsError)40001 /**< Framework failed to initialize. */
#define KZA_ERROR_INVALID_THREAD (kzsError)40002 /**< Invalid thread was used for function call. */


KZ_HEADER_END


#endif
