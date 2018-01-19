/**
* \file
* Specifies tag filter.
* Tag filter is used to collect all objects that have been assigned a certain tag.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_TAG_FILTER_H
#define KZU_TAG_FILTER_H


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
struct KzuPropertyType;


/** Creates tag filter. */
kzsError kzuTagFilterCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                            kzString name, struct KzuObjectSource** out_objectSource);

/** Loads a tag filter from KZB. */
kzsError kzuTagFilterLoadFromKZB(struct KzuObjectSource* objectSource, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

/** Tells if object source is tag filter. */
kzBool kzuObjectSourceIsTagFilter(const struct KzuObjectSource* objectSource);

/** Initializes a tag filter. */
kzsError kzuTagFilterInitialize(struct KzuObjectSource* objectSource, struct KzuObjectSource* input,
                                struct KzuPropertyType* const* inclusiveTags, struct KzuPropertyType* const* exclusiveTags,
                                kzBool isExclusive);


/** Converts object source to tag filter. */
struct KzuTagFilter* kzuTagFilterFromObjectSource_private(struct KzuObjectSource* objectSource);


KZ_HEADER_END


#endif
