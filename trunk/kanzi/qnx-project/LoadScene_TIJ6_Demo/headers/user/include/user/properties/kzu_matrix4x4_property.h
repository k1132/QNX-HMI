/**
* \file
* Specifies matrix4x4 property.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_MATRIX4X4_PROPERTY_H
#define KZU_MATRIX4X4_PROPERTY_H


#include <core/util/math/kzc_matrix4x4.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuPropertyType;


/** 
* \struct KzuMatrix4x4PropertyType
* Structure for matrix4x4 property type.
*/
struct KzuMatrix4x4PropertyType;


/** Creates a new matrix property type. */
kzsError kzuMatrix4x4PropertyTypeCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzcMatrix4x4 defaultValue,
                                        struct KzuMatrix4x4PropertyType** out_matrix4x4PropertyType);
/** Deletes matrix property type. */
kzsError kzuMatrix4x4PropertyTypeDelete(struct KzuMatrix4x4PropertyType* matrix4x4PropertyType);

/** Loads matrix property type from KZB. */
kzsError kzuMatrix4x4PropertyTypeLoadFromKzb(struct KzuMatrix4x4PropertyType* matrix4x4PropertyType, struct KzcInputStream* inputStream);


/** Returns matrix 4x4 property type from property type. */
struct KzuMatrix4x4PropertyType* kzuMatrix4x4PropertyTypeFromPropertyType(const struct KzuPropertyType* propertyType);
/** Returns property type from matrix property type. */
struct KzuPropertyType* kzuMatrix4x4PropertyTypeToPropertyType(const struct KzuMatrix4x4PropertyType* matrix4x4PropertyType);

/** Gets the default value of matrix property type. */
struct KzcMatrix4x4 kzuMatrix4x4PropertyTypeGetDefaultValue(const struct KzuMatrix4x4PropertyType* matrix4x4PropertyType);
/** Gets the default SRT value of matrix property type. 
 * \param out_scale Scale vector of the matrix SRT, not returned when KZ_NULL given as an argument.
 * \param out_rotate Rotate vector of the matrix SRT in degrees, not returned when KZ_NULL given as an argument.
 * \param out_translate Translate vector of the matrix SRT, not returned when KZ_NULL given as an argument.
*/
void kzuMatrix4x4PropertyTypeGetDefaultSRTValue(const struct KzuMatrix4x4PropertyType* matrix4x4PropertyType, struct KzcVector3* out_scale, struct KzcVector3* out_rotateInDegrees, struct KzcVector3* out_translate);


KZ_HEADER_END


#endif
