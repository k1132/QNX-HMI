/**
* \file
* Specifies vector4 property.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_VECTOR4_PROPERTY_H
#define KZU_VECTOR4_PROPERTY_H


#include <core/util/math/kzc_vector4.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuPropertyType;


/** 
* \struct KzuVector4PropertyType
* Structure for vector4 property type.
*/
struct KzuVector4PropertyType;


/** Creates a new vector property type. */
kzsError kzuVector4PropertyTypeCreate(const struct KzcMemoryManager* memoryManager, kzString name,
                                      struct KzcVector4 defaultValue, struct KzuVector4PropertyType** out_vector4PropertyType);
/** Deletes vector property type. */
kzsError kzuVector4PropertyTypeDelete(struct KzuVector4PropertyType* vector4PropertyType);

/** Loads vector property type from KZB. */
kzsError kzuVector4PropertyTypeLoadFromKzb(struct KzuVector4PropertyType* vector4PropertyType, struct KzcInputStream* inputStream);


/** Returns vector4 property type from property type. */
struct KzuVector4PropertyType* kzuVector4PropertyTypeFromPropertyType(const struct KzuPropertyType* propertyType);
/** Returns property type from vector4 property type. */
struct KzuPropertyType* kzuVector4PropertyTypeToPropertyType(const struct KzuVector4PropertyType* vector4PropertyType);

/** Gets the default value of vector property type. */
struct KzcVector4 kzuVector4PropertyTypeGetDefaultValue(const struct KzuVector4PropertyType* vector4PropertyType);


KZ_HEADER_END


#endif
