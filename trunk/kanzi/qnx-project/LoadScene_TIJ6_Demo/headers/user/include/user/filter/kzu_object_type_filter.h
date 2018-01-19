/**
* \file
* Specifies object type filter. This filter accepts or rejects specific types of objects.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_OBJECT_TYPE_FILTER_H
#define KZU_OBJECT_TYPE_FILTER_H


#include <user/scene_graph/kzu_object_common.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuObjectSource;
struct KzuUIDomain;


/** Creates an object type filter. */
kzsError kzuObjectTypeFilterCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                   kzString name, struct KzuObjectSource** out_objectSource);

/** Loads an object type filter from KZB. */
kzsError kzuObjectTypeFilterLoadFromKZB(struct KzuObjectSource* objectSource, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

/** Initializes an object type filter. */
kzsError kzuObjectTypeFilterInitialize(struct KzuObjectSource* objectSource, struct KzuObjectSource* input,
                                       KzuObjectType objectType, kzBool isExclusive);


KZ_HEADER_END


#endif
