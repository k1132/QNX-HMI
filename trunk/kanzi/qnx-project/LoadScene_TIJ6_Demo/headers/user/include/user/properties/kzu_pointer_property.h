/**
* \file
* Specifies property that holds a pointer to arbitrary data.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_POINTER_PROPERTY_H
#define KZU_POINTER_PROPERTY_H


#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuUIDomain;
struct KzuPropertyType;


/** 
* \struct KzuPointerPropertyType
* Structure for pointer property type.
*/
struct KzuPointerPropertyType;


/** Creates a new pointer property type. */
kzsError kzuPointerPropertyTypeCreate(const struct KzcMemoryManager* memoryManager, kzString name,
                                      struct KzuPointerPropertyType** out_pointerPropertyType);

/** Creates a new pointer property type with relative path to referenced object. */
kzsError kzuPointerPropertyTypeCreateRelative(const struct KzcMemoryManager* memoryManager, kzString name, kzString defaultPathValue,
                                    struct KzuPointerPropertyType** out_pointerPropertyType);

/** Deletes pointer property type. */
kzsError kzuPointerPropertyTypeDelete(struct KzuPointerPropertyType* pointerPropertyType);

/** Loads pointer property type from KZB. */
kzsError kzuPointerPropertyTypeLoadFromKzb(struct KzuPointerPropertyType* pointerPropertyType, struct KzcInputStream* inputStream,
                                           const struct KzuBinaryFileInfo* file);


/** Returns pointer property type from property type. */
struct KzuPointerPropertyType* kzuPointerPropertyTypeFromPropertyType(const struct KzuPropertyType* propertyType);
/** Converts pointer property type to property type. */
struct KzuPropertyType* kzuPointerPropertyTypeToPropertyType(const struct KzuPointerPropertyType* pointerPropertyType);

/** Gets the default path value of pointer property type. */
kzString kzuPointerPropertyTypeGetDefaultPathValue(const struct KzuPointerPropertyType* pointerPropertyType);


KZ_HEADER_END


#endif
