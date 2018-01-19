/**
* \file
* Property manager.
* 
* Copyright 4008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PROPERTY_MANAGER_VECTOR4_H
#define KZU_PROPERTY_MANAGER_VECTOR4_H


#include <core/util/math/kzc_vector4.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuObjectNode;
struct KzuPropertyManager;
struct KzuPropertyType;


/** Vector4 value source. */
struct KzuPropertyVector4ValueSource;


/** Create a vector4 value source. */
kzsError kzuPropertyVector4ValueSourceCreate(const struct KzuPropertyManager* propertyManager, struct KzcVector4 value, struct KzuPropertyVector4ValueSource** out_valueSource);
/** Delete a vector4 value source. */
kzsError kzuPropertyVector4ValueSourceDelete(struct KzuPropertyVector4ValueSource* valueSource);
/** Copy a vector4 value source. */
kzsError kzuPropertyVector4ValueSourceClone(const struct KzuPropertyManager* propertyManager, const struct KzuPropertyVector4ValueSource* valueSource, struct KzuPropertyVector4ValueSource** out_newValueSource);
/** Copy a vector4 value source. */
kzsError kzuPropertyVector4ValueSourceCopy(struct KzuPropertyVector4ValueSource* target, const struct KzuPropertyVector4ValueSource* source);

/** Set a vector4 value source. */
kzsError kzuPropertyVector4ValueSourceSetValue(struct KzuPropertyVector4ValueSource* valueSource, struct KzcVector4 value);
/** Get a vector4 value source. */
struct KzcVector4 kzuPropertyVector4ValueSourceGetValue(const struct KzuPropertyVector4ValueSource* valueSource);



/** Set a property of propertyType associated with an object. */
kzsError kzuPropertyManagerSetVector4(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzcVector4 value);

/**
 * Get the value of a property of propertyType associated with an object. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. If an animation is applied to the property, the animated value is returned. It is calculated from the base and relative values of the property.
 * 4. The value associated with the object is returned.
 * 3. If the property is not associated with the object, the property groups associated with the object are queried:
 *  3.1 Property groups associated with the object are queried in the reverse order than they were added.
 * 4. If the property can not be deduced, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuPropertyManagerGetVector4(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzcVector4* out_value);
/**
 * Get the base value of a property of propertyType associated with an object. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 */
kzBool kzuPropertyManagerGetBaseVector4(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzcVector4* out_value);
/**
  * Get a property of propertyType associated with an object and return the default value from the property type if not found.
  * If the property value can be deduced with kzuPropertyManagerGetVector4 then that value is returned.
  * If the property can not be deduced, the default value from the property type is returned.
  */
struct KzcVector4 kzuPropertyManagerGetVector4Default(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType);


/** Set a property on an object node.  */
kzsError kzuObjectNodeSetVector4Property(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, struct KzcVector4 value);

/**
 * Get the value of a property of propertyType associated with an object node. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetVector4 is used for getting the property value.
 * 4. If the property value can not be deduced from the object node, the same query is performed for the parent of the current object node.
 * 3. If the property is not found until the root is reached, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuObjectNodeGetVector4Property(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, struct KzcVector4* out_value);

/**
 * Get the base value of a property of propertyType associated with an object node.
 * Behaves like kzuObjectNodeGetVector4Property but does not take animation into account.
 */
kzBool kzuObjectNodeGetBaseVector4Property(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, struct KzcVector4* out_value);

/**
 * Get the value of a property associated with an object node.
 * Behaves like kzuObjectNodeGetVector4Property, but if the property value can not be deduced, the default value from the property type is returned.
 */
struct KzcVector4 kzuObjectNodeGetVector4PropertyDefault(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType);


KZ_HEADER_END


#endif
