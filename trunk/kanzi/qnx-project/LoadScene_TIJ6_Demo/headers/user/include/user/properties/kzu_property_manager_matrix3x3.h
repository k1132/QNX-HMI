/**
* \file
* Property manager.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PROPERTY_MANAGER_MATRIX3X3_H
#define KZU_PROPERTY_MANAGER_MATRIX3X3_H


#include <core/util/math/kzc_matrix3x3.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuObjectNode;
struct KzuPropertyManager;
struct KzuPropertyType;


/** Matrix3x3 value source. */
struct KzuPropertyMatrix3x3ValueSource;


/** Create a matrix3x3 value source. */
kzsError kzuPropertyMatrix3x3ValueSourceCreate(const struct KzuPropertyManager* propertyManager, struct KzcMatrix3x3 value, struct KzuPropertyMatrix3x3ValueSource** out_valueSource);
/** Create matrix3x3 value source from SRT. */
kzsError kzuPropertyMatrix3x3ValueSourceCreateSRT(const struct KzuPropertyManager* propertyManager,
                                                  const struct KzcVector2* scale, kzFloat rotateInDegrees, const struct KzcVector2* translate,
                                                  struct KzuPropertyMatrix3x3ValueSource** out_valueSource);
/** Delete a matrix3x3 value source. */
kzsError kzuPropertyMatrix3x3ValueSourceDelete(struct KzuPropertyMatrix3x3ValueSource* valueSource);
/** Copy a matrix3x3 value source. */
kzsError kzuPropertyMatrix3x3ValueSourceClone(const struct KzuPropertyManager* propertyManager, const struct KzuPropertyMatrix3x3ValueSource* valueSource, struct KzuPropertyMatrix3x3ValueSource** out_newValueSource);
/** Copy a matrix3x3 value source. */
kzsError kzuPropertyMatrix3x3ValueSourceCopy(struct KzuPropertyMatrix3x3ValueSource* target, const struct KzuPropertyMatrix3x3ValueSource* source);

/** Set a matrix3x3 value source. */
kzsError kzuPropertyMatrix3x3ValueSourceSetValue(struct KzuPropertyMatrix3x3ValueSource* valueSource, struct KzcMatrix3x3 value);
/** Set a matrix3x3 value source using SRT. */
kzsError kzuPropertyMatrix3x3ValueSourceSetValueSRT(struct KzuPropertyMatrix3x3ValueSource* valueSource, const struct KzcVector2* scale, kzFloat rotateInDegrees, const struct KzcVector2* translate);
/** Get a matrix3x3 value source. */
struct KzcMatrix3x3 kzuPropertyMatrix3x3ValueSourceGetValue(struct KzuPropertyMatrix3x3ValueSource* valueSource);
/** Get a matrix3x3 value source using SRT. 
 * \param out_scale Scale vector of the matrix SRT, not returned when KZ_NULL given as an argument.
 * \param out_rotate Rotate scalar of the matrix SRT in degrees, not returned when KZ_NULL given as an argument.
 * \param out_translate Translate vector of the matrix SRT, not returned when KZ_NULL given as an argument.
 */
void kzuPropertyMatrix3x3ValueSourceGetValueSRT(const struct KzuPropertyMatrix3x3ValueSource* valueSource, struct KzcVector2* out_scale, kzFloat* out_rotateInDegrees, struct KzcVector2* out_translate);

/** Set a property of propertyType associated with an object. */
kzsError kzuPropertyManagerSetMatrix3x3(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, const struct KzcMatrix3x3* value);
/** Set a property of propertyType associated with an object in SRT form, rotation in degrees. */
kzsError kzuPropertyManagerSetMatrix3x3SRT(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType,
                                           const struct KzcVector2* scale, kzFloat rotateInDegrees, const struct KzcVector2* translate);
/**
 * Get the value of a property of propertyType associated with an object. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. If an animation is applied to the property, the animated value is returned. It is calculated from the base and relative values of the property.
 * 2. The value associated with the object is returned.
 * 3. If the property is not associated with the object, the property groups associated with the object are queried:
 *  3.1 Property groups associated with the object are queried in the reverse order than they were added.
 * 4. If the property can not be deduced, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuPropertyManagerGetMatrix3x3(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzcMatrix3x3* out_value);
/**
 * Get the value of a property of propertyType associated with an object in SRT form. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise. Doesn't take relative matrix into account.
 * The return value is calculated based on the following steps:
 * 1. If an animation is applied to the property, the animated value is returned. It is calculated from the base and relative values of the property.
 * 2. The value associated with the object is returned.
 * 3. If the property is not associated with the object, the property groups associated with the object are queried:
 *  3.1 Property groups associated with the object are queried in the reverse order than they were added.
 * 4. If the property can not be deduced, the output value is not modified and KZ_FALSE is returned.
 * \param out_scale Scale vector of the matrix SRT, not returned when KZ_NULL given as an argument.
 * \param out_rotate Rotate scalar of the matrix SRT in degrees, not returned when KZ_NULL given as an argument.
 * \param out_translate Translate vector of the matrix SRT, not returned when KZ_NULL given as an argument.
 */
kzBool kzuPropertyManagerGetMatrix3x3SRT(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, 
                                         struct KzcVector2* out_scale, kzFloat* out_rotateInDegrees, struct KzcVector2* out_translate);
/**
 * Get the base value of a property of propertyType associated with an object. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 */
kzBool kzuPropertyManagerGetBaseMatrix3x3(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzcMatrix3x3* out_value);
/**
 * Get the base value of a property of propertyType associated with an object in SRT format. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * \param out_scale Scale vector of the matrix SRT, not returned when KZ_NULL given as an argument.
 * \param out_rotate Rotate scalar of the matrix SRT in degrees, not returned when KZ_NULL given as an argument.
 * \param out_translate Translate vector of the matrix SRT, not returned when KZ_NULL given as an argument.
 */
kzBool kzuPropertyManagerGetBaseMatrix3x3SRT(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType,
                                             struct KzcVector2* out_scale, kzFloat* out_rotateInDegrees, struct KzcVector2* out_translate);
/**
  * Get a property of propertyType associated with an object and return the default value from the property type if not found.
  * If the property value can be deduced with kzuPropertyManagerGetMatrix3x3 then that value is returned.
  * If the property can not be deduced, the default value from the property type is returned.
  */
struct KzcMatrix3x3 kzuPropertyManagerGetMatrix3x3Default(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType);
/**
  * Get a property of propertyType associated with an object and return the default value from the property type if not found, in form of SRT.
  * If the property value can be deduced with kzuPropertyManagerGetMatrix3x3 then that value is returned.
  * If the property can not be deduced, the default value from the property type is returned.
  * \param out_scale Scale vector of the matrix SRT, not returned when KZ_NULL given as an argument.
  * \param out_rotate Rotate scalar of the matrix SRT in degrees, not returned when KZ_NULL given as an argument.
  * \param out_translate Translate vector of the matrix SRT, not returned when KZ_NULL given as an argument.
  */
void kzuPropertyManagerGetMatrix3x3DefaultSRT(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType,
                                              struct KzcVector2* out_scale, kzFloat* out_rotateInDegrees, struct KzcVector2* out_translate);

/** Get combined value of matrix and SRT values. Also retrieves flag value if matrix value was last set (if so, SRT values are not reliable since they are extracted from matrix).*/
kzBool kzuPropertyManagerGetMatrix3x3Combined(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType,
                                              struct KzcMatrix3x3* out_matrix, struct KzcVector2* out_scale, kzFloat* out_rotation, struct KzcVector2* out_translation,
                                              kzBool* out_isMatrixValue);

/** Set a property on an object node.  */
kzsError kzuObjectNodeSetMatrix3x3Property(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, const struct KzcMatrix3x3* value);
/** Set a property on an object node in SRT format. */
kzsError kzuObjectNodeSetMatrix3x3PropertySRT(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType,
                                              const struct KzcVector2* scale, kzFloat rotate, const struct KzcVector2* translate);
/**
 * Get the value of a property of propertyType associated with an object node. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetMatrix3x3 is used for getting the property value.
 * 2. If the property value can not be deduced from the object node, the same query is performed for the parent of the current object node.
 * 3. If the property is not found until the root is reached, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuObjectNodeGetMatrix3x3Property(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, struct KzcMatrix3x3* out_value);
/**
 * Get the value of a property of propertyType associated with an object node in SRT format. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetMatrix3x3 is used for getting the property value.
 * 2. If the property value can not be deduced from the object node, the same query is performed for the parent of the current object node.
 * 3. If the property is not found until the root is reached, the output value is not modified and KZ_FALSE is returned.
 * \param out_scale Scale vector of the matrix SRT, not returned when KZ_NULL given as an argument.
 * \param out_rotate Rotate scalar of the matrix SRT in degrees, not returned when KZ_NULL given as an argument.
 * \param out_translate Translate vector of the matrix SRT, not returned when KZ_NULL given as an argument.
 */
kzBool kzuObjectNodeGetMatrix3x3SRTProperty(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType,
                                            struct KzcVector2* out_scale, kzFloat* out_rotateInDegrees, struct KzcVector2* out_translate);

/**
 * Get the base value of a property of propertyType associated with an object node.
 * Behaves like kzuObjectNodeGetMatrix3x3Property but does not take animation into account.
 */
kzBool kzuObjectNodeGetBaseMatrix3x3Property(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, struct KzcMatrix3x3* out_value);

/**
 * Get the value of a property associated with an object node.
 * Behaves like kzuObjectNodeGetMatrix3x3Property, but if the property value can not be deduced, the default value from the property type is returned.
 */
struct KzcMatrix3x3 kzuObjectNodeGetMatrix3x3PropertyDefault(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType);

/**Get the value of a property associated with an object node in SRT format. 
 * \param out_scale Scale vector of the matrix SRT, not returned when KZ_NULL given as an argument.
 * \param out_rotate Rotate scalar of the matrix SRT in degrees, not returned when KZ_NULL given as an argument.
 * \param out_translate Translate vector of the matrix SRT, not returned when KZ_NULL given as an argument.
 */
void kzuObjectNodeGetMatrix3x3PropertyDefaultSRT(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType,
                                                 struct KzcVector2* out_scale, kzFloat* out_rotateInDegrees, struct KzcVector2* out_translate);

KZ_HEADER_END


#endif
