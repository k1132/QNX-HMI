/**
 * \file
 * Generic sorting functions.
 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZC_SORT_H
#define KZC_SORT_H


#include "kzc_comparator.h"

#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Sorts the given buffer of elementCount elements with the given comparator. Size of the elements is determined automatically. */
#define kzcSortArray(buffer_param, length_param, comparator_param) \
        kzcSort(buffer_param, length_param, sizeof(*buffer_param), comparator_param)
/**
 * Sorts the given buffer of elementCount elements with the given comparator and given context.
 * Size of the elements is determined automatically.
 */
#define kzcSortArrayWithContext(buffer_param, length_param, comparator_param, context_param) \
        kzcSortWithContext(buffer_param, length_param, sizeof(*buffer_param), comparator_param, context_param)


/** Sorts the given buffer of elementCount elements, each of size elementSize, with the given comparator. Unstable sorting method. */
void kzcSort(void* buffer, kzUint elementCount, kzUint elementSize, KzcComparatorFunction comparator);

/**
 * Sorts the given buffer of elementCount elements, each of size elementSize, with the given comparator.
 * Additionally an arbitrary context can be given as parameter, which is passed to the comparator.
 * Unstable sorting method.
 */
void kzcSortWithContext(void* buffer, kzUint elementCount, kzUint elementSize, KzcComparatorWithContextFunction comparator,
                        const void* context);


KZ_HEADER_END


#endif
