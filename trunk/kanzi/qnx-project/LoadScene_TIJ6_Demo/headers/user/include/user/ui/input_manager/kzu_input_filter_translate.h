/**
* \file
* Translating input filter.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_INPUT_FILTER_TRANSLATE_H
#define KZU_INPUT_FILTER_TRANSLATE_H

#include <system/debug/kzs_error.h>
#include <system/input/kzs_input.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzsEventQueue;


/** Translate input events. */
kzsError kzuInputFilterTranslateProcessEventQueue(const struct KzsEventQueue* queueIn, struct KzsEventQueue* queueOut, enum KzsInputTranslation translation);


KZ_HEADER_END


#endif
