/**
* \file
* Rotating input filter.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_INPUT_FILTER_ROTATE_H
#define KZU_INPUT_FILTER_ROTATE_H

#include <system/debug/kzs_error.h>
#include <system/input/kzs_input.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzsEventQueue;


/** Translate input events. */
kzsError kzuInputFilterRotateProcessEventQueue(const struct KzsEventQueue* queueIn, struct KzsEventQueue* queueOut, enum KzsInputOrientation angle, kzUint areaWidth, kzUint areaHeight);


KZ_HEADER_END


#endif
