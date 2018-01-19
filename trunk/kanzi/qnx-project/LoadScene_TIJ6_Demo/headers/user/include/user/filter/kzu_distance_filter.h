/**
* \file
* Specifies distance filter.
* Distance filter accepts or rejects objects that are within given range from specified object.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_DISTANCE_FILTER_H
#define KZU_DISTANCE_FILTER_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;
struct KzuObjectNode;
struct KzuUIDomain;
struct KzuObjectSource;


/**
 * Creates distance filter. All objects that are nearer than given maxDistance from given object are either
 * accepted or rejected depending on whether isExclusive is set or not.
 */
kzsError kzuDistanceFilterCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                 struct KzuObjectSource* input, kzString name, struct KzuObjectNode* object,
                                 const kzFloat maxDistance, kzBool isExclusive, struct KzuObjectSource** out_objectSource);


KZ_HEADER_END


#endif
