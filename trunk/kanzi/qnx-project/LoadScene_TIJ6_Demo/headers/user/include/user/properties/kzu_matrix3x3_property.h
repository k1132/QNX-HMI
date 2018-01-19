/**
* \file
* Specifies matrix3x3 property.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_MATRIX3X3_PROPERTY_H
#define KZU_MATRIX3X3_PROPERTY_H


#include <core/util/math/kzc_matrix3x3.h>

#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuPropertyType;


/** 
* \struct KzuMatrix3x3PropertyType
* Structure for matrix3x3 property type.
*/
struct KzuMatrix3x3PropertyType;


/** Creates a new matrix property type. */
kzsError kzuMatrix3x3PropertyTypeCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzcMatrix3x3 defaultValue,
                                        struct KzuMatrix3x3PropertyType** out_matrix3x3PropertyType);
/** Deletes matrix property type. */
kzsError kzuMatrix3x3PropertyTypeDelete(struct KzuMatrix3x3PropertyType* matrix3x3PropertyType);

/** Loads matrix property type from KZB. */
kzsError kzuMatrix3x3PropertyTypeLoadFromKzb(struct KzuMatrix3x3PropertyType* matrix3x3PropertyType, struct KzcInputStream* inputStream);


/** Returns matrix 3x3 property type from property type. */
struct KzuMatrix3x3PropertyType* kzuMatrix3x3PropertyTypeFromPropertyType(const struct KzuPropertyType* propertyType);
/** Returns property type from matrix property type. */
struct KzuPropertyType* kzuMatrix3x3PropertyTypeToPropertyType(const struct KzuMatrix3x3PropertyType* matrix3x3PropertyType);

/** Gets the default value of matrix property type. */
struct KzcMatrix3x3 kzuMatrix3x3PropertyTypeGetDefaultValue(const struct KzuMatrix3x3PropertyType* matrix3x3PropertyType);
/** Gets the default SRT value of matrix property type. 
 * \param out_scale Scale vector of the matrix SRT, not returned when KZ_NULL given as an argument.
 * \param out_rotate Rotate scalar of the matrix SRT in degrees, not returned when KZ_NULL given as an argument.
 * \param out_translate Translate vector of the matrix SRT, not returned when KZ_NULL given as an argument.
 */
void kzuMatrix3x3PropertyTypeGetDefaultSRTValue(const struct KzuMatrix3x3PropertyType* matrix3x3PropertyType, struct KzcVector2* out_scale, kzFloat* out_rotateInDegrees, struct KzcVector2* out_translate);


KZ_HEADER_END


#endif
