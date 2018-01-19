/**
* \file
* Property manager.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PROPERTY_MANAGER_VECTOR2_H
#define KZU_PROPERTY_MANAGER_VECTOR2_H


#include <core/util/math/kzc_vector2.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuObjectNode;
struct KzuPropertyManager;
struct KzuPropertyType;


/** Vector2 value source. */
struct KzuPropertyVector2ValueSource;


/** Create a vector2 value source. */
kzsError kzuPropertyVector2ValueSourceCreate(const struct KzuPropertyManager* propertyManager, struct KzcVector2 value, struct KzuPropertyVector2ValueSource** out_valueSource);
/** Delete a vector2 value source. */
kzsError kzuPropertyVector2ValueSourceDelete(struct KzuPropertyVector2ValueSource* valueSource);
/** Copy a vector2 value source. */
kzsError kzuPropertyVector2ValueSourceClone(const struct KzuPropertyManager* propertyManager, const struct KzuPropertyVector2ValueSource* valueSource, struct KzuPropertyVector2ValueSource** out_newValueSource);
/** Copy a vector2 value source. */
kzsError kzuPropertyVector2ValueSourceCopy(struct KzuPropertyVector2ValueSource* target, const struct KzuPropertyVector2ValueSource* source);

/** Set a vector2 value source. */
kzsError kzuPropertyVector2ValueSourceSetValue(struct KzuPropertyVector2ValueSource* valueSource, struct KzcVector2 value);
/** Get a vector2 value source. */
struct KzcVector2 kzuPropertyVector2ValueSourceGetValue(const struct KzuPropertyVector2ValueSource* valueSource);


/** Set a property of propertyType associated with an object. */
kzsError kzuPropertyManagerSetVector2(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzcVector2 value);

/**
 * Get the value of a property of propertyType associated with an object. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. If an animation is applied to the property, the animated value is returned. It is calculated from the base and relative values of the property.
 * 2. The value associated with the object is returned.
 * 3. If the property is not associated with the object, the property groups associated with the object are queried:
 *  3.1 Property groups associated with the object are queried in the reverse order than they were added.
 * 4. If the property can not be deduced, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuPropertyManagerGetVector2(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzcVector2* out_value);
/**
 * Get the base value of a property of propertyType associated with an object. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 */
kzBool kzuPropertyManagerGetBaseVector2(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzcVector2* out_value);
/**
  * Get a property of propertyType associated with an object and return the default value from the property type if not found.
  * If the property value can be deduced with kzuPropertyManagerGetVector2 then that value is returned.
  * If the property can not be deduced, the default value from the property type is returned.
  */
struct KzcVector2 kzuPropertyManagerGetVector2Default(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType);


/** Set a property on an object node.  */
kzsError kzuObjectNodeSetVector2Property(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, struct KzcVector2 value);

/**
 * Get the value of a property of propertyType associated with an object node. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetVector2 is used for getting the property value.
 * 2. If the property value can not be deduced from the object node, the same query is performed for the parent of the current object node.
 * 3. If the property is not found until the root is reached, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuObjectNodeGetVector2Property(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, struct KzcVector2* out_value);

/**
 * Get the base value of a property of propertyType associated with an object node.
 * Behaves like kzuObjectNodeGetVector2Property but does not take animation into account.
 */
kzBool kzuObjectNodeGetBaseVector2Property(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, struct KzcVector2* out_value);

/**
 * Get the value of a property associated with an object node.
 * Behaves like kzuObjectNodeGetVector2Property, but if the property value can not be deduced, the default value from the property type is returned.
 */
struct KzcVector2 kzuObjectNodeGetVector2PropertyDefault(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType);


KZ_HEADER_END


#endif
