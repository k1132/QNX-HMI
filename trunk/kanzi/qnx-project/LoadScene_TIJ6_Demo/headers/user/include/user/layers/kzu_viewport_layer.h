/**
* \file
* Viewport layer class. KzuViewportLayer renders its ::KzuScene child. Most applications have at least one KzuViewportLayer: the root layer.
*
* Viewport Layer Messages
* ----
* KzuViewportLayer does not send or receive any messages.
*
* Viewport Layer Properties
* ----
* ::KZU_PROPERTY_TYPE_VIEWPORT_LAYER_HIT_TEST_CAMERA pointer property specifies the camera used for input hit testing (picking). If the property is not set,
* the viewport uses the scene's default picking camera.
* 
* ::KZU_PROPERTY_TYPE_VIEWPORT_LAYER_CAMERA pointer property specifies the camera for viewing the KzuViewportLayer's scene. If the property is not set,
* the viewport uses the scene's camera.
*
* ::KZU_PROPERTY_TYPE_VIEWPORT_LAYER_COMPOSER resource ID property specifies the composer for drawing the scene. If the property is not set,
* the viewport uses the scene's composer.
*
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_VIEWPORT_LAYER_H
#define KZU_VIEWPORT_LAYER_H


#include <user/scene_graph/kzu_object_common.h>


KZ_HEADER_BEGIN


/* Forward declaration. */
struct KzcMemoryManager;
struct KzcRay;
struct KzcVector2;
struct KzuEngine;
struct KzuFactory;
struct KzuLayer;
struct KzuMessageDispatcher;
struct KzuObjectNode;
struct KzuUIDomain;
struct KzuPropertyManager;
struct KzuScene;
struct KzuViewportLayer;


/** Object type for viewport layers. */
extern const KzuObjectType KZU_OBJECT_TYPE_VIEWPORT_LAYER;


/** Convert layer to viewport layer. */
struct KzuViewportLayer* kzuViewportLayerFromLayer(const struct KzuLayer* layer);
/** Convert viewport layer to layer. */
struct KzuLayer* kzuViewportLayerToLayer(const struct KzuViewportLayer* viewportLayer);
/** Tell if a layer is a viewport layer. */
kzBool kzuLayerIsViewport(const struct KzuLayer* layer);
/** Tell if an object node is a viewport layer. */
kzBool kzuObjectNodeIsViewportLayer(const struct KzuObjectNode* objectNode);

/** Create a viewport layer. */
kzsError kzuViewportLayerCreate(const struct KzcMemoryManager* memoryManager, kzString name, struct KzuUIDomain* uiDomain,
                                struct KzuViewportLayer** out_viewportLayer);
/** Register viewport layer to the factory. */
kzsError kzuViewportLayerRegisterToFactory(const struct KzuFactory* factory);

/** Get camera assigned to viewport layer. If none present, return camera from scene instead. */
struct KzuCameraNode* kzuViewportLayerGetCamera(const struct KzuViewportLayer* viewportLayer);
/** Get composer assigned to viewport layer. If none present, return composer from scene instead. */
struct KzuComposer* kzuViewportLayerGetComposer(const struct KzuViewportLayer* viewportLayer);
/** Get hit test camera assigned to viewport layer. If none present, return hit test camera from scene instead. */
struct KzuCameraNode* kzuViewportLayerGetHitTestCamera(const struct KzuViewportLayer* viewportLayer);
/** Get the scene currently used by this viewport layer. May be KZ_NULL if called before initialization. */
struct KzuScene* kzuViewportLayerGetScene(const struct KzuViewportLayer* viewportLayer);
/** Get the transformed scene associated with this viewport layer. */
struct KzuTransformedScene* kzuViewportLayerGetTransformedScene(const struct KzuViewportLayer* viewportLayer);

/**
 * Set the scene for this viewport layer.
 * This function will remove references to the previous scene as part of the process.
 * Calling this function with scene parameter set to KZ_NULL will just clear all scene settings.
 */
kzsError kzuViewportLayerSetScene(struct KzuViewportLayer* viewportLayer, struct KzuScene* scene);
/** Private function to invalidate viewport layer's scene (marks as NULL), called from scene when detaching. */
void kzuViewportLayerInvalidateScene_private(struct KzuViewportLayer* viewportLayer);


KZ_HEADER_END


#endif
