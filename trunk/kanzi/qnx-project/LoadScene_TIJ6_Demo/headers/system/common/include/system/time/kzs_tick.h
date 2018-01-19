/**
* \file
* Provides relative time in milliseconds from the system.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_TICK_H
#define KZS_TICK_H


#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/**
 * Returns current time from the system in milliseconds. The returned value is guaranteed to be monotonic.
 * Values should be only used relative to each other because starting time is not specified.
 */
kzUint kzsTimeGetCurrentTimestamp(void);


KZ_HEADER_END


#endif
