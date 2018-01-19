/**
* \file
* Utilities for creating objects for debugging purposes.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_DEBUG_OBJECT_GENERATOR_H
#define KZU_DEBUG_OBJECT_GENERATOR_H


#include <system/debug/kzs_error.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuEngine;
struct KzuUIDomain;
struct KzuObjectNode;


/**
* Creates a sphere object node that can be used for debugging.
* Can be used to create sequences of different colored and sized objects for debugging.
* \param index Index of object in sequence.
* \param sequenceLength Length of sequence. Sequence loops after this many objects.
*/
kzsError kzuDebugObjectGeneratorCreateSphere(const struct KzcMemoryManager* memoryManager, const struct KzuEngine* engine,
                                             struct KzuUIDomain* uiDomain, kzUint index, kzUint sequenceLength,
                                             const struct KzuObjectNode** out_object);


KZ_HEADER_END


#endif
