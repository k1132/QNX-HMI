/**
* \file
* Property query.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_PROPERTY_QUERY_H
#define KZU_PROPERTY_QUERY_H


#include <core/util/math/kzc_vector2.h>
#include <core/util/math/kzc_vector3.h>
#include <core/util/math/kzc_vector4.h>
#include <core/util/math/kzc_matrix2x2.h>
#include <core/util/math/kzc_matrix3x3.h>
#include <core/util/math/kzc_matrix4x4.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMatrix2x2;
struct KzcMatrix3x3;
struct KzcMatrix4x4;
struct KzcVector2;
struct KzcVector3;
struct KzcVector4;
struct KzcMemoryManager;
struct KzuObjectNode;
struct KzuPropertyManager;
struct KzuPropertyType;
struct KzuResource;
struct KzuTransformedObjectNode;


/**
 * \struct KzuPropertyQuery
 * Query object for querying property values with temporary master values. When querying property values trough
 * a property query object, all properties from pushed pointers or object nodes are considered as well.
 * The last pushed item has higher priority than the earlier ones.
 */
struct KzuPropertyQuery;


/** Create a property query object. */
kzsError kzuPropertyQueryCreate(const struct KzcMemoryManager* memoryManager, struct KzuPropertyManager* propertyManager, struct KzcMemoryManager* quickMemoryManager,
                                struct KzuPropertyQuery** out_propertyQuery);

/** Delete a property query object. */
kzsError kzuPropertyQueryDelete(struct KzuPropertyQuery* propertyQuery);

/** Gets the property manager of the property query */
struct KzuPropertyManager* kzuPropertyQueryGetPropertyManager(const struct KzuPropertyQuery* propertyQuery);

/** Push an arbitrary pointer to the property query. */
kzsError kzuPropertyQueryPush(const struct KzuPropertyQuery* propertyQuery, const void* object);

/** Push an object node to the property query. */
kzsError kzuPropertyQueryPushObjectNode(const struct KzuPropertyQuery* propertyQuery, const struct KzuObjectNode* objectNode);

/** Push an transformed object node to the property query. */
kzsError kzuPropertyQueryPushTransformedObjectNode(const struct KzuPropertyQuery* propertyQuery, const struct KzuTransformedObjectNode* transformedObjectNode);

/** Pop the last pushed item from the property query. */
kzsError kzuPropertyQueryPop(const struct KzuPropertyQuery* propertyQuery);

/** Resets property query frame. */
kzsError kzuPropertyQueryResetFrame(struct KzuPropertyQuery* propertyQuery);

/** Add an arbitrary pointer to the beginning of the property query. */
kzsError kzuPropertyQueryAddFirst(const struct KzuPropertyQuery* propertyQuery, const void* object);

/** Remove an item from the beginning of the property query. */
kzsError kzuPropertyQueryRemoveFirst(const struct KzuPropertyQuery* propertyQuery);

/** Returns if property query is empty. */
kzBool kzuPropertyQueryIsEmpty(const struct KzuPropertyQuery* propertyQuery);

/**
 * Get the value of a property using the property query.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetFloat is used for getting the property value from all pushed objects.
 * 2. If the property is found from multiple objects, the one with the highest priority wins.
 *    If the highest priority is on multiple objects, the last pushed object of those wins.
 * 3. If the property is not found from any of the pushed objects, the default value from the property type is returned.
 */
kzFloat kzuPropertyQueryGetFloat(const struct KzuPropertyQuery* propertyQuery, const struct KzuPropertyType* propertyType);

/**
 * Get the value of a property using the property query.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetInt is used for getting the property value from all pushed objects.
 * 2. If the property is found from multiple objects, the one with the highest priority wins.
 *    If the highest priority is on multiple objects, the last pushed object of those wins.
 * 3. If the property is not found from any of the pushed objects, the default value from the property type is returned.
 */
kzInt kzuPropertyQueryGetInt(const struct KzuPropertyQuery* propertyQuery, const struct KzuPropertyType* propertyType);

/**
 * Get the value of a property using the property query.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetBool is used for getting the property value from all pushed objects.
 * 2. If the property is found from multiple objects, the one with the highest priority wins.
 *    If the highest priority is on multiple objects, the last pushed object of those wins.
 * 3. If the property is not found from any of the pushed objects, the default value from the property type is returned.
 */
kzBool kzuPropertyQueryGetBool(const struct KzuPropertyQuery* propertyQuery, const struct KzuPropertyType* propertyType);

/**
 * Get the value of a property using the property query.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetColor is used for getting the property value from all pushed objects.
 * 2. If the property is found from multiple objects, the one with the highest priority wins.
 *    If the highest priority is on multiple objects, the last pushed object of those wins.
 * 3. If the property is not found from any of the pushed objects, the default value from the property type is returned.
 */
struct KzcColorRGBA kzuPropertyQueryGetColor(const struct KzuPropertyQuery* propertyQuery, const struct KzuPropertyType* propertyType);

/**
 * Get the value of a property using the property query.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetVector2 is used for getting the property value from all pushed objects.
 * 2. If the property is found from multiple objects, the one with the highest priority wins.
 *    If the highest priority is on multiple objects, the last pushed object of those wins.
 * 3. If the property is not found from any of the pushed objects, the default value from the property type is returned.
 */
struct KzcVector2 kzuPropertyQueryGetVector2(const struct KzuPropertyQuery* propertyQuery, const struct KzuPropertyType* propertyType);

/**
 * Get the value of a property using the property query.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetVector3 is used for getting the property value from all pushed objects.
 * 2. If the property is found from multiple objects, the one with the highest priority wins.
 *    If the highest priority is on multiple objects, the last pushed object of those wins.
 * 3. If the property is not found from any of the pushed objects, the default value from the property type is returned.
 */
struct KzcVector3 kzuPropertyQueryGetVector3(const struct KzuPropertyQuery* propertyQuery, const struct KzuPropertyType* propertyType);

/**
 * Get the value of a property using the property query.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetVector4 is used for getting the property value from all pushed objects.
 * 2. If the property is found from multiple objects, the one with the highest priority wins.
 *    If the highest priority is on multiple objects, the last pushed object of those wins.
 * 3. If the property is not found from any of the pushed objects, the default value from the property type is returned.
 */
struct KzcVector4 kzuPropertyQueryGetVector4(const struct KzuPropertyQuery* propertyQuery, const struct KzuPropertyType* propertyType);

/**
 * Get the value of a property using the property query.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetMatrix2x2 is used for getting the property value from all pushed objects.
 * 2. If the property is found from multiple objects, the one with the highest priority wins.
 *    If the highest priority is on multiple objects, the last pushed object of those wins.
 * 3. If the property is not found from any of the pushed objects, the default value from the property type is returned.
 */
struct KzcMatrix2x2 kzuPropertyQueryGetMatrix2x2(const struct KzuPropertyQuery* propertyQuery, const struct KzuPropertyType* propertyType);

/**
 * Get the value of a property using the property query.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetMatrix3x3 is used for getting the property value from all pushed objects.
 * 2. If the property is found from multiple objects, the one with the highest priority wins.
 *    If the highest priority is on multiple objects, the last pushed object of those wins.
 * 3. If the property is not found from any of the pushed objects, the default value from the property type is returned.
 */
struct KzcMatrix3x3 kzuPropertyQueryGetMatrix3x3(const struct KzuPropertyQuery* propertyQuery, const struct KzuPropertyType* propertyType);

/**
 * Get the value of a property using the property query.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetMatrix4x4 is used for getting the property value from all pushed objects.
 * 2. If the property is found from multiple objects, the one with the highest priority wins.
 *    If the highest priority is on multiple objects, the last pushed object of those wins.
 * 3. If the property is not found from any of the pushed objects, the default value from the property type is returned.
 */
struct KzcMatrix4x4 kzuPropertyQueryGetMatrix4x4(const struct KzuPropertyQuery* propertyQuery, const struct KzuPropertyType* propertyType);

/**
 * Get the value of a property using the property query.
 * The return value is calculated based on the following steps:
 * 1. kzuPropertyManagerGetPointer is used for getting the property value from all pushed objects.
 * 2. If the property is found from multiple objects, the one with the highest priority wins.
 *    If the highest priority is on multiple objects, the last pushed object of those wins.
 * 3. If the property is not found from any of the pushed objects, the default value from the property type is returned.
 * 4. In every case when a value is found, a check is made to ensure that the value is a reference to KzuResource. If not, KZ_NULL is returned.
 */
kzsError kzuPropertyQueryGetResource(const struct KzuPropertyQuery* propertyQuery, const struct KzuPropertyType* propertyType,
                                     struct KzuResource** out_resource);


KZ_HEADER_END


#endif
