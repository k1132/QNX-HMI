/**
* \file
* Property manager.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PROPERTY_MANAGER_MATRIX2X2_H
#define KZU_PROPERTY_MANAGER_MATRIX2X2_H


#include <core/util/math/kzc_matrix2x2.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuObjectNode;
struct KzuPropertyManager;
struct KzuPropertyType;


/** Matrix2x2 value source. */
struct KzuPropertyMatrix2x2ValueSource;


/** Create a matrix2x2 value source. */
kzsError kzuPropertyMatrix2x2ValueSourceCreate(const struct KzuPropertyManager* propertyManager, struct KzcMatrix2x2 value, struct KzuPropertyMatrix2x2ValueSource** out_valueSource);
/** Delete a matrix2x2 value source. */
kzsError kzuPropertyMatrix2x2ValueSourceDelete(struct KzuPropertyMatrix2x2ValueSource* valueSource);
/** Copy a matrix2x2 value source. */
kzsError kzuPropertyMatrix2x2ValueSourceClone(const struct KzuPropertyManager* propertyManager, const struct KzuPropertyMatrix2x2ValueSource* valueSource, struct KzuPropertyMatrix2x2ValueSource** out_newValueSource);
/** Copy a matrix2x2 value source. */
kzsError kzuPropertyMatrix2x2ValueSourceCopy(struct KzuPropertyMatrix2x2ValueSource* target, const struct KzuPropertyMatrix2x2ValueSource* source);

/** Set a matrix2x2 value source. */
kzsError kzuPropertyMatrix2x2ValueSourceSetValue(struct KzuPropertyMatrix2x2ValueSource* valueSource, struct KzcMatrix2x2 value);
/** Get a matrix2x2 value source. */
struct KzcMatrix2x2 kzuPropertyMatrix2x2ValueSourceGetValue(const struct KzuPropertyMatrix2x2ValueSource* valueSource);


/** Set a property of propertyType associated with an object. */
kzsError kzuPropertyManagerSetMatrix2x2(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, const struct KzcMatrix2x2* value);

/**
 * Get the value of a property of propertyType associated with an object. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. If an animation is applied to the property, the animated value is returned. It is calculated from the base and relative values of the property.
 * 2. The value associated with the object is returned.
 * 3. If the property is not associated with the object, the property groups associated with the object are queried:
 *  3.1 Property groups associated with the object are queried in the reverse order than they were added.
 * 4. If the property can not be deduced, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuPropertyManagerGetMatrix2x2(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzcMatrix2x2* out_value);
/**
 * Get the base value of a property of propertyType associated with an object. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 */
kzBool kzuPropertyManagerGetBaseMatrix2x2(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzcMatrix2x2* out_value);
/**
  * Get a property of propertyType associated with an object and return the default value from the property type if not found.
  * If the property value can be deduced with kzuPropertyManagerGetMatrix2x2 then that value is returned.
  * If the property can not be deduced, the default value from the property type is returned.
  */
struct KzcMatrix2x2 kzuPropertyManagerGetMatrix2x2Default(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType);


/** Set a property on an object node.  */
kzsError kzuObjectNodeSetMatrix2x2Property(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, const struct KzcMatrix2x2* value);

/**
 * Get the value of a property of propertyType associated with an object node. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetMatrix2x2 is used for getting the property value.
 * 2. If the property value can not be deduced from the object node, the same query is performed for the parent of the current object node.
 * 3. If the property is not found until the root is reached, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuObjectNodeGetMatrix2x2Property(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, struct KzcMatrix2x2* out_value);

/**
 * Get the base value of a property of propertyType associated with an object node.
 * Behaves like kzuObjectNodeGetMatrix2x2Property but does not take animation into account.
 */
kzBool kzuObjectNodeGetBaseMatrix2x2Property(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, struct KzcMatrix2x2* out_value);

/**
 * Get the value of a property associated with an object node.
 * Behaves like kzuObjectNodeGetMatrix2x2Property, but if the property value can not be deduced, the default value from the property type is returned.
 */
struct KzcMatrix2x2 kzuObjectNodeGetMatrix2x2PropertyDefault(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType);


KZ_HEADER_END


#endif
