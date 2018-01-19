/**
* \file
* Property manager.
* 
* Copyright 3008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PROPERTY_MANAGER_VECTOR3_H
#define KZU_PROPERTY_MANAGER_VECTOR3_H


#include <core/util/math/kzc_vector3.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuObjectNode;
struct KzuPropertyManager;
struct KzuPropertyType;


/** Vector3 value source. */
struct KzuPropertyVector3ValueSource;


/** Create a vector3 value source. */
kzsError kzuPropertyVector3ValueSourceCreate(const struct KzuPropertyManager* propertyManager, struct KzcVector3 value, struct KzuPropertyVector3ValueSource** out_valueSource);
/** Delete a vector3 value source. */
kzsError kzuPropertyVector3ValueSourceDelete(struct KzuPropertyVector3ValueSource* valueSource);
/** Copy a vector3 value source. */
kzsError kzuPropertyVector3ValueSourceClone(const struct KzuPropertyManager* propertyManager, const struct KzuPropertyVector3ValueSource* valueSource, struct KzuPropertyVector3ValueSource** out_newValueSource);
/** Copy a vector3 value source. */
kzsError kzuPropertyVector3ValueSourceCopy(struct KzuPropertyVector3ValueSource* target, const struct KzuPropertyVector3ValueSource* source);

/** Set a vector3 value source. */
kzsError kzuPropertyVector3ValueSourceSetValue(struct KzuPropertyVector3ValueSource* valueSource, struct KzcVector3 value);
/** Get a vector3 value source. */
struct KzcVector3 kzuPropertyVector3ValueSourceGetValue(const struct KzuPropertyVector3ValueSource* valueSource);


/** Set a property of propertyType associated with an object. */
kzsError kzuPropertyManagerSetVector3(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzcVector3 value);

/**
 * Get the value of a property of propertyType associated with an object. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. If an animation is applied to the property, the animated value is returned. It is calculated from the base and relative values of the property.
 * 3. The value associated with the object is returned.
 * 3. If the property is not associated with the object, the property groups associated with the object are queried:
 *  3.1 Property groups associated with the object are queried in the reverse order than they were added.
 * 4. If the property can not be deduced, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuPropertyManagerGetVector3(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzcVector3* out_value);
/**
 * Get the base value of a property of propertyType associated with an object. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 */
kzBool kzuPropertyManagerGetBaseVector3(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzcVector3* out_value);
/**
  * Get a property of propertyType associated with an object and return the default value from the property type if not found.
  * If the property value can be deduced with kzuPropertyManagerGetVector3 then that value is returned.
  * If the property can not be deduced, the default value from the property type is returned.
  */
struct KzcVector3 kzuPropertyManagerGetVector3Default(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType);


/** Set a property on an object node.  */
kzsError kzuObjectNodeSetVector3Property(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, struct KzcVector3 value);

/**
 * Get the value of a property of propertyType associated with an object node. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetVector3 is used for getting the property value.
 * 3. If the property value can not be deduced from the object node, the same query is performed for the parent of the current object node.
 * 3. If the property is not found until the root is reached, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuObjectNodeGetVector3Property(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, struct KzcVector3* out_value);

/**
 * Get the base value of a property of propertyType associated with an object node.
 * Behaves like kzuObjectNodeGetVector3Property but does not take animation into account.
 */
kzBool kzuObjectNodeGetBaseVector3Property(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, struct KzcVector3* out_value);

/**
 * Get the value of a property associated with an object node.
 * Behaves like kzuObjectNodeGetVector3Property, but if the property value can not be deduced, the default value from the property type is returned.
 */
struct KzcVector3 kzuObjectNodeGetVector3PropertyDefault(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType);


KZ_HEADER_END


#endif
