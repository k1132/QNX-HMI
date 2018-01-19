/**
* \file
* Property manager.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PROPERTY_MANAGER_MATRIX4X4_H
#define KZU_PROPERTY_MANAGER_MATRIX4X4_H


#include <core/util/math/kzc_matrix4x4.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuObjectNode;
struct KzuPropertyManager;
struct KzuPropertyType;


/** Matrix4x4 value source. */
struct KzuPropertyMatrix4x4ValueSource;


/** Create a matrix4x4 value source. */
kzsError kzuPropertyMatrix4x4ValueSourceCreate(const struct KzuPropertyManager* propertyManager, struct KzcMatrix4x4 value, struct KzuPropertyMatrix4x4ValueSource** out_valueSource);
/** Create matrix4x4 value source from SRT. */
kzsError kzuPropertyMatrix4x4ValueSourceCreateSRT(const struct KzuPropertyManager* propertyManager,
                                                  const struct KzcVector3* scale, const struct KzcVector3* rotateInDegrees, const struct KzcVector3* translate,
                                                  struct KzuPropertyMatrix4x4ValueSource** out_valueSource);
/** Delete a matrix4x4 value source. */
kzsError kzuPropertyMatrix4x4ValueSourceDelete(struct KzuPropertyMatrix4x4ValueSource* valueSource);
/** Copy a matrix4x4 value source. */
kzsError kzuPropertyMatrix4x4ValueSourceClone(const struct KzuPropertyManager* propertyManager, const struct KzuPropertyMatrix4x4ValueSource* valueSource, struct KzuPropertyMatrix4x4ValueSource** out_newValueSource);
/** Copy a matrix4x4 value source. */
kzsError kzuPropertyMatrix4x4ValueSourceCopy(struct KzuPropertyMatrix4x4ValueSource* target, const struct KzuPropertyMatrix4x4ValueSource* source);

/** Set a matrix4x4 value source. */
kzsError kzuPropertyMatrix4x4ValueSourceSetValue(struct KzuPropertyMatrix4x4ValueSource* valueSource, struct KzcMatrix4x4 value);
/** Set a matrix4x4 value source using SRT. */
kzsError kzuPropertyMatrix4x4ValueSourceSetValueSRT(struct KzuPropertyMatrix4x4ValueSource* valueSource, const struct KzcVector3* scale, const struct KzcVector3* rotateInDegrees, const struct KzcVector3* translate);
/** Get a matrix4x4 value source. */
struct KzcMatrix4x4 kzuPropertyMatrix4x4ValueSourceGetValue(struct KzuPropertyMatrix4x4ValueSource* valueSource);
/** Get a matrix4x4 value source using SRT. 
 * \param out_scale Scale vector of the matrix SRT, not returned when KZ_NULL given as an argument.
 * \param out_rotate Rotate vector of the matrix SRT in degrees, not returned when KZ_NULL given as an argument.
 * \param out_translate Translate vector of the matrix SRT, not returned when KZ_NULL given as an argument.
 */
void kzuPropertyMatrix4x4ValueSourceGetValueSRT(const struct KzuPropertyMatrix4x4ValueSource* valueSource, struct KzcVector3* out_scale, struct KzcVector3* out_rotateInDegrees, struct KzcVector3* out_translate);


/** Set a property of propertyType associated with an object. */
kzsError kzuPropertyManagerSetMatrix4x4(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, const struct KzcMatrix4x4* value);
/** Set a property of propertyType associated with an object in SRT form, rotation in degrees. */
kzsError kzuPropertyManagerSetMatrix4x4SRT(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType,
                                           const struct KzcVector3* scale, const struct KzcVector3* rotateInDegrees, const struct KzcVector3* translate);

/**
 * Get the value of a property of propertyType associated with an object. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. If an animation is applied to the property, the animated value is returned. It is calculated from the base and relative values of the property.
 * 2. The value associated with the object is returned.
 * 3. If the property is not associated with the object, the property groups associated with the object are queried:
 *  3.1 Property groups associated with the object are queried in the reverse order than they were added.
 * 4. If the property can not be deduced, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuPropertyManagerGetMatrix4x4(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzcMatrix4x4* out_value);
/**
 * Get the value of a property of propertyType associated with an object in SRT form. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise. Doesn't take relative matrix into account.
 * The return value is calculated based on the following steps:
 * 1. If an animation is applied to the property, the animated value is returned. It is calculated from the base and relative values of the property.
 * 2. The value associated with the object is returned.
 * 3. If the property is not associated with the object, the property groups associated with the object are queried:
 *  3.1 Property groups associated with the object are queried in the reverse order than they were added.
 * 4. If the property can not be deduced, the output value is not modified and KZ_FALSE is returned.
 * \param out_scale Scale vector of the matrix SRT, not returned when KZ_NULL given as an argument.
 * \param out_rotate Rotate vector of the matrix SRT in degrees, not returned when KZ_NULL given as an argument.
 * \param out_translate Translate vector of the matrix SRT, not returned when KZ_NULL given as an argument.
 */
kzBool kzuPropertyManagerGetMatrix4x4SRT(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, 
                                         struct KzcVector3* out_scale, struct KzcVector3* out_rotateInDegrees, struct KzcVector3* out_translate);
/**
 * Get the base value of a property of propertyType associated with an object. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 */
kzBool kzuPropertyManagerGetBaseMatrix4x4(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzcMatrix4x4* out_value);

/**
 * Get the base value of a property of propertyType associated with an object in SRT format. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * \param out_scale Scale vector of the matrix SRT, not returned when KZ_NULL given as an argument.
 * \param out_rotate Rotate vector of the matrix SRT in degrees, not returned when KZ_NULL given as an argument.
 * \param out_translate Translate vector of the matrix SRT, not returned when KZ_NULL given as an argument.
 */
kzBool kzuPropertyManagerGetBaseMatrix4x4SRT(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType,
                                             struct KzcVector3* out_scale, struct KzcVector3* out_rotateInDegrees, struct KzcVector3* out_translate);
/**
  * Get a property of propertyType associated with an object and return the default value from the property type if not found.
  * If the property value can be deduced with kzuPropertyManagerGetMatrix4x4 then that value is returned.
  * If the property can not be deduced, the default value from the property type is returned.
  */
struct KzcMatrix4x4 kzuPropertyManagerGetMatrix4x4Default(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType);
/**
  * Get a property of propertyType associated with an object and return the default value from the property type if not found, in form of SRT.
  * If the property value can be deduced with kzuPropertyManagerGetMatrix4x4 then that value is returned.
  * If the property can not be deduced, the default value from the property type is returned.
  * \param out_scale Scale vector of the matrix SRT, not returned when KZ_NULL given as an argument.
  * \param out_rotate Rotate vector of the matrix SRT in degrees, not returned when KZ_NULL given as an argument.
  * \param out_translate Translate vector of the matrix SRT, not returned when KZ_NULL given as an argument.
  */
void kzuPropertyManagerGetMatrix4x4DefaultSRT(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType,
                                              struct KzcVector3* out_scale, struct KzcVector3* out_rotateInDegrees, struct KzcVector3* out_translate);

/** Get combined value of matrix and SRT values. Also retrieves flag value if matrix value was last set (if so, SRT values are not reliable since they are extracted from matrix).*/
kzBool kzuPropertyManagerGetMatrix4x4Combined(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType,
                                              struct KzcMatrix4x4* out_matrix, struct KzcVector3* out_scale, struct KzcVector3* out_rotation, struct KzcVector3* out_translation,
                                              kzBool* out_isMatrixValue);

/** Set a property on an object node.  */
kzsError kzuObjectNodeSetMatrix4x4Property(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, const struct KzcMatrix4x4* value);
/** Set a property on an object node in SRT format. */
kzsError kzuObjectNodeSetMatrix4x4SRTProperty(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType,
                                              const struct KzcVector3* scale, const struct KzcVector3* rotateInDegrees, const struct KzcVector3* translate);

/**
 * Get the value of a property of propertyType associated with an object node. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetMatrix4x4 is used for getting the property value.
 * 2. If the property value can not be deduced from the object node, the same query is performed for the parent of the current object node.
 * 3. If the property is not found until the root is reached, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuObjectNodeGetMatrix4x4Property(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, struct KzcMatrix4x4* out_value);
/**
 * Get the value of a property of propertyType associated with an object node in SRT format. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetMatrix4x4 is used for getting the property value.
 * 2. If the property value can not be deduced from the object node, the same query is performed for the parent of the current object node.
 * 3. If the property is not found until the root is reached, the output value is not modified and KZ_FALSE is returned.
 * \param out_scale Scale vector of the matrix SRT, not returned when KZ_NULL given as an argument.
 * \param out_rotate Rotate vector of the matrix SRT in degrees, not returned when KZ_NULL given as an argument.
 * \param out_translate Translate vector of the matrix SRT, not returned when KZ_NULL given as an argument.
 */
kzBool kzuObjectNodeGetMatrix4x4SRTProperty(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType,
                                            struct KzcVector3* out_scale, struct KzcVector3* out_rotateInDegrees, struct KzcVector3* out_translate);

/**
 * Get the base value of a property of propertyType associated with an object node.
 * Behaves like kzuObjectNodeGetMatrix4x4Property but does not take animation into account.
 */
kzBool kzuObjectNodeGetBaseMatrix4x4Property(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, struct KzcMatrix4x4* out_value);

/**
 * Get the value of a property associated with an object node.
 * Behaves like kzuObjectNodeGetMatrix4x4Property, but if the property value can not be deduced, the default value from the property type is returned.
 */
struct KzcMatrix4x4 kzuObjectNodeGetMatrix4x4PropertyDefault(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType);

/** Get the value of a property associated with an object node in SRT format.
 * \param out_scale Scale vector of the matrix SRT, not returned when KZ_NULL given as an argument.
 * \param out_rotate Rotate vector of the matrix SRT in degrees, not returned when KZ_NULL given as an argument.
 * \param out_translate Translate vector of the matrix SRT, not returned when KZ_NULL given as an argument.
*/
void kzuObjectNodeGetMatrix4x4PropertyDefaultSRT(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType,
                                                 struct KzcVector3* out_scale, struct KzcVector3* out_rotateInDegrees, struct KzcVector3* out_translate);


KZ_HEADER_END


#endif
