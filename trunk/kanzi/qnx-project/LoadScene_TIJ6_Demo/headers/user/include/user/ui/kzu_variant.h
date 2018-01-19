/**
* \file
* Value variant.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_VARIANT_H
#define KZU_VARIANT_H


#include <user/properties/kzu_property_common.h>
#include <user/properties/kzu_property_manager.h>
#include <user/properties/kzu_property.h>

#include <core/util/math/kzc_vector2.h>
#include <core/util/math/kzc_vector3.h>
#include <core/util/math/kzc_vector4.h>
#include <core/util/math/kzc_matrix2x2.h>
#include <core/util/math/kzc_matrix3x3.h>
#include <core/util/math/kzc_matrix4x4.h>
#include <core/util/color/kzc_color.h>
#include <core/util/string/kzc_string.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/**
 * \struct KzuVariant
 * Union container for manipulating an object from a heterogeneous set of types in a uniform manner.
 */
struct KzuVariant;


/** Creates an empty variant object. */
kzsError kzuVariantCreate(const struct KzcMemoryManager* memoryManager, struct KzuVariant** out_variant);
/** Deletes a variant object. */
kzsError kzuVariantDelete(struct KzuVariant* variant);

/** Set a variant to be empty. Empty variants are considered invalid. */
kzsError kzuVariantSetEmpty(struct KzuVariant* variant);
/** Checks if a variant is empty. Empty variants are considered invalid. */
kzBool kzuVariantIsEmpty(const struct KzuVariant* variant);
/** Get the type of the value stored in a variant. */
enum KzuPropertyDataType kzuVariantGetType(const struct KzuVariant* variant);

/** Initialize a variant with a kzFloat value. */
kzsError kzuVariantSetFloat(struct KzuVariant* variant, kzFloat value);
/** Set a float field of a variant. */
kzsError kzuVariantSetFloatWithField(struct KzuVariant* variant, enum KzuPropertyField field, kzFloat value);
/** Get the kzFloat value stored in a variant. */
kzFloat kzuVariantGetFloat(const struct KzuVariant* variant);
/** Get the kzFloat value stored in a variant, also use field. */
kzFloat kzuVariantGetFloatWithField(const struct KzuVariant* variant, enum KzuPropertyField field);
/** Initialize a variant with a kzInt value. */
kzsError kzuVariantSetInt(struct KzuVariant* variant, kzInt value);
/** Get the kzInt value stored in a variant. */
kzInt kzuVariantGetInt(const struct KzuVariant* variant);
/** Initialize a variant with a kzBool value. */
kzsError kzuVariantSetBool(struct KzuVariant* variant, kzBool value);
/** Get the kzBool value stored in a variant. */
kzBool kzuVariantGetBool(const struct KzuVariant* variant);
/** Initialize a variant with a KzcColorRGBA value. */
kzsError kzuVariantSetColor(struct KzuVariant* variant, struct KzcColorRGBA value);
/** Get the KzcColorRGBA value stored in a variant. */
struct KzcColorRGBA kzuVariantGetColor(const struct KzuVariant* variant);
/** Initialize a variant with a KzcVector2 value. */
kzsError kzuVariantSetVector2(struct KzuVariant* variant, struct KzcVector2 value);
/** Get the KzcVector2 value stored in a variant. */
struct KzcVector2 kzuVariantGetVector2(const struct KzuVariant* variant);
/** Initialize a variant with a KzcVector3 value. */
kzsError kzuVariantSetVector3(struct KzuVariant* variant, struct KzcVector3 value);
/** Get the KzcVector3 value stored in a variant. */
struct KzcVector3 kzuVariantGetVector3(const struct KzuVariant* variant);
/** Initialize a variant with a KzcVector4 value. */
kzsError kzuVariantSetVector4(struct KzuVariant* variant, struct KzcVector4 value);
/** Get the KzcVector4 value stored in a variant. */
struct KzcVector4 kzuVariantGetVector4(const struct KzuVariant* variant);
/** Initialize a variant with a KzcMatrix2x2 value. */
kzsError kzuVariantSetMatrix2x2(struct KzuVariant* variant, struct KzcMatrix2x2 value);
/** Get the KzcMatrix2x2 value stored in a variant. */
struct KzcMatrix2x2 kzuVariantGetMatrix2x2(const struct KzuVariant* variant);
/** Initialize a variant with a KzcMatrix3x3 value. */
kzsError kzuVariantSetMatrix3x3(struct KzuVariant* variant, struct KzcMatrix3x3 value);
/** Initialize a variant with KzcMatrix3x3 SRT values. */
kzsError kzuVariantSetMatrix3x3SRT(struct KzuVariant* variant, const struct KzcVector2* scale, kzFloat rotation, const struct KzcVector2* translation);
/** Get the KzcMatrix3x3 value stored in a variant. */
struct KzcMatrix3x3 kzuVariantGetMatrix3x3(const struct KzuVariant* variant);
/** Get the KzcMatrix3x3 SRT values stored in a variant. */
void kzuVariantGetMatrix3x3SRT(const struct KzuVariant* variant, struct KzcVector2* out_scale, kzFloat* out_rotation, struct KzcVector2* out_translation);
/** Initialize a variant with a KzcMatrix4x4 value. */
kzsError kzuVariantSetMatrix4x4(struct KzuVariant* variant, struct KzcMatrix4x4 value);
/** Initialize a variant with KzcMatrix4x4 SRT values. */
kzsError kzuVariantSetMatrix4x4SRT(struct KzuVariant* variant, const struct KzcVector3* scale, const struct KzcVector3* rotation, const struct KzcVector3* translation);
/** Get the KzcMatrix4x4 value stored in a variant. */
struct KzcMatrix4x4 kzuVariantGetMatrix4x4(const struct KzuVariant* variant);
/** Get the KzcMatrix4x4 SRT values stored in a variant. */
void kzuVariantGetMatrix4x4SRT(const struct KzuVariant* variant, struct KzcVector3* out_scale, struct KzcVector3* out_rotation, struct KzcVector3* out_translation);
/** Initialize a variant with a kzString value. */
kzsError kzuVariantSetString(struct KzuVariant* variant, kzString value);
/** Initialize a variant with a kzString value without copying the value.
* The variant will take possession of the string. Only use this if ready to relinquish the ownership.
*/
kzsError kzuVariantSetStringWithoutCopy(struct KzuVariant* variant, kzMutableString value);
/** Get the kzString value stored in a variant. */
kzString kzuVariantGetString(const struct KzuVariant* variant);
/** Initialize a variant with a pointer value. */
kzsError kzuVariantSetPointer(struct KzuVariant* variant, void* value);
/** Initialize a variant with a resource value. */
kzsError kzuVariantSetPointerResource(struct KzuVariant* variant, struct KzuResource* resource);
/** Initialize a variant with a relative path. */
kzsError kzuVariantSetPointerRelativePath(struct KzuVariant* variant, kzString path);
/** Get the pointer value stored in a variant. */
void* kzuVariantGetPointer(const struct KzuVariant* variant);

/** Initialize a variant with a resourceID value. */
kzsError kzuVariantSetResourceID(struct KzuVariant* variant, kzString value);
/** Get the pointer value stored in a variant. */
kzString kzuVariantGetResourceID(const struct KzuVariant* variant);

/** Check if variants are equal. Empty variants are not equal to each other.
* KZU_PROPERTY_DATA_TYPE_STRUCT and KZU_PROPERTY_DATA_TYPE_ARRAY data types are not supported.
* \return KZ_TRUE if the variants are equal, KZ_FALSE otherwise.
*/
kzBool kzuVariantIsEqual(const struct KzuVariant* variantA, const struct KzuVariant* variantB);

/** Copy a variant. */
kzsError kzuVariantCopy(struct KzuVariant* targetVariant, const struct KzuVariant* sourceVariant);

/** Resolve the actual data type of a variant, including the field.
* \param variant Variant to examine.
* \param field Field.
* \return Data type.
*/
enum KzuPropertyDataType kzuVariantResolveType(const struct KzuVariant* variant, enum KzuPropertyField field);

/** Cast a variant into the target variant.
* \param targetVariant The variant which value is written.
* \param targetDataType ::KzuPropertyDataType to use as the target variant's data type.
* \param sourceVariant The variant which value is read.
* \param out_cast Set on success. The value is KZ_TRUE if the cast succeeded, otherwise KZ_FALSE.
* \return KZS_SUCCESS on success.
*/
kzsError kzuVariantCast(struct KzuVariant* targetVariant, enum KzuPropertyDataType targetDataType, const struct KzuVariant* sourceVariant, kzBool* out_cast);

/**
* Gets an object's property from a property manager and sets the property value to the given variant.
* \param propertyManager The property manager to use.
* \param object Object owning the property to read.
* \param propertyType ::KzuPropertyType of the property to read.
* \param field The field to read from the property.
* \param variant Previously created variant which value is set.
* \param out_found Set on success. The value is KZ_TRUE if the property was found, otherwise KZ_FALSE.
* \return KZS_SUCCESS on success, KZS_ERROR_ENUM_OUT_OF_RANGE in case of unsuitable data type or field.
*/
kzsError kzuVariantInitializeFromProperty(const struct KzuPropertyManager* propertyManager,
                                          const void* object,
                                          const struct KzuPropertyType* propertyType, enum KzuPropertyField field,
                                          struct KzuVariant* variant, kzBool* out_found);

/** Sets an object's property from a variant.
* \param variant Variant which value is read.
* \param propertyManager The property manager to use.
* \param object Object owning the property to set.
* \param propertyType ::KzuPropertyType of the property to set.
* \param field ::KzuPropertyField of the property to set.
* \param out_found Set on success. The value is KZ_TRUE if the property was written, otherwise KZ_FALSE.
* \return KZS_SUCCESS on success, KZU_ERROR_WRONG_PROPERTY_DATA_TYPE if the field is not suitable, KZS_ERROR_ENUM_OUT_OF_RANGE if the variant data type is invalid.
*/
kzsError kzuVariantSetToProperty(const struct KzuVariant* variant, const struct KzuPropertyManager* propertyManager, const void* object,
                                 const struct KzuPropertyType* propertyType, enum KzuPropertyField field,
                                 kzBool* out_written);

/** Changes the value and the type of the variant to a sub-value and a sub-type of the variant.
* \param variant Variant which value is filtered.
* \param field The field to filter by.
* \return KZS_SUCCESS on success, KZU_ERROR_WRONG_PROPERTY_DATA_TYPE if the field is not suitable for filtering,
          KZS_ERROR_ENUM_OUT_OF_RANGE if the variant data type is invalid.
*/
kzsError kzuVariantFilterWithField(struct KzuVariant* variant, enum KzuPropertyField field);


KZ_HEADER_END


#endif
