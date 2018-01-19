/**
* \file
* Specifies contains property filter.
* Contains property filter accepts or rejects an object if it contains a property of specified type.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_CONTAINS_PROPERTY_FILTER_H
#define KZU_CONTAINS_PROPERTY_FILTER_H


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


/** Creates property filter. */
kzsError kzuContainsPropertyFilterCreate(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                         kzString name, struct KzuObjectSource** out_objectSource);

/** Loads a contain property filter from KZB. */
kzsError kzuContainsPropertyFilterLoadFromKZB(struct KzuObjectSource* objectSource, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

/** Initializes a contains property filter. */
kzsError kzuContainsPropertyFilterInitialize(struct KzuObjectSource* objectSource, struct KzuObjectSource* input,
                                             const struct KzuPropertyType* propertyType, kzBool isExclusive);

/** Tells if object source is the contains property filter. */
kzBool kzuObjectSourceIsContainsPropertyFilter(const struct KzuObjectSource* objectSource);

/** Gets property type of the filter. */
const struct KzuPropertyType* kzuContainsPropertyFilterGetPropertyType(struct KzuObjectSource* objectSource);

/** Sets property type of the filter. */
void kzuContainsPropertyFilterSetPropertyType(struct KzuObjectSource* objectSource, const struct KzuPropertyType* propertyType);


KZ_HEADER_END


#endif
