/**
* \file
* Specifies sort object source for material type.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_SORT_OBJECT_SOURCE_H
#define KZU_SORT_OBJECT_SOURCE_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuUIDomain;
struct KzuObjectSource;


/** Creates an object source which performs sorting. */
kzsError kzuSortObjectSourceCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                   kzString name, struct KzuObjectSource** out_objectSource);

/** Creates an object source which performs sorting by material type. */
kzsError kzuSortByShaderObjectSourceCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                           struct KzuObjectSource* input, kzString name, struct KzuObjectSource** out_objectSource);

/** Creates an object source which performs sorting by object view z value. */
kzsError kzuSortByZObjectSourceCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                      struct KzuObjectSource* input, kzString name, kzBool frontToBack,
                                      struct KzuObjectSource** out_objectSource);


/** Loads sort object source from KZB. */
kzsError kzuSortObjectSourceLoadFromKZB(struct KzuObjectSource* objectSource, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);


KZ_HEADER_END


#endif
