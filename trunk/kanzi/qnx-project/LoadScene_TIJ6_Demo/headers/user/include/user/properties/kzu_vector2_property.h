/**
* \file
* Specifies vector2 property.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_VECTOR2_PROPERTY_H
#define KZU_VECTOR2_PROPERTY_H


#include <core/util/math/kzc_vector2.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuPropertyType;


/** 
* \struct KzuVector2PropertyType
* Structure for vector2 property type.
*/
struct KzuVector2PropertyType;


/** Creates a new vector property type. */
kzsError kzuVector2PropertyTypeCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzcVector2 defaultValue,
                                      struct KzuVector2PropertyType** out_vector2PropertyType);
/** Deletes vector property type. */
kzsError kzuVector2PropertyTypeDelete(struct KzuVector2PropertyType* vector2PropertyType);

/** Loads vector property type from KZB. */
kzsError kzuVector2PropertyTypeLoadFromKzb(struct KzuVector2PropertyType* vector2PropertyType, struct KzcInputStream* inputStream);


/** Returns vector2 property type from property type. */
struct KzuVector2PropertyType* kzuVector2PropertyTypeFromPropertyType(const struct KzuPropertyType* propertyType);
/** Returns property type from vector3 property type. */
struct KzuPropertyType* kzuVector2PropertyTypeToPropertyType(const struct KzuVector2PropertyType* vector2PropertyType);

/** Gets the default value of vector property type. */
struct KzcVector2 kzuVector2PropertyTypeGetDefaultValue(const struct KzuVector2PropertyType* vector2PropertyType);


KZ_HEADER_END


#endif
