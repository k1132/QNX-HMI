/**
* \file
* Allows suspending the execution of current thread.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_SLEEP_H
#define KZS_SLEEP_H


#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Suspends the execution of current thread until the time-out interval elapses. */
void kzsSleep(kzUint milliseconds);


KZ_HEADER_END


#endif
