/**
* \file
* Private layer data.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_VIEWPORT_LAYER_BASE_H
#define KZU_VIEWPORT_LAYER_BASE_H


#include "kzu_layer_base.h"


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuComposer; 


/** Viewport layer. */
struct KzuViewportLayer
{
    struct KzuLayer layer;                        /**< Inherited from layer. */

    struct KzuComposer* composer; /**< Composer used by viewport layer, when KZ_NULL using the scene composer in rendering. */

    struct KzuScene* scene;                       /**< Scene to render in this layer. */
    struct KzuTransformedScene* transformedScene; /**< Transformed version of the scene. */
};


/** Viewport layer class. */
extern const struct KzuLayerClass KZU_VIEWPORT_LAYER_CLASS;


/** Viewport layer initialize implementation. */
kzsError kzuViewportLayerInitialize_protected(struct KzuObjectNode* objectNode);
/** Viewport layer uninitialize implementation. */
kzsError kzuViewportLayerUninitialize_protected(struct KzuObjectNode* objectNode);

/** Viewport layer hit test implementation. */
kzsError kzuViewportLayerHitTestContents_protected(const struct KzuLayer* layer, const struct KzcVector2* point,
                                                   struct KzuObjectNode** out_objectNode, struct KzcRay* out_ray,
                                                   kzFloat* out_distance);

/** Viewport layer measure implementation. */
kzsError kzuViewportLayerMeasure_protected(struct KzuLayer* layer, const struct KzcVector2* availableSize, struct KzcVector2* out_measuredSize);
/** Viewport layer extract implementation. */
kzsError kzuViewportLayerExtract_protected(const struct KzuLayer* layer);

/** Refresh viewport layer contents (if needed). */
kzsError kzuViewportLayerRefresh_protected(struct KzuViewportLayer* viewportLayer);

/**
 * Render background quad for the viewport layer.
 * Layer node must be pushed into the renderer property query before calling this function.
 */
kzsError kzuViewportLayerRenderBackgroundQuad_protected(const struct KzuLayer* layer, struct KzuRenderer* renderer,
                                                        const struct KzuRenderContextStack* renderContextStack,
                                                        kzBool enableDepth);
/**
 * Render scene inside a layer boundary.
 * Layer node must be pushed into the renderer property query before calling this function.
 */
kzsError kzuViewportLayerRenderScene_protected(const struct KzuLayer* layer, struct KzuRenderer* renderer, struct KzuRenderContextStack* renderContextStack,
                                               const struct KzuScene* scene, const struct KzuTransformedScene* transformedScene,
                                               struct KzuComposer* composer);
/** Viewport layer render implementation. */
kzsError kzuViewportLayerRender_protected(struct KzuLayer* layer, struct KzuRenderer* renderer, struct KzuRenderContextStack* renderContextStack,
                                          struct KzuMaterial** out_material);


KZ_HEADER_END


#endif
