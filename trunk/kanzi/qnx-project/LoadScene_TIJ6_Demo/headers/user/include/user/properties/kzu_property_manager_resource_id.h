/**
* \file
* Property manager.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PROPERTY_MANAGER_RESOURCE_ID_H
#define KZU_PROPERTY_MANAGER_RESOURCE_ID_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuObjectNode;
struct KzuPropertyManager;
struct KzuPropertyType;
struct KzuResourceManager;


/** ResourceID value source. */
struct KzuPropertyResourceIDValueSource;


/** Create a ResourceID value source. */
kzsError kzuPropertyResourceIDValueSourceCreate(const struct KzuPropertyManager* propertyManager, kzString value, struct KzuPropertyResourceIDValueSource** out_valueSource);

/** Delete a ResourceID value source. */
kzsError kzuPropertyResourceIDValueSourceDelete(struct KzuPropertyResourceIDValueSource* valueSource);
/** Copy a resourceID value source. */
kzsError kzuPropertyResourceIDValueSourceClone(const struct KzuPropertyManager* propertyManager, const struct KzuPropertyResourceIDValueSource* valueSource, struct KzuPropertyResourceIDValueSource** out_newValueSource);
/** Copy a resourceID value source. */
kzsError kzuPropertyResourceIDValueSourceCopy(struct KzuPropertyResourceIDValueSource* target, const struct KzuPropertyResourceIDValueSource* source);

/** Set a resourceID value source. */
kzsError kzuPropertyResourceIDValueSourceSetValue(struct KzuPropertyResourceIDValueSource* valueSource, kzString value);
/** Get a resourceID value source. */
kzString kzuPropertyResourceIDValueSourceGetValue(const struct KzuPropertyResourceIDValueSource* valueSource);


/** Set a property of propertyType associated with an object. */
kzsError kzuPropertyManagerSetResourceID(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, kzString value);
/** Set a property of propertyType associated with an object. */
kzsError kzuPropertyManagerSetResourceIDResource(const struct KzuPropertyManager* propertyManager, const void* object,
                                                 const struct KzuPropertyType* propertyType, struct KzuResource* resource);
/** Set a property of propertyType associated with an object. */
kzsError kzuPropertyManagerSetResourceIDURL(const struct KzuPropertyManager* propertyManager,
                                            const void* object, const struct KzuPropertyType* propertyType,
                                            struct KzuResourceManager* resourceManager, kzString resourceURL);

/**
 * Get the value of a property of propertyType associated with an object. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. The value associated with the object is returned.
 * 2. If the property is not associated with the object, the property groups associated with the object are queried:
 *  2.1 Property groups associated with the object are queried in the reverse order than they were added.
 * 3. If the property can not be deduced, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuPropertyManagerGetResourceID(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, kzString* out_value);
/**
 * Get the value of a property of propertyType associated with an object. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. The value associated with the object is returned.
 * 2. If the property is not associated with the object, the property groups associated with the object are queried:
 *  2.1 Property groups associated with the object are queried in the reverse order than they were added.
 * 3. If the property can not be deduced, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuPropertyManagerGetResourceIDResource(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzuResource** out_resource);
/**
  * Get a property of propertyType associated with an object and return the default value from the property type if not found.
  * If the property value can be deduced with kzuPropertyManagerGetResourceID then that value is returned.
  * If the property can not be deduced, the default value from the property type is returned.
  */
kzString kzuPropertyManagerGetResourceIDDefault(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType);
/**
  * Get a property of propertyType associated with an object and return the default value from the property type if not found.
  * If the property value can be deduced with kzuPropertyManagerGetResourceID then that value is returned.
  * If the property can not be deduced, the default value from the property type is returned.
  */
struct KzuResource* kzuPropertyManagerGetResourceIDResourceDefault(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType);


/** Set a property on an object node.  */
kzsError kzuObjectNodeSetResourceIDProperty(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, kzString value);
/** Set a property on an object node.  */
kzsError kzuObjectNodeSetResourceIDResourceProperty(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, struct KzuResource* resource);

/**
 * Get the value of a property of propertyType associated with an object node. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetResourceID is used for getting the property value.
 * 2. If the property value can not be deduced from the object node, the same query is performed for the parent of the current object node.
 * 3. If the property is not found until the root is reached, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuObjectNodeGetResourceIDProperty(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, kzString* out_value);
/**
 * Get the value of a property of propertyType associated with an object node. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetResourceIDResource is used for getting the property value.
 * 2. If the property value can not be deduced from the object node, the same query is performed for the parent of the current object node.
 * 3. If the property is not found until the root is reached, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuObjectNodeGetResourceIDResourceProperty(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, struct KzuResource** out_resource);

/**
 * Get the value of a property associated with an object node.
 * Behaves like kzuObjectNodeGetResourceIDProperty, but if the property value can not be deduced, the default value from the property type is returned.
 */
kzString kzuObjectNodeGetResourceIDPropertyDefault(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType);
/**
 * Get the value of a property associated with an object node.
 * Behaves like kzuObjectNodeGetResourceIDResourceProperty, but if the property value can not be deduced, the default value from the property type is returned.
 */
struct KzuResource* kzuObjectNodeGetResourceIDResourcePropertyDefault(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType);

/** Attaches a resource ID property by acquiring the resource from the object node's resource dictionary. */
kzsError kzuObjectNodeResourceIDPropertyAttach(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType);
/** Detaches a resource ID property by releasing the resource that was acquired from the object node's resource dictionary. */
kzsError kzuObjectNodeResourceIDPropertyDetach(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType);
/** Reattaches a resource ID property if needed. */
kzsError kzuObjectNodeResourceIDPropertyReattach(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType);


KZ_HEADER_END


#endif
