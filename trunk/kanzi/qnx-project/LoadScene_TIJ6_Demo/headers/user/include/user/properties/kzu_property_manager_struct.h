/**
* \file
* Property manager.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PROPERTY_MANAGER_STRUCT_H
#define KZU_PROPERTY_MANAGER_STRUCT_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuObjectNode;
struct KzuPropertyManager;
struct KzuPropertyType;


/** Type for struct property. */
typedef const void* KzuStructProperty;


/** Set a property of propertyType associated with an object. Return an object representing the struct, which can be used for assigning child properties to. */
kzsError kzuPropertyManagerSetStruct(const struct KzuPropertyManager* propertyManager, const void* object,
                                     const struct KzuPropertyType* propertyType, KzuStructProperty* const out_value);

/**
 * Get the value of a property of propertyType associated with an object. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. If an animation is applied to the property, the animated value is returned. It is calculated from the base and relative values of the property.
 * 2. The value associated with the object is returned.
 * 3. If the property is not associated with the object, the property groups associated with the object are queried:
 *  3.1 Property groups associated with the object are queried in the reverse order than they were added.
 * 4. If the property can not be deduced, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuPropertyManagerGetStruct(const struct KzuPropertyManager* propertyManager, const void* object,
                                   const struct KzuPropertyType* propertyType, KzuStructProperty* const out_value);
/**
  * Get a property of propertyType associated with an object and return the default value from the property type if not found.
  * If the property value can be deduced with kzuPropertyManagerGetStruct then that value is returned.
  * If the property can not be deduced, KZ_NULL is returned.
  */
KzuStructProperty kzuPropertyManagerGetStructDefault(const struct KzuPropertyManager* propertyManager, const void* object,
                                                     const struct KzuPropertyType* propertyType);


/** Set a property on an object node.  */
kzsError kzuObjectNodeSetStructProperty(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType,
                                        KzuStructProperty* const out_value);

/**
 * Get the value of a property of propertyType associated with an object node. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetStruct is used for getting the property value.
 * 2. If the property value can not be deduced from the object node, the same query is performed for the parent of the current object node.
 * 3. If the property is not found until the root is reached, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuObjectNodeGetStructProperty(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType,
                                      KzuStructProperty* const out_value);

/**
 * Get the value of a property associated with an object node.
 * Behaves like kzuObjectNodeGetStructProperty, but if the property value can not be deduced, KZ_NULL is returned.
 */
KzuStructProperty kzuObjectNodeGetStructPropertyDefault(const struct KzuObjectNode* objectNode,
                                                        const struct KzuPropertyType* propertyType);


KZ_HEADER_END


#endif
