/**
* \file
* Specifies vector3 property.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_VECTOR3_PROPERTY_H
#define KZU_VECTOR3_PROPERTY_H


#include <core/util/math/kzc_vector3.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuPropertyType;


/** 
* \struct KzuVector3PropertyType
* Structure for vector3 property type.
*/
struct KzuVector3PropertyType;


/** Type of vector3 property. */
enum KzuVector3Type
{
    KZU_VECTOR3_TYPE_NORMAL,                    /**< Normal vector3 property. */
    KZU_VECTOR3_TYPE_POSITION_FROM_MATRIX4X4,   /**< Vector3 property value fetch from pipeline 4x4 world matrix position. */
    KZU_VECTOR3_TYPE_DIRECTION_FROM_MATRIX4X4   /**< Vector3 property value fetch from pipeline 4x4 world matrix direction. */
};


/** Creates a new vector property type. */
kzsError kzuVector3PropertyTypeCreate(const struct KzcMemoryManager* memoryManager, kzString name,
                                      enum KzuVector3Type vectorType, struct KzcVector3 defaultValue,
                                      struct KzuVector3PropertyType** out_vector3PropertyType);
/** Deletes vector property type. */
kzsError kzuVector3PropertyTypeDelete(struct KzuVector3PropertyType* vector3PropertyType);

/** Loads vector property type from KZB. */
kzsError kzuVector3PropertyTypeLoadFromKzb(struct KzuVector3PropertyType* vector3PropertyType, struct KzcInputStream* inputStream);


/** Returns vector3 property type from property type. */
struct KzuVector3PropertyType* kzuVector3PropertyTypeFromPropertyType(const struct KzuPropertyType* propertyType);
/** Returns property type from vector3 property type. */
struct KzuPropertyType* kzuVector3PropertyTypeToPropertyType(const struct KzuVector3PropertyType* vector3PropertyType);

/** Gets the default value of vector property type. */
struct KzcVector3 kzuVector3PropertyTypeGetDefaultValue(const struct KzuVector3PropertyType* vector3PropertyType);

/** Gets vector type from vector property. */
enum KzuVector3Type kzuVector3PropertyTypeGetVectorType(const struct KzuVector3PropertyType* vector3PropertyType);


KZ_HEADER_END


#endif
