/**
* \file
* Property manager.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PROPERTY_MANAGER_BOOL_H
#define KZU_PROPERTY_MANAGER_BOOL_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuObjectNode;
struct KzuPropertyManager;
struct KzuPropertyType;


/** Bool value source. */
struct KzuPropertyBoolValueSource;


/** Create a bool value source. */
kzsError kzuPropertyBoolValueSourceCreate(const struct KzuPropertyManager* propertyManager, kzBool value, struct KzuPropertyBoolValueSource** out_valueSource);
/** Delete a bool value source. */
kzsError kzuPropertyBoolValueSourceDelete(struct KzuPropertyBoolValueSource* valueSource);
/** Copy a bool value source. */
kzsError kzuPropertyBoolValueSourceClone(const struct KzuPropertyManager* propertyManager, const struct KzuPropertyBoolValueSource* valueSource, struct KzuPropertyBoolValueSource** out_newValueSource);
/** Copy a bool value source. */
kzsError kzuPropertyBoolValueSourceCopy(struct KzuPropertyBoolValueSource* target, const struct KzuPropertyBoolValueSource* source);

/** Set a bool value source. */
kzsError kzuPropertyBoolValueSourceSetValue(struct KzuPropertyBoolValueSource* valueSource, kzBool value);
/** Get a bool value source. */
kzBool kzuPropertyBoolValueSourceGetValue(const struct KzuPropertyBoolValueSource* valueSource);


/** Set a property of propertyType associated with an object. */
kzsError kzuPropertyManagerSetBool(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, kzBool value);

/**
 * Get the value of a property of propertyType associated with an object. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. The value associated with the object is returned.
 * 2. If the property is not associated with the object, the property groups associated with the object are queried:
 *  2.1 Property groups associated with the object are queried in the reverse order than they were added.
 * 3. If the property can not be deduced, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuPropertyManagerGetBool(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, kzBool* out_value);
/**
 * Get the base value of a property of propertyType associated with an object. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 */
kzBool kzuPropertyManagerGetBaseBool(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, kzBool* out_value);
/**
  * Get a property of propertyType associated with an object and return the default value from the property type if not found.
  * If the property value can be deduced with kzuPropertyManagerGetBool then that value is returned.
  * If the property can not be deduced, the default value from the property type is returned.
  */
kzBool kzuPropertyManagerGetBoolDefault(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType);


/** Set a property on an object node.  */
kzsError kzuObjectNodeSetBoolProperty(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, kzBool value);

/**
 * Get the value of a property of propertyType associated with an object node. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetBool is used for getting the property value.
 * 2. If the property value can not be deduced from the object node, the same query is performed for the parent of the current object node.
 * 3. If the property is not found until the root is reached, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuObjectNodeGetBoolProperty(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, kzBool* out_value);

/**
 * Get the value of a property associated with an object node.
 * Behaves like kzuObjectNodeGetBoolProperty, but if the property value can not be deduced, the default value from the property type is returned.
 */
kzBool kzuObjectNodeGetBoolPropertyDefault(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType);


KZ_HEADER_END


#endif
