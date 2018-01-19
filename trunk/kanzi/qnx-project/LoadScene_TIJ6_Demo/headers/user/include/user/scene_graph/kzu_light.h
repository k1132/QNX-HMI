/**
 * \file
 * Represents a light in a scene. Contains a constructor for a directional, point and spot light. Node inherited from KzuObjectNode.
 *
 * Light Messages
 * ----
 * KzuLightNode does not send or receive any messages. 
 *
 * Common Light Properties
 * ----
 * These properties are common for all types of lights.
 *
 * ::KZU_PROPERTY_TYPE_LIGHT_ENABLED Boolean property specifies whether the light is on or off. If the value is ::KZ_FALSE, the light does not affect rendering.
 * The default value is ::KZ_TRUE.
 *
 * Directional Light Properties
 * ----
 * These properties affect only directional lights.
 *
 * ::KZU_PROPERTY_TYPE_DIRECTIONAL_LIGHT_COLOR ::KzcColorRGBA property specifies the color of the light. The default value is {0.4980392, 0.4980392, 0.4980392, 1}.
 *
 * ::KZU_PROPERTY_TYPE_DIRECTIONAL_LIGHT_DIRECTION ::KzcVector3 property value is set based on the light's transformation matrix.
 *
 * Point Light Properties
 * ----
 * These properties affect only point lights.
 *
 * ::KZU_PROPERTY_TYPE_POINT_LIGHT_COLOR ::KzcColorRGBA property specifies the color of the light. The default value is {0.4980392, 0.4980392, 0.4980392, 1}.
 *
 * ::KZU_PROPERTY_TYPE_POINT_LIGHT_ATTENUATION ::KzcVector3 property specifies three factors that are used to lessen the effect of the light for objects that are farther away.
 * The three factors specify a constant, linear and quadratic attenuation respectively. The default value is {1, 0, 0}.
 *
 * ::KZU_PROPERTY_TYPE_POINT_LIGHT_POSITION ::KzcVector3 property value is set based on the light's transformation matrix.
 *
 * Spot Light Properties
 * ----
 * These properties affect only spot lights.
 *
 * ::KZU_PROPERTY_TYPE_SPOT_LIGHT_COLOR ::KzcColorRGBA property specifies the color of the light. The default value is {0.4980392, 0.4980392, 0.4980392, 1}.
 *
 * ::KZU_PROPERTY_TYPE_SPOT_LIGHT_ATTENUATION ::KzcVector3 property specifies three factors that are used to lessen the effect of the light for objects that are farther away.
 * The three factors specify a constant, linear and quadratic attenuation respectively. The default value is {1, 0, 0}.
 *
 * ::KZU_PROPERTY_TYPE_SPOT_LIGHT_CUTOFF_ANGLE float property specifies the angle of the light cone in degrees. The default value is 90.
 *
 * ::KZU_PROPERTY_TYPE_SPOT_LIGHT_DIRECTION ::KzcVector3 property value is set based on the light's transformation matrix.
 *
 * ::KZU_PROPERTY_TYPE_SPOT_LIGHT_EXPONENT float property specifies how fast the fully lit area of the center of the light cone turns into non-lit area.
 *
 * ::KZU_PROPERTY_TYPE_SPOT_LIGHT_POSITION ::KzcVector3 property value is set based on the light's transformation matrix.
 *
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZU_LIGHT_H
#define KZU_LIGHT_H


#include <user/scene_graph/kzu_object_common.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryFileInfo;
struct KzuObjectNode;
struct KzuUIDomain;
struct KzuStructPropertyType;
struct KzuFactory;


/**
* \struct KzuLightNode
* Structure for the light node, inherited from KzuObjectNode.
*/
struct KzuLightNode;


/* Fixed light property type names. */

extern const kzString KZU_DIRECTIONAL_LIGHT_PROPERTY;               /**< Directional light. */

extern const kzString KZU_POINT_LIGHT_PROPERTY;                     /**< Point light. */

extern const kzString KZU_SPOT_LIGHT_PROPERTY;                      /**< Spot light. */


/** Object type identifier for Light objects. */
extern const KzuObjectType KZU_OBJECT_TYPE_LIGHT;


/** Creates a new light node. The type of the light can be set with ::kzuLightNodeInitialize(). */
kzsError kzuLightNodeCreate(const struct KzcMemoryManager* memoryManager, kzString name, 
                            struct KzuUIDomain* uiDomain, struct KzuLightNode** out_lightNode);

/** Creates new directional light. */
kzsError kzuLightNodeCreateDirectional(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                       kzString name, struct KzuLightNode** out_lightNode);
/** Creates new point light. */
kzsError kzuLightNodeCreatePoint(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                 kzString name, struct KzuLightNode** out_lightNode);
/** Creates new spot light. */
kzsError kzuLightNodeCreateSpot(const struct KzcMemoryManager* memoryManager, struct KzuUIDomain* uiDomain,
                                kzString name, struct KzuLightNode** out_lightNode);

/** Registers light node type to factory. */
kzsError kzuLightNodeRegisterToFactory(const struct KzuFactory* factory);

/** Sets the light type for light node. */
kzsError kzuLightNodeInitialize(struct KzuLightNode* lightNode, struct KzuStructPropertyType* lightType);


/** Get light object node from object node. */
struct KzuLightNode* kzuLightNodeFromObjectNode(const struct KzuObjectNode* objectNode);
/** Returns an object node from light node. */
struct KzuObjectNode* kzuLightNodeToObjectNode(const struct KzuLightNode* lightNode);


/** Returns light property type from light. */
struct KzuStructPropertyType* kzuLightNodeGetLightType(const struct KzuLightNode* lightNode);


KZ_HEADER_END


#include "kzu_light_properties.h"


#endif
