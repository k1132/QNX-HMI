/**
* \file
* Coalescing input filter.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_INPUT_FILTER_COALESCE_H
#define KZU_INPUT_FILTER_COALESCE_H


#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzsEventQueue;


/** Coalesce input events. */
kzsError kzuInputFilterCoalesceProcessEventQueue(const struct KzsEventQueue* queueIn, struct KzsEventQueue* queueOut);


KZ_HEADER_END


#endif
