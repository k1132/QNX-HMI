/**
* \file
* Property manager.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PROPERTY_MANAGER_POINTER_H
#define KZU_PROPERTY_MANAGER_POINTER_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzuObjectNode;
struct KzuPropertyManager;
struct KzuPropertyType;
struct KzuResource;
struct KzuResourceManager;


/** Set a property of propertyType associated with an object. */
kzsError kzuPropertyManagerSetPointer(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, void* value);

/**
 * Get the value of a property of propertyType associated with an object. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. The value associated with the object is returned.
 * 2. If the property is not associated with the object, the property groups associated with the object are queried:
 *  2.1 Property groups associated with the object are queried in the reverse order than they were added.
 * 3. If the property can not be deduced, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuPropertyManagerGetPointer(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, void** out_value);
/**
 * Get the value of a property of propertyType associated with an object.
 * Same as kzuPropertyManagerGetPointer, except this resolves the target pointer from relative path in run-time.
 */
kzBool kzuPropertyManagerGetPointerWithBase(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzuObjectNode* baseObject, void** out_value);
/**
 * Get a property of propertyType associated with an object and return the default value from the property type if not found.
 * If the property value can be deduced with kzuPropertyManagerGetPointer then that value is returned.
 * If the property can not be deduced, the default value from the property type is returned.
 */
void* kzuPropertyManagerGetPointerDefault(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType);
/**
 * Get a property of propertyType associated with an object and return the default value from the property type if not found.
 * Same as kzuPropertyManagerGetPointer, except this resolves the target pointer from relative path in run-time.
 */
void* kzuPropertyManagerGetPointerWithBaseDefault(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzuObjectNode* baseObject);

/**
 * Get the path value of a property of propertyType associated with an object. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. The value associated with the object is returned.
 * 2. If the property is not associated with the object, the property groups associated with the object are queried:
 *  2.1 Property groups associated with the object are queried in the reverse order than they were added.
 * 3. If the property can not be deduced, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuPropertyManagerGetPointerRelativePath(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, kzString* out_path);

/** Set a property of propertyType associated with an object. */
kzsError kzuPropertyManagerSetPointerRelativePath(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, kzString value);
/**
 * Get a path value of propertyType associated with an object and return the default value from the property type if not found.
 * If the property value can be deduced with kzuPropertyManagerGetPointer then that value is returned.
 * If the property can not be deduced, the default value from the property type is returned.
 */
kzString kzuPropertyManagerGetRelativePathDefault(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType);

/** Set a property of propertyType associated with an object. Pointer must be a resource. Acquires the resource, and releases the previously associated resource if exists. */
kzsError kzuPropertyManagerSetPointerResource(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzuResource* resource);
/** Set a property of propertyType associated with an object. Value must be a resource URL. The property must later be resolved with kzuPropertyManagerResolvePointerResourceURL, which will acquire the resource. */
kzsError kzuPropertyManagerSetPointerResourceURL(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, kzString resourceURL);
/** Resolves a pointer property with a resource URL value by acquiring the resource. This must be called in the main thread after kzuPropertyManagerSetPointerResourceURL. */
kzsError kzuPropertyManagerResolvePointerResourceURL(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType,
                                                     struct KzuResourceManager* resourceManager);
/**
 * Checks if the property of propertyType associated with an object is a resource.
 * Returns KZ_TRUE if the property has been set with \ref kzuPropertyManagerSetPointerResource()
 * and KZ_FALSE if the property has been set with \ref kzuPropertyManagerSetPointer().
 */
kzBool kzuPropertyManagerIsPointerResource(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType);

/**
 * Attaches base object node for the property. After this when querying the reference target the query can return valid object node 
 * if it is not set by kzuPropertyManagerSetPointer. 
 * \param baseNode Base node for which the target node resolving is done for. For example MyNode, and relative path "../." will return MyNode:s parent. Also needed for absolute paths to be able to solve it from the root node.
 */ 
kzsError kzuPropertyManagerPointerAttach(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType, struct KzuObjectNode* base);
/** Detaches base object node from the property. After this all queries to GetObjectReferenceTarget will be invalid (null)
 *  if it is not set by kzuPropertyManagerSetPointer. */
kzsError kzuPropertyManagerPointerDetach(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType);

/** Checks if the given pointer property has been attached in the given object. */
kzBool kzuPropertyManagerPointerIsAttached(const struct KzuPropertyManager* propertyManager, const void* object, const struct KzuPropertyType* propertyType);

/** Set a property on an object node.  */
kzsError kzuObjectNodeSetPointerProperty(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, void* value);

/** Sets pointer resource property for object node. */
kzsError kzuObjectNodeSetPointerResourceProperty(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, struct KzuResource* resource);

/**
 * Get the value of a property of propertyType associated with an object node. Returns KZ_TRUE if the property is found and KZ_FALSE otherwise.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetPointer is used for getting the property value.
 * 2. If the property value can not be deduced from the object node, the same query is performed for the parent of the current object node.
 * 3. If the property is not found until the root is reached, the output value is not modified and KZ_FALSE is returned.
 */
kzBool kzuObjectNodeGetPointerProperty(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType, void** out_value);

/**
 * Get the value of a property associated with an object node.
 * Behaves like kzuObjectNodeGetPointerProperty, but if the property value can not be deduced, the default value from the property type is returned.
 */
void* kzuObjectNodeGetPointerPropertyDefault(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType);

/**
 * Checks if the property of propertyType associated with an object node is a resource.
 * Returns KZ_TRUE if the property has been set with \ref kzuPropertyManagerSetPointerResource()
 * and KZ_FALSE if the property has been set with \ref kzuPropertyManagerSetPointer().
 */
kzBool kzuObjectNodeIsPointerResourceProperty(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType);

/**
 * Attaches base object node for the property. After this when querying the reference target the query can return valid object node
 * if it is not set by kzuPropertyManagerSetPointer. 
 */ 
kzsError kzuObjectNodePointerPropertyAttach(struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType);
/** Detaches base object node from the property. After this all queries to GetObjectReferenceTarget will be invalid (null)
  * if it is not set by kzuPropertyManagerSetPointer. */
kzsError kzuObjectNodePointerPropertyDetach(const struct KzuObjectNode* objectNode, const struct KzuPropertyType* propertyType);


KZ_HEADER_END


#endif
