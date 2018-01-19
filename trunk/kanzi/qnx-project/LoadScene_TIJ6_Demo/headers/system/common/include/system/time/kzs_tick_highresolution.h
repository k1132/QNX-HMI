/**
* \file
* Provides relative time in microseconds from the system.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_TICK_HIGHRESOLUTION_H
#define KZS_TICK_HIGHRESOLUTION_H


#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/**
 * Returns current time from the system in microseconds.
 * Values should be only used relative to each other because starting time is not specified.
 */
kzU64 kzsTimeGetCurrentTimeMicroseconds();


KZ_HEADER_END


#endif
